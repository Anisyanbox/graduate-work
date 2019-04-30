#include "stdbool.h"
#include "stdint.h"
#include "led.h"
#include "hal_1967VN034R1.h"
#include "stupid_delay.h"
#include "pthread.h"
#include "sysreg.h"

#define LED_DELAY_BLINK ((int)500000)

static void * Led1Thread(void * args) {
	(void)args;

	while (true) {
		__builtin_sysreg_write(__FLAGREGST, 0x01); // on FLAG0
		StupidDelay(LED_DELAY_BLINK);
		__builtin_sysreg_write(__FLAGREGCL, 0x00); // off FLAG0
	}
}

static void * Led2Thread(void * args) {
	(void)args;

	while (true) {
		__builtin_sysreg_write(__FLAGREGST, 0x02); // on FLAG1
		StupidDelay(LED_DELAY_BLINK);
		__builtin_sysreg_write(__FLAGREGCL, 0x00); // off FLAG1
	}
}

void LedInit(void) {
    static pthread_t led1_handl;
	static pthread_t led2_handl;
    
    HAL_SYS_FlagEnable();
    pthread_create(&led1_handl, NULL, Led1Thread, NULL);
	pthread_create(&led2_handl, NULL, Led2Thread, NULL);
}
