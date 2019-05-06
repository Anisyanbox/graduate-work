#include "rtc.h"
#include "hal_1967VN034R1.h"
#include "clock.h"
#include "apptime.h"

// -----------------------------------------------------------------------------
#pragma interrupt
static void RtcIrqHandler(void) {
  AppTimeMsInc();
}

// -----------------------------------------------------------------------------
void RtcInit(void) {
  /* make tic every millisecond */
  HAL_RTC_InitTicPeriod((int)ClockGetInputXtiKhz());
  HAL_RTC_InitSecPeriod(1000);
  HAL_Interrupt_SubscribeHandler(intTIC, RtcIrqHandler);
  HAL_Interrupt_Enable(intTIC);
}
