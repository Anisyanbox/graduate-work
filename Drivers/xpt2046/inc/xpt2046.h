#ifndef _DRIVERS_XPT2046_INC_XPT2046_H_
#define _DRIVERS_XPT2046_INC_XPT2046_H_

// HW types for init/send/rec throuth SPI bus
typedef void (*SpiInit_t)(void);
typedef void (*SpiSendReceive_t)(unsigned char send_byte, unsigned char * two_bytes_rx_arr);
typedef void (*SpiSelect_t)(void);
typedef void (*SpiUnselect_t)(void);
typedef void (*DelayMs_t)(unsigned int ms);
typedef int (*GetPenIrqPinState_t)(void);

// type for drawing point on LCD 
typedef void (*LcdDrawPoint_t)(unsigned int x, unsigned int y);

typedef struct {
  SpiInit_t             spi_and_gpio_init;
  SpiSendReceive_t      send_receive;
  SpiSelect_t           select;
  SpiUnselect_t         unselect;
  GetPenIrqPinState_t   get_penirq_pin;
  DelayMs_t             delay;
  int                   is_generate_irq;
} Xpt2046HwDependFuncs_t;

typedef struct {
  unsigned int x_lcd_size;
  unsigned int y_lcd_size;
  unsigned int is_xy_lcd_and_xy_touch_swap;
  unsigned int is_x_lcd_and_x_touch_diff_direction;
  unsigned int is_y_lcd_and_y_touch_diff_direction;
} Xpt2046LcdInfo_t;

//
// Pointer hw_depend_funs can be created on stack because its fields are seved
// into xpt2046 driver.
//
// 'select' and 'unselect' can be NULL. It will mean that your SPI controller will
// manage select/unselect pin.
//
// If is_generate_irq == true, xpt2046 will generate low lewel on penIRQ pin.
//
// In SpiSendReceive_t function second args are array from two unsigned char value.
// Your realization must write MSB spi byte to two_bytes_rx_arr[0]
// and LSB spi byte two two_bytes_rx_arr[1].
//
// SpiInit_t function must setup SPI clock not more 0.5 MHz.
//
// Returns 0, if init was done successly.
int Xpt2046Init(Xpt2046HwDependFuncs_t * hw_depend_funs);
int Xpt2046IsTouched(void);

//
// lcd_info.x_lcd_size - real lcd x size in pixels
// lcd_info.y_lcd_size - real lcd y size in pixels
//
// lcd_info.is_xy_lcd_and_xy_touch_swap = 1 if axises XY touch and axises XY lcd  
// are swapped
void Xpt2046Calibrate(LcdDrawPoint_t lcd_draw, Xpt2046LcdInfo_t * lcd_info);
void Xpt2046GetXY(unsigned int * x, unsigned int * y);

#endif  // _DRIVERS_XPT2046_INC_XPT2046_H_
