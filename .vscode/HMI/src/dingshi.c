/*********************Please don't delete******************************/
#include "macro.h"
#include "include\macrolib.h"
#include "include\glib.h"

void Macro_Entry( )
{
// TO DO
	short now_min,now_hour,now_week;
	now_min = BCD2BIN(LocalWord[3921]);
	now_hour = BCD2BIN(LocalWord[3922]);
	now_week = BCD2BIN(LocalWord[3926]);
	if(LocalBit[3000] == 1 && now_min == LocalWord[3000] && now_hour == LocalWord[3001] && now_week == LocalWord[3002])
	{
		if(LocalBit[3001] == 0)
		{
			LocalBit[3001] = 1;	//执行循环标志
			LocalBit[3002] = 1;	//执行开机标志
		}
	}
	else if(LocalBit[3000] == 0)
	{
		LocalWord[101] =0;	//时间清零
		LocalBit[3001] = 0;	//执行循环标志
		LocalBit[3002] = 0;	//执行开机标志
		LocalBit[3003] = 0;	//执行关机标志
	}
}
//根本312