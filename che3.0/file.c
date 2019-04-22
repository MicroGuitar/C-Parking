#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include"file.h"
#include"main.h"
#include"svga.h"

FILE *OpenFile(const char *fname, char *mode)
{
	FILE *fp;

	if( (fp=fopen(fname,mode)) == NULL )
	{
		SVGA_ENtext16(0, 20, fname, _RED);
		//Error(OPENFAIL);
	}
	return fp;
}

void CloseFile(FILE *fp)
{
	if( fclose(fp) != 0 )
	{
		//Error(CLOSEFAIL);
	}	
}

void BuildFile(char *file)//�����ļ����������򲻽���
{
	FILE *fp;
	
	if((fp=fopen(file,"r"))==NULL)//�޴��ļ�
	{
		clearerr(fp);//���
		
		fp=OpenFile(file,"w");		
	}
	CloseFile(fp);
}		
///////////////////////////////////////////////////////////////////////////////
void WriteFile(char *msg, int length, FILE *fp)//ֻ�ʺ�д�����ַ���ֻ�ʺ��з����ַ��͵�д
{	
	if( fwrite(msg, 1, length, fp) < length )
	{
		//Error(WRITEFAIL);	
	}
}

void ReadFile(char *msg, int length, FILE *fp)//ֻ�ʺ��з����ַ��͵Ķ�
{
	if( fread(msg, 1, length, fp) < length )
	{
		if(feof(fp)==1)//�������ļ�β
		{
			//Error(END_OF_FILE);
		}		
		else
		{
			//Error(READFAIL);
		}
		
	}
}
///////////////////////////////////////////////////////////////////////////
void AddUser(struct UserInfo user)    
{
	FILE *fp;
	char userNum_ge, userNum_shi;
	int userNum;
	
	fp = OpenFile("data\\user.dat", "r+");
	ReadFile(&userNum_ge, 1, fp);
	ReadFile(&userNum_shi, 1, fp);
	
	userNum_ge -= '0';
	userNum_shi -= '0';
	userNum = userNum_ge + 10*userNum_shi; //���������
	
	if(userNum == 99)//��һ�����
	{
		//Error(USER_FULL);
	}	

	fseek(fp, userNum*45, SEEK_CUR);//�ƶ�ָ��
	WriteFile(user.id, 15, fp);
	Encrypt(user.password, userNum + 1);//����
	WriteFile(user.password, 15, fp);		
	WriteFile(user.score, 15, fp);	
	
	/*�޸�������*/
	userNum += 1;
	userNum_ge = userNum%10 + '0';
	userNum_shi = userNum/10 + '0';
	
	rewind(fp);//�ƶ�ָ��//д������
	WriteFile(&userNum_ge, 1, fp);
	WriteFile(&userNum_shi, 1, fp);
	
	CloseFile(fp);
}

void LoadUser(int num, struct UserInfo* pu)//�����num���û���Ϣ
{
	FILE *fp;

	if(num<1 || num>99)
	{
		//Error(LoadUser_ERROR);
	}

	fp = OpenFile("data\\user.dat", "r");
	fseek(fp, (num-1)*45 + 2, SEEK_CUR);//�ƶ�ָ��
	ReadFile(pu->id, 15, fp);
	ReadFile(pu->password, 15, fp);	
	Decode(pu->password, num);//����
	ReadFile(pu->score, 15, fp);		
	
	CloseFile(fp);
}

int CheckUser(struct UserInfo user)//���û����д���ļ��� ������
{
	char i;//Ҫдi��������char��
	struct UserInfo temp;
	int userNum;

	userNum = GetTotUserNum();//���������
	
	if(userNum == 0)
	{
		return 0;
	}
	
	for(i=1; i<=userNum; i++)
	{
		LoadUser(i, &temp);
		
		if(   !strcmp(temp.id, user.id)
			&& !strcmp(temp.password, user.password) )
		{
			FILE *fp;
			
			fp = OpenFile("data\\cuser.dat", "w");			
			WriteFile(&i, 1, fp);
			CloseFile(fp);
			break;
		}
	}
		
	if(i == (userNum+1))//���޴��� ����-1
	{
		i = -1;
	}
	return i;
}

int CheckAdmin(struct AdminInfo admin)//ֻ��һ������Ա������1��0
{
	FILE *fp;
	struct AdminInfo temp;
	
	fp = OpenFile("data\\admin.dat", "r");
	
	ReadFile(temp.id, 15, fp);
	ReadFile(temp.password, 15, fp);	
	CloseFile(fp);
	
	if(   !strcmp(temp.id, admin.id)
		&& !strcmp(temp.password, admin.password) )	
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void AddScore(int score, int offset)//�ڵ�ǰ�û�������¼���ĵ�offset�ֽڸ�Ϊscore //offset��0��14
{
	FILE *fpu, *fpc;
	int num;
	char stemp=(char)score;
	
	fpu = OpenFile("data\\user.dat", "r+");

	num = GetCurUserNum();
	fseek(fpu, (num-1)*45 + 30 + offset + 2, SEEK_CUR);//�ƶ�ָ�뵽������+offset
	WriteFile(&stemp, 1, fpu);//д����
		
	CloseFile(fpu);
}

int ChangeUser(int num, struct UserInfo user)
{
	FILE *fp;
	int findFlag;

	findFlag = FindUser(user);
	if((findFlag == -1) || (findFlag == num))//��������0 //��ʱ�޴��û���   ��������Ϊ�û������Բ���
	{
		fp = OpenFile("data\\user.dat", "r+");
		
		fseek(fp, (num-1)*45+2, SEEK_SET);//�ƶ�ָ��
		WriteFile(user.id, 15, fp);
		Encrypt(user.password, num);//����
		WriteFile(user.password, 15, fp);		
		CloseFile(fp);
		return 0;
	}
	else 
	{
		return 1;
	}
}

int FindUser(struct UserInfo user)//�����û��������ر��
{
	int i;
	struct UserInfo temp;
	int userNum;
	
	userNum = GetTotUserNum();
	if(userNum == 0)
	{
		return 0;
	}
	
	for(i=1; i<=userNum; i++)
	{
		LoadUser(i, &temp);
		
		if( !strcmp(temp.id, user.id) )
		{
			break;
		}
	}
		
	if(i == (userNum+1))//���޴��� ����-1
	{
		i = -1;
	}
	return i;
}

int GetCurUserNum(void)//���ص�ǰ�û����
{
	char num_char;
	int num;
	FILE *fp;
	
	fp=OpenFile("data\\CUSER.DAT","r");
	ReadFile(&num_char,1,fp);
	CloseFile(fp);	
	
	num = num_char;
	return num;
}

int GetTotUserNum(void)//�����ܵ��û�����
{
	FILE *fpu;
	char userNum_ge, userNum_shi;
	int userNum;	
	
	fpu = OpenFile("data\\user.dat", "r");
	ReadFile(&userNum_ge, 1, fpu);
	ReadFile(&userNum_shi, 1, fpu);
	CloseFile(fpu);
	
	userNum_ge -= '0';
	userNum_shi -= '0';
	userNum = userNum_ge + 10*userNum_shi;//���������	
	
	return userNum;
}
///////////////////����Ϊ������д������Ϊ̷���α�д/////////////////////
void InitFiles(void)//���������ļ�������ʼ��
{
	FILE *fpu, *fpa;
	//char id[16]="1234567890", password[16]="2333";//��ʼ�˺�����
	char id[16]="", password[16]="";
	char num[3]="00";
	int temp;	
	/*�û��ļ���ʼ��*/
	BuildFile("data\\user.dat");
	fpu = OpenFile("data\\user.dat", "r+");
	if( fread(&temp, 2, 1, fpu) < 1 )//�ս������ʼ��
	{
		clearerr(fpu);//���
		WriteFile(num, 2, fpu);
	}
	CloseFile(fpu);	
	/*����Ա�ļ���ʼ��*/
	BuildFile("data\\admin.dat");
	fpa = OpenFile("data\\admin.dat", "r+");//������д
	WriteFile(id, 15, fpa);
	WriteFile(password, 15, fpa);	
	CloseFile(fpa);	
	/*�����ļ���ʼ��*/
	BuildFile("data\\config.dat");	
	/*��ǰ�û��ļ���ʼ��*/
	BuildFile("data\\cuser.dat");	
}
void SortTop5(int num[2][5])//����intָ�룬����������û�top5�ı�ŴӸߵ���д��ָ��ָ�������ȿ�Ŀ2�ٿ�Ŀ3 //��Ϊ�㣬˵����������5��
{
	struct UserInfo temp;
	struct SortNode sortList[101];//0��100��
	int userNum;	
	register int i;
	int scoreCount;//��ʾ��¼�˶��ٸ�����
	int	keMuFlag;//Ϊ0ʱ��ʾ�����Ŀ����Ϊ1ʱ��ʾ�����Ŀ��

	userNum = GetTotUserNum();//���������
	
	for(keMuFlag=0; keMuFlag<2; keMuFlag++)
	{
		for(i=0; i<101; i++)//��ʼ��
		{
			sortList[i].count = 0;
			sortList[i].pnum = NULL;
		}
		scoreCount = 0;
		
		for(i=1; i<=userNum; i++)//�����ڽӱ�
		{
			register int countTemp;
			register int scoreTemp;
			
			LoadUser(i, &temp);
			scoreTemp = temp.score[keMuFlag];
			sortList[scoreTemp].count +=1;
			countTemp = sortList[scoreTemp].count;

			if(countTemp == 1)//û�з����ڴ棬�����10*int�ڴ�
			{
				sortList[scoreTemp].pnum = (int *)malloc(10*sizeof(int));

				if(sortList[scoreTemp].pnum == NULL)
				{
					//Error(MEM_LACK);
				}
			}
			if(countTemp == 11)//pnum���ڴ�պò����ˣ��ٷ�50*int
			{
				sortList[scoreTemp].pnum = (int *)realloc(sortList[scoreTemp].pnum ,50*sizeof(int));
				if(sortList[scoreTemp].pnum == NULL)
				{
					//Error(MEM_LACK);
				}			
			}
			if(countTemp == 51)//pnum���ڴ��ָպò����ˣ��ٷ�100*int//�����100����
			{
				sortList[scoreTemp].pnum = (int *)realloc(sortList[scoreTemp].pnum ,100*sizeof(int));
				if(sortList[scoreTemp].pnum == NULL)
				{
					//Error(MEM_LACK);
				}				
			}
			( sortList[scoreTemp].pnum )[countTemp-1] = i;
				
		}

		for(i=100; i>=0; i--)//�����ڽӱ�
		{
			if(sortList[i].count != 0)//����Ϊi������
			{
				register int j=sortList[i].count, k;
				
				if(j+scoreCount > 5)//��5��������
				{
					j = 5-scoreCount;//�����������Ա				
				}
				
				k = j;
				for(j=0; j<k; j++)//���봫����������ָ��
				{
					num[keMuFlag][scoreCount]= ( sortList[i].pnum )[j];//����[]����.ʱ ���ṹ����ĳ�Ա��ȡ�����Ա ���������
					scoreCount++;
				}
			}
			if(scoreCount == 5)//��5��
			{
				break;
			}
		}
		
		for(i=100; i>=0; i--)//�ͷ��ڴ�
		{
			if(sortList[i].pnum != NULL)
			{
				free(sortList[i].pnum);
			}
		}	
	}
}

void Encrypt(char *plainText, int seed)//�������ַ���ͨ�������������//ֻ�ܼ������λΪ0��ascii��
{
	int len, i;
	char r;
	
	len = strlen(plainText);
	srand(seed);
	
	for(i=0; i<len; i++)
	{
		r = (char)rand();
		r |= 0x80;//��֤r���ַ����󲻳��֡�\0��
		
		plainText[i] ^= r;
	}
}

void Decode(char *cipherText, int seed)//����
{
	int len, i;
	char r;
	
	len = strlen(cipherText);
	srand(seed);
	
	for(i=0; i<len; i++)
	{
		r = (char)rand();
		r |= 0x80;//��֤r���ַ����󲻳��֡�\0��
		
		cipherText[i] ^= (char)r;	
	}
}

