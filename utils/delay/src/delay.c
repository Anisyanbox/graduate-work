#include "delay.h"
#include "apptime.h"

// -----------------------------------------------------------------------------
void DelayMs(uint32_t d) {
  unsigned long long app_time = (unsigned long long)d + AppTimeGetInMs();
  while (AppTimeGetInMs() != app_time);  
}
