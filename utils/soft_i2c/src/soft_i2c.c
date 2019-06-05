#include "soft_i2c.h"
#include "hal_1967VN034R1.h"
#include "def1967VN034R1.h"

#define I2C_PORT_BASE    base_GPA
#define I2C_GPIO_PORT    LX_GPIO_PA
#define I2C_SCL_PIN      GPIO_PIN_24
#define I2C_SDA_PIN      GPIO_PIN_23

#define MODE_HIZ  0
#define MODE_DRV  1

// -----------------------------------------------------------------------------
static void SetSclMode(int mode) {
  GPIO_PinMode m = (mode == MODE_DRV) ? GPIO_PinMode_OutPU : GPIO_PinMode_InPU;
  HAL_GPIO_Init(I2C_GPIO_PORT, I2C_SCL_PIN, m);
}

// -----------------------------------------------------------------------------
static void SetSdaMode(int mode) {
  GPIO_PinMode m = (mode == MODE_DRV) ? GPIO_PinMode_OutPU : GPIO_PinMode_InPU;
  HAL_GPIO_Init(I2C_GPIO_PORT, I2C_SDA_PIN, m);
}

// -----------------------------------------------------------------------------
static void SetScl(int state) {
  GPIO_PinState nstate = (state) ? GPIO_PinState_Set : GPIO_PinState_Reset;
  HAL_GPIO_WritePin(I2C_GPIO_PORT, I2C_SCL_PIN, nstate);
}

// -----------------------------------------------------------------------------
static void SetSda(int state) {
  GPIO_PinState nstate = (state) ? GPIO_PinState_Set : GPIO_PinState_Reset;
  HAL_GPIO_WritePin(I2C_GPIO_PORT, I2C_SDA_PIN, nstate);
}

// -----------------------------------------------------------------------------
static int GetScl(void) {
  GPIO_PinState t = HAL_GPIO_ReadPin(I2C_GPIO_PORT, I2C_SCL_PIN);
  if (t == GPIO_PinState_Set) {
    return 1;
  } else {
    return 0;
  }
}

// -----------------------------------------------------------------------------
static int GetSda(void) {
  GPIO_PinState t = HAL_GPIO_ReadPin(I2C_GPIO_PORT, I2C_SDA_PIN);
  if (t == GPIO_PinState_Set) {
    return 1;
  } else {
    return 0;
  }
}

// -----------------------------------------------------------------------------
static void HalfPeriodDelay(void) {
  for (volatile int i = 0; i < 36; i++) {
    asm("nop;;");
  }
}

// -----------------------------------------------------------------------------
static void QuarterPeriodDelay(void) {
  for (volatile int i = 0; i < 18; i++) {
    asm("nop;;");  
  }
}

// Before calling init function appropriate alternate functions should be set
// for the SCL and SDA lines
// The I2C drivers changes only direction and output value on these pins.
// -----------------------------------------------------------------------------
void SoftI2cInit(void) {
  HAL_GPIO_Init(I2C_GPIO_PORT, GPIO_PIN_24 | GPIO_PIN_23, GPIO_PinMode_OutPU);
  SetScl(1);
  SetSda(1);
  SetSclMode(MODE_DRV);
  SetSdaMode(MODE_DRV);
  HalfPeriodDelay();
}

// -----------------------------------------------------------------------------
void SoftI2cStart(void) {
  SetScl(1);
  SetSda(1);
  HalfPeriodDelay();
  SetSda(0);
  HalfPeriodDelay();
  SetScl(0);
  HalfPeriodDelay();
}

// -----------------------------------------------------------------------------
void SoftI2cEnd(void) {
  QuarterPeriodDelay();
  SetScl(1);
  SetSda(0);
  HalfPeriodDelay();
  SetSda(1);
  HalfPeriodDelay();
}

// -----------------------------------------------------------------------------
SoftI2cAckStatus_t SoftI2cSendByte(unsigned char data) {
  unsigned char bit_mask = 0x80;
  unsigned char ack_state = 0;
  		
  while(bit_mask) {
    SetSda(data & bit_mask);
    QuarterPeriodDelay();
    SetScl(1);
    HalfPeriodDelay();
    SetScl(0);
    QuarterPeriodDelay();
    bit_mask >>= 1;
  }

  // Provide one more clock for ACK
  SetSdaMode(MODE_HIZ);
  QuarterPeriodDelay();
  SetScl(1);
  QuarterPeriodDelay();
  ack_state = GetSda();
  QuarterPeriodDelay();
  SetScl(0);
  QuarterPeriodDelay();
  		
  // Leave bus
  SetSda(0);
  SetSdaMode(MODE_DRV);
  return (ack_state == 0) ? (SOFT_I2C_ACK) : (SOFT_I2C_NO_ACK);
}

// -----------------------------------------------------------------------------
void SoftI2cReadByte(unsigned char * data) {
  unsigned char in_val = 0;
  int bit_cnt = 7;

  *data = 0;
  SetSdaMode(MODE_HIZ);
  while(bit_cnt) {
    QuarterPeriodDelay();
    SetScl(1);
    QuarterPeriodDelay();
    in_val = (unsigned char)GetSda();
    QuarterPeriodDelay();
    SetScl(0);
    QuarterPeriodDelay();

    *data |= (in_val << bit_cnt);
    --bit_cnt;
  }

  // send NACK
  QuarterPeriodDelay();
  SetScl(1);
  QuarterPeriodDelay();
  SetSda(1);
  QuarterPeriodDelay();
  SetScl(0);
  QuarterPeriodDelay();
  
  // Leave bus
  SetSda(0);
  SetSdaMode(MODE_DRV);
  return;
}
