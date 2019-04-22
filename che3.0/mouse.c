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
	 _AX=0x00;        //����00H*/
	 geninterrupt(0x33);//0x33:����ж�����*/
}
 
/*********************************************************************/
void UnmountMouse(void)//��ʵ��������������ͼ��
{
	 _AX=0x02;        /*����02H*/
	 geninterrupt(0x33);    /*0x33:����ж�����*/
	 return ;
}

/*********************************************************************/

int GetMouseX(void)//�������λ��xֵ
{        int MX;
		 _AX=0x03;
	 geninterrupt(0x33);
	 MX=_CX;         //�����ˮƽ����λ�ô�ŵ�MouseX
		return MX;

}
/*********************************************************************/

int GetMouseY(void)
{        int MY;
		 _AX=0x03;
	 geninterrupt(0x33);
		 MY=_DX;         //����괹ֱ����λ�ô�ŵ�MouseY
		 return MY;

}

/*********************************************************************/
int GetMouseSta(void)      //�ж���갴��״̬
{
	 int MouseMSG=0;
	 _AX=0x03;
	 geninterrupt(0x33);

	 if((_BX&1) && !(_BX&2))         //������������ͬʱ�Ҽ�û�а���,���
		  MouseMSG=LEFTBTN;

	 if((_BX&2) && !(_BX&1))         //����Ҽ�������ͬʱ���û�а��£��Ҽ�
		  MouseMSG=RIGHTBTN;

	if(_BX&1 && _BX&2)              //���������Ҽ�ͬʱ������
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
//�������ˮƽ�߽�
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

void begin_set(void)/*�Խ�����г�ʼ����趨*/
{    MountMouse();
     SetMouseBound(0, 639, 0, 479); //�������߽�
     SetMouseXY( GetMouseX(),GetMouseY() );				// ��û���ã�
	 //SetMouseXY(0,0);
	 asm  mov AX, 1;
	 asm  int 0x33;}


/**************����жϺ���*************ʹ��겻����ס******************************************/
void SetMouse(void)
{
	asm     mov AX, 2 //����
	asm 	int 0x33
	asm     mov AX, 1   //��ʾ
	asm     int 0x33
}
/******************************����Ϊ14����ǰ����***********************************************************/














