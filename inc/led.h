#ifndef _INC_LED_H_
#define _INC_LED_H_

typedef enum {
  LED_FLAG_0 = (1 << 0),
  LED_FLAG_1 = (1 << 1),
  LED_FLAG_3 = (1 << 2),
  LED_FLAG_4 = (1 << 3)
} LedFlagType_t;

void LedInit(void);
void LedOn(LedFlagType_t led);
void LedOff(LedFlagType_t led);

#endif  // _INC_LED_H_
