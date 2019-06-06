#ifndef _UTILS_INIT_INC_SOFT_I2C_H_
#define _UTILS_INIT_INC_SOFT_I2C_H_

#include <stdint.h>

typedef enum {
  SOFT_I2C_ACK = 0,
  SOFT_I2C_NO_ACK
} SoftI2cAckStatus_t;

void SoftI2cInit(void);
void SoftI2cStart(void);
void SoftI2cEnd(void);
SoftI2cAckStatus_t SoftI2cSendByte(unsigned char data);
void SoftI2cReadByte(unsigned char * data);

#endif  // _UTILS_INIT_INC_SOFT_I2C_H_
