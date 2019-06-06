/*
 * hal_camera.h
 *
 *  Author: sharavyev.d
 */

#ifndef __HAL_CAMERA_H__
#define __HAL_CAMERA_H__

#include <def1967VN034R1.h>
#include <stdint.h>

typedef union {
  uint32_t word;
  struct {
    uint32_t EMPTY:1;
    uint32_t FULL:1;
    uint32_t OVERF:1;
    uint32_t UNDERF:1;
  } b;
} CAMERA_SR_type;

typedef union {
  uint32_t word;
  struct {
    uint32_t VCON:1;
    uint32_t VCIE:1;
    uint32_t SMODE:1;
    uint32_t VPOL :1;
  } b;
} CAMERA_CR_type;

typedef volatile struct
{
  __builtin_quad DR;
  CAMERA_SR_type SR;
  CAMERA_CR_type CR;
} CAMERA_Type;

#define LX_CAMERA     ( ( CAMERA_Type * ) base_VIDEO )

typedef enum {
  CAMERA_RECEIVE_MODE_CAMERA = 0,
  CAMERA_RECEIVE_MODE_MASTER
} CAMERA_Mode_type;

typedef enum {
  CAMERA_VSYNC_LOW = 0,
  CAMERA_VSYNC_HIGH
} CAMERA_VSYNC_type;

typedef struct {
  CAMERA_Mode_type eMode;
  CAMERA_VSYNC_type eVSYNC;
} CAMERA_Conf_type;

void HAL_CAMERA_SetupGpio( void );
void HAL_CAMERA_Enable( void );
void HAL_CAMERA_Disable( void );
void HAL_CAMERA_Config( CAMERA_Conf_type *pxConf );
void HAL_CAMERA_StartDma( uint32_t ulChannel, 
                          void *pvCameraBuf, 
                          uint32_t ulXSize, 
                          uint32_t ulYSize,
                          uint32_t ulDelta,
                          uint8_t ucPixelsInWord, 
                          void *pvDmaIsrHandler );

#endif /* __HAL_CAMERA_H__ */
