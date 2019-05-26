#ifndef _INC_KEYBOARD_H_
#define _INC_KEYBOARD_H_

typedef enum {
  KEYBOARD_INIT = 0,
  KEYBOARD_INIT_FALSE
} KeyboardInitStat_t;

KeyboardInitStat_t KeyboardInit(void);

#endif  // _INC_KEYBOARD_H_
