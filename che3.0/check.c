#include"svga.h"
#include"mouse.h"
#include<stdlib.h>
#include<string.h>
#include"mode.h"
#include"move.h"
#include"shuru.h"
#include"showcar.h"
#include"showtime.h"
#include"showinfo.h"
#include"enter.h"
void check(int *flag,int floor)
{

	FILE *fp;
	int z;
	int f;	//不同车型对应费用
	int pos=0;
	char k;	//存车型
	char c[9]={'\0'};  //取车时间
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
		f=1;
	}
	else if(g=='1')//选择大型车
	{
		f=2;
	}
	else if(g=='2')//选择特种车
	{
		f=3;
	}	
	
	switch(pos)
	{
		case 0:
				*flag=12;//返回
				break;
		case 1:
				if('k'!=parkingnum[0].car[0])
				{
					SVGA_PartBmp(137,380,145,516,200,140,"pic\\shouju.bmp");//贴图 账号密码背景
					SVGA_ENtext16(360,154,parkingnum[0].username,_WHITE);//输出停车账号
					SVGA_ENtext16(360,192,parkingnum[0].password,_WHITE);//输出停车密码
					strcpy(c,parkingnum[0].time);
					checkt(c);//调用函数 计算停车时间 收费
					/*while(1)//闪烁 按任意键返回
					{
						SVGA_PartBmp(158,372,176,481,255,150,"pic\\inok.bmp");//贴图 取车成功
						
					
						break;//按任意键返回selectm界面
					}*/
					getch();
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
					SVGA_PartBmp(137,380,145,516,200,140,"pic\\shouju.bmp");//贴图 账号密码背景
					SVGA_ENtext16(360,154,parkingnum[1].username,_WHITE);//输出停车账号
					SVGA_ENtext16(360,192,parkingnum[1].password,_WHITE);//输出停车密码
					strcpy(c,parkingnum[1].time);
					checkt(c);//调用函数 计算停车时间 收费
					/*while(1)//闪烁 按任意键返回
					{
						SVGA_PartBmp(158,372,176,481,255,150,"pic\\inok.bmp");//贴图 取车成功
						
						getch();
						*flag=0;
						break;//按任意键返回selectm界面
					}*/
					getch();
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
					SVGA_PartBmp(137,380,145,516,200,140,"pic\\shouju.bmp");//贴图 账号密码背景
					SVGA_ENtext16(360,154,parkingnum[2].username,_WHITE);//输出停车账号
					SVGA_ENtext16(360,192,parkingnum[2].password,_WHITE);//输出停车密码
					strcpy(c,parkingnum[2].time);
					checkt(c);//调用函数 计算停车时间 收费
					/*while(1)//闪烁 按任意键返回
					{
						SVGA_PartBmp(158,372,176,481,255,150,"pic\\inok.bmp");//贴图 取车成功
						
						getch();
						*flag=0;
						break;//按任意键返回selectm界面
					}*/
					getch();
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
					SVGA_PartBmp(137,380,145,516,200,140,"pic\\shouju.bmp");//贴图 账号密码背景
					SVGA_ENtext16(360,154,parkingnum[3].username,_WHITE);//输出停车账号
					SVGA_ENtext16(360,192,parkingnum[3].password,_WHITE);//输出停车密码
					strcpy(c,parkingnum[3].time);
					checkt(c);//调用函数 计算停车时间 收费
					/*while(1)//闪烁 按任意键返回
					{
						SVGA_PartBmp(158,372,176,481,255,150,"pic\\inok.bmp");//贴图 取车成功
						
						getch();
						*flag=0;
						break;//按任意键返回selectm界面
					}*/
					getch();
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
					SVGA_PartBmp(137,380,145,516,200,140,"pic\\shouju.bmp");//贴图 账号密码背景
					SVGA_ENtext16(360,154,parkingnum[4].username,_WHITE);//输出停车账号
					SVGA_ENtext16(360,192,parkingnum[4].password,_WHITE);//输出停车密码
					strcpy(c,parkingnum[4].time);
					checkt(c);//调用函数 计算停车时间 收费
					/*while(1)//闪烁 按任意键返回
					{
						SVGA_PartBmp(158,372,176,481,255,150,"pic\\inok.bmp");//贴图 取车成功
						
						getch();
						*flag=0;
						break;//按任意键返回selectm界面
					}*/
					getch();
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
					SVGA_PartBmp(137,380,145,516,200,140,"pic\\shouju.bmp");//贴图 账号密码背景
					SVGA_ENtext16(360,154,parkingnum[5].username,_WHITE);//输出停车账号
					SVGA_ENtext16(360,192,parkingnum[5].password,_WHITE);//输出停车密码
					strcpy(c,parkingnum[5].time);
					checkt(c);//调用函数 计算停车时间 收费
					/*while(1)//闪烁 按任意键返回
					{
						SVGA_PartBmp(158,372,176,481,255,150,"pic\\inok.bmp");//贴图 取车成功
						
						getch();
						*flag=0;
						break;//按任意键返回selectm界面
					}*/
					getch();
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
					SVGA_PartBmp(137,380,145,516,200,140,"pic\\shouju.bmp");//贴图 账号密码背景
					SVGA_ENtext16(360,154,parkingnum[6].username,_WHITE);//输出停车账号
					SVGA_ENtext16(360,192,parkingnum[6].password,_WHITE);//输出停车密码
					strcpy(c,parkingnum[6].time);
					checkt(c);//调用函数 计算停车时间 收费
					/*while(1)//闪烁 按任意键返回
					{
						SVGA_PartBmp(158,372,176,481,255,150,"pic\\inok.bmp");//贴图 取车成功
						
						getch();
						*flag=0;
						break;//按任意键返回selectm界面
					}*/
					getch();
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
					SVGA_PartBmp(137,380,145,516,200,140,"pic\\shouju.bmp");//贴图 账号密码背景
					SVGA_ENtext16(360,154,parkingnum[7].username,_WHITE);//输出停车账号
					SVGA_ENtext16(360,192,parkingnum[7].password,_WHITE);//输出停车密码
					strcpy(c,parkingnum[7].time);
					checkt(c);//调用函数 计算停车时间 收费
					/*while(1)//闪烁 按任意键返回
					{
						SVGA_PartBmp(158,372,176,481,255,150,"pic\\inok.bmp");//贴图 取车成功
						
						getch();
						*flag=0;
						break;//按任意键返回selectm界面
					}*/
					getch();
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
					*flag=14;//一楼上二楼
				}
				if(2==floor)
				{
					*flag=15;//二楼上三楼
				}
				break;
		case 10://下楼
				if(2==floor)
				{
					*flag=13;//一楼上二楼
				}
				if(3==floor)
				{
					*flag=14;//二楼上三楼
				}
				break;
	}   
}
void checkt(char *c)
{
	char h1,h2,m1,m2,s1,s2;
	int time1, time2;
   //	char fare[8]={'\0'};
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
}