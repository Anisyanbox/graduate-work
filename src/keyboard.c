#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "keyboard.h"
#include "btn_adapter.h"
#include "hal_1967VN034R1.h"

// -----------------------------------------------------------------------------
static void EventHandler(BtnChar_t c) {
  char buffer[10] = {0};

  sprintf(buffer, "--> %c", c);
  HAL_UART_Send(LX_UART1, buffer, strlen((const char*)buffer));
  return;
}

// -----------------------------------------------------------------------------
KeyboardInitStat_t KeyboardInit(void) {
  /* low level initialization and thread create */
  if (BtnInit() != 0) {
    return KEYBOARD_INIT_FALSE;
  }

  /* Subscribe handlers for event */
  BtnSubscribeSyncEventHandler(BTN_SB1_ID, PRESS_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB2_ID, PRESS_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB3_ID, PRESS_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB4_ID, PRESS_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB5_ID, PRESS_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB6_ID, PRESS_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB7_ID, PRESS_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB8_ID, PRESS_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB9_ID, PRESS_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB11_ID, RELEASE_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB12_ID, RELEASE_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB13_ID, RELEASE_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB14_ID, RELEASE_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB15_ID, BOTH_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB16_ID, BOTH_EVNT, EventHandler);
  return KEYBOARD_INIT;
}
