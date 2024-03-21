/*
 ============================================================================
 Name        : sMPI.c
 Author      : Randolph
 Version     :
 Copyright   : Your copyright notice
 Description : sMPI Functions
 ============================================================================
 */
#include <sMPI.h>
#include "common.h"
#include <stdarg.h>
#include <stdio.h>

int print_str( char *s)
{
	while(*s)
	{
		putchar(*s++);
	}
	return 0;
}

int sMPI_router_trans_test(
//  const void *buf,        //要发送的数据
    int type,                //包的类型
    int dest,                //目的地
    int depth               //数据深度
    )
{
	// int a;					//未填充的buff和dest操作
	// if(dest)
	// {
	// 	a = sizeof(buf);
	// }
    uint32_t rdata;
    uint32_t wdata;
    long long y = 0xA000000000000000; // 64位数y
    long long mask;
    long long extended_x;

    // 读取操作
    rdata = read_reg32((reg32_t)LBR_BASE);//4000 0000
    
    // 写入操作
    if(type == spike)
    {
        //
    }
    else if(type == nonspike)
    {
        // 触发CPU传输
        write_reg32((reg32_t)LBR_REG_ADDR(TRANS_BASE_ADDR), 0x08);//4000 C030             

    /*******************第一拍*******************/
        switch(dest)
        {
            case sMPI_East:
                mask = ~(((1ULL << 13) - 1) << 28);
                extended_x = (long long)depth << (64 - 13);
                y = (y & mask) | extended_x;
                break;

            case sMPI_West:
                mask = ~(((1ULL << 13) - 1) << 28);
                extended_x = (long long)(-depth) << (64 - 13);
                y = (y & mask) | extended_x;
                break;

            case sMPI_North:
                mask = ~(((1ULL << 13) - 1) << 42);
                extended_x = (long long)depth << (64 - 13);
                y = (y & mask) | extended_x;
                break;
                
            case sMPI_South:
                mask = ~(((1ULL << 13) - 1) << 42);
                extended_x = (long long)(-depth) << (64 - 13);
                y = (y & mask) | extended_x;
                break;
        }

        // 写入SRAM低32位
        // 1100 0000 0000 0000 0000 0000 0000 0000
        write_reg32((reg32_t)LBR_SRAM_ADDR(LBR_TRANS_SRAM_0), (unsigned int)y);//4000 A000        

        // 写入SRAM高32位
        // 1010 0000 0000 0000 1100 0000 0000 0000
        write_reg32((reg32_t)(LBR_SRAM_ADDR(LBR_TRANS_SRAM_0)+4), (y >> 32));//4000 A004
    
        // 数据处理
        wdata = rdata & 0x00000FFF;                      

    /*******************第二拍*******************/
        // 写入SRAM低32位
        write_reg32((reg32_t)(LBR_SRAM_ADDR(LBR_TRANS_SRAM_0)+8), wdata);//4000 A008

        //读取操作
        rdata = read_reg32((reg32_t)(LBR_BASE+4));//4000 0004

        // 数据处理
        wdata = rdata & 0x00000FFF;    

        //写入SRAM高32位
        write_reg32((reg32_t)(LBR_SRAM_ADDR(LBR_TRANS_SRAM_0)+12), wdata);//4000 A00C

        // 另一个特定操作
        write_reg32((reg32_t)LBR_REG_ADDR(TRANS_BASE_ADDR), 0x00004050);//4000 C030

    }
    return 0;
}

int sMPI_router_bcast_test(
//  const void *buf,        //要发送的数据
    int type,                //包的类型
    int depth,               //数据深度
    int numDests,            //多个目的地
    ...
    )
{
    if(type == spike)
    {

    }
    else if(type == nonspike)
    {
        va_list args;
        va_start(args, numDests); // 初始化 args 来检索额外的参数

        for (int i = 0; i < numDests; i++) 
        {
            int dest = va_arg(args, int); // 获取下一个参数（目的地地址）
            sMPI_router_trans_test(type, dest, depth);
        }
    }

    return 0;
}

int sMPI_router_recv_test()
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

     write_reg32(0x40000000, rdata); 
    //Now read the mem
    //1111 1111 1111 1111 1111 0111 1111 1111 = FFFF F7FF
    //write_reg32((reg32_t)LBR_REG_ADDR(RECV_BASE_ADDR), rdata & 0xfffff7ff);        //第11bit的mask置0

    // if(rdata_rcv_avail == 1)
    // {
    //     for(uint32_t i = 0; i < rdata_rcv_len; i++)
    //     {
    //         // 读RECV的SRAM0：4000 8000
    //         rdata_low = read_reg32(LBR_SRAM_ADDR(LBR_RECV_SRAM_0) + i*8);        //写mem低位
    //         rdata_high = read_reg32(LBR_SRAM_ADDR(LBR_RECV_SRAM_0) + i*8 + 4);    //写mem高位
    //         write_reg32(0x40000000+i*8, rdata_low);   
    //         write_reg32(0x40000004+i*8, rdata_high); 
    //     }
    // }

    // else if(rdata_rcv_avail == 2 || rdata_rcv_avail == 3)
    // {
    //     for(uint32_t i = 0; i < rdata_rcv_len; i++)
    //     {
    //         // 读RECV的SRAM1：4000 9000
    //         rdata_low = read_reg32(LBR_SRAM_ADDR(LBR_RECV_SRAM_1) + i*8);        //写mem低位
    //         rdata_high = read_reg32(LBR_SRAM_ADDR(LBR_RECV_SRAM_1) + i*8 + 4);    //写mem高位
    //         write_reg32(0x40000000+i*8, rdata_low);   
    //         write_reg32(0x40000004+i*8, rdata_high); 
    //     }
    // }

    // else
    // {
    // 	// char *wrong = "No RAM to READ!.\n";
    // 	// print_str(wrong);
    // }
   // write_reg32((reg32_t)LBR_REG_ADDR(RECV_BASE_ADDR), rdata | 0x00000800);        //第11bit的mask置1
    //0000 0000 0000 0000 0000 1000 0000 0000 = 0000 0800
     

    return 0;
}
