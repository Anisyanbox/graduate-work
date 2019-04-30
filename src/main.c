#include "stdbool.h"
#include "stdint.h"
#include "clock.h"
#include "main.h"
#include "led.h"
#include "reset_reason.h"
#include "sysreg.h"

int main(void) {

	RstRsnDetect();
	ClockInit();
	LedInit();

	while(true);
}
