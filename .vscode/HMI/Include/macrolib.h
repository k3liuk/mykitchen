#ifndef _MACROLIB_H
#define _MACROLIB_H
#include<math.h>
#include<stdio.h>
#include <stdlib.h>




short LOBYTE(short source);

short LOWORD(short source);

void FLOAT2ASCII(float value, unsigned char *array);

short BCD2BIN(short source);

short BIN2BCD(short source);

void DEC2ASCII(char *result,short source, char no);//十进制值转换为字符串。

void  HEX2ASCII(int source , char * ret );

short ASCII2DEC(char* source,char no);

short ASCII2HEX(char* source,char no);

short SWAPB(short source);

int   SWAPW(int source);
void  DELAY(int dwMilliseconds);

int HIBYTE(int source);

int HIWORD (int source);

int GETBIT(int source,short bit_pos);

int SETBIT(int source,short pos,char bvalue);

int INVBIT(int source,short bit_pos);

short ADDSUM(char *data,short Len);

unsigned short XORSUM(char *data,unsigned short Len);

unsigned short CRC( char *data,unsigned short Len);

float ASCII2FLOAT(char a[],int len);

char* FLOATASCII(float source);

void delay_ms(int t);

int PUTCHARS(char ComID,char *data,unsigned char Len);

int GETCHARS(char ComID,char *data);

int GETBUFFERLENGTH(char ComID);

int CLEARBUFFER(char ComID);

void Enable(char ComID);
void Disable(char ComID);
void SetRlyOuput0(char onoff);  
void SetRlyOuput1(char onoff);  
void SetRlyOuput2(char onoff); 
void  ScreenOpen(short screenindex);

/*关闭屏幕*/
void DISABLELCD(void);

/*开启屏幕*/
void ENABLELCD(void);

#endif
