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

int router_rcv_int_flag;//中断的flag

//定义中断函数
void router_intr()
{	
	router_rcv_int_flag = 1;
}

int main(void)
{

    //init the router interrupt
	enable_int(INT_ROUTER);
    
    // 定义并初始化一个整数数组
    int array[] = {1, 2, 3, 4};
    int *buf = array;

    sMPI_router_trans_test(nonspike, sMPI_East, 1);
    //sMPI_router_bcast_test(buf, sMPI_East, sMPI_South, sMPI_West, sMPI_North);

    while(1)
    {
		if(router_rcv_int_flag)
		{
			router_rcv_int_flag = 0;
			sMPI_router_recv_test();
			char *intstr = "I am in the interrupt!\n";
			print_str(intstr);
		}
    }

    //Never reach this point.
    return 0;
}

