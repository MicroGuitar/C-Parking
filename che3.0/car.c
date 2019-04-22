#include"svga.h"
#include"mouse.h"
#include"mode.h"
void selectcar(int *flag,int *k)
{
	int MouseX, MouseY, oldx, oldy;//鼠标坐标
	int pic[1024], mouseShape[1024];//鼠标和鼠标移动缓存
	SVGA_SetMode(0X111);
	SVGA_PartBmp(0,480,0,640,0,0,"sm\\car.bmp");

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
/*****************小型车按钮******************/
			if(CheckArea(MouseX,MouseY,115,160,235,330))
			{
				SVGA_RestoreArea(oldx,oldy,pic);				
				SVGA_PartBmp(115,160,235,330,235,115, "pic\\cbutton.bmp"); 		
				SVGA_SaveArea(MouseX,MouseY,pic);
				SVGA_ImgBlackMask(MouseX,MouseY,mouseShape);
			}	
			else	// 一直在按钮外
			{
				SVGA_PartBmp(115,160,235,330,235,115,"sm\\car.bmp");
			}
/*****************大型车按钮******************/
			if(CheckArea(MouseX,MouseY,239,283,302,393))
			{
				SVGA_RestoreArea(oldx,oldy,pic);				
				SVGA_PartBmp(239,283,302,393,302,239, "pic\\cbutton.bmp"); 		
				SVGA_SaveArea(MouseX,MouseY,pic);
				SVGA_ImgBlackMask(MouseX,MouseY,mouseShape);
			}	
			else	// 一直在按钮外
			{
				SVGA_PartBmp(239,283,302,393,302,239,"sm\\car.bmp");
			}
/*****************特种车按钮******************/
			if(CheckArea(MouseX,MouseY,361,407,237,328))
			{
				SVGA_RestoreArea(oldx,oldy,pic);				
				SVGA_PartBmp(361,407,237,328,237,361, "pic\\cbutton.bmp"); 		
				SVGA_SaveArea(MouseX,MouseY,pic);
				SVGA_ImgBlackMask(MouseX,MouseY,mouseShape);
			}	
			else	// 一直在按钮外
			{
				SVGA_PartBmp(361,407,237,328,237,361,"sm\\car.bmp");
			}			
			
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,130,158,265,331))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			*flag=2;
			*k=0;
			break;//选择小型车
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,245,273,330,397))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			*flag=2;
			*k=1;
			break;//选择大型车
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,367,394,265,332))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			*flag=2;
			*k=2;
			break;//选择特种车
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,439,480,0,70))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			*flag=0;
			break;//返回模式选择
		}
	}
}