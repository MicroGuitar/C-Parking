#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include"ourtime.h"

void timeread(char *h1, char *h2, char *m1, char *m2, char *s1, char *s2)
{
	time_t nowtime;		//<time.h>头文件中定义的数据类型，time_t是长整形long int 用于保存1970年1月1日0时0分0秒到现在时刻的秒数，在后文中用time()这个函数获取数值。
	struct tm *timeinfo;	//<time.h>头文件中定义
	char h[10],m[10],s[10];
	time(&nowtime);		//将当前时间保存在&nowtime地址
	timeinfo=localtime(&nowtime);	////localtime函数为time.h头函数中的函数 功能为返回本地时间(实质是一个数组)，localtime()中第一个参数是时间戳，如果没有给出则使用从time()返回的当前时间，第二参数是is_associative，如果设为flase或未提供则返回的是普通数字索引数组，如果该参数设为true则localtime（）函数返回一个关联数组
	
	//itoa(((timeinfo->tm_year) + 1900), y, 10);//十表示十进制   //itoa(int value(被转换的整数),char *string(转换后储存的字符),int radix(转换进制数))
	//itoa(((timeinfo->tm_mon) + 1), mon, 10);//此函数为头文件中包含的函数 将timeinfo中的tm_mon的参数加1后转成十进制后存入mon中
	//itoa((timeinfo->tm_mday), d, 10);
	itoa((timeinfo->tm_hour), h, 10);		//将小时信息以十进制信息存入h中
	itoa((timeinfo->tm_min), m, 10);		//将分钟信息以十进制信息存入m中
	itoa((timeinfo->tm_sec), s, 10);		//将秒钟信息以十进制信息存入s中
	if(h[1]==NULL)
	{
		h[1]=h[0];
		h[0]='0';
	}
	if(m[1]==NULL)
	{
		m[1]=m[0];
		m[0]='0';
	}
	if(s[1]==NULL)
	{
		s[1]=s[0];
		s[0]='0';
	}
	*h1=h[0];
	*h2=h[1];
	*m1=m[0];
	*m2=m[1];
	*s1=s[0];
	*s2=s[1];
}



/**  结构体tm 即为我所需要使用的*timeinfo
     struct tm_hour{
	int tm_sec;秒的取值为【0,59】
	int tm_min;分的取值为【0,59】  
	int tm_hour;时的取值为【0,23】
	int tm_mday;一个月中的日期，取值区间【1,31】
	int tm_mon;月份 从一月份开始，取值区间为【0，11】0代表一月份
	int tm_year;年份，其值从1900开始
	int tm_wday;星期一取值区间为【0,6】，0代表周日，1代表星期一
	int tm_yday;从每年的1月1日开始的天数，取值区间为【0,365】其中0代表1月1日，1代表1月2日
	int tm_isdst;夏时令标识符
      	…
}

**/