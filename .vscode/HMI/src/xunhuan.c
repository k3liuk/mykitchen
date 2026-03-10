/*********************Please don't delete******************************/
#include "macro.h"
#include "include\macrolib.h"
#include "include\glib.h"

void Macro_Entry( )
{
// TO DO
	short now_sec;
	now_sec = BCD2BIN(LocalWord[3920]);
	
	if(LocalBit[3001] == 1 && LocalBit[3002] == 1 && now_sec != LocalWord[100])
	{
		LocalWord[100] = now_sec;
		LocalWord[101]++;
		if(LocalWord[101] > LocalWord[3003])	//到了开机时间
		{
			LocalWord[101] = 0;
			LocalBit[100] = 1;	//开机指示灯
			LocalBit[3002] = 0;
			LocalBit[3003] = 1;	//执行循环关机标志
		}
	}
	if(LocalBit[3001] == 1 && LocalBit[3003] == 1 && now_sec != LocalWord[100])
	{
		LocalWord[100] = now_sec;
		LocalWord[101]++;
		if(LocalWord[101] > LocalWord[3004])	//到了关机时间
		{
			LocalWord[101] = 0;
			LocalBit[100] = 0;	//开机指示灯
			LocalBit[3003] = 0;
			LocalBit[3002] = 1;	//执行循环开机标志
		}
	}
}
