#ifndef _DRIVERS_TVL320AIC23B_INC_AIC23B_H_
#define _DRIVERS_TVL320AIC23B_INC_AIC23B_H_

#include <stdint.h>
#include <stddef.h>

// HW types for init/send/rec throuth SPI/I2C bus
typedef void (*Aic23bInit_t)(void);
typedef void (*Aic23bSend_t)(uint8_t * tx, size_t n);
typedef void (*Aic23bSelect_t)(void);
typedef void (*Aic23bDelayMs_t)(unsigned int ms);
typedef void (*Aic23bUnselect_t)(void);

typedef struct {
  Aic23bInit_t       hw_init;
  Aic23bSend_t       send;
  Aic23bSelect_t     select;
  Aic23bUnselect_t   unselect;
  Aic23bDelayMs_t    delay;
} Aic23bHwDependFuncs_t;

typedef enum {
  AIC23B_ADC_96_DAC_96 = 0,
  AIC23B_ADC_48_DAC_48,
  AIC23B_ADC_32_DAC_32,
  AIC23B_ADC_8_DAC_8,
  AIC23B_ADC_48_DAC_8,
  AIC23B_ADC_8_DAC_48
} Aic23bSamples_t;

typedef enum {
  AIC23B_16BIT_SOUNND = 0,
  AIC23B_20BIT_SOUNND,
  AIC23B_24BIT_SOUNND,
  AIC23B_32BIT_SOUNND
} Aic23bSoundDepth_t;

//
// Pointer hw_depend_funcs can be created on stack because its fields are seved
// into aic23b driver.
//
// 'select' and 'unselect' can be NULL. It will mean that your SPI controller will
// manage select/unselect pin.
//
//
// Returns 0, if init was done successly.
int Aic23bInit(Aic23bHwDependFuncs_t * hw_depend_funcs);

// percent = 0 - mute 
// percent = 100 - max volume
void Aic23bSetInputVolume(unsigned short percent);
void Aic23bSetOutVolume(unsigned short percent);

// 'AIC23B_ADC_48_DAC_48' is default after init function
void Aic23bSetRate(Aic23bSamples_t srate);

// 'AIC23B_16BIT_SOUNND' is default after init function
void Aic23bSetAdcDacResolution(Aic23bSoundDepth_t depth);
unsigned int Aic23bGetAdcRes(void);
unsigned int Aic23bGetDacRes(void);

#endif  // _DRIVERS_TVL320AIC23B_INC_AIC23B_H_
