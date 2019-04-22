#include"svga.h"
#include<stdio.h>
#include<dos.h>
#include<string.h>
#include"glpass.h"
#include"shuru.h"
#include<bios.h>
#include<stdlib.h>


void password(int *flag)
{
	FILE *fp;
	char str[7]={'\0'};//存输入的密码
	char a[7];//存管理员密码
	
	
	if((fp=fopen("message//gl.txt","rt+"))==NULL)
	{
		exit(0);
	}
	fgets(a,7,fp);
	rewind(fp);
	fclose(fp);
	
	SVGA_PartBmp(373,429,274,484,274,373,"pic\\glpass.bmp");//贴图 请输入密码
	glpassword(278,377,480,425,str);
	if(strcmp(str,a)==0)//如果密码匹配
	{
		*flag=3;
	}
	else
	{
		SVGA_PartBmp(146,325,180,455,255,150,"pic\\fail3.bmp");//贴图 密码错误
		delay(900);
		*flag=0;
	}

}


void modify(int *flag)
{
	FILE *fp;
	char str[7];
	char a[7];
	
	if((fp=fopen("message//gl.txt","rt+"))==NULL)
	{
		exit(0);
	}
	fgets(a,7,fp);
	rewind(fp);
	
	SVGA_PartBmp(373,429,274,484,274,373,"pic\\glpass.bmp");//贴图 请输入密码
	glpassword(278,377,480,425,str);//调用输入函数输入新密码 用str存
	if(strcmp(a,str)!=0)
	{
		fwrite(str,6,1,fp);
	}
	rewind(fp);
	fclose(fp);
	*flag=3;
	
}

/***********输入管理员密码***********/
void glpassword(int x1, int y1, int x2, int y2, char str[])
{
	int i=0,flag=0,check=0;
	unsigned int key;
	int k=6;
	char ch;
	int color=0xffff;
	while(bioskey(1))
	{
		getch();
	}
   	color=quse(290, 250);// 取输入框背景色
	SVGA_Rectangular(y1,y2,x1,x2,color);//输入框坐标：(315，175),(530，215)
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
				   //	putsound();//无输入的情况下按下退格键，发出警告音
				}
				else
				{
					i--;
					SVGA_Rectangular(y1+8,y1+40,x1+i*16+5,x1+i*16+21,color);
				}
			}
			else if((key==0x0d)&&(i==6))//检测是否按下Enter键
			{
				if(i==0)
				{
					//putsound();//无输入的情况下按下Enter键，发出警告音
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
			   //	putsound();
			}
			
		}	
	}
}