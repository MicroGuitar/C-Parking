#ifndef _SHURU_H__
    #define _SHURU_H__
#include"dos.h"
#include"svga.h"
#include<bios.h>
#include"mouse.h"
#include<stdio.h>	
#include<stdlib.h>
#include<conio.h>
	void inputch(int x1, int y1, int x2, int y2, char str[]);
	void inputpassword(int x1, int y1, int x2, int y2, char str[]);
	void hide_mouse(void);
	void Drawpoint(int x, int y, unsigned int color);
	void selectpage(char page);
	void showcursor(int x, int y, unsigned int color);
	void putsound();
	int quse(int x, int y);
	void fillellipse1(float x,float y,float xr,float yr,int color);
#endif