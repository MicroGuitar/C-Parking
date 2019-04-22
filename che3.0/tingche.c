#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>
#include"tingche.h"
#include"move.h"
#include"svga.h"
#include"shuru.h"
#include"ourtime.h"
 struct POINT
{   
    char car[3];
	char username[10];
	char password[10];  
    char time[10]; 	
};
void _parking(int floor,int k,int pos,int *flag)
{
	FILE *fp;
	int z;
	char a[7]={'\0'};//存储账号的数组
	char b[7]={'\0'};//存储密码的数组 
	char h1,h2,m1,m2,s1,s2;
	char c[7]={'\0'};//存储time的数组
	char d[2]={'\0'};//用于判断车辆类型	
	struct POINT parkingnum[8];//八个停车
	
	
	switch(floor)//停车时间
	{
		case 1:if((fp=fopen("message//time1.txt","rt+"))==NULL)
               {
	               exit(1);	
               }
			   break;
		case 2:if((fp=fopen("message//time2.txt","rt+"))==NULL)
               {
	               exit(1);	
               }
			   break;
		case 3:if((fp=fopen("message//time3.txt","rt+"))==NULL)
               {
	               exit(1);	
               }
			   break;
	}
	

	for(z=0;z<8;z++)//停车时间信息初始化
	{   
        fgets(parkingnum[z].time,7,fp);
		fseek(fp,2,SEEK_CUR);
	}
	rewind(fp);
	fclose(fp);
	
	
	switch(floor)//选择停车楼层信息
	{
		case 1:if((fp=fopen("message//floor1.txt","rt+"))==NULL)
               {
	               exit(1);	
               }
			   break;
		case 2:if((fp=fopen("message//floor2.txt","rt+"))==NULL)
               {
	               exit(1);	
               }
			   break;
		case 3:if((fp=fopen("message//floor3.txt","rt+"))==NULL)
               {
	               exit(1);	
               }
			   break;
	}
	for(z=0;z<8;z++)//车位信息初始化
	{   fgets(parkingnum[z].car,2,fp);
        fseek(fp,1,SEEK_CUR);
        fgets(parkingnum[z].username,7,fp);//六位数账号
		fseek(fp,1,SEEK_CUR);
		fgets(parkingnum[z].password,7,fp);//六位数密码
		fseek(fp,2,SEEK_CUR);
	}
	rewind(fp);
	
	switch(k)
	{
		case 0:
				d[0]='0';
				break;
		case 1:
				d[0]='1';
				break;
		case 2:
				d[0]='2';
				break;
	}
	
	switch(pos)//选择停车位信息
	{
		case 1:
				if(((strcmp(parkingnum[0].username,"usernm"))==0)&&((strcmp(parkingnum[0].password,"passwd"))==0))//判断是否有车
				{	
					move1(k);//车辆移动函数
					SVGA_PartBmp(158,372,176,481,255,150,"sm\\save.bmp");//贴图 登录界面
					inputch(315,175,530,215,a);		// 输入账号
					strcpy(parkingnum[0].username,a);//传递账号
					inputpassword(315,238,538,278,b);//输入密码
					strcpy(parkingnum[0].password,b);//传递密码
					timeread(&h1, &h2, &m1, &m2, &s1, &s2);//获取时间信息
					c[0]=h1;//将时间信息存入数组
					c[1]=h2;
					c[2]=m1;
					c[3]=m2;
					c[4]=s1;
					c[5]=s2;
					stpcpy(parkingnum[0].time,c);
					strcpy(parkingnum[0].car,d);//传递车型
					SVGA_PartBmp(175,394,161,481,245,155,"pic\\inok.bmp");//贴图 停车成功
					delay(300);	
					*flag=0;
				}
				else
				{
					SVGA_PartBmp(126,352,154,498,230,135,"pic\\pfail.bmp");//贴图 登录界面
					delay(1200);
				}
				break;
		
	
		case 2:
				if(((strcmp(parkingnum[1].username,"usernm"))==0)&&((strcmp(parkingnum[1].password,"passwd"))==0))//判断是否有车
				{	
					move2(k);//车辆移动函数
					SVGA_PartBmp(158,372,176,481,255,150,"sm\\save.bmp");//贴图 登录界面
					inputch(315,175,530,215,a);		// 输入账号
					strcpy(parkingnum[1].username,a);//传递账号
					inputpassword(315,238,538,278, b);//输入密码
					strcpy(parkingnum[1].password,b);//传递密码
					timeread(&h1, &h2, &m1, &m2, &s1, &s2);//获取时间信息
					c[0]=h1;//将时间信息存入数组
					c[1]=h2;
					c[2]=m1;
					c[3]=m2;
					c[4]=s1;
					c[5]=s2;
					stpcpy(parkingnum[1].time,c);
					strcpy(parkingnum[1].car,d);//传递车型
					SVGA_PartBmp(175,394,161,481,245,155,"pic\\inok.bmp");//贴图 停车成功
					delay(300);
					*flag=0;
				}
				else
				{
					SVGA_PartBmp(126,352,154,498,230,135,"pic\\pfail.bmp");//贴图 登录界面
					delay(1200);
				}
				break;
	
		case 3:
				if(((strcmp(parkingnum[2].username,"usernm"))==0)&&((strcmp(parkingnum[2].password,"passwd"))==0))//判断是否有车
				{	
					move3(k);//车辆移动函数
					SVGA_PartBmp(158,372,176,481,255,150,"sm\\save.bmp");//贴图 登录界面
					inputch(315,175,530,215,a);		// 输入账号
					strcpy(parkingnum[2].username,a);//传递账号
					inputpassword(315,238,538,278, b);//输入密码
					strcpy(parkingnum[2].password,b);//传递密码
					timeread(&h1, &h2, &m1, &m2, &s1, &s2);//获取时间信息
					c[0]=h1;//将时间信息存入数组
					c[1]=h2;
					c[2]=m1;
					c[3]=m2;
					c[4]=s1;
					c[5]=s2;
					stpcpy(parkingnum[2].time,c);
					strcpy(parkingnum[2].car,d);//传递车型
					SVGA_PartBmp(175,394,161,481,245,155,"pic\\inok.bmp");//贴图 停车成功
					delay(300);
					*flag=0;
				}
				else
				{
					SVGA_PartBmp(126,352,154,498,230,135,"pic\\pfail.bmp");//贴图 登录界面
					delay(1200);
				}
				break;
	
		case 4:
				if(((strcmp(parkingnum[3].username,"usernm"))==0)&&((strcmp(parkingnum[3].password,"passwd"))==0))//判断是否有车
				{	
					move4(k);//车辆移动函数
					SVGA_PartBmp(158,372,176,481,255,150,"sm\\save.bmp");//贴图 登录界面
					inputch(315,175,530,215,a);		// 输入账号
					strcpy(parkingnum[3].username,a);//传递账号
					inputpassword(315,238,538,278, b);//输入密码
					strcpy(parkingnum[3].password,b);//传递密码
					timeread(&h1, &h2, &m1, &m2, &s1, &s2);//获取时间信息
					c[0]=h1;//将时间信息存入数组
					c[1]=h2;
					c[2]=m1;
					c[3]=m2;
					c[4]=s1;
					c[5]=s2;
					stpcpy(parkingnum[3].time,c);
					strcpy(parkingnum[3].car,d);//传递车型
					SVGA_PartBmp(175,394,161,481,245,155,"pic\\inok.bmp");//贴图 停车成功
					delay(300);
					*flag=0;
				}
				else
				{
					SVGA_PartBmp(126,352,154,498,230,135,"pic\\pfail.bmp");//贴图 登录界面
					delay(1200);
				}
				break;
		case 5:
				if(((strcmp(parkingnum[4].username,"usernm"))==0)&&((strcmp(parkingnum[4].password,"passwd"))==0))//判断是否有车
				{	
					move5(k);//车辆移动函数
					SVGA_PartBmp(158,372,176,481,255,150,"sm\\save.bmp");//贴图 登录界面
					inputch(315,175,530,215,a);		// 输入账号
					strcpy(parkingnum[4].username,a);//传递账号
					inputpassword(315,238,538,278, b);//输入密码
					strcpy(parkingnum[4].password,b);//传递密码
					timeread(&h1, &h2, &m1, &m2, &s1, &s2);//获取时间信息
					c[0]=h1;//将时间信息存入数组
					c[1]=h2;
					c[2]=m1;
					c[3]=m2;
					c[4]=s1;
					c[5]=s2;
					stpcpy(parkingnum[4].time,c);
					strcpy(parkingnum[4].car,d);//传递车型
					SVGA_PartBmp(175,394,161,481,245,155,"pic\\inok.bmp");//贴图 停车成功
					delay(300);
					*flag=0;
				}
				else
				{
					SVGA_PartBmp(126,352,154,498,230,135,"pic\\pfail.bmp");//贴图 登录界面
					delay(1200);
				}
				break;
		case 6:
				if(((strcmp(parkingnum[5].username,"usernm"))==0)&&((strcmp(parkingnum[5].password,"passwd"))==0))//判断是否有车
				{	
					move6(k);//车辆移动函数
					SVGA_PartBmp(158,372,176,481,255,150,"sm\\save.bmp");//贴图 登录界面
					inputch(315,175,530,215,a);		// 输入账号
					strcpy(parkingnum[5].username,a);//传递账号
					inputpassword(315,238,538,278, b);//输入密码
					strcpy(parkingnum[5].password,b);//传递密码
					timeread(&h1, &h2, &m1, &m2, &s1, &s2);//获取时间信息
					c[0]=h1;//将时间信息存入数组
					c[1]=h2;
					c[2]=m1;
					c[3]=m2;
					c[4]=s1;
					c[5]=s2;
					stpcpy(parkingnum[5].time,c);
					strcpy(parkingnum[5].car,d);//传递车型
					SVGA_PartBmp(175,394,161,481,245,155,"pic\\inok.bmp");//贴图 停车成功
					delay(300);
					*flag=0;
				}
				else
				{
					SVGA_PartBmp(126,352,154,498,230,135,"pic\\pfail.bmp");//贴图 登录界面
					delay(1200);
				}
				break;
	
		case 7:
				if(((strcmp(parkingnum[6].username,"usernm"))==0)&&((strcmp(parkingnum[6].password,"passwd"))==0))//判断是否有车
				{	
					move7(k);//车辆移动函数
					SVGA_PartBmp(158,372,176,481,255,150,"sm\\save.bmp");//贴图 登录界面
					inputch(315,175,530,215,a);		// 输入账号
					strcpy(parkingnum[6].username,a);//传递账号
					inputpassword(315,238,538,278, b);//输入密码
					strcpy(parkingnum[6].password,b);//传递密码
					timeread(&h1, &h2, &m1, &m2, &s1, &s2);//获取时间信息
					c[0]=h1;//将时间信息存入数组
					c[1]=h2;
					c[2]=m1;
					c[3]=m2;
					c[4]=s1;
					c[5]=s2;
					stpcpy(parkingnum[6].time,c);
					strcpy(parkingnum[6].car,d);//传递车型
					SVGA_PartBmp(175,394,161,481,245,155,"pic\\inok.bmp");//贴图 停车成功
					delay(300);
					*flag=0;
				}
				else
				{
					SVGA_PartBmp(126,352,154,498,230,135,"pic\\pfail.bmp");//贴图 登录界面
					delay(1200);
				}
				break;
		case 8:
				if(((strcmp(parkingnum[7].username,"usernm"))==0)&&((strcmp(parkingnum[7].password,"passwd"))==0))//判断是否有车
				{	
					move8(k);//车辆移动函数
					SVGA_PartBmp(158,372,176,481,255,150,"sm\\save.bmp");//贴图 登录界面
					inputch(315,175,530,215,a);		// 输入账号
					strcpy(parkingnum[7].username,a);//传递账号
					inputpassword(315,238,538,278, b);//输入密码
					strcpy(parkingnum[7].password,b);//传递密码
					timeread(&h1, &h2, &m1, &m2, &s1, &s2);//获取时间信息
					c[0]=h1;//将时间信息存入数组
					c[1]=h2;
					c[2]=m1;
					c[3]=m2;
					c[4]=s1;
					c[5]=s2;
					stpcpy(parkingnum[7].time,c);
					strcpy(parkingnum[7].car,d);//传递车型
					SVGA_PartBmp(175,394,161,481,245,155,"pic\\inok.bmp");//贴图 停车成功
					delay(300);
					*flag=0;
				}
				else
				{
					SVGA_PartBmp(126,352,154,498,230,135,"pic\\pfail.bmp");//贴图 登录界面
					delay(1200);
				}
				break;
	}
	
	for(z=0;z<8;z++)//将数据写入文件中保存
	{    fwrite(parkingnum[z].car,1,1,fp);
         fputc(' ',fp);
	     fwrite(parkingnum[z].username,6,1,fp);
		 fputc(' ',fp);
		 fwrite(parkingnum[z].password,6,1,fp);
		 fputc('\n',fp);
	}
	
	rewind(fp);
	fclose(fp);
	
	
    switch(floor)
	{
		case 1:if((fp=fopen("message//time1.txt","rt+"))==NULL)
               {
	               exit(1);	
               }
			   break;
		case 2:if((fp=fopen("message//time2.txt","rt+"))==NULL)
               {
	               exit(1);	
               }
			   break;
		case 3:if((fp=fopen("message//time3.txt","rt+"))==NULL)
               {
	               exit(1);	
               }
			   break;
	}
	for(z=0;z<8;z++)//存入停车时间信息
	{
		fwrite(parkingnum[z].time,6,1,fp);
		fputc('\n',fp);
	}
	rewind(fp);
    fclose(fp);
}