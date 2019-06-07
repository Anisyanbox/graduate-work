#ifndef _DRIVERS_OV7670_INC_OV7670_H_
#define _DRIVERS_OV7670_INC_OV7670_H_

// HW types for init/send/rec throuth SCCB (Serial Camera Control Bus)
typedef void (*SccbInit_t)(void);
typedef void (*SccbStart_t)(void);
typedef void (*SccbEnd_t)(void);
typedef int (*SccbSendByte)(unsigned char byte);
typedef void (*SccbRecByte)(unsigned char * byte);
typedef void (*SccbDelayMs)(unsigned int ms);

typedef struct {
  SccbInit_t   sccb_init;
  SccbStart_t  sccb_start;
  SccbEnd_t    sccb_end;
  SccbSendByte sccb_send_byte;
  SccbRecByte  sccb_rec_byte;
  SccbDelayMs  sccb_delay_ms;
} Ov7670HwDependFunc_t;

typedef enum {
  RES480x272_RGB565 = 0
} Ov7670Res_t;

// Only 'sccb_start' and 'sccb_end' functions can be NULL.
// This will mean that start and stop condition for SCCB protocol 
// are done inside send/receive functions.
// Pointer hw_sccb_funcs can be created on stackm because it fields are seved
// into ov7670 driver
int ov7670Init(Ov7670HwDependFunc_t * hw_sccb_funcs, Ov7670Res_t res);
void ov7670Reset(void);
void ov7670StandbyDisable(void);
void ov7670StandbyEnable(void);

// rotate the image 180 degrees
void ov7670MirrorImage(void);

#endif  // _DRIVERS_OV7670_INC_OV7670_H_
