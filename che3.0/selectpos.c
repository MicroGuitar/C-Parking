#include"svga.h"
#include"mouse.h"
#include<stdlib.h>
#include"mode.h"
#include"showtime.h"
int selectpos()
{
	int MouseX, MouseY, oldx, oldy,j;//鼠标坐标
	int pic[1024], mouseShape[1024];//鼠标和鼠标移动缓存
	int i=1;

	SVGA_ImportBmp( "sm\\mouse.bmp",mouseShape);

		/*获取鼠标坐标*/
	SetMouseBound(0, 640, 0, 480);
	MouseX=GetMouseX();
	MouseY=GetMouseY();
	oldx=MouseX;
	oldy=MouseY;
	SVGA_SaveArea(MouseX,MouseY,pic);
	while(1)
	{
		showtime();
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
		if(1==i)
		{
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,426,457,4,59))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				return 0;//返回
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,90,155,200,318))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				return 1;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,167,253,192,322))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				return 2;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,255,343,192,322))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				return 3;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,344,426,192,322))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				return 4;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,79,165,472,600))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				return 5;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,167,253,472,600))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				return 6;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,255,343,472,600))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				return 7;//停车函数(楼层，检查，车位)
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,344,426,472,600))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				return 8;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,428,480,480,596))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				return 9;//上楼
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,439,480,175,428))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				return 10;//下楼
			}
		}
	}
}