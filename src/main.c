/*
 ============================================================================
 Name        : main.c
 Author      : Randolph
 Version     :
 Copyright   : Your copyright notice
 Description : sMPI Main File
 ============================================================================
*/


/*
============================================================================
Name        : Header File
============================================================================
*/
#include <stdio.h>
#include "stdint.h"
#include <stdarg.h>

/*
============================================================================
Name        : Variables
============================================================================
*/
int router_rcv_int_flag;//中断的flag

/*
============================================================================
Name        : Common 
============================================================================
*/

typedef volatile unsigned char  reg8_t;
typedef volatile unsigned short reg16_t;
typedef volatile unsigned int   reg32_t;

typedef	volatile unsigned char           u8;
typedef volatile unsigned short          u16;
typedef volatile unsigned int            u32;
typedef volatile unsigned long long      u64;

void _close_r()
{

}

void _fstat_r()
{

}

void _isatty_r()
{

}

void _lseek_r()
{

}  

void _read_r()
{

}

void _write_r()
{

} 

void write_reg32(uint32_t addr,uint32_t data)
{
  *((volatile uint32_t*)(addr)) = data;
}


uint32_t read_reg32(uint32_t addr)
{
  uint32_t rdata;
  rdata = *((volatile uint32_t*)(addr));
  return rdata;
}

int print_str( char *s)
{
	while(*s)
	{
		putchar(*s++);
	}
	return 0;
}

/*
============================================================================
Name        : Interrupt 
============================================================================
*/
#define RV_PIC_BASE_ADDR       0xe0000000

#define RV_PIC_MEIPL(n)        (RV_PIC_BASE_ADDR | 0x0004 + (0x04*(n)))
#define RV_PIC_MEIE(n)         (RV_PIC_BASE_ADDR | 0x2004 + (0x04*(n)))
#define RV_PIC_MEIPT           (RV_PIC_BASE_ADDR | 0x3004)

#define INT_ROUTER				   32


#define MCAUSE_INT         0x80000000
#define MCAUSE_CAUSE       0x7FFFFFFF
#define IRQ_S_SOFT   1
#define IRQ_H_SOFT   2
#define IRQ_M_SOFT   3
#define IRQ_S_TIMER  5
#define IRQ_H_TIMER  6
#define IRQ_M_TIMER  7
#define IRQ_S_EXT    9
#define IRQ_H_EXT    10
#define IRQ_M_EXT    11
#define IRQ_COP      12
#define IRQ_HOST     13
#define CONFIG_TIMER_NUM    1  //ORI 4
#define CONFIG_USART_NUM    2  //ori 1
#define CONFIG_GPIO_NUM     8
#define CONFIG_GPIO_PIN_NUM 18

#define read_csr(reg) ({ unsigned long __tmp; asm volatile ("csrr %0, " #reg : "=r"(__tmp)); __tmp; })

#define write_csr(reg, val) ({ asm volatile ("csrw " #reg ", %0" :: "i"(val));})

#define write_csr_ns(reg, val) ({ asm volatile ("csrw " #reg ", %0" :: "r"(val));})

void __attribute__((weak))router_intr();
void __attribute__((weak))apb_uart_intr();
void __attribute__((weak))apb_timer_0_intr();

void pic_enable_interrupt(uint32_t int_num) {
  write_reg32(RV_PIC_MEIE(int_num), 0x1);
}

void pic_disable_interrupt(uint32_t int_num) {
  write_reg32(RV_PIC_MEIE(int_num), 0x0);
}

void pic_set_threshold(uint32_t prior) {
  write_reg32(RV_PIC_MEIPT, prior);
}

void pic_set_priority(uint32_t int_num, uint32_t prior) {
  write_reg32(RV_PIC_MEIPL(int_num), prior);
}

void enable_int(uint32_t int_num) {
  // Disable interrupt globally
  __asm__("csrrci x0, mstatus, 0x8;\n");
  // Disable external interrupt
  __asm__("li a0,(1<<11);\n");
  pic_set_threshold(1);
  pic_set_priority(int_num, 7);
  __asm__("csrrc zero,mie,a0;\n");
  pic_enable_interrupt(int_num);
  // Enable external interrupt
  __asm__(
    "li a0,(1<<11);\n"
    "csrrs zero,mie,a0;\n"
  );
  // Enable interrupt globally
  __asm__("csrrs x0, mstatus, 0x8;\n");
}

void disable_int(uint32_t int_num) {
  // Disable interrupt globally
  __asm__("csrrci x0, mstatus, 0x8;\n");
  // Disable external interrupt
  __asm__("li a0,(1<<11);\n");
  pic_set_threshold(1);
  pic_set_priority(int_num, 7);
  __asm__("csrrc zero,mie,a0;\n");
  pic_disable_interrupt(int_num);
  // Enable external interrupt
  __asm__(
    "li a0,(1<<11);\n"
    "csrrs zero,mie,a0;\n"
  );
  // Enable interrupt globally
  __asm__("csrrs x0, mstatus, 0x8;\n");
}

void handle_m_ext_interrupt() 
{
  write_csr(0xBCA, 1);                           // meicpct
  uint32_t int_num = (read_csr(0xFC8) >> 2) - 1; // meihap
//  printf("\nint_num is %x\n", int_num);          // For debug
  switch (int_num) {
    case INT_ROUTER			  :
      router_intr();
      break;

    default:
      break;
  }
}

uint32_t handle_trap(uint32_t mcause, uint32_t epc) {
  if (0){
    // External Machine-Level interrupt from PLIC
  } else if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE) == IRQ_M_EXT)) {
    handle_m_ext_interrupt();
    // External Machine-Level interrupt from PLIC
  } else if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE) == IRQ_M_TIMER)){
    //handle_m_time_interrupt();
  }
  //else {
  //  write(1, "trap\n", 5);
  //  _exit(1 + mcause);
  //}
  return epc;
}

//定义中断函数
void router_intr()
{	
	router_rcv_int_flag = 1;
}

/*
============================================================================
Name        : MPI 
============================================================================
*/
//调用地址
#define LBR_REG_ADDR(n)                       (LBR_BASE_REG_ADDR | n)
#define LBR_SRAM_ADDR(n)                      (LBR_BASE | n)
//寄存器基础地址定义
#define LBR_BASE                              0x40000000
#define LBR_BASE_REG_ADDR                     0x4000C000

//CPU_TRANS和CPU_RCV寄存器地址定义
#define TRANS_BASE_ADDR                       0x30
#define RECV_BASE_ADDR                        0x34 

//Others
#define LBR_DST                               0x00
#define LBR_SRC                               0x04
#define LBR_LOCAL                             0x08
#define LB_XY_SRC_CPU                         0x0C
#define SP_DATA_LOW                           0x10
#define SP_DATA_HIGH                          0x14
#define LBR_BASE_ADDR                         0x18
#define LBR_XY_SRC                            0x20
#define CPU_CODE                              0x24
#define CPU_STATUS                            0x28
#define TEST_REG                              0x2C  

//TRANS硬件SRAM地址
#define LBR_TRANS_SRAM_0                      0xA000
#define LBR_TRANS_SRAM_1                      0xffff

//RECV硬件SRAM地址
#define LBR_RECV_SRAM_0                 	    0x8000
#define LBR_RECV_SRAM_1                       0x9000

#define sMPI_East							                0
#define sMPI_South                            1
#define sMPI_West                             2
#define sMPI_North							              3

#define spike                                 0
#define nonspike                              1

//基本测试收发
int sMPI_router_trans_test(
//  const void *buf,         //要发送的数据
    int type,                //包的类型
    int dest,                //目的地
	int depth				 //深度
    );

int sMPI_router_bcast_test(
//  const void *buf,        //要发送的数据
    int type,                //包的类型
    int depth,               //数据深度
    int numDests,            //多个目的地
    ...
    );

int sMPI_router_recv_test();

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
        }
    }

    else if(rdata_rcv_avail == 2 || rdata_rcv_avail == 3)
    {
        for(uint32_t i = 0; i < rdata_rcv_len; i++)
        {
            // 读RECV的SRAM1：4000 9000
            rdata_low = read_reg32(LBR_SRAM_ADDR(LBR_RECV_SRAM_1) + i*8);        //写mem低位
            rdata_high = read_reg32(LBR_SRAM_ADDR(LBR_RECV_SRAM_1) + i*8 + 4);    //写mem高位
        }
    }

    else
    {
    	// char *wrong = "No RAM to READ!.\n";
    	// print_str(wrong);
    }
   
    //0000 0000 0000 0000 0000 1000 0000 0000 = 0000 0800
    write_reg32((reg32_t)LBR_REG_ADDR(RECV_BASE_ADDR), rdata | 0x00000800);        //第11bit的mask置1

    return 0;
}

/*
============================================================================
Name        : Main 
============================================================================
*/
int main(void)
{

    //init the router interrupt
	  enable_int(INT_ROUTER);
    
    // 定义并初始化一个整数数组
    //int array[] = {1, 2, 3, 4};
    //int *buf = array;

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

