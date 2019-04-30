/**********************************************************************************************************************
  Copyright (c) 2016 Milandr Corporation. All rights reserved.

  History:
  	  Zatonsky Pavel - Created.
**********************************************************************************************************************/
#include <hal_1967VN034R1.h>
#include <sysreg.h>
#include <builtins.h>

void HAL_Interrupt_Enable( InterruptRequest_type intRQST, void *ptrHndlr )
{
	unsigned int tmp32;

	*( unsigned int * ) ( IVT_BASE + intRQST ) = ( unsigned int )ptrHndlr;

	if ( intRQST < 32 )
	{
		tmp32 = __builtin_sysreg_read( __IMASKL );
		__builtin_sysreg_write( __IMASKL, ( tmp32 | ( 1 << intRQST ) ) );
	}
	else
	{
		tmp32 = __builtin_sysreg_read( __IMASKH );
		__builtin_sysreg_write( __IMASKH, ( tmp32 | ( 1 << ( intRQST - 32 ) ) ) );
	}
}

void HAL_Interrupt_Disable(InterruptRequest_type intRQST){
	unsigned int tmp32;

	if (intRQST < 32){
		tmp32 = __builtin_sysreg_read(__IMASKL);
		__builtin_sysreg_write(__IMASKL, ( tmp32 & ~(1<<intRQST) ));
	}
	else{
		tmp32 = __builtin_sysreg_read(__IMASKH);
		__builtin_sysreg_write(__IMASKH, (tmp32 & ~(1<<(intRQST-32))));
	}

}


void HAL_Interrupt_GlobalEnable(void){
	__builtin_sysreg_write(__SQCTLST, SQCTL_GIE);

}

void HAL_Interrupt_GlobalDisable(void){
	__builtin_sysreg_write(__SQCTLCL, ~SQCTL_GIE);

}


void HAL_Interrupt_IMASKClear(void){
	__builtin_sysreg_write(__IMASKL, 0);
	__builtin_sysreg_write(__IMASKH, 0);
}


void HAL_Interrupt_ILATClear(void){
	__builtin_sysreg_write(__ILATCLL, 0);
	__builtin_sysreg_write(__ILATCLH, 0);
}


void HAL_Interrupt_RqstReset(InterruptRequest_type intRQST){

	if (intRQST < 32){
		__builtin_sysreg_write( __ILATCLL, ~(1<<intRQST) );
	}
	else{
		__builtin_sysreg_write( __ILATCLH, ~(1<<(intRQST-32)) );
	}

}

void HAL_Interrupt_RqstSet(InterruptRequest_type intRQST){

	if (intRQST < 32){
		__builtin_sysreg_write( __ILATSTL, (1<<intRQST) );
	}
	else{
		__builtin_sysreg_write( __ILATSTH, (1<<(intRQST-32)) );
	}

}


