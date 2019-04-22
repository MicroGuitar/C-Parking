#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"timer.h"
#include"svga.h"

char *CurrentTime(void)
{
	time_t t;
	char *pt;
	
	t = time(NULL);
	pt = ctime(&t);
	return pt;
}

void Displaytime(time_t t, int x, int y)
{
	int min=0,sec=0;
	char str[10],str1[3];
	min= (int)t/60;
	sec= (int)t%60;
	itoa(min,str,10);
	strcat(str,":");
	itoa(sec,str1,10);
	strcat(str,str1);
	SVGA_Rectangular(y, y+16, x, x+6*8, _GREY);
	SVGA_ENtext16(x, y, str, _RED);		
}