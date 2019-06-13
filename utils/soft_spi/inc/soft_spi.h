#ifndef _UTILS_INIT_INC_SOFT_I2C_H_
#define _UTILS_INIT_INC_SOFT_I2C_H_

#include <stdint.h>
#include <stddef.h>

void SoftSpiInit(void);
void SoftSpiSend(uint8_t * tx_data, size_t n);
void SoftSpiSelect(void);
void SoftSpiUnselect(void);

#endif  // _UTILS_INIT_INC_SOFT_I2C_H_
