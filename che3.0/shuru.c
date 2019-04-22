#include"shuru.h"
#include"dos.h"
#include"svga.h"
#include<bios.h>
#include"mouse.h"
#include"tingche.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>

/***********输入单个字符***********/
void inputch(int x1, int y1, int x2, int y2, char str[])
{
	int i=0,flag=0,check=0;
	unsigned int key;
	int k=6;
	char ch;
	int color;
	while(bioskey(1))
	{
		getch();
	}
	color=quse(290, 250);// 取输入框背景色
	SVGA_Rectangular(y1,y2,x1,x2,color);//输入车牌号框坐标：(315，175),(530，215)
	while(1)
	{
		if(flag==0)
		{
			hide_mouse();
			flag=1;
		}
		showcursor(x1+i*16+5,y1+5,0x0000);//显示黑色光标
		key=bioskey(0);
		showcursor(x1+i*16+5,y1+5,color);
		if((key&0x00ff)!=0)
		{
			key=key&0x00ff;
			if(key==0x08)  //检测是否按下退格键
			{                 
				if(i==0)
				{
				   	putsound();//无输入的情况下按下退格键，发出警告音
				}
				else
				{
					i--;
					SVGA_Rectangular(y1+8,y1+40,x1+i*16+5,x1+i*16+21,color);
				}
			}
			else if((key==0x0d)&&(6==i))//检测是否按下Enter键
			{
				if(i==0)
				{
					putsound();//无输入的情况下按下Enter键，发出警告音
				}	
				else
				{
					str[i]='\0';
					break;
				}
			}
			else if((((key>=0x61)&&(key<=0x7a))||((key>=0x30)&&(key<=0x39))||((key>=0x41)&&(key<=0x5a)))&&(i<k))//如果输入的是数字或字母
			{
				ch=(char)key;//强制类型转换，将key转换为字符
				str[i++]=ch;
				SVGA_ENtextch16(x1+(i-1)*16+5, y1+12, ch, 0xffff);//输出白色字符
			}
			
			else
			{
			   	putsound();
			}
			
		}	
	}
}

/***********输入密码***********/
void inputpassword(int x1, int y1, int x2, int y2, char str[])
{
	int i=0,flag=0,check=0;
	unsigned int key;
	int k=6;
	char ch;
	int color;
	while(bioskey(1))
	{
		getch();
	}
	color=quse(290, 250);// 取输入框背景色
	SVGA_Rectangular(y1,y2,x1,x2,color);//输入车牌号框坐标：(315，175),(530，215)
	while(1)
	{
		if(flag==0)
		{
			hide_mouse();
			flag=1;
		}
		showcursor(x1+i*16+5,y1+5,0x0000);//显示黑色光标
		key=bioskey(0);
		showcursor(x1+i*16+5,y1+5,color);
		if((key&0x00ff)!=0)
		{
			key=key&0x00ff;
			if(key==0x08)  //检测是否按下退格键
			{                 
				if(i==0)
				{
				   	putsound();//无输入的情况下按下退格键，发出警告音
				}
				else
				{
					i--;
					SVGA_Rectangular(y1+8,y1+40,x1+i*16+5,x1+i*16+21,color);
				}
			}
			else if((key==0x0d)&&(6==i))//检测是否按下Enter键
			{
				if(i==0)
				{
					putsound();//无输入的情况下按下Enter键，发出警告音
				}	
				else
				{
					str[i]='\0';
					break;
				}
			}
			else if((((key>=0x61)&&(key<=0x7a))||((key>=0x30)&&(key<=0x39))||((key>=0x41)&&(key<=0x5a)))&&(i<k))//如果输入的是数字或字母
			{
				ch=(char)key;//强制类型转换，将key转换为字符
				str[i++]=ch;
				//SVGA_ENtextch16(x1+(i-1)*16+5, y1+12, ch, 0xffff);//输出白色字符
				fillellipse1(x1+(i-1)*16+10, y1+20,6,6,0xffff);
			}
			
			else
			{
			   	putsound();
			}
			
		}	
	}
}


/******隐藏鼠标******/
void hide_mouse(void)
{
	union REGS ireg;
	
	ireg.x.ax=2;
	int86(0x33,&ireg,&ireg);
}

/**********画点********/
void Drawpoint(int x, int y, unsigned int color)
{
	unsigned short far *video_buffer=(unsigned short far *)0xA0000000L;
	unsigned long int pos;
	unsigned int page;
	if(x<0||x>639||y<0||y>479)
	{
		return;
	}
	pos=(y*640L+x);
	page=pos*2/65536L;
	selectpage(page);
	*((unsigned short far *)(video_buffer+pos))=color;
}

/************换页函数**********/
void selectpage(char page)/*换页函数*/
{
	union REGS r;
	r.x.ax=0x4f05;
	r.x.bx=0;
	r.x.dx=page;  /*选择页面*/
	int86(0x10,&r,&r);
}

/***********画光标***********/
void showcursor(int x, int y, unsigned int color)
{
	int i;
	for(i=0;i<7;i++)
	{
		Drawpoint(x+i, y, color);
		Drawpoint(x+i, y+25, color);
	}
	for(i=0;i<25;i++)
	{
		Drawpoint(x+3, y+i, color);
	}
}

/******发出警告音*******/
void putsound()
{
	sound(800);
	delay(100);
	nosound();
}


/**********取色********/
int quse(int x, int y)
{
	unsigned int color;
	unsigned short far *video_buffer=(unsigned short far *)0xA0000000L;
	unsigned long int pos;
	unsigned int page;
	if(x<0||x>639||y<0||y>479)
	{
		return;
	}
	pos=(y*640L+x);
	page=pos*2/65536L;
	selectpage(page);
	color=*((unsigned short far *)(video_buffer+pos));
	return color;
}


/***********画圆**********/
void fillellipse1(float x,float y,float xr,float yr,int color)
{
	int i;
	int x1,y1;
	float jiao;

	for(x1=0,y1=0;x1<xr&&y1<yr;x1++,y1++)
	{
		for(jiao=0;jiao<2*3.14159;jiao+=3.14159/180)
		{
			Drawpoint(x+x1*cos(jiao),y+y1*sin(jiao),color);
		}
	}
	
}