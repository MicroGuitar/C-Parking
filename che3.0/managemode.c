#include"svga.h"
#include"mouse.h"
#include<stdlib.h>
#include"mode.h"
#include"move.h"
#include"shuru.h"
#include"showcar.h"
void managem(int *flag)//显示车库所有信息
{
	int MouseX, MouseY, oldx, oldy,j;//鼠标坐标
	int pic[1024], mouseShape[1024];//鼠标和鼠标移动缓存
	SVGA_SetMode(0X111);
	SVGA_PartBmp(0,480,0,640,0,0,"sm\\manager.bmp");
	SVGA_ImportBmp( "sm\\mouse.bmp",mouseShape);
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
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,104,159,410,527))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			*flag=11;//显示车库所有信息
			break;
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,153,215,167,302))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			*flag=12;//进入按车位查询
			break;
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,316,365,23,134))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			*flag=17;//进入收费更改
			break;
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,251,350,289,359))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			*flag=18;//进入管理员密码更改
			break;
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,428,457,18,68))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			*flag=0;//返回模式选择
			break;
		}
	}
}
		
		
		
		
		
		
		