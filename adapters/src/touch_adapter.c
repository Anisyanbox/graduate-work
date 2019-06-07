#include "touch_adapter.h"
#include "xpt2046.h"
#include "hal_1967VN034R1.h"

#ifndef NULL
#define NULL 0
#endif

// -----------------------------------------------------------------------------
static void SpiInit(void) {
  return;
}

// -----------------------------------------------------------------------------
static void SpiSendNBytes(unsigned char * src, size_t n) {
  return;
}

// -----------------------------------------------------------------------------
static void SpiRecNBytes(unsigned char* dst, size_t n) {
  return;
}

// -----------------------------------------------------------------------------
static int GetBusyPinState(void) {
  return 0;
}

// -----------------------------------------------------------------------------
void TouchPanelInit(void) {
  Xpt2046HwDependFuncs_t xpt2046_hw_funcs;

  xpt2046_hw_funcs.spi_init = SpiInit;
  xpt2046_hw_funcs.spi_nss = NULL;
  xpt2046_hw_funcs.spi_send = SpiSendNBytes;
  xpt2046_hw_funcs.spi_rec = SpiRecNBytes;
  xpt2046_hw_funcs.get_busy_pin = GetBusyPinState;
  Xpt2046Init(&xpt2046_hw_funcs);
}
