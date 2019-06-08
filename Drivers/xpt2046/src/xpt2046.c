#include "xpt2046.h"

#ifndef NULL
#define NULL 0
#endif

#define CTRL_REG_START_BIT           (1 << 7)
#define CTRL_REG_X_TOUCT_ADDR_BITS   (1 << 4)
#define CTRL_REG_Y_TOUCT_ADDR_BITS   ((1 << 4) | (1 << 6))

#define CTRL_REG_MODE_12BIT          (0 << 3)
#define CTRL_REG_MODE_8BIT           (1 << 3)

#define CTRL_REG_SER_REF_BIT         (1 << 2)
#define CTRL_REG_DFR_BIT             (0 << 2)

#define CTRL_REG_PD_BIT_IRQ_GENERATE ((0 << 1) | (0 << 0))
#define CTRL_REG_PD_BIT_POW_DOWN_DIS ((1 << 1) | (1 << 0))

static Xpt2046HwDependFuncs_t hw_funcs = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, false};

// -----------------------------------------------------------------------------
static void CsSet(int val) {
  if (val == 0) {
    if (hw_funcs.spi_nss != NULL) {
      hw_funcs.spi_nss(0);
    }
  } else if (val == 1) {
    if (hw_funcs.spi_nss != NULL) {
      hw_funcs.spi_nss(1);
    }
  }
}

// -----------------------------------------------------------------------------
static void GetXY(unsigned int * x, unsigned int * y) {
  unsigned char src = 0;
  unsigned char msb = 0;
  unsigned char lsb = 0;

  *x = 0;
  *y = 0;

  // read axis X
  src = CTRL_REG_START_BIT |      \
         CTRL_REG_MODE_12BIT |    \
         CTRL_REG_DFR_BIT |       \
         CTRL_REG_X_TOUCT_ADDR_BITS;
  CsSet(0);
  hw_funcs.spi_send(&src, 1);
  hw_funcs.spi_rec(&msb, 1);
  hw_funcs.spi_rec(&lsb, 1);
  CsSet(1);
  *x = ((msb << 8) | lsb) >> 4;

  // read axis Y
  src = CTRL_REG_START_BIT |      \
         CTRL_REG_MODE_12BIT |    \
         CTRL_REG_DFR_BIT |       \
         CTRL_REG_Y_TOUCT_ADDR_BITS;
  CsSet(0);
  hw_funcs.spi_send(&src, 1);
  hw_funcs.spi_rec(&msb, 1);
  hw_funcs.spi_rec(&lsb, 1);
  CsSet(1);
  *y = ((msb << 8) | lsb) >> 4;
}

// -----------------------------------------------------------------------------
int Xpt2046Init(Xpt2046HwDependFuncs_t * hw_depend_funs) {
  unsigned char src = 0;
  unsigned char dst = 0;

  if ((hw_depend_funs->spi_and_gpio_init == NULL) || \
      (hw_depend_funs->spi_rec == NULL) || \
      (hw_depend_funs->spi_send == NULL) || \
      (hw_depend_funs->get_busy_pin == NULL) || \
      (hw_depend_funs->get_penirq_pin == NULL) || \
      (hw_depend_funs->delay == NULL)) {
        return 1;
  }
  
  hw_funcs.spi_and_gpio_init = hw_depend_funs->spi_and_gpio_init;
  hw_funcs.spi_rec = hw_depend_funs->spi_rec;
  hw_funcs.spi_send = hw_depend_funs->spi_send;
  hw_funcs.get_busy_pin = hw_depend_funs->get_busy_pin;
  hw_funcs.spi_nss = hw_depend_funs->spi_nss;
  hw_funcs.get_penirq_pin = hw_depend_funs->get_penirq_pin;
  hw_funcs.is_generate_irq = hw_depend_funs->is_generate_irq;
  hw_funcs.delay = hw_depend_funs->delay;

  // init hw for xpt2046
  CsSet(1);
  hw_funcs.spi_and_gpio_init();

  // init xpt2046 controller
  src = CTRL_REG_START_BIT |   \
         CTRL_REG_MODE_12BIT | \
         CTRL_REG_DFR_BIT;
  if (hw_funcs.is_generate_irq) {
    src |= CTRL_REG_PD_BIT_IRQ_GENERATE;
  } else {
    src |= CTRL_REG_PD_BIT_POW_DOWN_DIS;
  }

  CsSet(0);
  hw_funcs.spi_send(&src, 1);
  hw_funcs.spi_rec(&dst, 1);
  hw_funcs.spi_rec(&dst, 1);
  CsSet(1);
  hw_funcs.delay(1000);
  return 0;
}

// -----------------------------------------------------------------------------
int Xpt2046IsTouched(void) {
  return hw_funcs.get_penirq_pin();
}

// -----------------------------------------------------------------------------
void Xpt2046GetXY(unsigned int * x, unsigned int * y, int num_measurements) {
  unsigned int xt = 0;
  unsigned int yt = 0;

  for (int i = 0; i < num_measurements; ++i) {
    GetXY(x,y);
    xt += *x;
    yt += *y;
  }
  *x = xt / num_measurements;
  *y = yt / num_measurements;
}

// -----------------------------------------------------------------------------
void Xpt2046Calibrate(LcdDrawPoint lcd_draw) {
  return;
}
