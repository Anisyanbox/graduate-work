#include "apptime.h"

static unsigned long long app_time_ms = 0;

// -----------------------------------------------------------------------------
inline void AppTimeMsInc(void) {
  ++app_time_ms;
}

// -----------------------------------------------------------------------------
inline unsigned long long AppTimeGetInMs(void) {
  return app_time_ms;
}