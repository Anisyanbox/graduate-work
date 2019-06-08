#ifndef _DRIVERS_XPT2046_INC_XPT2046_H_
#define _DRIVERS_XPT2046_INC_XPT2046_H_

#include <stdbool.h>
#include <string.h> // for size_t type

// HW types for init/send/rec throuth SPI bus
typedef void (*SpiInit_t)(void);
typedef void (*SpiNssSet_t)(int nss_state);
typedef void (*SpiSendNBytes_t)(unsigned char * src, size_t n);
typedef void (*SpiRecNBytes_t)(unsigned char* dst, size_t n);
typedef void (*DelayMsFunc_t)(unsigned int);
typedef int (*GetBusyPinState_t)(void);
typedef int (*GetPenIrqPinState_t)(void);

// type for drawing point on LCD 
typedef void (*LcdDrawPoint)(unsigned int x, unsigned int y);

typedef struct {
  SpiInit_t             spi_and_gpio_init;
  SpiNssSet_t           spi_nss;
  SpiSendNBytes_t       spi_send;
  SpiRecNBytes_t        spi_rec;
  GetBusyPinState_t     get_busy_pin;
  GetPenIrqPinState_t   get_penirq_pin;
  DelayMsFunc_t         delay;
  int                   is_generate_irq;
} Xpt2046HwDependFuncs_t;

// Func 'spi_nss' can be NULL pointer.
// It will mean that SPI controller in your microcontroller manages this pin.
//
// Pointer hw_depend_funs can be created on stack because its fields are seved
// into xpt2046 driver.
//
// If is_generate_irq == true, xpt2046 will generate low lewel on penIRQ pin
//
// Returns 0, if init was done successly
int Xpt2046Init(Xpt2046HwDependFuncs_t * hw_depend_funs);
int Xpt2046IsTouched(void);
void Xpt2046Calibrate(LcdDrawPoint lcd_draw);
void Xpt2046GetXY(unsigned int * x, unsigned int * y, int num_measurements);

#endif  // _DRIVERS_XPT2046_INC_XPT2046_H_
