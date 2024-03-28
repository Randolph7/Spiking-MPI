/*
 ============================================================================
 Name        : task2_send.c
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

//中断的flag
int router_rcv_int_flag = 0;

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

    }
   
	write_reg32((reg32_t)LBR_REG_ADDR(RECV_BASE_ADDR), rdata | 0x00000800);        //第11bit的mask置1
    //0000 0000 0000 0000 0000 1000 0000 0000 = 0000 0800
     
	router_rcv_int_flag = 1;
}

int main(void)
{
    //清除main的中断
    write_reg32(0x1040000c, 0);

    //init the router interrupt
    enable_int(INT_ROUTER);
	
	//send func
    sMPI_router_trans_test(nonspike,sMPI_East,1);

    while(1)
    {
		if(router_rcv_int_flag)
		{
			router_rcv_int_flag = 0;

            //verify the result by observing from server
			write_reg32(0x4000C000, 0xFF);
		}
    }

    //Never reach this point.
    return 0;
}

