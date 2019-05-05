#ifndef _INC_LED_H_
#define _INC_LED_H_

typedef enum {
  LED_FLAG_0 = ((unsigned int)(1 << 0)),
  LED_FLAG_1 = ((unsigned int)(1 << 1)),
  LED_FLAG_3 = ((unsigned int)(1 << 2)),
  LED_FLAG_4 = ((unsigned int)(1 << 3)),
  LED_ALL_FLAGS = ((unsigned int)0x0F)
} LedFlagType_t;

void LedFlagInit(void);
void LedOn(LedFlagType_t led);
void LedOff(LedFlagType_t led);

#endif  // _INC_LED_H_
