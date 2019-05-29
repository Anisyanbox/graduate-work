/*
 *    20-Mar-2017 Dmitriy Sharaviev  -  ?reated
 *    20-May-2019 Anisimov Alexander - fixed
 */
#ifndef __HAL_LCD_H__
#define __HAL_LCD_H__

#include <def1967VN034R1.h>
#include <hal_pll.h>
#include <stdint.h>

#define __IO                      volatile
#define LCD_WINDOW_BCKGRND_FROM_RGB(red, green, blue)  ( ((red & 0xFF)<<16) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 0) )

/* 
                    R            G            B
  RGB888:    data[23:16]   data[15:8]   data[7:0]
  RGB565:    data[15:11]   data[10:5]   data[4:0]
  RGB444_AR: data[13:10]   data[8:5]    data[3:0]
  RGB444_AL: data[14:11]   data[9:6]    data[4:1]
  RGB233:    data[7:6]     data[5:3]    data[2:0]
*/
//                    [buffer size div]  [3:2] = CD   [1:0] = VBL
#define HAL_LCD_RGB888      ((1 << 4) | (0x3 << 2) | (0x0 << 0))
#define HAL_LCD_RGB565      ((2 << 4) | (0x1 << 2) | (0x0 << 0))
#define HAL_LCD_RGB444_AR   ((2 << 4) | (0x1 << 2) | (0x2 << 0))
#define HAL_LCD_RGB444_AL   ((2 << 4) | (0x1 << 2) | (0x3 << 0))
#define HAL_LCD_RGB233      ((4 << 4) | (0x0 << 2) | (0x0 << 0))

#define HAL_LCD_MAX_PWM_DUTY    100

/* ----------------------------------------- Register Description ------------------------------------- */
typedef struct {
  union {
    uint32_t REG;
    struct {
      uint32_t VEN :1;        //  '1' - controller is on
      uint32_t VIE :1;        //
      uint32_t HIE :1;        //
      uint32_t VBIE :1;       //  Video Bank Interrupt Enable (INT is geerated when lsat world load from in-buf to convertor)
      uint32_t SLPIE :1;      //  Sleep End Interrupt Enable (INT is generated when sleep controller period will elapsed)
      uint32_t RESERVED1 :1;  // 
      uint32_t XRQEN :1;      // interrupts after DMA has finished reading from external memory
      uint32_t VBL :2;        // bits per pixel (depend on CD)
      uint32_t CD :2;         // bit count for one pixel input info
      uint32_t RESERVED2 :1;  // 
      uint32_t HLDM :1;       // '1' - stop load new data if last data is sent
      uint32_t HLDV :1;       // '1' - stop generation control signals if last data is sent
      uint32_t RESERVED3 :1;  //
      uint32_t BL :1;         // activ level for DRDY (0 - high, 1 - low)
      uint32_t RESERVED4 :1;  //
      uint32_t VBGR :1;       // '1' - BGR mode, 0 - RGB mode 
      uint32_t RESERVED5 :2;  //
      uint32_t SLP_MODE :1;   // '1' - sleep mode after sending data
      uint32_t SLP_PCLK :1;   // '1' - stop pixel clock devider in sleep mode
      uint32_t SPL_PXEN :1;   // '1' - stop pixel clock in sleep mode 
      uint32_t SPL_HOLD :1;   // '1' - stop generation control signals if last data is sent
      uint32_t SPL_CLRF :1;   // '1' - auto reset flags after sleep mode delay
      uint32_t RESERVED6 :3;  //
      uint32_t W2W_EN :1;     // '1' - allowed use erxtra registers in active area
      uint32_t PXP_EN :1;     // '1' - allowed stoping pixel clock if out-buffers has no data
      uint32_t RESERVED7 :2;  //
    } field;
  };
} LCD_CTRL_Type;

typedef struct {
  union {
    uint32_t REG;
    struct {
      uint32_t RESERVED1 :1;  //
      uint32_t LUINT :1;      // 
      uint32_t STA_SLEEP :1;  // sleep timer started calculate time (set when controller go to sleep mode)
      uint32_t FIN_SLEEP :1;  // sleep timer ended calculate time (set when controller finished sleep mode)
      uint32_t VINT :1;       // flag means conclusion of sending frame
      uint32_t HINT :1;       // flag means conclusion of sending line
      uint32_t VBSINT :1;     // data from input buf was transmitted to converter
      uint32_t DMA_END :1;    // 
      uint32_t RESERVED2 :12; //
      uint32_t SLEEP_EXE :1;  // sleep mode
      uint32_t RESERVED3 :11; //
    } field;
  };
} LCD_STATUS_Type;

typedef struct {
  union {
    uint32_t REG;
    struct {
      uint32_t HPS :10;
      uint32_t RESERVED1 :5; 
      uint32_t HPL :1;
      uint32_t HPW :10;
      uint32_t RESERVED2 :6;
    } field;
  };
} LCD_HTIM_Type;

typedef struct {
  union {
    uint32_t REG;
    struct {
      uint32_t VPS :10;
      uint32_t RESERVED1 :5;
      uint32_t VPL :1;
      uint32_t VPW :10;
      uint32_t RESERVED2 :6;
    } field;
  };
} LCD_VTIM_Type;

typedef struct {
  union {
    uint32_t REG;
    struct {
      uint32_t HT :7;
      uint32_t RESERVED1 :9;
      uint32_t VT :10;
      uint32_t RESERVED2 :6;
    } field;
  };
} LCD_HVLEN_Type;

typedef struct {
  union {
    uint32_t REG;
    struct {
      uint32_t VSIZE :20;
      uint32_t RESERVED1 :12;
    } field;
  };
} LCD_VSIZE_Type;

typedef struct {
  union {
    uint32_t REG;
    struct {
      uint32_t P_DIV :8;
      uint32_t EN_DIV :1;
      uint32_t RESERVED1 :23;
    } field;
  };
} LCD_PXDV_Type;

typedef struct {
  union {
    uint32_t REG;
    struct {
      uint32_t HDPS :10;
      uint32_t RESERVED1 :6;
      uint32_t HDPE :10;
      uint32_t RESERVED2 :6;
    } field;
  };
} LCD_HDTIM_Type;

typedef struct {
  union {
    uint32_t REG;
    struct {
      uint32_t VDPS :10;
      uint32_t RESERVED1 :6;
      uint32_t VDPE :10;
      uint32_t RESERVED2 :6;
    } field;
  };
} LCD_VDTIM_Type;

typedef struct {
  union {
    uint32_t REG;
    struct {
      uint32_t HXDPS :10;
      uint32_t RESERVED1 :6;
      uint32_t HXDPE :10;
      uint32_t RESERVED2 :6;
    } field;
  };
} LCD_HDxTIM_Type;

typedef struct {
  union {
    uint32_t REG;
    struct {
      uint32_t VXDPS :10;
      uint32_t RESERVED1 :6;
      uint32_t VXDPE :10;
      uint32_t RESERVED2 :6;
    } field;
  };
} LCD_VDxTIM_Type;

typedef struct {
  union {
    uint32_t REG;
    struct {
      uint32_t RESERVED1 :6;
      uint32_t FPSHI :1;
      uint32_t RESERVED2 :2;
      uint32_t DVI_MODE :1;
      uint32_t DVI_CLK :1;
      uint32_t RESERVED3 :21;
    } field;
  };
} LCD_PANEL_CFG_Type;

typedef struct {
  union {
    uint32_t REG;
    struct {
      uint32_t CLKEN :1;
      uint32_t RESERVED1 :2;
      uint32_t FRSH :1;   
      uint32_t PWM_Dv :4;
      uint32_t DUTY :8;
      uint32_t RELOAD :8;
      uint32_t RESERVED2 :8;
    } field;
  };
} LCD_PWM_CR_Type;

typedef struct {
  union {
    uint32_t REG;
    struct {
      uint32_t GPO_ST :10;
      uint32_t RESERVED1 :5;
      uint32_t HPL :1;
      uint32_t GPO_SP :10;
      uint32_t RESERVED2 :6;
    } field;
  };
} LCD_GPIO_Type;

typedef __IO struct {
  LCD_CTRL_Type CTRL;
  LCD_STATUS_Type STATUS;
  LCD_HTIM_Type HTIM;
  LCD_VTIM_Type VTIM;
  LCD_HVLEN_Type HVLEN;
  LCD_HDxTIM_Type HDxTIM;
  LCD_VDxTIM_Type VDxTIM;
  LCD_VSIZE_Type VSIZE;
  uint32_t FON;
  LCD_PXDV_Type PXDV;
  LCD_HDTIM_Type HDTIM;
  LCD_VDTIM_Type VDTIM;
  LCD_PANEL_CFG_Type PANEL_CFG;
  LCD_PWM_CR_Type PWM_CR;
  uint32_t SLP_PERIOD;
  uint32_t RESERVED;
  LCD_GPIO_Type GPIO_0;
  LCD_GPIO_Type GPIO_1;
  LCD_GPIO_Type GPIO_2;
  LCD_GPIO_Type GPIO_3;
} LCD_Type;

#define LX_LCD    ( ( LCD_Type * ) base_LCD )

/* -------------------------------------- Additional types for init ------------------------------------ */
typedef enum {
  LCD_Gpio_0 = 0,
  LCD_Gpio_1,
  LCD_Gpio_2,
  LCD_Gpio_3
} LCD_ExGpioNum_type;

typedef struct {
  uint32_t StartPosition;
  uint32_t StopPosition;
  uint32_t ActiveLevel; 
} LCD_ExGpio_type;

typedef struct {
  uint16_t usHSize;                // window size
  uint16_t usVSize;                //
  int16_t sHOffset;                // shift relatively  usHSize and usVSize area in conf struct
  int16_t sVOffset;                //
  uint32_t ulBackgndColor;         // color for background
} LCD_WindowConf_type;

typedef struct {
  uint32_t ulRgbMode;               // color format
  uint32_t ulPixelClock;            // freq for pixel sync
  uint32_t ulPwmDiv;                // freq PWM = Fcore / (2 * HAL_LCD_MAX_PWM_DUTY * 2^pwm_div)
  uint32_t bVSyncActiveLevel :1;    // active level VSYNC (0 - low 1 - high)
  uint32_t bHSyncActiveLevel :1;    // active level HSYNC (0 - low 1 - high)
  uint32_t bDReadyActiveLevel :1;   // active level for ready line
  uint32_t bPClkInverse :1;         // inversion for pixel clock
  uint32_t bStopPclkWhenNoData :1;  // stop pixel clock when no new data
  uint32_t bSwapRgbToBgr :1;        // RGB -> BGR

  uint16_t usHSyncPos;              // period pixel clock
  uint16_t usHSyncLen;              //
  uint16_t usHSize;                 //
  uint16_t usHFrontBlank;           //
  uint16_t usHBackBlank;            //

  uint16_t usVSyncPos;              // period pixel clock
  uint16_t usVSyncLen;              //
  uint16_t usVSize;                 //
  uint16_t usVFrontBlank;           //
  uint16_t usVBackBlank;            //

  LCD_WindowConf_type *pxWindow;    // set to NULL if windows mode isn't used
} LCD_Conf_type;

#ifdef __cplusplus
extern "C" {
#endif

void HAL_LCD_Enable(void);
void HAL_LCD_Disable(void);

void HAL_LCD_GpioInit(void);
void HAL_LCD_GpioDeInit(void);
void HAL_LCD_ExGpioInit(LCD_ExGpioNum_type eGpio, LCD_ExGpio_type *pxExGpioCfg);
void HAL_LCD_ExGpioDeInit(LCD_ExGpioNum_type eGpio);
void HAL_LCD_Setup(LCD_Conf_type *pxCfg);
void HAL_LCD_PwmSetDuty(uint8_t ucValue);
void HAL_LCD_StartDma(uint32_t ulChannel, 
                      void *pvLcdBuf,
                      uint32_t ulXSize, 
                      uint32_t ulYSize, 
                      uint32_t ulRgbMode,
                      void *pvDmaIsrHandler);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif  //__HAL_LCD_H__
