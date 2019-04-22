#ifndef MAIN_H
	#define MAIN_H
 
#define OPENFAIL 1
#define SWITCHERROR 2
#define CLOSEFAIL 3
#define ERROR 4

#define WRITEFAIL 6
#define READFAIL  7
#define END_OF_FILE 8
#define USER_FULL 9
#define LoadUser_ERROR 10
#define MEM_LACK 11
#define FILM_ERROR 12
#define ZOOM_PIC_ERROR 13
#define PIXEL_MIX_ERROR 14
#define HOLLOW_PIC_ERROR 15
#define PIC_CHANGE_ERROR 16

void Init(void);//初始化函数
void End(int Oldmode);//结束画面函数
void Error(int stat);//错误处理函数
void Debug(const int debug, int x, int y);//显示错误号函数
#endif