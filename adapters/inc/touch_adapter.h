#ifndef _ADAPTERS_INC_TOUCH_ADAPTER_H_
#define _ADAPTERS_INC_TOUCH_ADAPTER_H_

typedef struct {
  unsigned int x;
  unsigned int y;
} TouchPoint_t;

typedef void (*TouchAreaHandler_t)(void);

typedef struct {
  TouchPoint_t  p1;
  TouchPoint_t  p2;
} TouchArea_t;

int TouchPanelInit(void);

// Functions for subscribing your event 
// when touch press have been detected
// value x must has range only from 1 to LcdGetWigthInPixels()
// value y must has range only from 1 to LcdGetHeigthInPixels()
void TouchSubsribeArea(TouchArea_t * touch_area, TouchAreaHandler_t h);
void TouchUnsubsribeArea(TouchArea_t * touch_area);

#endif  // _ADAPTERS_INC_TOUCH_ADAPTER_H_
