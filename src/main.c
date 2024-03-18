/*
 ============================================================================
 Name        : main.c
 Author      : Randolph
 Version     :
 Copyright   : Your copyright notice
 Description : sMPI Main File
 ============================================================================
 */
#include "pic.h"
#include <sMPI.h>
#include "common.h"
#include <stdlib.h>
int router_rcv_int_flag;//中断的flag

//定义中断函数
void router_intr()
{	
	router_rcv_int_flag = 1;
  int i = rand();
}

int main(void)
{

    //init the router interrupt
	enable_int(INT_ROUTER);


    while(1)
    {
		if(router_rcv_int_flag)
		{
			router_rcv_int_flag = 0;
			sMPI_router_recv_test();
      write_reg32(0x4000C000, 0xFF);//
		}
    }

    //Never reach this point.
    return 0;
}

