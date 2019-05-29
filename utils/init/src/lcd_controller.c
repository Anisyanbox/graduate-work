#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "lcd_controller.h"
#include "hal_1967VN034R1.h"
#include "sdram_adapter.h"

#define LCD_XSIZE         ((uint16_t)480)
#define LCD_YSIZE         ((uint16_t)272)
#define LCD_BUF_SIZE      ((int)(((LCD_XSIZE) * (LCD_YSIZE)) / 2))
#define LCD_DMA_CHAN_NUM  ((uint32_t)4)

static long long int lcd_transfers = 0;
static uint32_t * lcd_buf = NULL;

// -----------------------------------------------------------------------------
#pragma interrupt
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

  // fill in video-buffer
  lcd_buf = SramGetStartBank0Addr();
  for(int i = 0; i < LCD_BUF_SIZE / 4; i++) {
    *(lcd_buf +i) = 0;
  }

  for(int i = LCD_BUF_SIZE / 4;  i < LCD_BUF_SIZE / 2; i++) {
    *(lcd_buf +i) = 0xAAAAAAAA;
  }

  for(int i = LCD_BUF_SIZE / 2;  i < 3*LCD_BUF_SIZE / 4; i++) {
    *(lcd_buf +i) = 0xffffffff;
  }

  for(int i = 3*LCD_BUF_SIZE / 4;  i < LCD_BUF_SIZE; i++) {
    *(lcd_buf +i) = 0xFB0CFB0C;
  }

  HAL_LCD_Disable();
  HAL_LCD_GpioInit();
  HAL_LCD_Setup(&lcd_hx8257_conf);

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
                   NULL);
  HAL_LCD_Enable();
  HAL_LCD_PwmSetDuty(100);
}

// -----------------------------------------------------------------------------
uint32_t * LcdControllerGetVideoBufAddr(void) {
  return lcd_buf;
}

// -----------------------------------------------------------------------------
int LcdControllerGetVideoBufSuze(void) {
  return LCD_BUF_SIZE;
}

// -----------------------------------------------------------------------------
int LcdControllerGetVideoBufWigth(void) {
  return (int)LCD_XSIZE;
}

// -----------------------------------------------------------------------------
int LcdControllerGetVideoBufHeigth(void) {
  return (int)LCD_YSIZE;
}
 