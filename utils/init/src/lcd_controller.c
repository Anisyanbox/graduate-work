#include <stdint.h>
#include <stdio.h>
#include "lcd_controller.h"
#include "hal_1967VN034R1.h"

#define LCD_XSIZE         ((uint16_t)480)
#define LCD_YSIZE         ((uint16_t)272)
#define LCD_BUF_SIZE      ((int)((LCD_XSIZE) * (LCD_YSIZE)))
#define LCD_DMA_CHAN_NUM  ((uint32_t)4)

static long long int lcd_transfers = 0;

// -----------------------------------------------------------------------------
__attribute__((section(".sdr_data")))
static uint32_t lcd_buf[LCD_XSIZE * LCD_YSIZE];

// -----------------------------------------------------------------------------
static void LcdDmaDoneTransfIrqHandler(void) {
  ++lcd_transfers;
}

// -----------------------------------------------------------------------------
void LcdControllerInit(void) {
  LCD_Conf_type lcd_hx8257_conf = {
    HAL_LCD_RGB565,   // color mode
    8000,             // freq for pixel sync
    10,               // freq PWM = Fcore / (2 * HAL_LCD_MAX_PWM_DUTY * 2^pwm_div)
    0,                // active level VSYNC (0 - low 1 - high)
    0,                // active level HSYNC (0 - low 1 - high)
    1,                // active level for ready line
    0,                // inversion for pixel clock
    1,                // stop pixel clock when no new data
    0,                // RGB -> BGR

    // >> value in period of pixel clock
    1,                // shift HSYNC
    10,               // duration HSYNC
    LCD_XSIZE,        // visible horizontal pixels
    41,               // empty pixels count in the left
    7,                // empty pixels count in the right
    
    // >> value in lines
    1,                // shift VSYNC
    10,               // duration VSYNC
    LCD_YSIZE,        // visible vertical pixels
    11,               // empty pixels count in the up
    2,                // empty pixels count in the down
    0,                // set to
  };

  // fill in video-buffer with orange color
  for(int i = 0; i < LCD_BUF_SIZE / 2; i++) {
    lcd_buf[i] = 0xF4A3F4A3;
  }

  HAL_LCD_Disable();
  HAL_LCD_GpioInit();

  // DMA will continously send data from video-buf to  LCD input buf.
  // Input buf is connected to 128-bit aligned bus and contain five 128-bit words.
  // Then data go to converter and then to output buffer with RGB out.
  // Video buf has 'uint32_t' type because input lcd buffer is aligned to 32 bit.
  // And bits CD in CTRL reg contain info about bit vount in input 32 bit word for conversion to RGB.
  HAL_LCD_StartDma(LCD_DMA_CHAN_NUM,
                   (void*)lcd_buf,
                   lcd_hx8257_conf.usHSize,
                   lcd_hx8257_conf.usVSize,
                   lcd_hx8257_conf.ulRgbMode,
                   LcdDmaDoneTransfIrqHandler);
  HAL_LCD_Setup(&lcd_hx8257_conf);
  HAL_LCD_Enable();
  HAL_LCD_PwmSetDuty(10);
}
