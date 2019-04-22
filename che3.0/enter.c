#include"svga.h"
#include"mouse.h"
#include<stdlib.h>
#include"mode.h"
#include"move.h"
#include"shuru.h"
#include"showcar.h"
#include"showtime.h"
#include"showinfo.h"
#include"tingche.h"
void Enter(int *flag,int *k,int i,int *from)
{
	int MouseX, MouseY, oldx, oldy,j;//鼠标坐标
	int pic[1024], mouseShape[1024];//鼠标和鼠标移动缓存
	SVGA_SetMode(0X111);
	if(*from==0)//上一楼动画
	{
		if(1==i)//选择楼层图
		{
			SVGA_PartBmp(0,480,0,640,0,0,"pic\\1f.bmp");
			showcar(i);
			chewei();//剩余车位
		}
		if(2==i)//选择楼层图
		{
			SVGA_PartBmp(0,480,0,640,0,0,"pic\\2f.bmp");
			showcar(i);
			chewei();//剩余车位
		}
		if(3==i)//选择楼层图
		{
			SVGA_PartBmp(0,480,0,640,0,0,"pic\\3f.bmp");
			showcar(i);
			chewei();//剩余车位
		}
		switch(*k)
		{
			case 0:
				move11(0);
				break;
			case 1:
				move11(1);
				break;
			case 2:
				move11(2);
				break;
		}
	}
	if(*from==2)//上二楼动画
	{
		SVGA_PartBmp(0,480,0,640,0,0,"pic\\1f.bmp");
		showcar(1);
		chewei();//剩余车位
		switch(*k)
		{
			case 0:
				move11(0);
				move9(0);
				break;
			case 1:
				move11(1);
				move9(1);
				break;
			case 2:
				move11(2);
				move9(1);
				break;
		}
		SVGA_PartBmp(0,480,0,640,0,0,"pic\\2f.bmp");
		showcar(i);
		chewei();//剩余车位
		switch(*k)
		{
			case 0:
				move11(0);
				break;
			case 1:
				move11(1);
				break;
			case 2:
				move11(2);
				break;
		}
	}
	if(*from==3)//上三楼动画
	{
		SVGA_PartBmp(0,480,0,640,0,0,"pic\\1f.bmp");
		showcar(1);
		chewei();//剩余车位
		switch(*k)
		{
			case 0:
				move11(0);
				move9(0);
				break;
			case 1:
				move11(1);
				move9(1);
				break;
			case 2:
				move11(2);
				move9(2);
				break;
		}
		SVGA_PartBmp(0,480,0,640,0,0,"pic\\2f.bmp");	
		showcar(2);
		chewei();//剩余车位
		switch(*k)
		{
			case 0:
				move11(0);
				move9(0);
				break;
			case 1:
				move11(1);
				move9(1);
				break;
			case 2:
				move11(2);
				move9(2);
				break;
		}
		SVGA_PartBmp(0,480,0,640,0,0,"pic\\3f.bmp");
		showcar(i);
		chewei();//剩余车位
		switch(*k)
		{
			case 0:
				move11(0);
				break;
			case 1:
				move11(1);
				break;
			case 2:
				move11(2);
				break;
		}
	}
	if(*from==1)//下楼动画
	{
		if(1==i)//选择楼层图
		{
			SVGA_PartBmp(0,480,0,640,0,0,"pic\\1f.bmp");
			showcar(i);
			chewei();//剩余车位
		}
		if(2==i)//选择楼层图
		{
			SVGA_PartBmp(0,480,0,640,0,0,"pic\\2f.bmp");
			showcar(i);
			chewei();//剩余车位
		}
		if(3==i)//选择楼层图
		{
			SVGA_PartBmp(0,480,0,640,0,0,"pic\\3f.bmp");	
			showcar(i);
			chewei();//剩余车位
		}
		switch(*k)
		{
			case 0:
				move12(0);
				break;
			case 1:
				move12(1);
				break;
			case 2:
				move12(2);
				break;
		}
	}
	SVGA_ImportBmp( "sm\\mouse.bmp",mouseShape);
	showcar(i);
	chewei();//剩余车位
	/*SVGA_PartBmp(30,130,27,73,375,300,"sm\\che.bmp");*/

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
		if(1==i)//一楼
		{
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,428,480,480,596))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				move9(*k);
				*flag=5;//到二楼
				*from=0;
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,90,155,200,318))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(1,*k,1,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,167,253,192,322))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(1,*k,2,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,255,343,192,322))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(1,*k,3,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,344,426,192,322))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(1,*k,4,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,79,165,472,600))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(1,*k,5,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,167,253,472,600))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(1,*k,6,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,255,343,472,600))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(1,*k,7,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,344,426,472,600))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(1,*k,8,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,425,455,0,55))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				*flag=2;//返回楼层选择
				break;
			}
		}
		if(2==i)//二楼
		{
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,428,480,480,596))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				move9(*k);
				*flag=6;//到三楼
				*from=0;
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,439,480,175,428))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				move10(*k);
				*flag=4;//到一楼
				*from=1;
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,90,155,200,318))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(2,*k,1,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,167,253,192,322))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(2,*k,2,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,255,343,192,322))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(2,*k,3,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,344,426,192,322))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(2,*k,4,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,79,165,472,600))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(2,*k,5,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,167,253,472,600))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(2,*k,6,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,255,340,472,600))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(2,*k,7,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,344,426,472,600))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(2,*k,8,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,425,455,0,55))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				*flag=2;//返回楼层选择
				break;
			}
		}
		if(3==i)
		{
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,439,480,175,428))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				move10(*k);
				*flag=5;//到二楼
				*from=1;
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,425,455,0,55))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				*flag=2;//返回楼层选择
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,90,155,200,318))
			{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
					;
				}
				_parking(3,*k,1,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,167,253,192,322))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(3,*k,2,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,255,343,192,322))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(3,*k,3,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,344,426,192,322))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(3,*k,4,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,79,165,472,600))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(3,*k,5,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,167,253,472,600))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(3,*k,6,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,255,340,472,600))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(3,*k,7,flag);//停车函数(楼层，检查，车位)
				break;
			}
			if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,344,426,472,600))
			{
				while(GetMouseSta() == LEFTBTN)//还在按着左键
				{
					;
				}
				_parking(3,*k,8,flag);//停车函数(楼层，检查，车位)
				break;
			}
		}
	}
}