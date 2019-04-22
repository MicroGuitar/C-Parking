#include<stdio.h>
#include"showcar.h"
#include"shuru.h"
#include"enter.h"
#include"ourtime.h"
#include"svga.h"
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include"showinfo.h"
#include<dos.h>


 struct POINT
{   
    char car[3];
	char username[10];
	char password[10];  
    char time[10]; 	
};

void takecar(int *flag,int floor)//取车函数
{
	FILE *fp;
	int z;//循环用量
	int f;	//不同车型对应费用
	int pos=0;
	char k;//存车型
	char a[7]={'\0'};  //取车用户名
	char b[7]={'\0'};  //取车密码	
	char c[9]={'\0'};  //取车时间
	char d[2];//读出价格信息
	char g;		//匹配车型时使用
	struct POINT parkingnum[8];//一层8个车位
	
	while(bioskey(1))//清除键盘缓存
	{
		getch();
	}
	
	SVGA_SetMode(0X111);
	switch(floor)	//匹配楼层时间信息
	{
		case 1:if((fp=fopen("message//time1.txt","rt+"))==NULL)
               {
	               exit(1);	
               }
			   SVGA_PartBmp(0,480,0,640,0,0,"pic\\1f.bmp");
			   break;
		case 2:if((fp=fopen("message//time2.txt","rt+"))==NULL)
               {
	               exit(1);	
               }
			   SVGA_PartBmp(0,480,0,640,0,0,"pic\\2f.bmp");
			   break;
		case 3:if((fp=fopen("message//time3.txt","rt+"))==NULL)
               {
	               exit(1);	
               }
			   SVGA_PartBmp(0,480,0,640,0,0,"pic\\3f.bmp");
			   break;
	}
	showcar(floor);
    chewei();//剩余车位	
	for(z=0;z<8;z++)
	{   
        fgets(parkingnum[z].time,7,fp);
		fseek(fp,2,SEEK_CUR);
	}
	rewind(fp);
	fclose(fp);	
	
	switch(floor)	//匹配楼层车位信息
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
	
	for(z=0;z<8;z++)
	{   
        fgets(parkingnum[z].car,2,fp);
        fseek(fp,1,SEEK_CUR);
        fgets(parkingnum[z].username,7,fp);
		fseek(fp,1,SEEK_CUR);
		fgets(parkingnum[z].password,7,fp);
		fseek(fp,2,SEEK_CUR);
	}
	rewind(fp);
	fclose(fp);
	
	
	pos=selectpos();
	k=parkingnum[pos-1].car[0];
	
	switch(k)  //导入车型信息
	{
		case '0':
				g='0';
				break;
		case '1':
				g='1';	
				break;
		case '2':
				g='2';
				break;		
	}
	
	if(g=='0')//选择小型车
	{
		if((fp=fopen("message//f1.txt","rt+"))==NULL)
		{
			exit(0);
		}
		fgets(d,2,fp);
		f=atoi(d);
	}
	else if(g=='1')//选择大型车
	{
		if((fp=fopen("message//f2.txt","rt+"))==NULL)
		{
			exit(0);
		}
		fgets(d,2,fp);
		f=atoi(d);
	}
	else if(g=='2')//选择特种车
	{
		if((fp=fopen("message//f3.txt","rt+"))==NULL)
		{
			exit(0);
		}
		fgets(d,2,fp);
		f=atoi(d);
	}	
	rewind(fp);
	fclose(fp);
	switch(pos)
	{
		case 0:
				*flag=7;//返回
				break;
		case 1:
				if('k'!=parkingnum[0].car[0])
				{
					SVGA_PartBmp(158,372,176,481,255,150,"sm\\save.bmp");//贴图 取车输入账号密码
					inputch(315,175,530,215,a);		// 输入账号
					inputpassword(315,238,538,278, b);//输入密码
					if(((strcmp(parkingnum[0].username,a))==0)&&((strcmp(parkingnum[0].password,b)==0)))//判断帐号密码是否输入正确
					{
						SVGA_PartBmp(154,334,186,463,255,150,"pic\\takeok.bmp");//贴图 取车成功
						delay(900);
						SVGA_PartBmp(137,380,145,516,200,140,"pic\\zhang.bmp");//贴图 收据 
						SVGA_ENtext16(360,154,parkingnum[0].username,_WHITE);//输出停车账号
						SVGA_ENtext16(360,192,parkingnum[0].password,_WHITE);//输出停车密码
						strcpy(c,parkingnum[0].time);
						parktime(c,f);//调用函数 计算停车时间 收费
						strcpy(parkingnum[0].username,"usernm");		//还原车位信息
						strcpy(parkingnum[0].password,"passwd");
						strcpy(parkingnum[0].time,"shjian");
						strcpy(parkingnum[0].car,"k");
						getch();
						*flag=0;
						break;//按任意键返回selectm界面
					}
					else
					{
						SVGA_PartBmp(146,325,180,455,255,150,"pic\\fail2.bmp");//贴图 密码错误 停车失败
						delay(1200);
					}
				}
				else
				{
					SVGA_PartBmp(146,325,180,455,255,150,"pic\\fail1.bmp");//贴图 此处无车 请重新选择！
					delay(1200);
				}
				break;
		case 2:
				if('k'!=parkingnum[1].car[0])
				{
					SVGA_PartBmp(158,372,176,481,255,150,"sm\\save.bmp");//贴图 取车输入账号密码
					inputch(315,175,530,215,a);		// 输入账号
					inputpassword(315,238,538,278, b);//输入密码
					if(((strcmp(parkingnum[1].username,a))==0)&&((strcmp(parkingnum[1].password,b)==0)))//判断帐号密码是否输入正确
					{
						SVGA_PartBmp(154,334,186,463,255,150,"pic\\takeok.bmp");//贴图 取车成功
						delay(900);
						SVGA_PartBmp(137,380,145,516,200,140,"pic\\zhang.bmp");//贴图 收据 
						SVGA_ENtext16(360,154,parkingnum[1].username,_WHITE);//输出停车账号
						SVGA_ENtext16(360,192,parkingnum[1].password,_WHITE);//输出停车密码
						strcpy(c,parkingnum[1].time);
						parktime(c,f);//调用函数 计算停车时间 收费
						strcpy(parkingnum[1].username,"usernm");		//还原车位信息
						strcpy(parkingnum[1].password,"passwd");
						strcpy(parkingnum[1].time,"shjian");
						strcpy(parkingnum[1].car,"k");
						getch();
						*flag=0;
						break;//按任意键返回selectm界面
					}
					else
					{
						SVGA_PartBmp(146,325,180,455,255,150,"pic\\fail2.bmp");//贴图 密码错误 停车失败
						delay(1200); 
					}
				}
				else
				{
					SVGA_PartBmp(146,325,180,455,255,150,"pic\\fail1.bmp");//贴图 此处无车 请重新选择！
					delay(1200);
				}
				break;
		case 3:
				if('k'!=parkingnum[2].car[0])
				{
					SVGA_PartBmp(158,372,176,481,255,150,"sm\\save.bmp");//贴图 取车输入账号密码
					inputch(315,175,530,215,a);		// 输入账号
					inputpassword(315,238,538,278, b);//输入密码
					if(((strcmp(parkingnum[2].username,a))==0)&&((strcmp(parkingnum[2].password,b)==0)))//判断帐号密码是否输入正确
					{
						SVGA_PartBmp(154,334,186,463,255,150,"pic\\takeok.bmp");//贴图 取车成功
						delay(900);
						SVGA_PartBmp(137,380,145,516,200,140,"pic\\zhang.bmp");//贴图 收据 
						SVGA_ENtext16(360,154,parkingnum[2].username,_WHITE);//输出停车账号
						SVGA_ENtext16(360,192,parkingnum[2].password,_WHITE);//输出停车密码
						strcpy(c,parkingnum[2].time);
						parktime(c,f);//调用函数 计算停车时间 收费
						strcpy(parkingnum[2].username,"usernm");		//还原车位信息
						strcpy(parkingnum[2].password,"passwd");
						strcpy(parkingnum[2].time,"shjian");
						strcpy(parkingnum[2].car,"k");
						getch();
						*flag=0;
						break;//按任意键返回selectm界面
					}
					else
					{
						SVGA_PartBmp(146,325,180,455,255,150,"pic\\fail2.bmp");//贴图 密码错误 停车失败
						delay(1200); 
					}
				}
				else
				{
					SVGA_PartBmp(146,325,180,455,255,150,"pic\\fail1.bmp");//贴图 此处无车 请重新选择！
					delay(1200);
				}
				break;
				
		case 4:
				if('k'!=parkingnum[3].car[0])
				{
					SVGA_PartBmp(158,372,176,481,255,150,"sm\\save.bmp");//贴图 取车输入账号密码
					inputch(315,175,530,215,a);		// 输入账号
					inputpassword(315,238,538,278, b);//输入密码
					if(((strcmp(parkingnum[3].username,a))==0)&&((strcmp(parkingnum[3].password,b)==0)))//判断帐号密码是否输入正确
					{
						SVGA_PartBmp(154,334,186,463,255,150,"pic\\takeok.bmp");//贴图 取车成功
						delay(900);
						SVGA_PartBmp(137,380,145,516,200,140,"pic\\zhang.bmp");//贴图 收据 
						SVGA_ENtext16(360,154,parkingnum[3].username,_WHITE);//输出停车账号
						SVGA_ENtext16(360,192,parkingnum[3].password,_WHITE);//输出停车密码
						strcpy(c,parkingnum[3].time);
						parktime(c,f);//调用函数 计算停车时间 收费
						strcpy(parkingnum[3].username,"usernm");		//还原车位信息
						strcpy(parkingnum[3].password,"passwd");
						strcpy(parkingnum[3].time,"shjian");
						strcpy(parkingnum[3].car,"k");
						getch();
						*flag=0;
						break;//按任意键返回selectm界面
					}
					else
					{
						SVGA_PartBmp(146,325,180,455,255,150,"pic\\fail2.bmp");//贴图 密码错误 停车失败
						delay(1200); 
					}
				}
				else
				{
					SVGA_PartBmp(146,325,180,455,255,150,"pic\\fail1.bmp");//贴图 此处无车 请重新选择！
					delay(1200);
				}
				break;
		case 5:
				if('k'!=parkingnum[4].car[0])
				{
					SVGA_PartBmp(158,372,176,481,255,150,"sm\\save.bmp");//贴图 取车输入账号密码
					inputch(315,175,530,215,a);		// 输入账号
					inputpassword(315,238,538,278, b);//输入密码
					if(((strcmp(parkingnum[4].username,a))==0)&&((strcmp(parkingnum[4].password,b)==0)))//判断帐号密码是否输入正确
					{
						SVGA_PartBmp(154,334,186,463,255,150,"pic\\takeok.bmp");//贴图 取车成功
						delay(900);
						SVGA_PartBmp(137,380,145,516,200,140,"pic\\zhang.bmp");//贴图 收据 
						SVGA_ENtext16(360,154,parkingnum[4].username,_WHITE);//输出停车账号
						SVGA_ENtext16(360,192,parkingnum[4].password,_WHITE);//输出停车密码
						strcpy(c,parkingnum[4].time);
						parktime(c,f);//调用函数 计算停车时间 收费
						strcpy(parkingnum[4].username,"usernm");		//还原车位信息
						strcpy(parkingnum[4].password,"passwd");
						strcpy(parkingnum[4].time,"shjian");
						strcpy(parkingnum[4].car,"k");
						getch();
						*flag=0;
						break;//按任意键返回selectm界面
					}
					else
					{
						SVGA_PartBmp(146,325,180,455,255,150,"pic\\fail2.bmp");//贴图 密码错误 停车失败
						delay(1200); 
					}
				}
				else
				{
					SVGA_PartBmp(146,325,180,455,255,150,"pic\\fail1.bmp");//贴图 此处无车 请重新选择！
					delay(1200);
				}
				break;
		case 6:	
				if('k'!=parkingnum[5].car[0])
				{
					SVGA_PartBmp(158,372,176,481,255,150,"sm\\save.bmp");//贴图 取车输入账号密码
					inputch(315,175,530,215,a);		// 输入账号
					inputpassword(315,238,538,278, b);//输入密码
					if(((strcmp(parkingnum[5].username,a))==0)&&((strcmp(parkingnum[5].password,b)==0)))//判断帐号密码是否输入正确
					{
						SVGA_PartBmp(154,334,186,463,255,150,"pic\\takeok.bmp");//贴图 取车成功
						delay(900);
						SVGA_PartBmp(137,380,145,516,200,140,"pic\\zhang.bmp");//贴图 收据 
						SVGA_ENtext16(360,154,parkingnum[5].username,_WHITE);//输出停车账号
						SVGA_ENtext16(360,192,parkingnum[5].password,_WHITE);//输出停车密码
						strcpy(c,parkingnum[5].time);
						parktime(c,f);//调用函数 计算停车时间 收费
						strcpy(parkingnum[5].username,"usernm");		//还原车位信息
						strcpy(parkingnum[5].password,"passwd");
						strcpy(parkingnum[5].time,"shjian");
						strcpy(parkingnum[5].car,"k");
						getch();
						*flag=0;
						break;//按任意键返回selectm界面
					}
					else
					{
						SVGA_PartBmp(146,325,180,455,255,150,"pic\\fail2.bmp");//贴图 密码错误 停车失败
						delay(1200); 
					}
				}
				else
				{
					SVGA_PartBmp(146,325,180,455,255,150,"pic\\fail1.bmp");//贴图 此处无车 请重新选择！
					delay(1200);
				}
				break;
		case 7:
				if('k'!=parkingnum[6].car[0])
				{
					SVGA_PartBmp(158,372,176,481,255,150,"sm\\save.bmp");//贴图 取车输入账号密码
					inputch(315,175,530,215,a);		// 输入账号
					inputpassword(315,238,538,278, b);//输入密码
					if(((strcmp(parkingnum[6].username,a))==0)&&((strcmp(parkingnum[6].password,b)==0)))//判断帐号密码是否输入正确
					{
						SVGA_PartBmp(154,334,186,463,255,150,"pic\\takeok.bmp");//贴图 取车成功
						delay(900);
						SVGA_PartBmp(137,380,145,516,200,140,"pic\\zhang.bmp");//贴图 收据 
						SVGA_ENtext16(360,154,parkingnum[6].username,_WHITE);//输出停车账号
						SVGA_ENtext16(360,192,parkingnum[6].password,_WHITE);//输出停车密码
						strcpy(c,parkingnum[6].time);
						parktime(c,f);//调用函数 计算停车时间 收费
						strcpy(parkingnum[6].username,"usernm");		//还原车位信息
						strcpy(parkingnum[6].password,"passwd");
						strcpy(parkingnum[6].time,"shjian");
						strcpy(parkingnum[6].car,"k");
						getch();
						*flag=0;
						break;//按任意键返回selectm界面
					}
					else
					{
						SVGA_PartBmp(146,325,180,455,255,150,"pic\\fail2.bmp");//贴图 密码错误 停车失败
						delay(1200); 
					}
				}
				else
				{
					SVGA_PartBmp(146,325,180,455,255,150,"pic\\fail1.bmp");//贴图 此处无车 请重新选择！
					delay(1200);
				}
				break;

		case 8:
				if('k'!=parkingnum[7].car[0])
				{
					SVGA_PartBmp(158,372,176,481,255,150,"sm\\save.bmp");//贴图 取车输入账号密码
					inputch(315,175,530,215,a);		// 输入账号
					inputpassword(315,238,538,278, b);//输入密码
					if(((strcmp(parkingnum[7].username,a))==0)&&((strcmp(parkingnum[7].password,b)==0)))//判断帐号密码是否输入正确
					{
						SVGA_PartBmp(154,334,186,463,255,150,"pic\\takeok.bmp");//贴图 取车成功
						delay(900);
						SVGA_PartBmp(137,380,145,516,200,140,"pic\\zhang.bmp");//贴图 收据 
						SVGA_ENtext16(360,154,parkingnum[7].username,_WHITE);//输出停车账号
						SVGA_ENtext16(360,192,parkingnum[7].password,_WHITE);//输出停车密码
						strcpy(c,parkingnum[7].time);
						parktime(c,f);//调用函数 计算停车时间 收费
						strcpy(parkingnum[7].username,"usernm");		//还原车位信息
						strcpy(parkingnum[7].password,"passwd");
						strcpy(parkingnum[7].time,"shjian");
						strcpy(parkingnum[7].car,"k");
						getch();
						*flag=0;
						break;//按任意键返回selectm界面
					}
					else
					{
						SVGA_PartBmp(146,325,180,455,255,150,"pic\\fail2.bmp");//贴图 密码错误 停车失败
						delay(1200); 
					}
				}
				else
				{
					SVGA_PartBmp(146,325,180,455,255,150,"pic\\fail1.bmp");//贴图 此处无车 请重新选择！
					delay(1200);
				}
				break;
		case 9://上楼
				if(1==floor)
				{
					*flag=9;//一楼上二楼
				}
				if(2==floor)
				{
					*flag=10;//二楼上三楼
				}
				break;
		case 10://下楼
				if(2==floor)
				{
					*flag=8;//一楼上二楼
				}
				if(3==floor)
				{
					*flag=9;//二楼上三楼
				}
				break;
	}   
	
	switch(floor)
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
	for(z=0;z<8;z++)
	{
		 fwrite(parkingnum[z].car,1,1,fp);
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
	for(z=0;z<8;z++)
	{
		fwrite(parkingnum[z].time,6,1,fp);
		fputc('\n',fp);
	}
	rewind(fp);
    fclose(fp);
	
}

void parktime(char *c, int f)		//计算停车时间,费用函数
{
	char h1,h2,m1,m2,s1,s2;
	long int time1, time2, money;
	char fare[8]={1,1,1,1,1,1};
	h1=c[0];
	h2=c[1];
	m1=c[2];
	m2=c[3];
	s1=c[4];
	s2=c[5];
	c[0]=h1;
	c[1]=h2;
	c[2]=':';
	c[3]=m1;
	c[4]=m2;
	c[5]=':';
	c[6]=s1;
	c[7]=s2;
	SVGA_ENtext16(360,235,c,_WHITE);//输出停车时间
	time1=((((int)h1-48)*10+((int)h2-48))*3600+(((int)m1-48)*10+((int)m2-48))*60+(((int)s1-48)*10+((int)s2-48)));
	timeread(&h1, &h2, &m1, &m2, &s1, &s2);
	time2=((((int)h1-48)*10+((int)h2-48))*3600+(((int)m1-48)*10+((int)m2-48))*60+(((int)s1-48)*10+((int)s2-48)));
	c[0]=h1;
	c[1]=h2;
	c[2]=':';
	c[3]=m1;
	c[4]=m2;
	c[5]=':';
	c[6]=s1;
	c[7]=s2;	
	SVGA_ENtext16(360,278,c,_WHITE);//输出取车时间
	money=((time2-time1)*f);
	itoa(money,fare,10);
	SVGA_ENtext16(360,320,fare,_WHITE);//输出停车费用
	
}