#ifndef _INC_TOUCH_EVENTS_H_
#define _INC_TOUCH_EVENTS_H_

typedef enum {
  TOUCH_INIT = 0,
  TOUCH_INIT_FALSE
} TouchInitStat_t;

TouchInitStat_t TouchInit(void);

#endif  // _INC_TOUCH_EVENTS_H_
