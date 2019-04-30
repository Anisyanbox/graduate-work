/**********************************************************************************************************************
  Copyright (c) 2017 Milandr Corporation. All rights reserved.

  History:
  	  14-Mar-2017 Ivan Osadchy 	 - add LX_GPIO_...
  	  02-Mar-2017 Ivan Osadchy   - Created
**********************************************************************************************************************/
#include <hal_1967VN034R1.h>
#include <hal_gpio.h>

// Инициализация режима работы пинов для порта PA, PB или PC:
void HAL_GPIO_Init (GPIO_PortPi * const GPIO_Pi, const uint Pins, const GPIO_PinMode Mode) {

	__IO uint *ALT = (Mode & 0x4)? &GPIO_Pi->ALT.SET : &GPIO_Pi->ALT.CLR;
	__IO uint *DDR = (Mode & 0x2)? &GPIO_Pi->DDR.SET : &GPIO_Pi->DDR.CLR;
	__IO uint *PUR = (Mode & 0x1)? &GPIO_Pi->PUR.SET : &GPIO_Pi->PUR.CLR;

	*ALT 				= Pins;
	*DDR 				= Pins;
	*PUR 				= Pins;
	GPIO_Pi->DR.CLR 	= Pins;
	GPIO_Pi->INVR.CLR 	= Pins;

}


// Деинициализация пинов в начальное состояние:
void HAL_GPIO_DeInit (GPIO_PortPi * const GPIO_Pi, const uint Pins) {

	HAL_GPIO_InterruptConfig (GPIO_Pi, Pins, GPIO_InterruptMode_Off);

	GPIO_Pi->ALT.CLR = Pins;
	GPIO_Pi->DDR.CLR = Pins;
	GPIO_Pi->PUR.CLR = Pins;

}

void HAL_GPIO_Px_AltInit (const GPIO_PxAlt_type PxAlt, const GPIO_PxAlt_Mode_type PxAltMode) {
	GPIO_RegPxALT ALT;
	ALT.word =  (uint)PxAlt;
	ALT.b.PDXF = (uint)PxAltMode;
	LX_GPIO_PxALT->word = ALT.word;
}

void HAL_GPIO_Px_AltDeInit (void) {
	LX_GPIO_PxALT->word = 0;
}

// Инициализация режима работы пинов для порта PxD как GPIO:
void HAL_GPIO_PxD_Init (const uint Pins, const GPIO_PinMode Mode) {
	HAL_GPIO_Px_AltDeInit ();
	if (Mode & 0x02) 	LX_GPIO_PxD->DIR |= Pins;
	else 				LX_GPIO_PxD->DIR &= (~Pins);
	if (Mode & 0x01)	LX_GPIO_PxD->PUR |=   Pins;
	else 				LX_GPIO_PxD->PUR &= (~Pins);
}

// Деинициализация режима работы пинов для порта PxD:
void HAL_GPIO_PxD_DeInit (const uint Pins) {
	HAL_GPIO_Px_AltDeInit ();
	LX_GPIO_PxD->DIR &= (~Pins);
	LX_GPIO_PxD->PUR &= (~Pins);
}


// Запись значения в 1 пин порта:
void HAL_GPIO_WritePin (GPIO_PortPi * const GPIO_Pi, const GPIO_PIN Pin, const GPIO_PinState NewState) {

	if (NewState == GPIO_PinState_Set)	GPIO_Pi->DR.SET = Pin;
	else								GPIO_Pi->DR.CLR = Pin;

}


// Прочитать текущее значение 1 пина порта:
GPIO_PinState HAL_GPIO_ReadPin (GPIO_PortPi * const GPIO_Pi, const GPIO_PIN Pin) {

	return ((GPIO_PinState) ((GPIO_Pi->PXD & Pin) != 0));

}


// Записать значения в набор пинов порта:
void HAL_GPIO_WritePins (GPIO_PortPi * const GPIO_Pi, const uint Pins, const uint Data) {

	GPIO_Pi->DR.CLR = (Pins & (~Data));
	GPIO_Pi->DR.SET = (Pins &   Data );

}


// Инвертировать значения в наборе пинов порта:
void HAL_GPIO_TogglePins (GPIO_PortPi * const GPIO_Pi, const uint Pins) {

	GPIO_Pi->DR.INV = Pins;

}


// Прочитать значения из набора пинов порта:
uint HAL_GPIO_ReadPins (GPIO_PortPi * const GPIO_Pi, const uint Pins) {

	return (GPIO_Pi->PXD & Pins);

}


// Записать значения в пины портов PxA или PxD:
void HAL_GPIO_Px_WritePins (const GPIO_PxPort Px, const uint Pins, const uint Data) {

	__IO uint *CLR = (Px == GPIO_PxPort_A)? &LX_GPIO_PxA->CLR : &LX_GPIO_PxD->CLR;
	__IO uint *SET = (Px == GPIO_PxPort_A)? &LX_GPIO_PxA->SET : &LX_GPIO_PxD->SET;

	*CLR = (Pins & (~Data));
	*SET = (Pins &   Data );

}


// Прочитать значения из пинов портов PxA или PxD:
uint HAL_GPIO_Px_ReadPins (const GPIO_PxPort Px, const uint Pins) {

	__IO uint *DR = (Px == GPIO_PxPort_A)? &LX_GPIO_PxA->DR : &LX_GPIO_PxD->DR;

	return (*DR & Pins);

}


// Настройка прерываний от пинов порта:
void HAL_GPIO_InterruptConfig (GPIO_PortPi * const GPIO_Pi, const uint Pins, const GPIO_InterruptMode Mode) {

	__IO uint *IMR  = (Mode == GPIO_InterruptMode_Off	 )? 	&GPIO_Pi->IMR.CLR  : &GPIO_Pi->IMR.SET;
	__IO uint *PEIE = (Mode == GPIO_InterruptMode_Posedge)? 	&GPIO_Pi->PEIE.SET : &GPIO_Pi->PEIE.CLR;
	__IO uint *NEIE = (Mode == GPIO_InterruptMode_Negedge)? 	&GPIO_Pi->NEIE.SET : &GPIO_Pi->NEIE.CLR;
	__IO uint *INVR = (Mode == GPIO_InterruptMode_LowLvl )? 	&GPIO_Pi->INVR.SET : &GPIO_Pi->INVR.CLR;

	// Сброс запросов прерываний до настройки:
	HAL_GPIO_InterruptEdgeClear (GPIO_Pi, Pins);

	// Настройка прерываний:
	*IMR 	= Pins;
	*PEIE 	= Pins;
	*NEIE 	= Pins;
	*INVR 	= Pins;

}

// Проверка возникновения прерывания на пине порта:
uint HAL_GPIO_InterruptCheck (GPIO_PortPi * const GPIO_Pi, const uint Pins) {

	return (GPIO_Pi->INTREQ & Pins);

}

// Сброс прерывания по фронту:
void HAL_GPIO_InterruptEdgeClear (GPIO_PortPi * const GPIO_Pi, const uint Pins) {

	GPIO_Pi->ECLR = Pins;

}
