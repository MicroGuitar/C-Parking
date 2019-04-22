#include"svga.h"
#include"mouse.h"
#include"mode.h"
void selectfloor(int *flag,int k,int *from)
{
	int MouseX, MouseY, oldx, oldy;//鼠标坐标
	int pic[1024], mouseShape[1024];//鼠标和鼠标移动缓存
	SVGA_SetMode(0X111);
	SVGA_PartBmp(0,480,0,640,0,0,"sm\\floor.bmp");

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
		/********************楼层选择按钮1效果******************/		
		if(CheckArea(MouseX,MouseY,125,180,200,425))
		{
			SVGA_RestoreArea(oldx,oldy,pic);				
			SVGA_PartBmp(125,180,100,170,100,125, "pic\\fbutton.bmp"); //左
			SVGA_PartBmp(125,180,455,530,455,125, "pic\\fbutton.bmp"); //右			
			SVGA_SaveArea(MouseX,MouseY,pic);
			SVGA_ImgBlackMask(MouseX,MouseY,mouseShape);
		}	
		else	// 一直在按钮外
		{
			SVGA_PartBmp(125,180,100,170,100,125,"sm\\floor.bmp");
			SVGA_PartBmp(125,180,455,530,455,125,"sm\\floor.bmp");
		}
/********************楼层选择按钮2效果******************/
		if(CheckArea(MouseX,MouseY,220,270,200,425))
		{
			SVGA_RestoreArea(oldx,oldy,pic);				
			SVGA_PartBmp(220,270,100,170,100,220, "pic\\fbutton.bmp"); //左
			SVGA_PartBmp(220,270,455,530,455,220, "pic\\fbutton.bmp"); //右		
			SVGA_SaveArea(MouseX,MouseY,pic);
			SVGA_ImgBlackMask(MouseX,MouseY,mouseShape);
		}	
		else	// 一直在按钮外
		{
			SVGA_PartBmp(220,270,100,170,100,220,"sm\\floor.bmp");
			SVGA_PartBmp(220,270,455,530,455,220,"sm\\floor.bmp");
		}	
/********************楼层选择按钮3效果******************/
		if(CheckArea(MouseX,MouseY,315,370,200,425))
		{
			SVGA_RestoreArea(oldx,oldy,pic);				
			SVGA_PartBmp(300,370,100,170,100,300, "pic\\fbutton.bmp"); //左
			SVGA_PartBmp(300,370,455,530,455,300, "pic\\fbutton.bmp"); //右		
			SVGA_SaveArea(MouseX,MouseY,pic);
			SVGA_ImgBlackMask(MouseX,MouseY,mouseShape);
		}	
		else	// 一直在按钮外
		{
			SVGA_PartBmp(300,370,100,170,100,300,"sm\\floor.bmp");
			SVGA_PartBmp(300,370,455,530,455,300,"sm\\floor.bmp");
		}				
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,120,180,200,430))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			if(1==k)
			{
				*flag=4;//第一层
				*from=0;
				break;
			}
			if(2==k)
			{
				*flag=8;//第一层
				break;
			}
			if(3==k)
			{
				*flag=13;//第一层
				break;
			}
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,220,275,200,430))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			if(1==k)
			{
				*flag=5;//第二层
				*from=2;
				break;
			}
			if(2==k)
			{
				*flag=9;//第二层
				break;
			}
			if(3==k)
			{
				*flag=14;//第二层
				break;
			}
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,312,367,200,430))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			if(1==k)
			{
				*flag=6;//第三层
				*from=3;
				break;
			}
			if(2==k)
			{
				*flag=10;//第三层
				break;
			}
			if(3==k)
			{
				*flag=15;//第三层
				break;
			}
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,449,480,0,84))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			if(1==k)
			{
				*flag=1;//返回车型选择
				break;
			}
			if(2==k)
			{
				*flag=0;//返回模式选择
				break;
			}
			if(3==k)
			{
				*flag=3;//第一层
				break;
			}
		}
	}
}	