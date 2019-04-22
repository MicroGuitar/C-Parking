#include<conio.h>
#include<stdio.h>
#include"svga.h"
#include"load.h"
#include"car.h"
#include"enter.h"
#include"floor.h"
#include"file.h"
#include"showcar.h"
#include"showinfo.h"
#include"mode.h"
#include"check.h"
#include"glpass.h"
#include"change.h"
void main()
{
	static int flag=0;
	static int from=0;
	int k;
	/*load();*/
	while(1)
	{
		switch(flag)
		{
			case 0:_selectm(&flag);//初始模式选择
			break;
			case 1:selectcar(&flag,&k);//用户选车
			break;
			case 2:selectfloor(&flag,1,&from);//用户选楼层停车
			break;
			case 3:managem(&flag);//管理员选择模式
			break;
			case 4:Enter(&flag,&k,1,&from);   /**停车楼层**///k用于传递选车信息 ，第三位代表层数，1,2,3对应1,2,3层
		    break; 
			case 5:Enter(&flag,&k,2,&from);
		    break;
			case 6:Enter(&flag,&k,3,&from);
		    break;	
			case 7:selectfloor(&flag,2,&from);//用户选楼层取车
			break;
			case 8:takecar(&flag,1);//1,2,3对应1,2,3层
		    break; 
			case 9:takecar(&flag,2);//1,2,3对应1,2,3层
		    break; 
			case 10:takecar(&flag,3);//1,2,3对应1,2,3层
		    break; 
			case 11:showinfo(&flag);//显示车库所有信息
		    break; 
			case 12:selectfloor(&flag,3,&from);//管理员选楼层查看
			break;
			case 13:check(&flag,1);//查看楼层车位信息，1 2 3代表层数
			break;
			case 14:check(&flag,2);//查看楼层车位信息，1 2 3代表层数
			break;
			case 15:check(&flag,3);//查看楼层车位信息，1 2 3代表层数
			break;
			case 16:password(&flag);//输入管理员密码
			break;
			case 17:change(&flag);
			break;
			case 18:modify(&flag);
		}
	}
	getch();
}
