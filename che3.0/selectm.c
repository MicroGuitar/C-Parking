#include"svga.h"
#include"mouse.h"
#include"mode.h"
#include<time.h>
#include"timer.h"
#include<stdio.h>
#include<stdlib.h>
void _selectm(int *flag)
{	
	int MouseX, MouseY, oldx, oldy;//鼠标坐标
	int pic[1024], mouseShape[1024];//鼠标和鼠标移动缓存
	char *tStr=NULL;
	time_t t, oldt;
	SVGA_SetMode(0X111);
	SVGA_PartBmp(0,480,0,640,0,0,"sm\\sm.bmp");

	SVGA_ImportBmp( "sm\\mouse.bmp",mouseShape);
	
		/*时间初始化*/
	SVGA_Rectangular(460, 460+16, 0, 8*24, _BLACK);
	t = time(NULL);
	oldt = t;			
	tStr = CurrentTime();
	SVGA_ENtext16(0, 460, tStr, _WHITE);
	SVGA_Rectangular(460, 460+16, 8*24, 8*25, _BLACK);//盖去\n字符	
	
		/*获取鼠标坐标*/ 
	SetMouseBound(0, 640, 0, 480);
    MouseX=GetMouseX();
    MouseY=GetMouseY();
	oldx=MouseX;
	oldy=MouseY;
	SVGA_SaveArea(MouseX,MouseY,pic);
    while(1)
	{		
        MouseX=GetMouseX();
        MouseY=GetMouseY();	
        if((oldx!=MouseX)||(oldy!=MouseY))
		{	
			/* 处理鼠标移动 */		
			SVGA_RestoreArea(oldx,oldy,pic);		
			SVGA_SaveArea(MouseX,MouseY,pic);		
			SVGA_ImgBlackMask(MouseX,MouseY,mouseShape);			
		
			oldx=MouseX;
			oldy=MouseY;	
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,140,170,430,480))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			*flag=1;
			break;//进入车型选择
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,179,208,430,480))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			*flag=7;
			break;//进入取车楼层选择
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,295,325,430,480))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			*flag=16;
			break;//进入管理员选择
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,18,39,3,43))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			resetinfo();//重置
			break;
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,11,57,595,631))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			exit(1);//退出
			break;
		}
		/*************显示时间*************************/

		t = time(NULL);//获取当前时间
		if(t!=oldt)//时间要更改
		{
			SVGA_Rectangular(460, 460+16, 0, 8*24, _BLACK);
			tStr = CurrentTime();
			SVGA_ENtext16(0, 460, tStr, _WHITE);
			SVGA_Rectangular(460, 460+16, 8*24, 8*25, _BLACK);//盖去\n字符
			oldt = t;
		}
	}	
}
	int CheckArea(int MouseX,int MouseY, int top, int bottom, int left, int right) //判断是否处于判定区域,参数：坐标XY，判定位置 X0,X1,Y0,Y1
{
    if(( MouseX >= left && MouseX <= right ) && ( MouseY >= top && MouseY <= bottom ))
    return 1;
    else
    return 0;
}