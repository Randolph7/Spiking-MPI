/*
 ============================================================================
 Name        : test.c
 Author      : Randolph
 Version     :
 Copyright   : Your copyright notice
 Description : sMPI Test File
 ============================================================================
 */
#include "common.h"

int main(void)
{

	write_reg32(0x4000C000, 0xFF);//
	write_reg32(0x4000C000, 0x10);//
	write_reg32(0x4000C000, 0x11);//
	write_reg32(0x4000C000, 0x00);//

	while(1)
    {
	
	}

	//Never reach this point.
    return 0;
}

