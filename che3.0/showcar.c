#include<stdio.h>
#include"svga.h"
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#define h0 98//1,5车位y坐标
#define h1 186//2,6车位y坐标
#define h2 274//3,7车位y坐标
#define h3 362//4,8车位y坐标
struct POINT
{
	char car[10];
	char username[10];
	char password[10]; 
    char time[10]; 	
};


void showcar(int floor)
{
	FILE *fp;
	int z;
	char t;
	struct POINT parkingnum[8];  //八个车位
	
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
        fgets(parkingnum[z].car,2,fp);
        fseek(fp,1,SEEK_CUR);
        fgets(parkingnum[z].username,7,fp);
		fseek(fp,1,SEEK_CUR);
		fgets(parkingnum[z].password,7,fp);
		fseek(fp,2,SEEK_CUR);
	}
	rewind(fp);
	fclose(fp);
	
	for(z=0;z<4;z++)//1 2 3 4 号车位
	{
		if(((strcmp(parkingnum[z].username,"usernm"))!=0)||((strcmp(parkingnum[z].password,"passwd"))!=0))
		{
			t=parkingnum[z].car[0];
			switch(t)
			{
				case '0':SVGA_PartBmp(259,297,252,326,211,h0+z*88,"sm\\che.bmp");//贴图 第一类车
						 break;
				case '1':SVGA_PartBmp(255,301,28,127,211,h0+z*88,"sm\\che1.bmp");// 贴图 第二类车
						 break;
				case '2':SVGA_PartBmp(261,296,137,236,211,h0+z*88,"sm\\che2.bmp");// 贴图 第三类车
						 break;
			}
		}
	}
	for(z=4;z<8;z++)//5 6 7 8 号车位
	{
		if(((strcmp(parkingnum[z].username,"usernm"))!=0)||((strcmp(parkingnum[z].password,"passwd"))!=0))
		{
			t=parkingnum[z].car[0];
			switch(t)
			{
				case '0':SVGA_PartBmp(184,222,252,326,480,h0+((z-4)*88),"sm\\che.bmp");//贴图 第一类车
						 break;
				case '1':SVGA_PartBmp(180,226,28,127,480,h0+((z-4)*88),"sm\\che1.bmp");// 贴图 第二类车
						 break;
				case '2':SVGA_PartBmp(185,220,137,236,480,h0+((z-4)*88),"sm\\che2.bmp");// 贴图 第三类车
						 break;
			}
		}
	}	
}