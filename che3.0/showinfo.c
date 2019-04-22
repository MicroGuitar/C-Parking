#include"svga.h"
#include<bios.h>
#include"ourtime.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"showinfo.h"
#include"mouse.h"
struct POINT
{   
    char car[3];
	char username[10];
	char password[10];  
    char time[10]; 	
};
void showinfo(int *flag)
{
	FILE *fp;
	int z;//车位循环
	int g;//代表不同车型
	int f;//不同车型收费
	int t;//停车时间
	int car=0;//停车数量
	int car0=0;//小型车停车数量
	int car1=0;//大型车停车数量
	int car2=0;//特种车停车数量
	int money=0;//停车费用
	long int sum=0;//总停车费用
	char type;
	char c[10];
	char d[2];//读出价格信息
	char time[10]={'\0'};//接收时间信息
	char fare[10]={'\0'};//接收费用信息
	char ncar[10]={'\0'};//存储当前车辆总数信息
	char ncar0[10]={'\0'};//存储当前小型车总数信息
	char ncar1[10]={'\0'};//存储当前大型车总数信息
	char ncar2[10]={'\0'};//存储当前特种车总数信息
	char summ[10]={'\0'};//存储总收入信息
	int MouseX, MouseY, oldx, oldy;//鼠标坐标
	int pic[1024], mouseShape[1024];//鼠标和鼠标移动缓存
	struct POINT parkingnum[8];//八个车位
	SVGA_PartBmp(0,480,0,640,0,0,"pic//info.bmp");
	
	while(bioskey(1))
	{
		getch();
	}
	
	if((fp=fopen("message//floor1.txt","rt+"))==NULL)//打开一楼信息
	{
		exit(1);
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
	if((fp=fopen("message//time1.txt","rt+"))==NULL)
	{
		exit(1);
	}
	for(z=0;z<8;z++)
	{
		fgets(parkingnum[z].time,7,fp);
		fseek(fp,2,SEEK_CUR);
	}
	rewind(fp);
	fclose(fp);
	
	for(z=0;z<4;z++) //一楼一到四号车位
	{	
		if(parkingnum[z].car[0]!='k')
		{
			car++;
			type=parkingnum[z].car[0];//获取车型信息
			switch(type)
			{
				case '0':
						car0++;
						g=0;
					  	if((fp=fopen("message//f1.txt","rt+"))==NULL)
						{
							exit(0);
						}
						fgets(d,2,fp);
						f=atoi(d);
						break;
				case '1':
						car1++;
						g=1;
						if((fp=fopen("message//f2.txt","rt+"))==NULL)
						{
							exit(0);
						}
						fgets(d,2,fp);
						f=atoi(d);
						break;
				case '2':
						car2++;
						g=2;
						if((fp=fopen("message//f3.txt","rt+"))==NULL)
						{
							exit(0);
						}
						fgets(d,2,fp);
						f=atoi(d);
						break;
			}
			rewind(fp);
			fclose(fp);
			if(g==0)
			{
				SVGA_CHtext16(75,75+30*z,"С�ͳ�",_WHITE);
			}
			else if(g==1)
			{
				SVGA_CHtext16(75,75+30*z,"���ͳ�",_WHITE);
			}
			else if(g==2)
			{
				SVGA_CHtext16(75,75+30*z,"���ֳ�",_WHITE);
			}	
		
			*c=*parkingnum[z].time;
			/****停车时间****/
			t=parktime2(parkingnum[z].time);//计算停车时间
			itoa(t,time,10);
			/****停车费用****/		
			money=t*f;//计算停车费用
			itoa(money,fare,10);
			sum+=money;
			if(c[0]!='s')
			{
				SVGA_ENtext16(145,75+z*30,fare,_WHITE);//输出停车费用
				SVGA_ENtext16(200,75+z*30,time,_WHITE);//输出停车时间		
			}
		}			
	}
	
	for(z=4;z<8;z++) //一楼五到八号车位
	{	
		if(parkingnum[z].car[0]!='k')
		{
			car++;
			type=parkingnum[z].car[0];//获取车型信息
			switch(type)
			{
				case '0':
						car0++;
						g=0;
					  	if((fp=fopen("message//f1.txt","rt+"))==NULL)
						{
							exit(0);
						}
						fgets(d,2,fp);
						f=atoi(d);
						break;
				case '1':
						car1++;
						g=1;
						if((fp=fopen("message//f2.txt","rt+"))==NULL)
						{
							exit(0);
						}
						fgets(d,2,fp);
						f=atoi(d);
						break;
				case '2':
						car2++;
						g=2;
						if((fp=fopen("message//f3.txt","rt+"))==NULL)
						{
							exit(0);
						}
						fgets(d,2,fp);
						f=atoi(d);
						break;
			}
			rewind(fp);
			fclose(fp);
			if(g==0)
			{
				SVGA_CHtext16(435,75+30*(z-4),"С�ͳ�",_WHITE);
			}
			else if(g==1)
			{
				SVGA_CHtext16(435,75+30*(z-4),"���ͳ�",_WHITE);
			}
			else if(g==2)
			{
				SVGA_CHtext16(435,75+30*(z-4),"���ֳ�",_WHITE);
			}	
		
			*c=*parkingnum[z].time;
			/****停车时间****/
			t=parktime2(parkingnum[z].time);//计算停车时间
			itoa(t,time,10);
			/****停车费用****/		
			money=t*f;//计算停车费用
			itoa(money,fare,10);
			sum+=money;
			if(c[0]!='s')
			{
				SVGA_ENtext16(505,75+(z-4)*30,fare,_WHITE);//输出停车费用
				SVGA_ENtext16(560,75+(z-4)*30,time,_WHITE);//输出停车时间		
			}	
		}
	}

	if((fp=fopen("message//floor2.txt","rt+"))==NULL)//打开二楼信息
	{
		exit(1);
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
	if((fp=fopen("message//time2.txt","rt+"))==NULL)
	{
		exit(1);
	}
	for(z=0;z<8;z++)
	{
		fgets(parkingnum[z].time,7,fp);
		fseek(fp,2,SEEK_CUR);
	}
	rewind(fp);
	fclose(fp);
	
	for(z=0;z<4;z++) //二楼一到四号车位
	{	
		if(parkingnum[z].car[0]!='k')
		{
			car++;
			type=parkingnum[z].car[0];//获取车型信息
			switch(type)
			{
				case '0':
						car0++;
						g=0;
					  	if((fp=fopen("message//f1.txt","rt+"))==NULL)
						{
							exit(0);
						}
						fgets(d,2,fp);
						f=atoi(d);
						break;
				case '1':
						car1++;
						g=1;
						if((fp=fopen("message//f2.txt","rt+"))==NULL)
						{
							exit(0);
						}
						fgets(d,2,fp);
						f=atoi(d);
						break;
				case '2':
						car2++;
						g=2;
						if((fp=fopen("message//f3.txt","rt+"))==NULL)
						{
							exit(0);
						}
						fgets(d,2,fp);
						f=atoi(d);
						break;
			}
			rewind(fp);
			fclose(fp);
			if(g==0)
			{
				SVGA_CHtext16(75,225+30*z,"С�ͳ�",_WHITE);
			}
			else if(g==1)
			{
				SVGA_CHtext16(75,225+30*z,"���ͳ�",_WHITE);
			}
			else if(g==2)
			{
				SVGA_CHtext16(75,225+30*z,"���ֳ�",_WHITE);
			}	
		
			*c=*parkingnum[z].time;
			/****停车时间****/
			t=parktime2(parkingnum[z].time);//计算停车时间
			itoa(t,time,10);
			/****停车费用****/		
			money=t*f;//计算停车费用
			itoa(money,fare,10);
			sum+=money;
			if(c[0]!='s')
			{
				SVGA_ENtext16(145,225+z*30,fare,_WHITE);//输出停车费用
				SVGA_ENtext16(200,225+z*30,time,_WHITE);//输出停车时间		
			}	
		}
	}

	for(z=4;z<8;z++) //二楼五到八号车位
	{	
		if(parkingnum[z].car[0]!='k')
		{
			car++;
			type=parkingnum[z].car[0];//获取车型信息
			switch(type)
			{
				case '0':
						car0++;
						g=0;
					  	if((fp=fopen("message//f1.txt","rt+"))==NULL)
						{
							exit(0);
						}
						fgets(d,2,fp);
						f=atoi(d);
						break;
				case '1':
						car1++;
						g=1;
						if((fp=fopen("message//f2.txt","rt+"))==NULL)
						{
							exit(0);
						}
						fgets(d,2,fp);
						f=atoi(d);
						break;
				case '2':
						car2++;
						g=2;
						if((fp=fopen("message//f3.txt","rt+"))==NULL)
						{
							exit(0);
						}
						fgets(d,2,fp);
						f=atoi(d);
						break;
			}
			rewind(fp);
			fclose(fp);
			if(g==0)
			{
				SVGA_CHtext16(435,225+30*(z-4),"С�ͳ�",_WHITE);
			}
			else if(g==1)
			{
				SVGA_CHtext16(435,225+30*(z-4),"���ͳ�",_WHITE);
			}
			else if(g==2)
			{
				SVGA_CHtext16(435,225+30*(z-4),"���ֳ�",_WHITE);
			}	
		
			*c=*parkingnum[z].time;
			/****停车时间****/
			t=parktime2(parkingnum[z].time);//计算停车时间
			itoa(t,time,10);
			/****停车费用****/		
			money=t*f;//计算停车费用
			itoa(money,fare,10);
			sum+=money;
			if(c[0]!='s')
			{
				SVGA_ENtext16(505,225+(z-4)*30,fare,_WHITE);//输出停车费用
				SVGA_ENtext16(560,225+(z-4)*30,time,_WHITE);//输出停车时间		
			}
		}			
	}

	if((fp=fopen("message//floor3.txt","rt+"))==NULL)//打开三楼信息
	{
		exit(1);
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
	if((fp=fopen("message//time3.txt","rt+"))==NULL)
	{
		exit(1);
	}
	for(z=0;z<8;z++)
	{
		fgets(parkingnum[z].time,7,fp);
		fseek(fp,2,SEEK_CUR);
	}
	rewind(fp);
	fclose(fp);	
	
	for(z=0;z<4;z++) //三楼一到四号车位
	{	
		if(parkingnum[z].car[0]!='k')
		{
			car++;
			type=parkingnum[z].car[0];//获取车型信息
			switch(type)
			{
				case '0':
						car0++;
						g=0;
					  	if((fp=fopen("message//f1.txt","rt+"))==NULL)
						{
							exit(0);
						}
						fgets(d,2,fp);
						f=atoi(d);
						break;
				case '1':
						car1++;
						g=1;
						if((fp=fopen("message//f2.txt","rt+"))==NULL)
						{
							exit(0);
						}
						fgets(d,2,fp);
						f=atoi(d);
						break;
				case '2':
						car2++;
						g=2;
						if((fp=fopen("message//f3.txt","rt+"))==NULL)
						{
							exit(0);
						}
						fgets(d,2,fp);
						f=atoi(d);
						break;
			}
			rewind(fp);
			fclose(fp);
			if(g==0)
			{
				SVGA_CHtext16(75,370+30*z,"С�ͳ�",_WHITE);
			}
			else if(g==1)
			{
				SVGA_CHtext16(75,370+30*z,"���ͳ�",_WHITE);
			}
			else if(g==2)
			{
				SVGA_CHtext16(75,370+30*z,"���ֳ�",_WHITE);
			}	
		
			*c=*parkingnum[z].time;
			/****停车时间****/
			t=parktime2(parkingnum[z].time);//计算停车时间
			itoa(t,time,10);
			/****停车费用****/		
			money=t*f;//计算停车费用
			itoa(money,fare,10);
			sum+=money;
			if(c[0]!='s')
			{
				SVGA_ENtext16(145,370+z*30,fare,_WHITE);//输出停车费用
				SVGA_ENtext16(200,370+z*30,time,_WHITE);//输出停车时间		
			}
		}			
	}

	for(z=4;z<8;z++) //三楼五到八号车位
	{	
		if(parkingnum[z].car[0]!='k')
		{
			car++;
			type=parkingnum[z].car[0];//获取车型信息
			switch(type)
			{
				case '0':
						car0++;
						g=0;
					  	if((fp=fopen("message//f1.txt","rt+"))==NULL)
						{
							exit(0);
						}
						fgets(d,2,fp);
						f=atoi(d);
						break;
				case '1':
						car1++;
						g=1;
						if((fp=fopen("message//f2.txt","rt+"))==NULL)
						{
							exit(0);
						}
						fgets(d,2,fp);
						f=atoi(d);
						break;
				case '2':
						car2++;
						g=2;
						if((fp=fopen("message//f3.txt","rt+"))==NULL)
						{
							exit(0);
						}
						fgets(d,2,fp);
						f=atoi(d);
						break;
			}
			rewind(fp);
			fclose(fp);
			if(g==0)
			{
				SVGA_CHtext16(435,370+30*(z-4),"С�ͳ�",_WHITE);
			}
			else if(g==1)
			{
				SVGA_CHtext16(435,370+30*(z-4),"���ͳ�",_WHITE);
			}
			else if(g==2)
			{
				SVGA_CHtext16(435,370+30*(z-4),"���ֳ�",_WHITE);
			}	
		
			*c=*parkingnum[z].time;
			/****停车时间****/
			t=parktime2(parkingnum[z].time);//计算停车时间
			itoa(t,time,10);
			/****停车费用****/		
			money=t*f;//计算停车费用
			itoa(money,fare,10);
			sum+=money;
			if(c[0]!='s')
			{
				SVGA_ENtext16(505,370+(z-4)*30,fare,_WHITE);//输出停车费用
				SVGA_ENtext16(560,370+(z-4)*30,time,_WHITE);//输出停车时间		
			}	
		}
	}	

		/*获取鼠标坐标*/ 
	SVGA_ImportBmp( "sm//mouse.bmp",mouseShape);	
	SetMouseBound(0, 640, 0, 480);
    MouseX=GetMouseX();
    MouseY=GetMouseY();
	oldx=MouseX;
	oldy=MouseY;
	SVGA_SaveArea(MouseX,MouseY,pic);
    while(1)
	{		
        MouseX=GetMouseX();
        MouseY=GetMouseY();	
        if((oldx!=MouseX)||(oldy!=MouseY))
		{	
			/* 处理鼠标移动 */		
			SVGA_RestoreArea(oldx,oldy,pic);		
			SVGA_SaveArea(MouseX,MouseY,pic);		
			SVGA_ImgBlackMask(MouseX,MouseY,mouseShape);			
		
			oldx=MouseX;
			oldy=MouseY;	
		}
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,362,400,285,355))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			SVGA_PartBmp(67,331,139,504,139,67,"pic//all.bmp");//贴图 总收入
			//输出当前总收入 当前停车量 还可输出各种车型当前停车量
			itoa(car,ncar,10);
			SVGA_ENtext16(322,95,ncar,_WHITE);//输出当前停车总量
			itoa(car0,ncar0,10);
			SVGA_ENtext16(250,140,ncar0,_WHITE);//输出当前停车总量
			itoa(car1,ncar1,10);
			SVGA_ENtext16(250,180,ncar1,_WHITE);//输出当前停车总量
			itoa(car2,ncar2,10);
			SVGA_ENtext16(250,220,ncar2,_WHITE);//输出当前停车总量	
			ltoa(sum,summ,10);
			SVGA_ENtext16(250,260,summ,_WHITE);//输出当前停车总量	
			getch();
			*flag=11;//返回信息查询模式
			break;
		}			
		if(GetMouseSta()==LEFTBTN&&CheckArea(MouseX, MouseY,448,480,290,347))
		{
			while(GetMouseSta() == LEFTBTN)//还在按着左键
			{
				;
			}
			*flag=3;//返回管理员模式
			break;
		}
	}	
}


int parktime2(char *c)		//计算停车时间函数
{
	char h1,h2,m1,m2,s1,s2;
	long int time1, time2;
	long int t;//停车时间
	h1=c[0];
	h2=c[1];
	m1=c[2];
	m2=c[3];
	s1=c[4];
	s2=c[5];
	time1=((((int)h1-48)*10+((int)h2-48))*3600+(((int)m1-48)*10+((int)m2-48))*60+(((int)s1-48)*10+((int)s2-48)));
	timeread(&h1, &h2, &m1, &m2, &s1, &s2);//获取当前时间
	time2=((((int)h1-48)*10+((int)h2-48))*3600+(((int)m1-48)*10+((int)m2-48))*60+(((int)s1-48)*10+((int)s2-48)));
	t=time2-time1;
	return t;
}

void chewei()//剩余车位
{
	FILE *fp;
	int z;
	int count1=0;//1楼剩余车位
	int count2=0;//2楼剩余车位
	int count3=0;//3楼剩余车位
	struct POINT parkingnum[8];//八个车位
	if((fp=fopen("message//floor1.txt","rt+"))==NULL)//一楼信息
	{
		exit(1);
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
	
	for(z=0;z<8;z++)
	{
		if((strcmp(parkingnum[z].username,"usernm")==0)&&(strcmp(parkingnum[z].password,"passwd")==0))
		{
			count1++;
		}
	}
	
	switch(count1)
	{
		case 0:SVGA_PartBmp(32,54,23,42,82,183,"pic//num.bmp");
				break;
		case 1:SVGA_PartBmp(32,54,63,79,82,183,"pic//num.bmp");
				break;
		case 2:SVGA_PartBmp(32,54,105,122,82,183,"pic//num.bmp");
				break;
		case 3:SVGA_PartBmp(32,54,147,164,82,183,"pic//num.bmp");
				break;
		case 4:SVGA_PartBmp(32,54,191,206,82,183,"pic//num.bmp");
				break;
		case 5:SVGA_PartBmp(32,54,233,252,82,183,"pic//num.bmp");
				break;
		case 6:SVGA_PartBmp(32,54,276,293,82,183,"pic//num.bmp");
				break;
		case 7:SVGA_PartBmp(32,54,318,333,82,183,"pic//num.bmp");
				break;
		case 8:SVGA_PartBmp(32,54,351,367,82,183,"pic//num.bmp");
				break;
	}
	
	if((fp=fopen("message//floor2.txt","rt+"))==NULL)//二楼信息
	{
		exit(1);
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
	
	for(z=0;z<8;z++)
	{
		if((strcmp(parkingnum[z].username,"usernm")==0)&&(strcmp(parkingnum[z].password,"passwd")==0))
		{
			count2++;
		}
	}	
	
	switch(count2)
	{
		case 0:SVGA_PartBmp(32,54,23,42,82,233,"pic//num.bmp");
				break;
		case 1:SVGA_PartBmp(32,54,63,79,82,233,"pic//num.bmp");
				break;
		case 2:SVGA_PartBmp(32,54,105,122,82,233,"pic//num.bmp");
				break;
		case 3:SVGA_PartBmp(32,54,147,164,82,233,"pic//num.bmp");
				break;
		case 4:SVGA_PartBmp(32,54,191,206,82,233,"pic//num.bmp");
				break;
		case 5:SVGA_PartBmp(32,54,233,252,82,233,"pic//num.bmp");
				break;
		case 6:SVGA_PartBmp(32,54,276,293,82,233,"pic//num.bmp");
				break;
		case 7:SVGA_PartBmp(32,54,318,333,82,233,"pic//num.bmp");
				break;
		case 8:SVGA_PartBmp(32,54,351,367,82,233,"pic//num.bmp");
				break;
	}	
	
	if((fp=fopen("message//floor3.txt","rt+"))==NULL)//三楼信息
	{
		exit(1);
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
	
	for(z=0;z<8;z++)
	{
		if((strcmp(parkingnum[z].username,"usernm")==0)&&(strcmp(parkingnum[z].password,"passwd")==0))
		{
			count3++;
		}
	}

	switch(count3)
	{
		case 0:SVGA_PartBmp(32,54,23,42,82,283,"pic//num.bmp");
				break;
		case 1:SVGA_PartBmp(32,54,63,79,82,283,"pic//num.bmp");
				break;
		case 2:SVGA_PartBmp(32,54,105,122,82,283,"pic//num.bmp");
				break;
		case 3:SVGA_PartBmp(32,54,147,164,82,283,"pic//num.bmp");
				break;
		case 4:SVGA_PartBmp(32,54,191,206,82,283,"pic//num.bmp");
				break;
		case 5:SVGA_PartBmp(32,54,233,252,82,283,"pic//num.bmp");
				break;
		case 6:SVGA_PartBmp(32,54,276,293,82,283,"pic//num.bmp");
				break;
		case 7:SVGA_PartBmp(32,54,318,333,82,283,"pic//num.bmp");
				break;
		case 8:SVGA_PartBmp(32,54,351,367,82,283,"pic//num.bmp");
				break;
	}

}