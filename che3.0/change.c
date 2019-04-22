#include"svga.h"
#include"mouse.h"
#include"mode.h"
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include"change.h"
#define h1 138
#define h2 221
#define h3 302
void change(int *flag)
{
	int MouseX, MouseY, oldx, oldy;//鼠标坐标
	int pic[1024], mouseShape[1024];//鼠标和鼠标移动缓存
	char f[2];//读取文件
	FILE *fp;
	SVGA_SetMode(0X111);
	SVGA_PartBmp(0,480,0,640,0,0,"sm\\change.bmp");
	SVGA_ImportBmp( "sm\\mouse.bmp",mouseShape);
	SetMouseBound(0, 640, 0, 480);
    MouseX=GetMouseX();
    MouseY=GetMouseY();
	oldx=MouseX;
	oldy=MouseY;
	SVGA_SaveArea(MouseX,MouseY,pic);
	if((fp=fopen("message//f1.txt","rt+"))==NULL)
	{
		exit(0);
	}
	fgets(f,2,fp);
	rewind(fp);
	fclose(fp);
	switch(f[0])
	{
		case '0':SVGA_PartBmp(32,54,23,42,240,h1,"pic//num.bmp");
				break;
		case '1':SVGA_PartBmp(32,54,63,79,240,h1,"pic//num.bmp");
				break;
		case '2':SVGA_PartBmp(32,54,105,122,240,h1,"pic//num.bmp");
				break;
		case '3':SVGA_PartBmp(32,54,147,164,240,h1,"pic//num.bmp");
				break;
		case '4':SVGA_PartBmp(32,54,191,208,240,h1,"pic//num.bmp");
				break;
		case '5':SVGA_PartBmp(32,54,233,252,240,h1,"pic//num.bmp");
				break;
		case '6':SVGA_PartBmp(32,54,276,293,240,h1,"pic//num.bmp");
				break;
		case '7':SVGA_PartBmp(32,54,318,333,240,h1,"pic//num.bmp");
				break;
		case '8':SVGA_PartBmp(32,54,351,367,240,h1,"pic//num.bmp");
				break;
	}
	if((fp=fopen("message//f2.txt","rt+"))==NULL)
	{
		exit(0);
	}
	fgets(f,2,fp);
	rewind(fp);
	fclose(fp);
	switch(f[0])
	{
		case '0':SVGA_PartBmp(32,54,23,42,240,h2,"pic//num.bmp");
				break;
		case '1':SVGA_PartBmp(32,54,63,79,240,h2,"pic//num.bmp");
				break;
		case '2':SVGA_PartBmp(32,54,105,122,240,h2,"pic//num.bmp");
				break;
		case '3':SVGA_PartBmp(32,54,147,164,240,h2,"pic//num.bmp");
				break;
		case '4':SVGA_PartBmp(32,54,191,208,240,h2,"pic//num.bmp");
				break;
		case '5':SVGA_PartBmp(32,54,233,252,240,h2,"pic//num.bmp");
				break;
		case '6':SVGA_PartBmp(32,54,276,293,240,h2,"pic//num.bmp");
				break;
		case '7':SVGA_PartBmp(32,54,318,333,240,h2,"pic//num.bmp");
				break;
		case '8':SVGA_PartBmp(32,54,351,367,240,h2,"pic//num.bmp");
				break;
	}
	if((fp=fopen("message//f3.txt","rt+"))==NULL)
	{
		exit(0);
	}
	fgets(f,2,fp);
	rewind(fp);
	fclose(fp);
	switch(f[0])
	{
		case '0':SVGA_PartBmp(32,54,23,42,240,h3,"pic//num.bmp");
				break;
		case '1':SVGA_PartBmp(32,54,63,79,240,h3,"pic//num.bmp");
				break;
		case '2':SVGA_PartBmp(32,54,105,122,240,h3,"pic//num.bmp");
				break;
		case '3':SVGA_PartBmp(32,54,147,164,240,h3,"pic//num.bmp");
				break;
		case '4':SVGA_PartBmp(32,54,191,208,240,h3,"pic//num.bmp");
				break;
		case '5':SVGA_PartBmp(32,54,233,252,240,h3,"pic//num.bmp");
				break;
		case '6':SVGA_PartBmp(32,54,276,293,240,h3,"pic//num.bmp");
				break;
		case '7':SVGA_PartBmp(32,54,318,333,240,h3,"pic//num.bmp");
				break;
		case '8':SVGA_PartBmp(32,54,351,367,240,h3,"pic//num.bmp");
				break;
	}
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
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,141,160,295,317))//按下小型车 加
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			addf(1);
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,223,245,295,317))//按下大型车 加
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			addf(2);
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,306,328,295,317))//按下特种车 加
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			addf(3);
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,141,160,182,203))//按下小型车 减
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			redf(1);
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,223,245,182,203))//按下大型车 减
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			redf(2);
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,306,328,182,203))//按下小型车 减
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			redf(3);
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,397,437,4,76))//返回
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			*flag=3;
			break;
		}
	}
}
void addf(int k)
{
	FILE *fp;
	int f[2];
	if(1==k)
	{
		if((fp=fopen("message//f1.txt","rt+"))==NULL)
		{
			getch();
			exit(1);
		}
		fgets(f,2,fp);//打开小车费用文件，读取到t中
		rewind(fp);
		switch(f[0])
		{
			case '1':
					fwrite("2",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,105,122,240,h1,"pic//num.bmp");//贴图
					break;
			case '2':
					fwrite("3",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,147,164,240,h1,"pic//num.bmp");//贴图
					break;
			case '3':
					fwrite("4",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,191,208,240,h1,"pic//num.bmp");//贴图
					break;
			case '4':
					fwrite("5",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,233,252,240,h1,"pic//num.bmp");
					break;
			case '5':
					fwrite("6",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,276,293,240,h1,"pic//num.bmp");
					break;
			case '6':
					fwrite("7",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,318,333,240,h1,"pic//num.bmp");
					break;
			case '7':
					fwrite("8",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,351,367,240,h1,"pic//num.bmp");
					break;
			case '8':
					fwrite("8",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,351,367,240,h1,"pic//num.bmp");
					break;
		}
		fclose(fp);
	}
	if(2==k)
	{
		
		if((fp=fopen("message//f2.txt","rt+"))==NULL)
		{
			getch();
			exit(1);
		}
		fgets(f,2,fp);//打开小车费用文件，读取到t中
		rewind(fp);
		switch(f[0])
		{

			case '1':
					fwrite("2",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,105,122,240,h2,"pic//num.bmp");//贴图
					break;
			case '2':
					fwrite("3",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,147,164,240,h2,"pic//num.bmp");//贴图
					break;
			case '3':
					fwrite("4",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,191,208,240,h2,"pic//num.bmp");//贴图
					break;
			case '4':
					fwrite("5",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,233,252,240,h2,"pic//num.bmp");
					break;
			case '5':
					fwrite("6",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,276,293,240,h2,"pic//num.bmp");
					break;
			case '6':
					fwrite("7",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,318,333,240,h2,"pic//num.bmp");
					break;
			case '7':
					fwrite("8",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,351,367,240,h2,"pic//num.bmp");
					break;
			case '8':
					fwrite("8",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,351,367,240,h2,"pic//num.bmp");
					break;
		}
		fclose(fp);
	}
	if(3==k)
	{
		
		if((fp=fopen("message//f3.txt","rt+"))==NULL)
		{
			getch();
			exit(1);
		}
		fgets(f,2,fp);//打开小车费用文件，读取到t中
		rewind(fp);
		switch(f[0])
		{

			case '1':
					fwrite("2",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,105,122,240,h3,"pic//num.bmp");//贴图
					break;
			case '2':
					fwrite("3",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,147,164,240,h3,"pic//num.bmp");//贴图
					break;
			case '3':
					fwrite("4",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,191,208,240,h3,"pic//num.bmp");//贴图
					break;
			case '4':
					fwrite("5",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,233,252,240,h3,"pic//num.bmp");
					break;
			case '5':
					fwrite("6",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,276,293,240,h3,"pic//num.bmp");
					break;
			case '6':
					fwrite("7",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,318,333,240,h3,"pic//num.bmp");
					break;
			case '7':
					fwrite("8",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,351,367,240,h3,"pic//num.bmp");
					break;
			case '8':
					fwrite("8",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,351,367,240,h3,"pic//num.bmp");
					break;
		}
		fclose(fp);
	}	
}
void redf(int k)
{
	FILE *fp;
	int f[2];
	if(1==k)
	{
		if((fp=fopen("message//f1.txt","rt+"))==NULL)
		{
			getch();
			exit(1);
		}
		fgets(f,2,fp);//打开小车费用文件，读取到t中
		rewind(fp);
		switch(f[0])
		{
			case '1':
					fwrite("1",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,63,79,240,h1,"pic//num.bmp");
					break;
			case '2':
					fwrite("1",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,63,79,240,h1,"pic//num.bmp");
					break;		
			case '3':
					fwrite("2",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,105,122,240,h1,"pic//num.bmp");//贴图
					break;
			case '4':
					fwrite("3",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,147,164,240,h1,"pic//num.bmp");//贴图
					break;
			case '5':
					fwrite("4",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,191,208,240,h1,"pic//num.bmp");//贴图
					break;
			case '6':
					fwrite("5",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,233,252,240,h1,"pic//num.bmp");
					break;
			case '7':
					fwrite("6",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,276,293,240,h1,"pic//num.bmp");
					break;
			case '8':
					fwrite("7",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,318,333,240,h1,"pic//num.bmp");
					break;
		}
		fclose(fp);
	}
	if(2==k)
	{
		if((fp=fopen("message//f2.txt","rt+"))==NULL)
		{
			getch();
			exit(1);
		}
		fgets(f,2,fp);//打开小车费用文件，读取到t中
		rewind(fp);
		switch(f[0])
		{
			case '1':
					fwrite("1",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,63,79,240,h2,"pic//num.bmp");
					break;
			case '2':
					fwrite("1",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,63,79,240,h2,"pic//num.bmp");
					break;		
			case '3':
					fwrite("2",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,105,122,240,h2,"pic//num.bmp");//贴图
					break;
			case '4':
					fwrite("3",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,147,164,240,h2,"pic//num.bmp");//贴图
					break;
			case '5':
					fwrite("4",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,191,208,240,h2,"pic//num.bmp");//贴图
					break;
			case '6':
					fwrite("5",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,233,252,240,h2,"pic//num.bmp");
					break;
			case '7':
					fwrite("6",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,276,293,240,h2,"pic//num.bmp");
					break;
			case '8':
					fwrite("7",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,318,333,240,h2,"pic//num.bmp");
					break;
		}
		fclose(fp);
	}
	if(3==k)
	{
		if((fp=fopen("message//f3.txt","rt+"))==NULL)
		{
			getch();
			exit(1);
		}
		fgets(f,2,fp);//打开小车费用文件，读取到t中
		rewind(fp);
		switch(f[0])
		{
			case '1':
					fwrite("1",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,63,79,240,h3,"pic//num.bmp");
					break;
			case '2':
					fwrite("1",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,63,79,240,h3,"pic//num.bmp");
					break;		
			case '3':
					fwrite("2",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,105,122,240,h3,"pic//num.bmp");//贴图
					break;
			case '4':
					fwrite("3",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,147,164,240,h3,"pic//num.bmp");//贴图
					break;
			case '5':
					fwrite("4",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,191,208,240,h3,"pic//num.bmp");//贴图
					break;
			case '6':
					fwrite("5",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,233,252,240,h3,"pic//num.bmp");
					break;
			case '7':
					fwrite("6",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,276,293,240,h3,"pic//num.bmp");
					break;
			case '8':
					fwrite("7",2,1,fp);//将t写入文件中
					SVGA_PartBmp(32,54,318,333,240,h3,"pic//num.bmp");
					break;
		}
		fclose(fp);
	}
}