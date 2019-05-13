#ifndef _INC_LED_H_
#define _INC_LED_H_

typedef enum {
  LED_INIT = 0,
  LED_INIT_FALSE
} LedInitStat_t;

LedInitStat_t LedFlagInit(void);

#endif  // _INC_LED_H_
