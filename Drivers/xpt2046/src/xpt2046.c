#include "xpt2046.h"
#include <string.h>

#ifndef NULL
#define NULL 0
#endif

#define X_TOUCH_OFFSET_FOR_SQUARE    24
#define Y_TOUCH_OFFSET_FOR_SQUARE    24
#define SQUARE_SIZE_IN_PIXEL         12

#define MEASUREMENTS_CNT             15

#define XTP2046_ADC_RES              4095
#define CTRL_REG_START_BIT           (1 << 7)
#define CTRL_REG_X_TOUCT_ADDR_BITS   ((1 << 4) | (0 << 5) | (0 << 6))
#define CTRL_REG_Y_TOUCT_ADDR_BITS   ((1 << 4) | (0 << 5) | (1 << 6))
#define CTRL_REG_MODE_12BIT          (0 << 3)
#define CTRL_REG_MODE_8BIT           (1 << 3)
#define CTRL_REG_SER_REF_BIT         (1 << 2)
#define CTRL_REG_DFR_BIT             (0 << 2)
#define CTRL_REG_PD_BIT_IRQ_GENERATE ((0 << 1) | (0 << 0))
#define CTRL_REG_PD_BIT_POW_DOWN_DIS ((1 << 1) | (1 << 0))

static Xpt2046HwDependFuncs_t hw_funcs = { 0 };
static Xpt2046LcdInfo_t lcd_params = { 0 };
static float koeff_x = 0.0;
static float koeff_y = 0.0;

// -----------------------------------------------------------------------------
static void SelectPanelCtrl(void) {
  if (hw_funcs.select != NULL) {
    hw_funcs.select();
  }
}

// -----------------------------------------------------------------------------
static void UnselectPanelCtrl(void) {
  if (hw_funcs.unselect != NULL) {
    hw_funcs.unselect();
  }
}

// -----------------------------------------------------------------------------
static void DrawSquareInLeftLowCorner(LcdDrawPoint_t lcd_draw,
                                     Xpt2046LcdInfo_t * lcd_info) {
  unsigned int x_start = X_TOUCH_OFFSET_FOR_SQUARE - SQUARE_SIZE_IN_PIXEL / 2;
  unsigned int y_start = lcd_info->y_lcd_size - \
                         Y_TOUCH_OFFSET_FOR_SQUARE - SQUARE_SIZE_IN_PIXEL / 2;

  for (unsigned int j = 0; j < SQUARE_SIZE_IN_PIXEL; ++j) {
    for (unsigned int i = 0; i < SQUARE_SIZE_IN_PIXEL; ++i) {
      lcd_draw(x_start + i, y_start);
    }
    ++y_start;
  }
}

// -----------------------------------------------------------------------------
static void DrawSquareInRightHighCorner(LcdDrawPoint_t lcd_draw,
                                       Xpt2046LcdInfo_t * lcd_info) {
  unsigned int y_start = Y_TOUCH_OFFSET_FOR_SQUARE - SQUARE_SIZE_IN_PIXEL / 2;
  unsigned int x_start = lcd_info->x_lcd_size - \
                         X_TOUCH_OFFSET_FOR_SQUARE - SQUARE_SIZE_IN_PIXEL / 2;

  for (unsigned int j = 0; j < SQUARE_SIZE_IN_PIXEL; ++j) {
    for (unsigned int i = 0; i < SQUARE_SIZE_IN_PIXEL; ++i) {
      lcd_draw(x_start + i, y_start);
    }
    ++y_start;
  }                                      
}

// -----------------------------------------------------------------------------
static void GetPanelXY(unsigned int * x, unsigned int * y) {
  unsigned char src = 0;
  unsigned char rx[2] = { 0 };

  // read axis X
  src = CTRL_REG_START_BIT |   \
        CTRL_REG_MODE_12BIT |  \
        CTRL_REG_DFR_BIT |     \
        CTRL_REG_X_TOUCT_ADDR_BITS;
  if (hw_funcs.is_generate_irq) {
    src |= CTRL_REG_PD_BIT_IRQ_GENERATE;
  } else {
    src |= CTRL_REG_PD_BIT_POW_DOWN_DIS;
  }

  SelectPanelCtrl();
  hw_funcs.send_receive(src, rx);
  UnselectPanelCtrl();
  *x = (unsigned int)((((unsigned int)rx[0] << 8) | ((unsigned int)rx[1])) >> 3);
  
  // read axis Y
  src = CTRL_REG_START_BIT |   \
        CTRL_REG_MODE_12BIT |  \
        CTRL_REG_DFR_BIT |     \
        CTRL_REG_Y_TOUCT_ADDR_BITS;
  if (hw_funcs.is_generate_irq) {
    src |= CTRL_REG_PD_BIT_IRQ_GENERATE;
  } else {
    src |= CTRL_REG_PD_BIT_POW_DOWN_DIS;
  }

  SelectPanelCtrl();
  hw_funcs.send_receive(src, rx);
  UnselectPanelCtrl();
  *y = (unsigned int)((((unsigned int)rx[0] << 8) | ((unsigned int)rx[1])) >> 3);
}

// -----------------------------------------------------------------------------
static void CalibrateWaitTouched(unsigned int * x, unsigned int * y) {
  int is_touch_happend = 0;
  int measurement_num = 0;
  unsigned int xt = 0;
  unsigned int yt = 0;

  while (1) {
    if (hw_funcs.get_penirq_pin()) {
      GetPanelXY(x, y);
      xt += *x;
      yt += *y;
      ++measurement_num;
      is_touch_happend = 1;
      hw_funcs.delay(10);
    } else {
      if (is_touch_happend) {
        break;
      }
    }
  }
  *x = xt / measurement_num;
  *y = yt / measurement_num; 
}

// -----------------------------------------------------------------------------
int Xpt2046Init(Xpt2046HwDependFuncs_t * hw_depend_funs) {
  if ((hw_depend_funs->spi_and_gpio_init == NULL) || \
      (hw_depend_funs->send_receive == NULL) || \
      (hw_depend_funs->get_penirq_pin == NULL)) {
        return 1;
  }  
  memcpy((void*)&hw_funcs, (const void*)hw_depend_funs, sizeof(hw_funcs));

  // init xpt2046
  unsigned char bytes[2] = { 0 };

  hw_funcs.spi_and_gpio_init();
  hw_funcs.send_receive(0x80, bytes);
  return 0;
}

// -----------------------------------------------------------------------------
int Xpt2046IsTouched(void) {
  return hw_funcs.get_penirq_pin();
}

// -----------------------------------------------------------------------------
void Xpt2046Calibrate(LcdDrawPoint_t lcd_draw, Xpt2046LcdInfo_t * lcd_info) {
  unsigned int xp_left_low = 0;
  unsigned int yp_left_low = 0;
  unsigned int xp_right_high= 0;
  unsigned int yp_right_high = 0;
  unsigned int adc_dd_x = 0;
  unsigned int adc_dd_y = 0;

  memcpy((void*)&lcd_params, (const void*)lcd_info, sizeof(lcd_params));
  if (lcd_params.is_xy_lcd_and_xy_touch_swap) {
    unsigned int temp = lcd_params.x_lcd_size;
    lcd_params.x_lcd_size = lcd_params.y_lcd_size;
    lcd_params.y_lcd_size = temp;
  }

  // DrawSquareInLeftLowCorner(lcd_draw, lcd_info);
  // CalibrateWaitTouched(&xp_left_low, &yp_left_low);
  // DrawSquareInRightHighCorner(lcd_draw, lcd_info);
  // CalibrateWaitTouched(&xp_right_high, &yp_right_high);

  // // actual dynamic range for ADC
  // adc_dd_x = xp_right_high - xp_left_low;
  // adc_dd_y = yp_right_high - yp_left_low;

  koeff_x = (float)((float)lcd_params.x_lcd_size / XTP2046_ADC_RES);
  koeff_y = (float)((float)lcd_params.y_lcd_size / XTP2046_ADC_RES);
}

// -----------------------------------------------------------------------------
void Xpt2046GetXY(unsigned int * x, unsigned int * y) {
  unsigned int xt = 0;
  unsigned int yt = 0;
  unsigned int temp1 = 0;
  unsigned int temp2 = 0;

  for (int i = 0; i < MEASUREMENTS_CNT; ++i) {
    GetPanelXY(x,y);
    xt += *x;
    yt += *y;
  }

  if (lcd_params.is_xy_lcd_and_xy_touch_swap) {
    *x = (unsigned int)((float)((float)yt / MEASUREMENTS_CNT) * koeff_y);
    *y = (unsigned int)((float)((float)xt / MEASUREMENTS_CNT) * koeff_x);
  } else {
    *x = (unsigned int)((float)((float)xt / MEASUREMENTS_CNT) * koeff_x);
    *y = (unsigned int)((float)((float)yt / MEASUREMENTS_CNT) * koeff_y);
  }

  if (lcd_params.is_x_lcd_and_x_touch_diff_direction) {
    *x = lcd_params.y_lcd_size - *x;
  }
  if (lcd_params.is_y_lcd_and_y_touch_diff_direction) {
    temp1 = *y;
    *y = lcd_params.x_lcd_size - *y;
  }
}
