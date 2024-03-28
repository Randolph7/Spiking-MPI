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
#include "sMPI.h"
int main(void)
{

	//write_reg32(0x4000C030, 0xFFFF);
    sMPI_router_trans_test(nonspike, sMPI_East, 1);
	while(1)
    {
	
	}

	//Never reach this point.
    return 0;
}

