#ifndef FILE_H
	#define FILE_H

#ifndef FILE 
#include<stdio.h>
#endif

struct UserInfo
{
	char id[16];
	char password[16];
	char score[16];
};

struct AdminInfo
{
	char id[16];
	char password[16];
};

struct SortNode
{
	int count;//人数
	int* pnum;//指向编号
};
/*基本操作*/
void BuildFile(char *file);//建立文件函数
FILE* OpenFile(const char *fname, char *mode);//打开文件函数
void WriteFile(char *msg, int length, FILE *fp);//写文件函数
void ReadFile(char *msg, int length, FILE *fp);//读文件函数
void CloseFile(FILE *fp);//关闭文件函数
/*需要OpenFile的函数*/
void InitFiles(void);//程序文件初始化
void AddUser(struct UserInfo user);//添加用户函数
void LoadUser(int num, struct UserInfo* pu);//载入用户信息函数
int CheckUser(struct UserInfo user);//检查用户信息函数
int CheckAdmin(struct AdminInfo admin);//检查管理员信息函数
int GetCurUserNum(void);//获取当前用户编号函数
int GetTotUserNum(void);//获取用户总人数函数
void AddScore(int score, int offset);//写入用户分数函数
int ChangeUser(int num, struct UserInfo user);//修改用户信息函数
/*不需要OpenFile的函数*/
void SortTop5(int num[2][5]);//显示用户成绩前五名函数
int FindUser(struct UserInfo user);//返回用户编号函数
void Encrypt(char *plainText, int seed);//加密函数
void Decode(char *cipherText, int seed);//解密函数
#endif