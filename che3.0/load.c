#include "svga.h"
#include<stdio.h>
#include<dos.h>
void load()
{
	SVGA_SetMode(0X111);
	SVGA_PartBmp(0,480,0,640,0,0,"load//0.bmp");
	delay(900);
	SVGA_PartBmp(0,480,0,640,0,0,"load//1.bmp");
	delay(300);
	SVGA_PartBmp(0,480,0,640,0,0,"load//2.bmp");
	delay(300);
	SVGA_PartBmp(0,480,0,640,0,0,"load//3.bmp");
	delay(300);
	SVGA_PartBmp(0,480,0,640,0,0,"load//4.bmp");
	delay(300);
	SVGA_PartBmp(0,480,0,640,0,0,"load//5.bmp");
	delay(300);
	SVGA_PartBmp(0,480,0,640,0,0,"load//6.bmp");
	delay(300);
}
