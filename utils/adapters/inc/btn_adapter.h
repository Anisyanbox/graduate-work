#ifndef _UTILS_ADAPTERS_INC_BTN_ADAPTER_H_
#define _UTILS_ADAPTERS_INC_BTN_ADAPTER_H_

#define BTN_CNT     ((int)16)

typedef char BtnChar_t;

typedef enum {
  BTN_SB1_ID = 0,
  BTN_SB2_ID,
  BTN_SB3_ID,
  BTN_SB4_ID,
  BTN_SB5_ID,
  BTN_SB6_ID,
  BTN_SB7_ID,
  BTN_SB8_ID,
  BTN_SB9_ID,
  BTN_SB10_ID,
  BTN_SB11_ID,
  BTN_SB12_ID,
  BTN_SB13_ID,
  BTN_SB14_ID,
  BTN_SB15_ID,
  BTN_SB16_ID
} BtnId_t;

typedef enum {
  PRESS_EVNT = 0,
  RELEASE_EVNT,
  BOTH_EVNT
} EventForHandler_t;

/*
 * Low level initialization and thread creating.
 * return 0, if success.
 */
int BtnInit(void);

/*
 * For this function button must be in 'BTN_ASYNC' mode.
 * Note: Generate async event can be btn which not connected to external port
 */
void BtnSubscribeAsyncEventHandler(BtnId_t id_key_btn, 
                                   void (*async_handler)(void));

/*
 * For this functions button must be in 'BTN_SYNC' mode.
 */
void BtnSubscribeSyncEventHandler(BtnId_t id_key_btn,
                                  EventForHandler_t e,
                                  void (*handler)(BtnChar_t c));

#endif  // _UTILS_ADAPTERS_INC_BTN_ADAPTER_H_
