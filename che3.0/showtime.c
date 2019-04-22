#include"ourtime.h"
#include"showtime.h"
#include"svga.h"
#define x1 5 //第1个数字x坐标
#define x2 23 //第2个数字x坐标
#define x3 57 //第3个数字x坐标
#define x4 75 //第4个数字x坐标
#define x5 109 //第5个数字x坐标
#define x6 127 //第6个数字x坐标
void showtime()
{
	char h1,h2,m1,m2,s1,s2;
	static char h10,h20,m10,m20,s10,s20;
	h10=h1;
	h20=h2;
	m10=m1;
	m20=m2;
	s10=s1;
	s20=s2;
	timeread(&h1,&h2,&m1,&m2,&s1,&s2);
	SVGA_PartBmp(32,54,432,436,x2+25,370,"pic//num.bmp");
	SVGA_PartBmp(32,54,432,436,x4+25,370,"pic//num.bmp");
	if(h10!=h1)
	{
		if(h1=='0')//小时十位
		{
			SVGA_PartBmp(32,54,23,42,x1,370,"pic//num.bmp");
		}
		else if(h1=='1')
		{
			SVGA_PartBmp(32,54,63,79,x1,370,"pic//num.bmp");
		}
		else if(h1=='2')
		{
			SVGA_PartBmp(32,54,105,122,x1,370,"pic//num.bmp");
		}		
	}
	if(h20!=h2)
	{
		if(h2=='0')//小时个位
		{
			SVGA_PartBmp(32,54,23,42,x2,370,"pic//num.bmp");
		}
		else if(h2=='1')
		{
			SVGA_PartBmp(32,54,63,79,x2,370,"pic//num.bmp");
		}
		else if(h2=='2')
		{
			SVGA_PartBmp(32,54,105,122,x2,370,"pic//num.bmp");
		}
		else if(h2=='3')
		{
			SVGA_PartBmp(32,54,147,164,x2,370,"pic//num.bmp");
		}
		else if(h2=='4')
		{
			SVGA_PartBmp(32,54,191,206,x2,370,"pic//num.bmp");
		}
		else if(h2=='5')
		{
			SVGA_PartBmp(32,54,233,252,x2,370,"pic//num.bmp");
		}
		else if(h2=='6')
		{
			SVGA_PartBmp(32,54,276,293,x2,370,"pic//num.bmp");
		}
		else if(h2=='7')
		{
			SVGA_PartBmp(32,54,318,333,x2,370,"pic//num.bmp");
		}
		else if(h2=='8')
		{
			SVGA_PartBmp(32,54,351,367,x2,370,"pic//num.bmp");
		}
		else if(h2=='9')
		{
			SVGA_PartBmp(32,54,386,403,x2,370,"pic//num.bmp");
		}		
	}
	if(m10!=m1)
	{
		if(m1=='0')//分钟十位
		{
			SVGA_PartBmp(32,54,23,42,x3,370,"pic//num.bmp");
		}
		else if(m1=='1')
		{
			SVGA_PartBmp(32,54,63,79,x3,370,"pic//num.bmp");
		}
		else if(m1=='2')
		{
			SVGA_PartBmp(32,54,105,122,x3,370,"pic//num.bmp");
		}	
		else if(m1=='3')
		{
			SVGA_PartBmp(32,54,147,164,x3,370,"pic//num.bmp");
		}	
		else if(m1=='4')
		{
			SVGA_PartBmp(32,54,191,206,x3,370,"pic//num.bmp");
		}	
		else if(m1=='5')
		{
			SVGA_PartBmp(32,54,233,252,x3,370,"pic//num.bmp");
		}	
		else if(m1=='6')
		{
			SVGA_PartBmp(32,54,276,293,x3,370,"pic//num.bmp");
		}			
	}
	if(m20!=m2)
	{
		if(m2=='0')//分钟个位
		{
			SVGA_PartBmp(32,54,23,42,x4,370,"pic//num.bmp");
		}
		else if(m2=='1')
		{
			SVGA_PartBmp(32,54,63,79,x4,370,"pic//num.bmp");
		}
		else if(m2=='2')
		{
			SVGA_PartBmp(32,54,105,122,x4,370,"pic//num.bmp");
		}
		else if(m2=='3')
		{
			SVGA_PartBmp(32,54,147,164,x4,370,"pic//num.bmp");
		}
		else if(m2=='4')
		{
			SVGA_PartBmp(32,54,191,206,x4,370,"pic//num.bmp");
		}
		else if(m2=='5')
		{
			SVGA_PartBmp(32,54,233,252,x4,370,"pic//num.bmp");
		}
		else if(m2=='6')
		{
			SVGA_PartBmp(32,54,276,293,x4,370,"pic//num.bmp");
		}
		else if(m2=='7')
		{
			SVGA_PartBmp(32,54,318,333,x4,370,"pic//num.bmp");
		}
		else if(m2=='8')
		{
			SVGA_PartBmp(32,54,351,367,x4,370,"pic//num.bmp");
		}
		else if(m2=='9')
		{
			SVGA_PartBmp(32,54,386,403,x4,370,"pic//num.bmp");
		}		
	}	
	
	if(s10!=s1)
	{
		if(s1=='0')//秒钟十位
		{
			SVGA_PartBmp(32,54,23,42,x5,370,"pic//num.bmp");
		}
		else if(s1=='1')
		{
			SVGA_PartBmp(32,54,63,79,x5,370,"pic//num.bmp");
		}
		else if(s1=='2')
		{
			SVGA_PartBmp(32,54,105,122,x5,370,"pic//num.bmp");
		}	
		else if(s1=='3')
		{
			SVGA_PartBmp(32,54,147,164,x5,370,"pic//num.bmp");
		}	
		else if(s1=='4')
		{
			SVGA_PartBmp(32,54,191,206,x5,370,"pic//num.bmp");
		}	
		else if(s1=='5')
		{
			SVGA_PartBmp(32,54,233,252,x5,370,"pic//num.bmp");
		}	
		else if(s1=='6')
		{
			SVGA_PartBmp(32,54,276,293,x5,370,"pic//num.bmp");
		}			
	}
	if(s20!=s2)
	{
		if(s2=='0')//秒钟个位
		{
			SVGA_PartBmp(32,54,23,42,x6,370,"pic//num.bmp");
		}
		else if(s2=='1')
		{
			SVGA_PartBmp(32,54,63,79,x6,370,"pic//num.bmp");
		}
		else if(s2=='2')
		{
			SVGA_PartBmp(32,54,105,122,x6,370,"pic//num.bmp");
		}
		else if(s2=='3')
		{
			SVGA_PartBmp(32,54,147,164,x6,370,"pic//num.bmp");
		}
		else if(s2=='4')
		{
			SVGA_PartBmp(32,54,191,206,x6,370,"pic//num.bmp");
		}
		else if(s2=='5')
		{
			SVGA_PartBmp(32,54,233,252,x6,370,"pic//num.bmp");
		}
		else if(s2=='6')
		{
			SVGA_PartBmp(32,54,276,293,x6,370,"pic//num.bmp");
		}
		else if(s2=='7')
		{
			SVGA_PartBmp(32,54,318,333,x6,370,"pic//num.bmp");
		}
		else if(s2=='8')
		{
			SVGA_PartBmp(32,54,351,367,x6,370,"pic//num.bmp");
		}
		else if(s2=='9')
		{
			SVGA_PartBmp(32,54,386,403,x6,370,"pic//num.bmp");
		}		
	}	
}

