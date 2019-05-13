#include "delay.h"
#include "apptime.h"

// -----------------------------------------------------------------------------
void DelayMs(unsigned int d) {
  unsigned long long app_time = (unsigned long long)d + AppTimeGetInMs();
  while (AppTimeGetInMs() <= app_time);
}
