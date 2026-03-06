/*******************************************************************************
*нд╪Ч:uart.h																   *
*******************************************************************************/
#ifndef __UART_H__
#define __UART_H__
#ifdef __cplusplus
extern "C" {
#endif

#define	DEFAULT_BPS			(115200)

#define RXTIMEOUT_SOURCE_DATA		0x00000000
#define RXTIMEOUT_SOURCE_STATUS		0x02000000

/*UART STOP BIT*/
#define UART_STOPS_1						((u32)0x00000000)
#define UART_STOPS_2						((u32)0x00000008)
#define IS_UART_STOPBITS(STOPBITS) 	       (((STOPBITS) == UART_STOPS_1)   || \
                                    		((STOPBITS) == UART_STOPS_2))

/*UART PARITY BIT*/
#define UART_Parity_None               		((u32)0x00000000)
#define UART_Parity_Odd              		((u32)0x00000002)
#define UART_Parity_Even             		((u32)0x00000006)
#define UART_Parity_EPS_0            		((u32)0x00000082)
#define UART_Parity_EPS_1            		((u32)0x00000086)
#define IS_UART_PARITY(PARITY)   		   (((PARITY) == UART_Parity_None)    || \
											((PARITY) == UART_Parity_Odd)     || \
                                 			((PARITY) == UART_Parity_Even)    || \
											((PARITY) == UART_Parity_EPS_0)   || \
											((PARITY) == UART_Parity_EPS_1))

/*UART WORD LENGTH*/
#define UART_WordLength_5b           		((u32)0x00000000)
#define UART_WordLength_6b           		((u32)0x00000020)
#define UART_WordLength_7b           		((u32)0x00000040)
#define UART_WordLength_8b           		((u32)0x00000060)
#define IS_UART_WORD_LENGTH(LENGTH) 	   	   (((LENGTH) == UART_WordLength_5b) || \
                                      		((LENGTH) == UART_WordLength_6b) || \
											((LENGTH) == UART_WordLength_7b) || \
											((LENGTH) == UART_WordLength_8b))

/*APPUART INTERRUPT MODE*/
#define UART_INT_MODE_RXI					((u32)0x00100000)
#define UART_INT_MODE_TXI					((u32)0x00200000)
#define UART_INT_MODE_RTI					((u32)0x00400000)
#define UART_INT_MODE_FEI					((u32)0x00800000)
#define UART_INT_MODE_PEI					((u32)0x01000000)
#define UART_INT_MODE_BEI					((u32)0x02000000)
#define UART_INT_MODE_OEI					((u32)0x04000000)
#define UART_INT_MODE_TFEI					((u32)0x08000000)
#define IS_UART_INT_MODE(MODE) 	       	   ((((MODE) & 0x0FF00000) != 0) && (((MODE) & 0xF00FFFFF) == 0))

/*APPUART INTERRUPT FIFO LEVEL SELECT*/
#define UART_RXIFL_SEL_2						((u32)0x00000000)
#define UART_RXIFL_SEL_4						((u32)0x00100000)
#define UART_RXIFL_SEL_8						((u32)0x00200000)
#define UART_RXIFL_SEL_12						((u32)0x00300000)
#define UART_RXIFL_SEL_14						((u32)0x00400000)
#define UART_TXIFL_SEL_2						((u32)0x00000000)
#define UART_TXIFL_SEL_4						((u32)0x00010000)
#define UART_TXIFL_SEL_8						((u32)0x00020000)
#define UART_TXIFL_SEL_12						((u32)0x00030000)
#define UART_TXIFL_SEL_14						((u32)0x00040000)
#define IS_UART_RXIFL_SEL(VAL) 	       	   		(((VAL) == UART_RXIFL_SEL_2)   || \
	                                    		((VAL) == UART_RXIFL_SEL_4)   || \
	                                    		((VAL) == UART_RXIFL_SEL_8)	 || \
	                                    		((VAL) == UART_RXIFL_SEL_12)	 || \
	                                    		((VAL) == UART_RXIFL_SEL_14))

#define IS_UART_TXIFL_SEL(VAL) 	       	   		(((VAL) == UART_TXIFL_SEL_2)   || \
	                                    		((VAL) == UART_TXIFL_SEL_4)   || \
	                                    		((VAL) == UART_TXIFL_SEL_8)	 || \
	                                    		((VAL) == UART_TXIFL_SEL_12)	 || \
	                                    		((VAL) == UART_TXIFL_SEL_14))

#define ASM9260_UART_RIMIS				(1<<0)
#define ASM9260_UART_CTSMIS				(1<<1)
#define ASM9260_UART_DCDMIS			(1<<2)
#define ASM9260_UART_DSRMIS				(1<<3)
#define ASM9260_UART_RXIS				(1<<4)
#define ASM9260_UART_TXIS				(1<<5)
#define ASM9260_UART_RTIS				(1<<6)
#define ASM9260_UART_FEIS				(1<<7)
#define ASM9260_UART_PEIS				(1<<8)
#define ASM9260_UART_BEIS				(1<<9)
#define ASM9260_UART_OEIS				(1<<10)
#define ASM9260_UART_TFEIS				(1<<11)
#define ASM9260_UART_ABEO				(1<<12)
#define ASM9260_UART_ABTO				(1<<13)
#define ASM9260_UART_RIMIEN				(1<<16)

//int UartInit(u32 nBaudrate, u32 nData, u32 nParity, u32 nStops);
void serial_putc(char data);
int serial_getc(char * pD);
int UartSendChars(char* pD, u16 nLen);

#ifdef __cplusplus
}
#endif
#endif

