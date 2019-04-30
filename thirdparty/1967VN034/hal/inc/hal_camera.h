/*
 * hal_camera.h
 *
 *  Created on: 15 ����� 2017 �.
 *      Author: sharavyev.d
 */

#ifndef __HAL_CAMERA_H__
#define __HAL_CAMERA_H__

#include <def1967VN034R1.h>
#include <stdint.h>

// ������� SR:
typedef union
{
	uint32_t word;
	struct
	{
		uint32_t EMPTY:1;																			// ����� ����
		uint32_t FULL:1;																			// ����� ��������
		uint32_t OVERF:1;																			// ���� ������������ ������
		uint32_t UNDERF:1;																			// ���� ������ ������� ������
	} b;
} CAMERA_SR_type;

// ������� CR:
typedef union
{
	uint32_t word;
	struct
	{
		uint32_t VCON:1;																			// ��������� ����������
		uint32_t VCIE:1;																			// ���������� ����������
		uint32_t SMODE:1;																			// ����� ������ ����������
	} b;
} CAMERA_CR_type;

typedef volatile struct
{
	__builtin_quad DR;																				// 128-��������� ������� ������. �������� ������ �� ������ � �������� ������� FIFO
	CAMERA_SR_type SR;																				// ������� ���������
	CAMERA_CR_type CR;																				// ������� ����������
} CAMERA_Type;

#define LX_CAMERA 		( ( CAMERA_Type * ) base_VIDEO )

typedef enum
{
	RECEIVE_MODE_CAMERA = 0,
	RECEIVE_MODE_MASTER
}CAMERA_Mode_type;

void HAL_CAMERA_SetupGpio( void );
void HAL_CAMERA_Enable( CAMERA_Mode_type eMode );
void HAL_CAMERA_Disable( void );

void HAL_CAMERA_StartDma( uint32_t ulChannel, void *pvCameraBuf, uint32_t ulXSize, uint32_t ulYSize,
					uint32_t ulDelta, uint8_t ucPixelsInWord, void *pvDmaIsrHandler );

#endif /* __HAL_CAMERA_H__ */
