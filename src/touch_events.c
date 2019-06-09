#include "touch_events.h"
#include "touch_adapter.h"

// -----------------------------------------------------------------------------
TouchInitStat_t TouchInit(void) {
  // init touch hw and thread creation
  if (TouchPanelInit() != 0) {
    return TOUCH_INIT_FALSE;
  }
  return TOUCH_INIT;
}
