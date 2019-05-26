#ifndef _UTILS_RESET_REASON_INC_RESET_REASON_H_
#define _UTILS_RESET_REASON_INC_RESET_REASON_H_

typedef enum {
  NORMAL_RESET = 0,
  WD_TIMER
}RstRsn_t;

void RstRsnSave(void);
RstRsn_t RstRsnGetSavedState(void);


#endif  // _UTILS_RESET_REASON_INC_RESET_REASON_H_
