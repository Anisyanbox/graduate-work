#ifndef _INC_RESET_REASON_H_
#define _INC_RESET_REASON_H_

typedef enum {
  NORMAL_RESET = 0,
  WD_TIMER
}RstRsn_t;

void RstRsnSave(void);
RstRsn_t RstRsnGetSaveState(void);


#endif  // _INC_RESET_REASON_H_
