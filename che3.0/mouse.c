#include <dos.h>
#include <bios.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include "svga.h"
#include "mouse.h"
void MountMouse(void)
{
	 _AX=0x00;        //功能00H*/
	 geninterrupt(0x33);//0x33:鼠标中断类型*/
}
 
/*********************************************************************/
void UnmountMouse(void)//其实是隐藏载入的鼠标图形
{
	 _AX=0x02;        /*功能02H*/
	 geninterrupt(0x33);    /*0x33:鼠标中断类型*/
	 return ;
}

/*********************************************************************/

int GetMouseX(void)//返回鼠标位置x值
{        int MX;
		 _AX=0x03;
	 geninterrupt(0x33);
	 MX=_CX;         //将鼠标水平方向位置存放到MouseX
		return MX;

}
/*********************************************************************/

int GetMouseY(void)
{        int MY;
		 _AX=0x03;
	 geninterrupt(0x33);
		 MY=_DX;         //将鼠标垂直方向位置存放到MouseY
		 return MY;

}

/*********************************************************************/
int GetMouseSta(void)      //判断鼠标按键状态
{
	 int MouseMSG=0;
	 _AX=0x03;
	 geninterrupt(0x33);

	 if((_BX&1) && !(_BX&2))         //鼠标左键被按下同时右键没有按下,左键
		  MouseMSG=LEFTBTN;

	 if((_BX&2) && !(_BX&1))         //鼠标右键被按下同时左键没有按下，右键
		  MouseMSG=RIGHTBTN;

	if(_BX&1 && _BX&2)              //鼠标左键和右键同时被按下
		MouseMSG=ALLBTN;

	return MouseMSG;
}

/*********************************************************************/
void SetMouseXY(int x, int y)
{
	_AX=0x04;
	_CX=x;
	_DX=y;
	geninterrupt(0x33);

	return;
}

/*********************************************************************/
//设置鼠标水平边界
void SetMouseBound(int mouseMinX, int mouseMaxX, int mouseMinY, int mouseMaxY)
{
	_AX=0x07;
	_CX=mouseMinX;
	_DX=mouseMaxX;
	geninterrupt(0x33);

	_AX=0x08;
	_CX=mouseMinY;
	_DX=mouseMaxY;
	geninterrupt(0x33);

	return;
}

/*********************************************************************/

void begin_set(void)/*对界面进行初始鼠标设定*/
{    MountMouse();
     SetMouseBound(0, 639, 0, 479); //设置鼠标边界
     SetMouseXY( GetMouseX(),GetMouseY() );				// 有没有用？
	 //SetMouseXY(0,0);
	 asm  mov AX, 1;
	 asm  int 0x33;}


/**************鼠标中断函数*************使鼠标不被盖住******************************************/
void SetMouse(void)
{
	asm     mov AX, 2 //隐藏
	asm 	int 0x33
	asm     mov AX, 1   //显示
	asm     int 0x33
}
/******************************以上为14级以前代码***********************************************************/














