#include <sysreg.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "touch_adapter.h"
#include "xpt2046.h"
#include "hal_1967VN034R1.h"
#include "btn_adapter.h"
#include "video_buffer.h"
#include "pthread.h"
#include "main.h"
#include "stupid_delay.h"

#ifndef NULL
#define NULL 0
#endif

#define THREAD_PRIORITY     MAIN_THREAD_NORMAL_PRIO

#define SPI_CLOCK_PIN       GPIO_PIN_4
#define SPI_MOSI_PIN        GPIO_PIN_5
#define SPI_MISO_PIN        GPIO_PIN_6
#define SPI_CS_PIN          GPIO_PIN_9
#define XPT2046_BUSY_PORT   LX_GPIO_PB
#define XPT2046_BUSY_PIN    GPIO_PIN_23
#define XPT2046_penIRQ_PORT LX_GPIO_PB
#define XPT2046_penIRQ_PIN  GPIO_PIN_22

static volatile bool int_is_happend = false;

// -----------------------------------------------------------------------------
static void SpiAndGpioInit(void) {
  SPI_TypeDefInit spi_init_struct;

  // init GPIO for SPI controller
  HAL_GPIO_Init(LX_GPIO_PA, 
                SPI_CLOCK_PIN | SPI_MOSI_PIN | SPI_MISO_PIN | SPI_CS_PIN, 
                GPIO_PinMode_Alt);

  // init GPIO for busy pin
  HAL_GPIO_Init(XPT2046_BUSY_PORT, XPT2046_BUSY_PIN, GPIO_PinMode_OutPU);

  // init penIRQ pin
  HAL_GPIO_Init(XPT2046_penIRQ_PORT, XPT2046_penIRQ_PIN, GPIO_PinMode_In);

  // init SPI
  spi_init_struct.CLK_Phase      = SPI_CLK_Phase_Posedge;
  spi_init_struct.CLK_Polarity   = SPI_CLK_Polarity_High;
  spi_init_struct.CLK_Prescaler  = 149; // CoreClock/2 = SOC_CLOCK; (SOC_CLOCK / (149 + 1)) = SPI_CLOCK (1 MHz)
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
static void SpiSendNBytes(unsigned char * src, size_t n) {
  HAL_SPI_SendOnly((u16*)src, (const unsigned int)n);
  while (HAL_SPI_GetFlag(SPI_Flag_Busy));
}

// -----------------------------------------------------------------------------
static void SpiRecNBytes(unsigned char* dst, size_t n) {
  HAL_SPI_ReceiveOnly((u16*)dst, (unsigned int)n, 0);
  return;
}

// -----------------------------------------------------------------------------
static int GetBusyPinState(void) {
  return HAL_GPIO_ReadPin(XPT2046_BUSY_PORT, XPT2046_BUSY_PIN);
}

// -----------------------------------------------------------------------------
static int GetPenIrqPinState(void) {
  return !HAL_GPIO_ReadPin(XPT2046_penIRQ_PORT, XPT2046_penIRQ_PIN);
}

// -----------------------------------------------------------------------------
static void DrawPoint(unsigned int x, unsigned int y) {
  return;
}

// -----------------------------------------------------------------------------
static void * TouchThread(void * args) {
  static char buffer[50] = {0};
  unsigned int x = 0;
  unsigned int y = 0;

  Xpt2046Calibrate(DrawPoint);
  while(true) {
    DelayMs(4);
    if (Xpt2046IsTouched()) {
      Xpt2046GetXY(&x, &y, 5);
      sprintf(buffer, " >> x = %d y = %d << \n", x, y);
      HAL_UART_Send(UART_DEBUG_PORT, buffer, strlen((const char*)buffer));
    }
  }
}

// -----------------------------------------------------------------------------
int TouchPanelInit(void) {
  static pthread_t touch_thread_handl;
  pthread_attr_t touch_attr;
  sched_param_t touch_thread_prio;
  Xpt2046HwDependFuncs_t xpt2046_hw_funcs;

  // init hw
  xpt2046_hw_funcs.spi_and_gpio_init = SpiAndGpioInit;
  xpt2046_hw_funcs.spi_nss = NULL;
  xpt2046_hw_funcs.spi_send = SpiSendNBytes;
  xpt2046_hw_funcs.spi_rec = SpiRecNBytes;
  xpt2046_hw_funcs.get_busy_pin = GetBusyPinState;
  xpt2046_hw_funcs.get_penirq_pin = GetPenIrqPinState;
  xpt2046_hw_funcs.is_generate_irq = false;
  xpt2046_hw_funcs.delay = StupidDelayMs;
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
