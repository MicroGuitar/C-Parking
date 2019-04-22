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
	int count;//����
	int* pnum;//ָ����
};
/*��������*/
void BuildFile(char *file);//�����ļ�����
FILE* OpenFile(const char *fname, char *mode);//���ļ�����
void WriteFile(char *msg, int length, FILE *fp);//д�ļ�����
void ReadFile(char *msg, int length, FILE *fp);//���ļ�����
void CloseFile(FILE *fp);//�ر��ļ�����
/*��ҪOpenFile�ĺ���*/
void InitFiles(void);//�����ļ���ʼ��
void AddUser(struct UserInfo user);//����û�����
void LoadUser(int num, struct UserInfo* pu);//�����û���Ϣ����
int CheckUser(struct UserInfo user);//����û���Ϣ����
int CheckAdmin(struct AdminInfo admin);//������Ա��Ϣ����
int GetCurUserNum(void);//��ȡ��ǰ�û���ź���
int GetTotUserNum(void);//��ȡ�û�����������
void AddScore(int score, int offset);//д���û���������
int ChangeUser(int num, struct UserInfo user);//�޸��û���Ϣ����
/*����ҪOpenFile�ĺ���*/
void SortTop5(int num[2][5]);//��ʾ�û��ɼ�ǰ��������
int FindUser(struct UserInfo user);//�����û���ź���
void Encrypt(char *plainText, int seed);//���ܺ���
void Decode(char *cipherText, int seed);//���ܺ���
#endif