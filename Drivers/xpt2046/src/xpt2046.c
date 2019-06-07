#include "xpt2046.h"

#ifndef NULL
#define NULL 0
#endif

static Xpt2046HwDependFuncs_t hw_funcs = {NULL, NULL, NULL, NULL, NULL};

// -----------------------------------------------------------------------------
int Xpt2046Init(Xpt2046HwDependFuncs_t * hw_depend_funs) {
  if ((hw_depend_funs->spi_init == NULL) || \
      (hw_depend_funs->spi_rec == NULL) || \
      (hw_depend_funs->spi_send == NULL) || \
      (hw_depend_funs->get_busy_pin == NULL)) {
        return 1;
  }
  
  hw_funcs.spi_init = hw_depend_funs->spi_init;
  hw_funcs.spi_rec = hw_depend_funs->spi_rec;
  hw_funcs.spi_send = hw_depend_funs->spi_send;
  hw_funcs.get_busy_pin = hw_depend_funs->get_busy_pin;
  hw_funcs.spi_nss = hw_depend_funs->spi_nss;

  // init hw for xpt2046
  hw_funcs.spi_init();

  return 0;
}
