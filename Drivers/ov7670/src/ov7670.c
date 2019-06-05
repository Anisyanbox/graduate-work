#include "ov7670.h"
#include "hal_1967VN034R1.h"
#include "stupid_delay.h"
#include "soft_i2c.h"
#include <stdint.h>

#define CAMERA_WR_ADR       ((unsigned char)0x42)
#define CAMERA_RD_ADR       ((unsigned char)0x43)

typedef enum {
  GAIN  = 0x00,
  BLUE  = 0x01,
  RED   = 0x02,
  COM2  = 0x09,
  COM7  = 0x12,
  COM15 = 0x40
} ov7670Regs_t;

// -----------------------------------------------------------------------------
static void CamWriteReg(ov7670Regs_t reg_addr, unsigned char data) {
  SoftI2cStart();
  SoftI2cSendByte(CAMERA_WR_ADR);
  SoftI2cSendByte((unsigned char)reg_addr);
  SoftI2cSendByte(data);
  SoftI2cEnd();
}

// -----------------------------------------------------------------------------
static void CamReadReg(ov7670Regs_t reg_addr, unsigned char * data) {
  SoftI2cStart();
  SoftI2cSendByte(CAMERA_WR_ADR);
  SoftI2cSendByte((unsigned char)reg_addr);
  SoftI2cEnd();

  SoftI2cStart(); 
  SoftI2cSendByte(CAMERA_RD_ADR);
  SoftI2cReadByte(data);
  SoftI2cEnd();
}

// -----------------------------------------------------------------------------
void ov7670HwInit(void) {
  SoftI2cInit();
}

// -----------------------------------------------------------------------------
void ov7670StandbyDisable(void) {
  CamWriteReg(COM2, 0x01);
}

// -----------------------------------------------------------------------------
void ov7670StandbyEnable(void) {
  CamWriteReg(COM2, 0x11);
}

// -----------------------------------------------------------------------------
void ov7670Reset(void) {
  CamWriteReg(COM7, 0x80);
  StupidDelayMs(1000);
}

// -----------------------------------------------------------------------------
void ov7670Init(void) {
  CamWriteReg(COM7, 0x04);  // enable RGB
  CamWriteReg(COM15, 0xD0); // enable 565 rgb mode
}
