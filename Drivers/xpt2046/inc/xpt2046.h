#ifndef _DRIVERS_XPT2046_INC_XPT2046_H_
#define _DRIVERS_XPT2046_INC_XPT2046_H_

// HW types for init/send/rec throuth SPI bus
typedef void (*SpiInit_t)(void);
typedef void (*SpiSendReceive_t)(unsigned char send_byte, unsigned char * two_bytes_arr);
typedef void (*SpiSelect_t)(void);
typedef void (*SpiUnselect_t)(void);
typedef int (*GetBusyPinState_t)(void);
typedef int (*GetPenIrqPinState_t)(void);

// type for drawing point on LCD 
typedef void (*LcdDrawPoint)(unsigned int x, unsigned int y);

typedef struct {
  SpiInit_t             spi_and_gpio_init;
  SpiSendReceive_t      send_receive;
  SpiSelect_t           select;
  SpiUnselect_t         unselect;
  GetBusyPinState_t     get_busy_pin;
  GetPenIrqPinState_t   get_penirq_pin;
  int                   is_generate_irq;
} Xpt2046HwDependFuncs_t;

//
// Pointer hw_depend_funs can be created on stack because its fields are seved
// into xpt2046 driver.
//
// 'select' and 'unselect' can be NULL. It will mean that your SPI controller will
// manage select/unselect pin
//
// If is_generate_irq == true, xpt2046 will generate low lewel on penIRQ pin
//
// Returns 0, if init was done successly
int Xpt2046Init(Xpt2046HwDependFuncs_t * hw_depend_funs);
int Xpt2046IsTouched(void);
void Xpt2046Calibrate(LcdDrawPoint lcd_draw);
void Xpt2046GetXY(unsigned int * x, unsigned int * y);

#endif  // _DRIVERS_XPT2046_INC_XPT2046_H_
