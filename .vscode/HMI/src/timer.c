/*********************Please don't delete******************************/
#include "macro.h"
#include "include\macrolib.h"
#include "include\glib.h"

void Macro_Entry( )
{
// TO DO
	int year,month,day,hour,min;
	
	//从内部特定地址中获取当前年、月、日、时、分、秒时间
	year = BCD2BIN(LocalWord[3925]);
	month = BCD2BIN(LocalWord[3924]);
	day = BCD2BIN(LocalWord[3923]);
	hour   = BCD2BIN(LocalWord[3922]);
        min    = BCD2BIN(LocalWord[3921]);
	
	//判断第一段定时时间是否到达
	if(year == LocalWord[3000] && month == LocalWord[3001] && day == LocalWord[3002] &&\
		hour == LocalWord[3003] &&min ==LocalWord[3004] ) 
		{
			//定时时间到，亮led1；
			led1 = 1;
		}
	else
		led1 = 0;
	
	//判断第二段定时时间是否到达
	if(year == LocalWord[3010] && month == LocalWord[3011] && day == LocalWord[3012] &&\
		hour == LocalWord[3013] &&min ==LocalWord[3014] ) 
	{
		//定时时间到，亮led1；
		led2 = 1;
	}
	else
		led2 = 0;
	
}
