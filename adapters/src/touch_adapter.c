#include <sysreg.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "touch_adapter.h"
#include "xpt2046.h"
#include "hal_1967VN034R1.h"
#include "btn_adapter.h"
#include "video_buffer.h"
#include "pthread.h"
#include "main.h"
#include "delay.h"
#include "stupid_delay.h"

#ifndef NULL
#define NULL 0
#endif

#define SLEEP_TOUCH_MS      50
#define THREAD_PRIORITY     MAIN_THREAD_NORMAL_PRIO

#define SPI_CLOCK_PIN       GPIO_PIN_4
#define SPI_MOSI_PIN        GPIO_PIN_5
#define SPI_MISO_PIN        GPIO_PIN_6
#define SPI_CS_PORT         LX_GPIO_PA
#define SPI_CS_PIN          GPIO_PIN_9
#define XPT2046_BUSY_PORT   LX_GPIO_PB
#define XPT2046_BUSY_PIN    GPIO_PIN_23
#define XPT2046_penIRQ_PORT LX_GPIO_PB
#define XPT2046_penIRQ_PIN  GPIO_PIN_22

// -----------------------------------------------------------------------------
static void SpiAndGpioInit(void) {
  SPI_TypeDefInit spi_init_struct;

  // init GPIO for SPI controller
  HAL_GPIO_Init(LX_GPIO_PA, 
                SPI_CLOCK_PIN | SPI_MOSI_PIN | SPI_MISO_PIN | SPI_CS_PIN,
                GPIO_PinMode_Alt);

  // init penIRQ pin
  HAL_GPIO_Init(XPT2046_penIRQ_PORT, XPT2046_penIRQ_PIN, GPIO_PinMode_In);

  // init SPI
  spi_init_struct.CLK_Phase      = SPI_CLK_Phase_Posedge;
  spi_init_struct.CLK_Polarity   = SPI_CLK_Polarity_High;
  spi_init_struct.CLK_Prescaler  = 299; // CoreClock/2 = SOC_CLOCK; (SOC_CLOCK / (299 + 1)) = SPI_CLOCK (0.5 MHz)
  spi_init_struct.CSNum          = 2;
  spi_init_struct.CS_Active      = SPI_CS_Active_Low;
  spi_init_struct.FirstBit       = SPI_FirstBit_MSB;
  spi_init_struct.Mode           = SPI_Mode_Master;
  spi_init_struct.CS_Hold        = SPI_CS_Unhold;
  spi_init_struct.WordSize       = 8;
  spi_init_struct.LoopBack       = SPI_LoopBack_Off;
  HAL_SPI_Init(&spi_init_struct);
}

// -----------------------------------------------------------------------------
static void SpiSendReceive(unsigned char send_byte, unsigned char * two_bytes_rx_arr) {
  uint16_t tx_data[3] = { 0 };
  uint16_t rx_data[3] = { 0 };
  
  tx_data[0] = (uint16_t)send_byte;
  HAL_SPI_SendAndReceive(tx_data, rx_data, 2);

  *(two_bytes_rx_arr + 0) = (unsigned char)(rx_data[1]);
  *(two_bytes_rx_arr + 1) = (unsigned char)(rx_data[0]);
}

// -----------------------------------------------------------------------------
static int GetPenIrqPinState(void) {
  return !HAL_GPIO_ReadPin(XPT2046_penIRQ_PORT, XPT2046_penIRQ_PIN);
}

// -----------------------------------------------------------------------------
static void * TouchThread(void * args) {
  static char buffer[40] = {0};
  unsigned int x = 0;
  unsigned int y = 0;

  while(true) {
    if (Xpt2046IsTouched()) {
      Xpt2046GetXY(&x, &y);
      sprintf(buffer, "--> X = %d Y = %d", x, y);
      HAL_UART_Send(UART_DEBUG_PORT, buffer, strlen((const char*)buffer));
    }
    DelayMs(SLEEP_TOUCH_MS);
  }
}

// -----------------------------------------------------------------------------
int TouchPanelInit(void) {
  static pthread_t touch_thread_handl;
  pthread_attr_t touch_attr;
  sched_param_t touch_thread_prio;
  Xpt2046HwDependFuncs_t xpt2046_hw_funcs;

  // init hw
  xpt2046_hw_funcs.select = NULL;
  xpt2046_hw_funcs.unselect = NULL;
  xpt2046_hw_funcs.spi_and_gpio_init = SpiAndGpioInit;
  xpt2046_hw_funcs.send_receive = SpiSendReceive;
  xpt2046_hw_funcs.get_penirq_pin = GetPenIrqPinState;
  xpt2046_hw_funcs.delay = StupidDelayMs;
  xpt2046_hw_funcs.is_generate_irq = 1;
  if (Xpt2046Init(&xpt2046_hw_funcs)!= 0) {
    return 1;
  }
  
  // create thread for measurement and events calling
  if (pthread_attr_init(&touch_attr) != 0) {
    return 1;
  }
  touch_thread_prio.sched_priority = THREAD_PRIORITY;
  if (pthread_attr_setschedparam(&touch_attr,
                                (const sched_param_t*)&touch_thread_prio) != 0) {
    return 1;
  }
  if (pthread_create(&touch_thread_handl, 
                    (const pthread_attr_t*)touch_attr, 
                    TouchThread, 
                    NULL) != 0) {
    return 1;
  }
  if (pthread_attr_destroy(&touch_attr) != 0) {
    return 1;
  }
  return 0;
}
