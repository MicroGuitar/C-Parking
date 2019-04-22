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

void BuildFile(char *file)//建立文件，若存在则不建立
{
	FILE *fp;
	
	if((fp=fopen(file,"r"))==NULL)//无此文件
	{
		clearerr(fp);//清错
		
		fp=OpenFile(file,"w");		
	}
	CloseFile(fp);
}		
///////////////////////////////////////////////////////////////////////////////
void WriteFile(char *msg, int length, FILE *fp)//只适合写单个字符，只适合有符号字符型的写
{	
	if( fwrite(msg, 1, length, fp) < length )
	{
		//Error(WRITEFAIL);	
	}
}

void ReadFile(char *msg, int length, FILE *fp)//只适合有符号字符型的读
{
	if( fread(msg, 1, length, fp) < length )
	{
		if(feof(fp)==1)//读到了文件尾
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
	userNum = userNum_ge + 10*userNum_shi; //求出总人数
	
	if(userNum == 99)//加一后溢出
	{
		//Error(USER_FULL);
	}	

	fseek(fp, userNum*45, SEEK_CUR);//移动指针
	WriteFile(user.id, 15, fp);
	Encrypt(user.password, userNum + 1);//加密
	WriteFile(user.password, 15, fp);		
	WriteFile(user.score, 15, fp);	
	
	/*修改总人数*/
	userNum += 1;
	userNum_ge = userNum%10 + '0';
	userNum_shi = userNum/10 + '0';
	
	rewind(fp);//移动指针//写总人数
	WriteFile(&userNum_ge, 1, fp);
	WriteFile(&userNum_shi, 1, fp);
	
	CloseFile(fp);
}

void LoadUser(int num, struct UserInfo* pu)//载入第num个用户信息
{
	FILE *fp;

	if(num<1 || num>99)
	{
		//Error(LoadUser_ERROR);
	}

	fp = OpenFile("data\\user.dat", "r");
	fseek(fp, (num-1)*45 + 2, SEEK_CUR);//移动指针
	ReadFile(pu->id, 15, fp);
	ReadFile(pu->password, 15, fp);	
	Decode(pu->password, num);//解密
	ReadFile(pu->score, 15, fp);		
	
	CloseFile(fp);
}

int CheckUser(struct UserInfo user)//将用户编号写在文件里 并返回
{
	char i;//要写i，所以用char型
	struct UserInfo temp;
	int userNum;

	userNum = GetTotUserNum();//求出总人数
	
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
		
	if(i == (userNum+1))//查无此人 返回-1
	{
		i = -1;
	}
	return i;
}

int CheckAdmin(struct AdminInfo admin)//只有一个管理员，返回1或0
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
void AddScore(int score, int offset)//在当前用户分数记录区的第offset字节改为score //offset从0到14
{
	FILE *fpu, *fpc;
	int num;
	char stemp=(char)score;
	
	fpu = OpenFile("data\\user.dat", "r+");

	num = GetCurUserNum();
	fseek(fpu, (num-1)*45 + 30 + offset + 2, SEEK_CUR);//移动指针到分数区+offset
	WriteFile(&stemp, 1, fpu);//写分数
		
	CloseFile(fpu);
}

int ChangeUser(int num, struct UserInfo user)
{
	FILE *fp;
	int findFlag;

	findFlag = FindUser(user);
	if((findFlag == -1) || (findFlag == num))//不可能是0 //此时无此用户名   后者是因为用户名可以不改
	{
		fp = OpenFile("data\\user.dat", "r+");
		
		fseek(fp, (num-1)*45+2, SEEK_SET);//移动指针
		WriteFile(user.id, 15, fp);
		Encrypt(user.password, num);//加密
		WriteFile(user.password, 15, fp);		
		CloseFile(fp);
		return 0;
	}
	else 
	{
		return 1;
	}
}

int FindUser(struct UserInfo user)//查找用户，并返回编号
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
		
	if(i == (userNum+1))//查无此人 返回-1
	{
		i = -1;
	}
	return i;
}

int GetCurUserNum(void)//返回当前用户编号
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

int GetTotUserNum(void)//返回总的用户人数
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
	userNum = userNum_ge + 10*userNum_shi;//求出总人数	
	
	return userNum;
}
///////////////////以上为李杰雨编写，以下为谭培鑫编写/////////////////////
void InitFiles(void)//建立所需文件，并初始化
{
	FILE *fpu, *fpa;
	//char id[16]="1234567890", password[16]="2333";//初始账号密码
	char id[16]="", password[16]="";
	char num[3]="00";
	int temp;	
	/*用户文件初始化*/
	BuildFile("data\\user.dat");
	fpu = OpenFile("data\\user.dat", "r+");
	if( fread(&temp, 2, 1, fpu) < 1 )//刚建立则初始化
	{
		clearerr(fpu);//清错
		WriteFile(num, 2, fpu);
	}
	CloseFile(fpu);	
	/*管理员文件初始化*/
	BuildFile("data\\admin.dat");
	fpa = OpenFile("data\\admin.dat", "r+");//覆盖书写
	WriteFile(id, 15, fpa);
	WriteFile(password, 15, fpa);	
	CloseFile(fpa);	
	/*配置文件初始化*/
	BuildFile("data\\config.dat");	
	/*当前用户文件初始化*/
	BuildFile("data\\cuser.dat");	
}
void SortTop5(int num[2][5])//传入int指针，函数排序后将用户top5的编号从高到低写入指针指向区域，先科目2再科目3 //若为零，说明人数不足5人
{
	struct UserInfo temp;
	struct SortNode sortList[101];//0到100分
	int userNum;	
	register int i;
	int scoreCount;//表示记录了多少个分数
	int	keMuFlag;//为0时表示处理科目二，为1时表示处理科目三

	userNum = GetTotUserNum();//求出总人数
	
	for(keMuFlag=0; keMuFlag<2; keMuFlag++)
	{
		for(i=0; i<101; i++)//初始化
		{
			sortList[i].count = 0;
			sortList[i].pnum = NULL;
		}
		scoreCount = 0;
		
		for(i=1; i<=userNum; i++)//制作邻接表
		{
			register int countTemp;
			register int scoreTemp;
			
			LoadUser(i, &temp);
			scoreTemp = temp.score[keMuFlag];
			sortList[scoreTemp].count +=1;
			countTemp = sortList[scoreTemp].count;

			if(countTemp == 1)//没有分配内存，则分配10*int内存
			{
				sortList[scoreTemp].pnum = (int *)malloc(10*sizeof(int));

				if(sortList[scoreTemp].pnum == NULL)
				{
					//Error(MEM_LACK);
				}
			}
			if(countTemp == 11)//pnum的内存刚好不够了，再分50*int
			{
				sortList[scoreTemp].pnum = (int *)realloc(sortList[scoreTemp].pnum ,50*sizeof(int));
				if(sortList[scoreTemp].pnum == NULL)
				{
					//Error(MEM_LACK);
				}			
			}
			if(countTemp == 51)//pnum的内存又刚好不够了，再分100*int//最多有100个人
			{
				sortList[scoreTemp].pnum = (int *)realloc(sortList[scoreTemp].pnum ,100*sizeof(int));
				if(sortList[scoreTemp].pnum == NULL)
				{
					//Error(MEM_LACK);
				}				
			}
			( sortList[scoreTemp].pnum )[countTemp-1] = i;
				
		}

		for(i=100; i>=0; i--)//遍历邻接表
		{
			if(sortList[i].count != 0)//分数为i的有人
			{
				register int j=sortList[i].count, k;
				
				if(j+scoreCount > 5)//满5个分数了
				{
					j = 5-scoreCount;//减掉后面的人员				
				}
				
				k = j;
				for(j=0; j<k; j++)//记入传进来的数组指针
				{
					num[keMuFlag][scoreCount]= ( sortList[i].pnum )[j];//又有[]又有.时 ，结构数组的成员又取数组成员 必须加括号
					scoreCount++;
				}
			}
			if(scoreCount == 5)//够5人
			{
				break;
			}
		}
		
		for(i=100; i>=0; i--)//释放内存
		{
			if(sortList[i].pnum != NULL)
			{
				free(sortList[i].pnum);
			}
		}	
	}
}

void Encrypt(char *plainText, int seed)//将明文字符串通过随机数异或加密//只能加密最高位为0的ascii码
{
	int len, i;
	char r;
	
	len = strlen(plainText);
	srand(seed);
	
	for(i=0; i<len; i++)
	{
		r = (char)rand();
		r |= 0x80;//保证r与字符异或后不出现‘\0’
		
		plainText[i] ^= r;
	}
}

void Decode(char *cipherText, int seed)//解码
{
	int len, i;
	char r;
	
	len = strlen(cipherText);
	srand(seed);
	
	for(i=0; i<len; i++)
	{
		r = (char)rand();
		r |= 0x80;//保证r与字符异或后不出现‘\0’
		
		cipherText[i] ^= (char)r;	
	}
}

