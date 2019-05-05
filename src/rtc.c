#include "rtc.h"
#include "hal_1967VN034R1.h"
#include "clock.h"

static unsigned long long app_time_ms = 0;

// -----------------------------------------------------------------------------
#pragma interrupt
void RtcIntHandler(void) {
  ++app_time_ms;
}

// -----------------------------------------------------------------------------
unsigned long long RtcGetAppTimeInMs(void) {
  return app_time_ms;
}

// -----------------------------------------------------------------------------
void RtcInit(void) {
  /* make tic every millisecond */
  HAL_RTC_InitTicPeriod((int)ClockGetInputXtiKhz());
  HAL_RTC_InitSecPeriod(1000);
  HAL_Interrupt_SubscribeHandler(intTIC, RtcIntHandler);
  HAL_Interrupt_Enable(intTIC);
}
