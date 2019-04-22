#include<alloc.h>
#include<stdio.h> 
#include<dos.h>
#include<time.h>
#include<conio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>
#include<string.h>
#include<graphics.h>
#include<bios.h>
struct POINT
{   
    char car[3];
	char username[10];
	char password[10];  
    char time[10]; 	
};

void resetinfo()
{
	FILE *fp;
	int z; 	//车位循环时用
	struct POINT parkingnum[8];//一层八个车位
	
	
	if((fp=fopen("message//floor1.txt","rt+"))==NULL)  //一楼车位
	{
		exit(1);
	}
	for(z=0;z<8;z++)
	{
		fgets(parkingnum[z].car,2,fp);
		fseek(fp,1,SEEK_SET);
		fgets(parkingnum[z].username,7,fp);
		fseek(fp,1,SEEK_SET);
		fgets(parkingnum[z].password,7,fp);
		fseek(fp,1,SEEK_SET);
		if(((strcmp(parkingnum[z].username,"usernm"))!=0)||((strcmp(parkingnum[z].password,"passwd"))!=0))//如果有车，重置信息
		{
			stpcpy(parkingnum[z].car,"k");
			strcpy(parkingnum[z].username,"usernm");
			stpcpy(parkingnum[z].password,"passwd");
			continue;
		}
	}
	rewind(fp);
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
	
	if((fp=fopen("message//floor2.txt","rt+"))==NULL)//二楼车位
	{
		exit(1);
	}
	for(z=0;z<8;z++)
	{
		fgets(parkingnum[z].car,2,fp);
		fseek(fp,1,SEEK_SET);
		fgets(parkingnum[z].username,7,fp);
		fseek(fp,1,SEEK_SET);
		fgets(parkingnum[z].password,7,fp);
		fseek(fp,1,SEEK_SET);
		if(((strcmp(parkingnum[z].username,"usernm"))!=0)||((strcmp(parkingnum[z].password,"passwd")!=0)))//如果有车，重置信息
		{
			stpcpy(parkingnum[z].car,"k");
			strcpy(parkingnum[z].username,"usernm");
			stpcpy(parkingnum[z].password,"passwd");
			continue;
		}
	}
	rewind(fp);
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
	
	if((fp=fopen("message//floor3.txt","rt+"))==NULL)//三楼车位
	{
		exit(1);
	}
	for(z=0;z<8;z++)
	{
		fgets(parkingnum[z].car,2,fp);
		fseek(fp,1,SEEK_SET);
		fgets(parkingnum[z].username,7,fp);
		fseek(fp,1,SEEK_SET);
		fgets(parkingnum[z].password,7,fp);
		fseek(fp,1,SEEK_SET);
		if(((strcmp(parkingnum[z].username,"usernm"))!=0)||((strcmp(parkingnum[z].password,"passwd"))!=0))//如果有车，重置信息
		{
			stpcpy(parkingnum[z].car,"k");
			strcpy(parkingnum[z].username,"usernm");
			stpcpy(parkingnum[z].password,"passwd");
			continue;
		}
	}
	rewind(fp);
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
	
	if((fp=fopen("message//time1.txt","rt+"))==NULL)//一楼时间
	{
		exit(1);
	}
	for(z=0;z<8;z++)
	{
		fgets(parkingnum[z].time,7,fp);
		if(((strcmp(parkingnum[z].time,"shjian"))!=0))//时间信息重置
		{
			strcpy(parkingnum[z].time,"shjian");
			continue;
		}	
	}
	rewind(fp);
	for(z=0;z<8;z++)
	{
		fwrite(parkingnum[z].time,6,1,fp);
		fputc('\n',fp);
	}
	rewind(fp);
	fclose(fp);
	
	if((fp=fopen("message//time2.txt","rt+"))==NULL)//二楼时间
	{
		exit(1);
	}
	for(z=0;z<8;z++)
	{
		fgets(parkingnum[z].time,7,fp);
		if(((strcmp(parkingnum[z].time,"shjian"))!=0))//时间信息重置
		{
			strcpy(parkingnum[z].time,"shjian");
			continue;
		}
	}
	rewind(fp);
	for(z=0;z<8;z++)
	{
		fwrite(parkingnum[z].time,6,1,fp);
		fputc('\n',fp);
	}
	rewind(fp);
	fclose(fp);

	if((fp=fopen("message//time3.txt","rt+"))==NULL)//三楼时间
	{
		exit(1);
	}
	for(z=0;z<8;z++)
	{
		fgets(parkingnum[z].time,7,fp);
		if((strcmp(parkingnum[z].time,"shjian")!=0))//时间信息重置
		{
			strcpy(parkingnum[z].time,"shjian");
			continue;
		}	
	}
	rewind(fp);
	for(z=0;z<8;z++)
	{
		fwrite(parkingnum[z].time,6,1,fp);
		fputc('\n',fp);
	}
	rewind(fp);
	fclose(fp);	
}