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
	uint32_t rdata;
	uint32_t rdata_low;
	uint32_t rdata_high;
	uint32_t rdata_rcv_len;
	uint32_t rdata_rcv_avail;
    // write_reg32(0x40000000, 0x1234);
    rdata = read_reg32((reg32_t)LBR_REG_ADDR(RECV_BASE_ADDR));//4000 C034

	  rdata_rcv_avail = (rdata>>9) & 0x00000003;

    rdata_rcv_len = (rdata) & 0x000001ff;

    //Now read the mem
    //1111 1111 1111 1111 1111 0111 1111 1111 = FFFF F7FF
    write_reg32((reg32_t)LBR_REG_ADDR(RECV_BASE_ADDR), rdata & 0xfffff7ff);        //第11bit的mask置0

    if(rdata_rcv_avail == 1)
    {
        for(uint32_t i = 0; i < rdata_rcv_len; i++)
        {
            // 读RECV的SRAM0：4000 8000
            rdata_low = read_reg32(LBR_SRAM_ADDR(LBR_RECV_SRAM_0) + i*8);        //写mem低位
            rdata_high = read_reg32(LBR_SRAM_ADDR(LBR_RECV_SRAM_0) + i*8 + 4);    //写mem高位
            write_reg32(0x40000000+i*8, rdata_low);   
            write_reg32(0x40000004+i*8, rdata_high); 
        }
    }

    else if(rdata_rcv_avail == 2 || rdata_rcv_avail == 3)
    {
        for(uint32_t i = 0; i < rdata_rcv_len; i++)
        {
            // 读RECV的SRAM1：4000 9000
            rdata_low = read_reg32(LBR_SRAM_ADDR(LBR_RECV_SRAM_1) + i*8);        //写mem低位
            rdata_high = read_reg32(LBR_SRAM_ADDR(LBR_RECV_SRAM_1) + i*8 + 4);    //写mem高位
            write_reg32(0x40000000+i*8, rdata_low);   
            write_reg32(0x40000004+i*8, rdata_high); 
        }
    }

    else
    {
    	// char *wrong = "No RAM to READ!.\n";
    	// print_str(wrong);
    }
   write_reg32((reg32_t)LBR_REG_ADDR(RECV_BASE_ADDR), rdata | 0x00000800);        //第11bit的mask置1
    //0000 0000 0000 0000 0000 1000 0000 0000 = 0000 0800
     
	router_rcv_int_flag = 1;
  int i = rand();

}

int main(void)
{

    //init the router interrupt
    write_reg32(0x40000000, 0xFFFFBBBB);//
    write_reg32(0x1040000c, 0);//清除main的中断

    enable_int(INT_ROUTER);
    write_reg32(0x40000000, 0xAA00);//
    // 定义并初始化一个整数数组
//    int array[] = {1, 2, 3, 4};
 //   int *buf = array;
    // sMPI_router_trans_test(nonspike, sMPI_East, 1);
    //sMPI_router_bcast_test(buf, sMPI_East, sMPI_South, sMPI_West, sMPI_North);
	enable_int(INT_ROUTER);


    while(1)
    {
		if(router_rcv_int_flag)
		{
			router_rcv_int_flag = 0;
       write_reg32(0x40000000, 0x1234);
			sMPI_router_recv_test();

			//char *intstr = "I am in the interrupt!\n";
			//print_str(intstr);
      write_reg32(0x4000C000, 0xFF);//
		}
    }

    //Never reach this point.
    return 0;
}

