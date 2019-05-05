#include <stdbool.h>
#include <stdint.h>
#include "clock.h"
#include "main.h"
#include "led_flag.h"
#include "reset_reason.h"
#include "interrupt.h"
#include "sysreg.h"
#include "rtc.h"

int main(void) {
  RstRsnSave();
  ClockInit();
  IntInit();
  RtcInit();
  LedFlagInit();
}
