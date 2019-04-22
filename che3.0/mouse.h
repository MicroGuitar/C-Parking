#ifndef __PMOUSE_H__
    #define __PMOUSE_H__
	
#define LEFTBTN 1
#define RIGHTBTN 2
#define ALLBTN 0

void MountMouse (void);
void UnmountMouse(void);
void begin_set(void);
void write_mouse_9(int MouseX,int MouseY);
int GetMouseSta (void);
void SetMouseXY(int, int);
void SetMouseBound (int, int, int, int);
int GetMouseX(void);//返回鼠标位置x值
int GetMouseY(void);
void SetMouseXY(int x, int y);
void SetMouse(void);
#endif