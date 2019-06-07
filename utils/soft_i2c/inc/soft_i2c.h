#ifndef _UTILS_INIT_INC_SOFT_I2C_H_
#define _UTILS_INIT_INC_SOFT_I2C_H_

void SoftI2cInit(void);
void SoftI2cStart(void);
void SoftI2cEnd(void);

// return 0 if was ACK bit from slave;
// return 1 if was NACK bit from slave
int SoftI2cSendByte(unsigned char data);
void SoftI2cReadByte(unsigned char * data);

#endif  // _UTILS_INIT_INC_SOFT_I2C_H_
