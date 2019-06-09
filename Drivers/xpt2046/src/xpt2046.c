#include "xpt2046.h"

#ifndef NULL
#define NULL 0
#endif

#define MEASUREMENTS_CNT             5

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
int Xpt2046Init(Xpt2046HwDependFuncs_t * hw_depend_funs) {
  if ((hw_depend_funs->spi_and_gpio_init == NULL) || \
      (hw_depend_funs->send_receive == NULL) || \
      (hw_depend_funs->get_busy_pin == NULL) || \
      (hw_depend_funs->get_penirq_pin == NULL)) {
        return 1;
  }
  
  hw_funcs.select = hw_depend_funs->select;
  hw_funcs.unselect = hw_depend_funs->unselect;
  hw_funcs.spi_and_gpio_init = hw_depend_funs->spi_and_gpio_init;
  hw_funcs.send_receive = hw_depend_funs->send_receive;
  hw_funcs.get_busy_pin = hw_depend_funs->get_busy_pin;
  hw_funcs.get_penirq_pin = hw_depend_funs->get_penirq_pin;
  hw_funcs.is_generate_irq = hw_depend_funs->is_generate_irq;

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
void Xpt2046GetXY(unsigned int * x, unsigned int * y) {
  unsigned int xt = 0;
  unsigned int yt = 0;

  for (int i = 0; i < MEASUREMENTS_CNT; ++i) {
    GetPanelXY(x,y);
    xt += *x;
    yt += *y;
  }
  *x = xt / MEASUREMENTS_CNT;
  *y = yt / MEASUREMENTS_CNT;
}

// -----------------------------------------------------------------------------
void Xpt2046Calibrate(LcdDrawPoint lcd_draw) {
  return;
}
