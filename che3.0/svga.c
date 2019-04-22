#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <bios.h>
#include <time.h>
#include "svga.h"
#include "main.h"
#include "file.h"

/********************************
**函数名：SVGA_VBEInfo
**参数：
**    VBEInfo * info        指向目标信息位置的指针
**功能：获取VBE硬件信息
********************************/
/* int SVGA_VBEInfo(VBEInfo * info)
{
    short segx = FP_SEG(info);
    short offx = FP_OFF(info);

    _AX = 0x4F00;   //功能号
    _ES = segx;
    _DI = offx;     //ES:DI指向模式信息块的指针
    __int__(0x10);
    return _AX;
} */

/********************************
**函数名：SVGA_ModeInfo
**参数：
**    ModeInfo * info        指向目标信息位置的指针
**功能：获取VESA的SVGA工作模式信息
********************************/
/* int SVGA_ModeInfo(ModeInfo * info)
{
    short segx = FP_SEG(info);
    short offx = FP_OFF(info);

    _AX = 0x4F01;   //功能号
    _CX = 0x111;    //显示模式
    _ES = segx;
    _DI = offx;     //ES:DI指向模式信息块的指针
    __int__(0x10);
    return _AX;
} */

/********************************
**函数名：SVGA_SelectPlane
**参数：
**    register char page        目标位面
**功能：选择工作位面
********************************/
void
SVGA_SelectPlane(register char page)
{
    _BX = 0;
    _DX = page;
    _AX = 0x4f05;
    __int__(0x10);
}

/********************************
**函数名：SVGA_SetMode
**参数：
**    const int vmode            目标模式
**返回值：
**    extern unsigned char    若初始化成功返回值0x4F，初始化失败返回其他值
**功能：初始化SVGA模式
**    vmode=0x101 640*480*256色
**    vmode=0x103 800*600*256色
**    vmode=0X111 640*480*16B色
**    vmode=0X112 640*480*24B色
********************************/
extern unsigned char 
SVGA_SetMode(const int vmode)
{  
    _BX = vmode;
    _AX = 0x4f02;
    __int__(0x10);
    return _AX;
}

/********************************
**函数名：SVGA_GetMode
**返回值：
**    unsigned int    当前显示模式的中断号
**功能：获取当前工作模式
********************************/
extern unsigned int 
SVGA_GetMode(void)
{   
    _AX = 0x4f03;
    __int__(0x10); 
    return _BX; 
} 

/********************************
**函数名：SVGA_SetDisplay
**返回值：
**    unsigned int    VBE 返回状态
**功能：修改显示缓存位置
********************************/
/********************************
unsigned int SVGA_SetDisplay(const int Frame)
{
    _AX = 0x4f07;
	_BL = 0x00;
	_CX = 640;
	_DX = 480 * Frame;
	__int__(0x10);
    return _AX; 
}
*********************************/


/********************************
**函数名：SVGA_PartBmp
**参数：
**    const int  top          图片部分的上边界在整个bmp图片中的坐标
**    const int  bottom       图片部分的下边界在整个bmp图片中的坐标
**    const int  left         图片部分的左边界在整个bmp图片中的坐标
**    const int  right        图片部分的右边界在整个bmp图片中的坐标
**    const int  Offsetx      图片显示在屏幕上位置的左边界坐标
**    const int  Offsety      图片显示在屏幕上位置的上边界坐标
**    const char *filename    指定的用于配置调色板的图片
**功能：本函数在指定位置画指定文件的指定部分，本函数不设置调色板
********************************/
void
SVGA_PartBmp(const int  top,
	     const int  bottom,
	     const int  left,
	     const int  right,
	     const int  Offsetx,
	     const int  Offsety,
	     const char *filename)
{
    /*一行640个像素的颜色数据*/
    auto     int     buffer[640];
	auto     long    linebytes;

    /*接受文件路径*/
    auto     char     filepos[30];

    /*循环体使用*/
    register int      i;
    register int      j;

    /*宽高限制*/
    auto     int      ResX;
    auto     int      ResY;

    /*用于换页，减少一定计算量*/
    auto     int      spOffsety;

    /*BMP信息，图像宽高*/
    auto     long     Width;
    auto     long     Height;

    /*选择的部分的宽高*/
    auto     long     partWidth;
    auto     long     partHeight;

    /*文件流*/
    FILE *fp;

    /*显存操作*/
    auto     long     position1, position;
    register int      page_new = 0;	
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;

	SVGA_SelectPlane(page_old);

    strcpy(filepos,filename);
	// /*限制*/
	// if(top<0)
	// {
		// top = 0;
	// }
	// if(bottom>479)
	// {
		// bottom = 479;
	// }	
	// if(left<0)
	// {
		// left = 0;
	// }
	// if(right>639)
	// {
		// right = 639;
	// }	
    /*打开文件*/
    if ((fp = fopen(filepos,"rb")) == NULL)
    {
        SVGA_ENtext16(0, 20, filename, _RED);	
	    getch();
		fclose(fp);
		return;
    }

    /*获取BMP的宽高信息*/
    fseek(fp,18,SEEK_SET);
    fread(&Width,4,1,fp);
    fread(&Height,4,1,fp);

    /*目标文件截取部分的宽高*/
    if (right > Width)
	partWidth = Width;
    else partWidth = right;
    if (bottom > Height)
	partHeight = Height;
    else partHeight = bottom;

    partWidth -= left;
    partHeight -= top;

    if (fseek(fp, bottom * Width, SEEK_SET) == -1)
    {
        //	printf("Fail to analyse file !");
		fclose(fp);
		return;
    }

    /*设置宽高限制*/
    if ((partWidth + Offsetx) > 640)
	ResX = 640 - Offsetx;
    else ResX = partWidth;
    if ((partHeight + Offsety) > 480)
	ResY = 480 - Offsety;
    else ResY = partHeight;

    /*拼凑4字节倍数修正宽度*/
	linebytes = Width * 2;
	if (linebytes % 4) linebytes += 2;

    fseek(fp,70 + linebytes * (Height - bottom) + left * 2l, SEEK_SET);
    /*直接写显存*/
    for ( j = partHeight - 1; j >= 0 && (Offsety + j) >= 0; j--)
    {
		fread(buffer,2,partWidth,fp);
		spOffsety = Offsety + j;
		if(spOffsety > 479)//越界
		{
			continue;
		}			
		
		
		if (j < ResY)
		{
			position = spOffsety * 640l + Offsetx;
			
			if (  spOffsety * 5 % 256 > 251  )// spOffsety对51.2取余，都同乘5，此时表示算上第spOffsety行用了此页的行数，y=spOffsety表示第spOffsety+1行，
			{                                 //算上这一行后若仍小于51.2，则整行都处于同一页，得式子 spOffsety%51.2 + 1 < 51.2 ，同乘5即得
				for ( i = 0; i < ResX && i+Offsetx < 640; i++)
				{
				if(( Offsetx + i ) < 0 )//小于0不显示
				{
					continue;
				}						
					position1  = position + i; //计算要显示点的显存位置
					page_new = position1 >> 15; //计算显示页
					position1 &= 0x0000ffffl;//计算在一个页面上的偏移位置，整除65536的快速方案
					if (page_new != page_old) //更换页面
					{
						SVGA_SelectPlane(page_new);
						page_old = page_new;
					}
					VideoBuffer[position1] = buffer[i]; //写到显存位置
				}
			}

			else
			{				
				page_new = position >> 15; //计算显示页
				position &= 0x0000ffffl;//计算在一个页面上的偏移位置，整除65536的快速方案
				if (page_new != page_old) //更换页面
				{					
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}
				for ( i = 0; i < ResX && i+Offsetx < 640; i++)
				{	
				if(( Offsetx + i ) < 0 )//小于0不显示
				{
					continue;
				}					
					VideoBuffer[position+i] = buffer[i]; //写到显存位置	
				}			
			}
		}
		fseek(fp,linebytes - partWidth * 2l,SEEK_CUR);
    }
    /*关闭文件*/
    if (fclose(fp)==-1)
    {
      //	printf("Fail to close file");
    }
}

/********************************
**函数名：SVGA_ImportBmp
**参数：
**    const char *filename   指定文件的路径
**    int saveColor[1024]    存储指定文件的数组
**功能：本函数将指定32*32大小的bmp文件读到内存中
********************************/
void
SVGA_ImportBmp( const char *filename, int saveColor[1024] )
{
    /*接受文件路径*/
    auto     char     filepos[30];
    /*循环体*/
    register int      j;
	register int      i;
    /*BMP信息，图像宽高*/
    auto     long     Width;
    auto     long     Height;
    /*文件流*/
    FILE *fp;

    strcpy(filepos,filename);

    /*打开文件*/
    if ((fp = fopen(filepos,"rb")) == NULL)
    {
       //	printf("Fail to open file in Function ImportBmp  ");
	fclose(fp);
	return;
    }

    /*获取BMP的宽高信息*/
    fseek(fp,18,SEEK_SET);
    fread(&Width,4,1,fp);
    fread(&Height,4,1,fp);

    if (Width != 32 || Height != 32)
    {
       	//printf("Not 32*32! ");
	fclose(fp);
	return;
    }

    fseek(fp,70l,SEEK_SET);
    /*读入内存*/
    for ( j = 31; j >= 0; j--)
    {
		for ( i = 0; i < 32; i++)
		{
			fread(&saveColor[ j * 32 + i ], 2, 1, fp);
		}
    }

    /*关闭文件*/
    if (fclose(fp) == -1)
    {
       //	printf("Fail to close file");
    }
}




/********************************
**函数名：SVGA_Rectangular
**参数：
**    const int top       目标矩形的上界限坐标
**    const int bottom    目标矩形的下界限坐标
**    const int left      目标矩形的左界限坐标
**    const int right     目标矩形的右界限坐标
**    const int color     画线的颜色
**功能：调用SVGA_Dot从(left,top)到(right,bottom)画矩形
********************************/
void
SVGA_Rectangular(const int  top,
		 const int  bottom,
		 const int  left,
		 const int  right,
		 const int color)
{
    /*循环体*/
    register int     i;
    register int     j;
    /*矩形大小*/
    auto     int     ResY;
    auto     int     ResX;
    /*显存操作*/
    auto     long     position1, position;
    register int     page_new = 0;
    /*用于换页，减少一定计算量*/
    auto     int      spOffsety;
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;
	/*设置初始页面*/
	SVGA_SelectPlane(page_old);
	/*计算矩形大小*/
    ResY = bottom - top;
    ResX = right - left;

	for ( i = 0;i< ResY && (top + i) < 481; i++)
    {
		spOffsety = top +i;
		position = ( top + i ) * 640l + left;
	    if (  spOffsety * 5 % 256 > 251  )// spOffsety对51.2取余，都同乘5，此时表示算上第spOffsety行用了此页的行数，y=spOffsety表示第spOffsety+1行，
	    {                                 //算上这一行后若仍小于51.2，则整行都处于同一页，得式子 spOffsety%51.2 + 1 < 51.2 ，同乘5即得
			for ( j = 0; j < ResX && (left + j) < 641; j++)
			{
				position1 = position + j;
				page_new = position1 >> 15; /*计算显示页*/
				position1 &= 0x0000ffffl;    /*计算在一个页面上的偏移位置，整除65536的快速方案*/
				if (page_new != page_old)     /*更换页面*/
				{
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}
				VideoBuffer[position1] = color;
			}
		}
		else
		{
			page_new = position >> 15; /*计算显示页*/
			position &= 0x0000ffffl;    /*计算在一个页面上的偏移位置，整除65536的快速方案*/
			if (page_new != page_old)     /*更换页面*/
			{
				SVGA_SelectPlane(page_new);
				page_old = page_new;
			}
				
			for ( j = 0; j < ResX && (left + j) < 641; j++)
			{
				VideoBuffer[position+j] = color;
			}			
		}
    }
}

/********************************
**函数名：SVGA_MaskBmp
**参数：
**    const int  top           指定允许显示图形的屏幕范围的上界
**    const int  bottom        指定允许显示图形的屏幕范围的下界
**    const int  left          指定允许显示图形的屏幕范围的左界
**    const int  right         指定允许显示图形的屏幕范围的右界
**    const int  Offsetx       显示图片的左上位置在屏幕上的横坐标
**    const int  Offsety       显示图片的左上位置在屏幕上的纵坐标
**    const char *filename     要显示图片的路径
**    const int  MaskColor     图片上和这个颜色值相同的部分不会显示
**功能：本函数对齐(Offsetx,Offsety)画BMP，通过top,bottom,right,left设定图形的范围，不设置调色板，MaskColor透明
********************************/
void
SVGA_MaskBmp(const int  top,
	     const int  bottom,
	     const int  left,
	     const int  right,
	     const int  Offsetx,
	     const int  Offsety,
	     const char *filename,
	     const int  MaskColor)
{
    /*文件流*/
    FILE *fp;

    /*一行640个像素的颜色数据*/
    auto     int     buffer[640];
    auto     long    linebytes;

    /*存储文件路径，防止出现因为修改路径字符串导致的错误*/
    auto     char     filepos[30];

    /*循环体使用*/
    register int     i;
    register int     j;

    /*图形位置限制*/
    auto     int     ResX;
    auto     int     ResY;

    /*这个量仅用于换页，减少一定计算量*/
    register int      spOffsety;

    /*显存位置,使用两个是为了计算位面信息使用*/
    auto     long     position1, position;

    /*BMP信息，图像宽高*/
    auto     long     Width;
    auto     long     Height;

    /*位面信息*/
    register int     page_new = 0;
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;
	/*设置初始页面*/
	SVGA_SelectPlane(page_old);
    /*获取文件路径*/
    strcpy(filepos,filename);

    /*打开文件*/
    if ((fp = fopen(filepos,"rb")) == NULL)
    {
       //printf("Fail to open file in Function MaskBmp  ");
	fclose(fp);
	return;
    }

    /*获取BMP的宽高信息*/
    fseek(fp,18,SEEK_SET);
    fread(&Width,4,1,fp);
    fread(&Height,4,1,fp);

    /*设置宽高限制*/
    if ((Width + Offsetx) > right)
	ResX = right - Offsetx;
    else ResX = Width;

    if ((Height + Offsety) > bottom)
	ResY = bottom - Offsety;
    else ResY = Height;

    /*拼凑4字节倍数修正宽度，注意本部分会改变Width的值，应该先计算ResX*/
	linebytes = Width;
	if (linebytes % 2) linebytes += 1;

    fseek(fp,70l,SEEK_SET);
    /*直接写显存*/
    for ( j = Height - 1; j >= 0; j--)
    {
		fread(buffer,2,linebytes,fp);
		
		spOffsety = Offsety + j;
		position = spOffsety * 640l + Offsetx;
		if ((j < ResY) && (spOffsety > top))
		{
			if (  spOffsety * 5 % 256 > 251  )
			{
				for ( i = 0; i < ResX; i++)
				{
					position1 = position + i; //计算要显示点的显存位置

					page_new = position1 >> 15; //计算显示页
					position1 &= 0x0000ffffl;//计算在一个页面上的偏移位置，整除65536的快速方案
					if (page_new != page_old) //更换页面
					{
						SVGA_SelectPlane(page_new);
						page_old = page_new;
					}
					if ((buffer[i] != MaskColor) && (i + Offsetx) > left)
						VideoBuffer[ position1 ] = buffer[ i ]; //写到显存位置
				}
			}

			else
			{
				page_new = position >> 15; //计算显示页

				position &= 0x0000ffffl;//计算在一个页面上的偏移位置，整除65536的快速方案
				if (page_new != page_old) //更换页面
				{
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}
				for ( i = 0; i < ResX; i++)
				{
					if ((buffer[i] != MaskColor) && (i + Offsetx) > left)
						VideoBuffer[ position + i ] = buffer[ i ]; //写到显存位置
				}
				
			}
		}
    }
    /*关闭文件*/
    if (fclose(fp) == -1)
    {
       //	printf("Fail to close file");
    }
}

/********************************
**函数名：SVGA_ImgBlackMask
**参数：
**    const int x              指定要显示图形在屏幕上的横坐标
**    const int y              指定要显示图形在屏幕上的纵坐标
**    const int color[1024]    存储图形的数组
**功能：本函数将指定32*32大小的内存中图形写入显存，另黑色部分不显示
********************************/
void
SVGA_ImgBlackMask(  const int x,
		    const int y,
		    const int color[1024])
{
    /*循环体*/
    register int     i;
    register int     j;
    /*用于加速换页*/
    register int     offy;
    /*显存操作*/
    auto     long     position1, position;
    register int      page_new = 0;
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;
	/*设置初始页面*/
	SVGA_SelectPlane(page_old);
	
    for ( i = 0; i < 32 && (y + i) < 481; i++)
    {
		offy = y + i;
		position = offy * 640l + x;
		if (  offy * 5 % 256 > 251  )
		{
			for ( j = 0 ; j < 32; j++)
			{
				if (color[ 32 * i + j ] && ( x + j ) < 641)
				{
					position1 = position + j ;
					page_new = position1 >> 15; //计算显示页
					position1 &= 0x00007fffl;//计算在一个页面上的偏移位置，整除65536的快速方案
					if (page_new != page_old) //更换页面
					{
						SVGA_SelectPlane(page_new);
						page_old = page_new;
					}
					VideoBuffer[position1] = color[ i * 32 + j ];
				}
			}
		}
		else
		{
			page_new = position >> 15; //计算显示页
			position &= 0x00007fffl;//计算在一个页面上的偏移位置，整除65536的快速方案
			if (page_new != page_old) //更换页面
			{
				SVGA_SelectPlane(page_new);
				page_old = page_new;
			}
			for ( j = 0; j < 32; j++)
			{
				if ((x + j) < 641 && color[32 * i + j])
					VideoBuffer[position + j] = color[32 * i + j];
			}
		}
    }
}

/********************************
**函数名：SVGA_CHtext16
**参数：
**    const int  x         指定要显示文字最左端在屏幕上的位置
**    const int  y         指定要显示文字最右端在屏幕上的位置
**    const char *s        这个数组表示要显示的文字
**    const int  color     color指定要显示文字的颜色
**功能：本函数调用SVGA_Dot输出16*16大小的汉字
********************************/
void
SVGA_CHtext16(  const int  x,
		const int  y,
		const char s[],
		const int color )//上限25个汉字
{
    /*文件流*/
    FILE *fp;
    /*循环体使用*/
    register int     i;
    register int     j;
    register int     k;
    auto     int     l = 0;
    auto     int     startX = x;
    /*汉字库操作*/
    register unsigned char qh;
    register unsigned char wh;
    register unsigned long location;
    auto     char    buffer[32];
    /*接受字符串*/
    auto     char    string[51];
    /*显存操作*/
    auto     long    position1;
    register int     page_new = 0;
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;
	/*设置初始页面*/
	SVGA_SelectPlane(page_old);
	
    if ((fp = fopen("font\\hzk16","rb")) == NULL)
    {
       //	printf("Can't open hzk16!");
	fclose(fp);
	return;
    }

    strcpy(string,s);
    while ( * (string + l))
    {
		qh = * (string + l) - 0xa0;
		wh = * (string + l + 1) - 0xa0;
		location = (94 * (qh - 1) + (wh - 1)) * 32L; //计算位移量
		fseek(fp,location,SEEK_SET);
		fread(buffer,32,1,fp);           //读出点阵信息
		for ( i = 0; i < 16; i++)
		{
			for ( j = 0; j < 2; j++)
			{
				for ( k = 0; k < 8; k++)
				{
					if ((buffer[i * 2 + j] >> (7 - k)) & 0x1)  //为1的位显示
					{
						position1 = ( y + i ) * 640l + startX + ( 8*j ) + k;
						page_new = position1 >> 15;
						position1 &= 0x0000ffffl;
						if (page_new!=page_old)
						{
							SVGA_SelectPlane(page_new);
							page_old = page_new;
						}
						VideoBuffer[position1] = color;
					}
				}
			}
		}
		l += 2;
		startX += 16;
    }
    fclose(fp);
}



/********************************
**函数名：SVGA_ENtext16
**参数：
**    const int  x        指定要显示文字最左端在屏幕上的位置
**    const int  y        指定要显示文字最右端在屏幕上的位置
**    const char *s       这个数组表示要显示的文字
**    const int  color    color指定要显示文字的颜色
**功能：调用SVGA_Dot输出8*16大小的ASC字符
********************************/
void
SVGA_ENtext16( const int  x,
	       const int  y,
	       const char s[],
	       const int  color )//上限40
{
    /*文件流*/
    FILE *fp;
    /*循环体*/
    register int     i;
    register int     j;
    register int     k;
    register int     l;
    register int     startX;
    /*字库操作*/
    register unsigned char     wh;
    register unsigned long    position;
    auto     char    buffer[32];
    /*接受字符串*/
    auto     char    string[41];
    /*显存操作*/
    auto     long    position1;
    register int     page_new = 0;
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;
	/*设置初始页面*/
	SVGA_SelectPlane(page_old);
	
    l = 0;
    startX = x;

    if ((fp=fopen("font\\asc16","rb"))==NULL)
    {
	printf("Can't open asc16!");
    }

    strcpy(string,s);
    while ( *(string + l))
    {
		wh = *(string + l);
		position = wh * 16L;                         //计算位移量
		fseek(fp,position,SEEK_SET);
		fread(buffer,16,1,fp);                        //读出点阵信息
		for ( i = 0; i < 16; i++)
		{
			for ( k = 0; k < 8; k++)
			{
				if ((buffer[i] >> (7 - k)) & 0x1)    //为1的位显示
				{
					position1 = (y + i) * 640l + startX + k;
					page_new = position1 >> 15;
					position1 &= 0x0000ffffl;
					if (page_new != page_old)
					{
						SVGA_SelectPlane(page_new);
						page_old = page_new;
					}
					VideoBuffer[position1] = color;
				}
			}
		}
		l += 1;
		startX += 8;
    }
    fclose(fp);
}

/********************************
**函数名：SVGA_ENtextch16
**参数：
**    const int  x        指定要显示文字最左端在屏幕上的位置
**    const int  y        指定要显示文字最右端在屏幕上的位置
**    const char s        要输出的字符
**    const int  color    color指定要显示文字的颜色
**功能：调用SVGA_Dot输出8*16大小的ASC字符
********************************/
void
SVGA_ENtextch16( const int  x,
	       const int  y,
	       const char s,
	       const int  color )//上限40
{
    /*文件流*/
    FILE *fp;
    /*循环体*/
    register int     i;
    register int     j;
    register int     k;
    register int     l;
    register int     startX;
    /*字库操作*/
    register unsigned char     wh;
    register unsigned long    position;
    auto     char    buffer[32];
    /*接受字符串*/
    auto     char    string[41];
    /*显存操作*/
    auto     long    position1;
    register int     page_new = 0;
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;
	/*设置初始页面*/
	SVGA_SelectPlane(page_old);
	
    l = 0;
    startX = x;

    if ((fp=fopen("font\\asc16","rb"))==NULL)
    {
		union REGS r;
		r.x.ax=0x4f02;
		r.x.bx=0x03;
		int86(0x10, &r, &r);
	printf("Can't open asc16!");
    }

		wh = s;
		position = wh * 16L;                         //计算位移量
		fseek(fp,position,SEEK_SET);
		fread(buffer,16,1,fp);                        //读出点阵信息
		for ( i = 0; i < 16; i++)
		{
			for ( k = 0; k < 8; k++)
			{
				if ((buffer[i] >> (7 - k)) & 0x1)    //为1的位显示
				{
					position1 = (y + i) * 640l + startX + k;
					page_new = position1 >> 15;
					position1 &= 0x0000ffffl;
					if (page_new != page_old)
					{
						SVGA_SelectPlane(page_new);
						page_old = page_new;
					}
					VideoBuffer[position1] = color;
				}
			}
		}
    fclose(fp);
}


/********************************
**函数名：SVGA_SaveArea
**参数：
**    const int x     目标位置左界限
**    const int y     目标位置上界限
**    int str[1024]    用于寄存图形的数组
**功能：调用SVGA_GetDot在(x,y)获取范围32*32的点的信息
**用于MousePrint函数鼠标显示
********************************/
void
SVGA_SaveArea( const int x,
	       const int y,
	       int str[1024])
{
    /*循环体*/
    register int     i;
    register int     j;
    /*用于加速换页*/
    auto     int     offy;
    /*显存操作*/
    auto     long     position1, position;
    register int      page_new = 0;
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;
	/*设置初始页面*/
	SVGA_SelectPlane(page_old);
	
    for ( i = 0; i < 32 && (y + i) < 481; i++)
    {
		offy = y + i;
		position = offy * 640l + x;
		if (  offy * 5 % 256 > 251 )
		{
			for ( j =0; j < 32 && (x + j) < 641; j++)
			{
				position1 = position + j;
				page_new = position1 >> 15;
				position1 &= 0x0000ffffl;
				if (page_new != page_old)
				{
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}
				str[ 32 * i + j ] = VideoBuffer[position1];
			}
		}
		else
		{
			page_new = position >> 15;
			position &= 0x0000ffffl;
			if (page_new != page_old)
			{
				SVGA_SelectPlane(page_new);
				page_old = page_new;
			}
			for ( j =0; j < 32 && (x + j) < 641; j++)
			{
				str[ 32 * i + j ] = VideoBuffer[position + j];
			}
		}
    }
}


/********************************
**函数名：SVGA_RestoreArea
**参数：
**    int x         目标位置左界限
**    int y         目标位置上界限
**    int str[1024]    用于寄存图形的数组
**功能：调用SVGA_Dot在(x,y)画范围32*32的点的图像
**用于MousePrint函数鼠标显示
********************************/
void
SVGA_RestoreArea(const int  x,
		 const int  y,
		 const int  str[1024])
{
    /*循环体*/
    register int     i;
    register int     j;
    /*用于加速换页*/
    auto     int    offy;
    /*显存操作*/
    auto     long     position1,position;
    register int     page_new = 0;
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;
	/*设置初始页面*/
	SVGA_SelectPlane(page_old);
	
    for ( i = 0; i < 32 && (y + i) < 481; i++)
    {
		offy = y + i;
		position = offy * 640l + x;
		if (  offy * 5 % 256 > 251 )
		{
			for ( j = 0; j < 32 && (x + j) < 641; j++)
			{
				position1 = position + j; //计算要显示点的显存位置
				page_new = position1 >> 15; //计算显示页
				position1 &= 0x0000ffffl;//计算在一个页面上的偏移位置，整除65536的快速方案
				if (page_new != page_old) //更换页面
				{
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}
				VideoBuffer[position1] = str[ 32 * i + j ];
			}
		}
		else
		{
			page_new = position >> 15; //计算显示页
			position &= 0x0000ffffl;//计算在一个页面上的偏移位置，整除65536的快速方案
			if (page_new != page_old) //更换页面
			{
				SVGA_SelectPlane(page_new);
				page_old = page_new;
			}
			for ( j = 0; j < 32 && (x + j) < 641; j++)
			{
				VideoBuffer[position + j] = str[ 32 * i + j];
			}
		}
    }
}

/********************************
**函数名：SVGA_BMPInfo
**参数：
**    const char * const filename   目标文件路径
**    int * const Width             记录宽度的指针
**    int * const Height            记录长度的指针
**功能：获取目标bmp文件的长宽信息
********************************/
void
SVGA_BMPInfo(const char * const filename,
	     long * const Width,
	     long * const Height)
{
    /*接受文件路径信息*/
    auto     char      filepos[30];

    /*文件流*/
	FILE  *fp;

    strcpy(filepos,filename);              //获取文件路径

    /*打开文件*/
    if ((fp = fopen(filepos,"rb")) == NULL)
    {
       //	printf("Fail to open file");
	fclose(fp);
	return;
    }

    /*获取BMP的宽高信息*/
    fseek(fp,18,SEEK_SET);
    fread(Width,4,1,fp);
    fread(Height,4,1,fp);
	fclose(fp);
}
/******************************以上为14级以前代码***********************************************************/
//对有负数的贴图尚有欠缺，具体处理看ZoomPic()
/******************************************************************
**函数名：SVGA_ImgWhiteMask
**参数：
**    const int x              指定要显示图形在屏幕上的横坐标
**    const int y              指定要显示图形在屏幕上的纵坐标
**    const int color[1024]    存储图形的数组
**功能：本函数将指定32*32大小的内存中图形写入显存，另白色部分不显示
*****************************************************************/
void SVGA_ImgWhiteMask( const int x, const int y, const int color[1024] )//到时候可以换下鼠标图案
{
    /*循环体*/
    register int     i;		//行增量
    register int     j; 	//列增量
    /*用于加速换页*/
    register int     offy;
    /*显存操作*/
    auto     long    position, position1;
    register int    page_new = 0; 
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;
	/*设置初始页面*/
	SVGA_SelectPlane(page_old);
	
    for ( i = 0; i < 32 && offy < 479; i++) //offx最大439 // 不允许从479行(最后一行)开始贴图
    {		
		offy = y + i;
		position1 = offy * 640l+ x;
		if ( offy * 5 % 256 > 251 )
		{
			for ( j = 0 ; j < 32; j++)
			{
				if ( ~(color[ 32 * i + j ]) && ( x + j ) < 640) //offx最大639
				{
					position = position1 + j ; //注意是乘以640
					page_new = position >> 15; //计算显示页
					position &= 0x0000ffffl;   //计算在一个页面上的偏移位置，整除65536的快速方案
					if (page_new != page_old)  //更换页面
					{
						SVGA_SelectPlane(page_new);
						page_old = page_new;
					}
					VideoBuffer[position] = color[ i * 32 + j ];
				}
			}
		}
		else
		{
			page_new = position1 >> 15; //计算显示页
			position1 &= 0x0000ffffl;   //计算在一个页面上的偏移位置，整除65536的快速方案
			if (page_new != page_old)  //更换页面
			{
				SVGA_SelectPlane(page_new);
				page_old = page_new;
			}
					
			for ( j = 0 ; j < 32; j++)
			{
				if ( ~(color[ 32 * i + j ]) && ( x + j ) < 640) //offx最大639
				{
					VideoBuffer[position1 + j] = color[ i * 32 + j ];
				}
			}			
		}
    }
}

void SVGA_ImportSpeBmp( const int width, const int height, const char * const filename, int * const saveFile )//载入指定大小的bmp文件,不能太大
{
	/*循环体*/
	register int i;

	/*BMP信息，图像宽高，图像数据偏移量*/
	long realWidth;
	long realHeight;
	long bdOffset;
	
	/*行读取操作参数*/
	long seekLen;//每行实际信息与所需信息间的字节间隙
	
	/*文件操作*/
	FILE *fp;	
	fp = OpenFile(filename, "rb");
	
	/*检测宽高是否与实际对应*/
	fseek(fp, 0x0012, SEEK_SET);//文件信息指针移到宽高信息位置
	fread(&realWidth, 4, 1, fp);
	fread(&realHeight, 4, 1, fp);
	if( (width!=realWidth) || (height!=realHeight) )
	{
		//Error(ERROR);
	}
	
	/*判断4字节倍数宽度*/
	if((width % 2) == 1)//每行实际信息与所需信息间有2字节间隙
	{
		seekLen = 2;
	}
	else
	{
		seekLen = 0;
	}
		
	/*读入图像数据偏移量*/
	fseek(fp, 0x000a, SEEK_SET);
	fread(&bdOffset, 4, 1, fp);
	
	/*读入内存*/
	fseek(fp, bdOffset, SEEK_SET);
	for(i = height - 1; i >= 0; i--)
	{
		fread(&saveFile[ i * width ], 2, width, fp);
		
		if(i)
		{
			fseek(fp, seekLen, SEEK_CUR);
		}
	}
		
	/*关闭文件*/
	CloseFile(fp);	
}

void SVGA_RestoreSpeArea( const int x, const int y, const int width, const int height, const int * const saveFile )//复原指定大小的桌面图案
{
    /*循环体*/
    register int     i;		//行增量
    register int     j; 	//列增量

    /*显存操作*/
    auto     long    position, position1;
    register char    page_new = 0; 
    /*用于加速换页*/
    register int     offy;
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;
	/*设置初始页面*/
	SVGA_SelectPlane(page_old);
	
    for ( i = 0; i < height && (y + i) < 480; i++) 
    {	
		if((y + i) < 0)//小于0不显示
		{
			continue;
		}
		offy = y + i;
		position1 = offy * 640l+ x;
		if ( offy * 5 % 256 > 251 )
		{			
			for ( j = 0 ; j < width && ( x + j ) < 640; j++)
			{
				if(( x + j ) < 0 )//小于0不显示
				{
					continue;
				}
				
				position = position1 + j ; //注意是乘以640
				page_new = position >> 15; //计算显示页
				position &= 0x0000ffffl;   //计算在一个页面上的偏移位置，整除65536的快速方案				
				if (page_new != page_old)  //更换页面
				{
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}				
				VideoBuffer[position] = saveFile[ i * width + j ];			
			}			
		}
		else
		{
			page_new = position1 >> 15; //计算显示页
			position1 &= 0x0000ffffl;   //计算在一个页面上的偏移位置，整除65536的快速方案				
			if (page_new != page_old)  //更换页面
			{
				SVGA_SelectPlane(page_new);
				page_old = page_new;
			}	
				
			for ( j = 0 ; j < width && ( x + j ) < 640; j++)
			{
				if(( x + j ) < 0 )//小于0不显示
				{
					continue;
				}				
				VideoBuffer[position1 + j] = saveFile[ i * width + j ];			
			}						
		}
    }	
}

void SVGA_SaveSpeArea( const int x, const int y, const int width, const int height, int * const saveFile )//保存指定大小的桌面图案，不能太大
{
    /*循环体*/
    register int     i;		//行增量
    register int     j; 	//列增量
	
    /*显存操作*/
    auto     long    position, position1;
    register char    page_new = 0; 
    /*用于加速换页*/
    register int     offy;
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;
	/*设置初始页面*/
	SVGA_SelectPlane(page_old);
	
    for ( i = 0; i < height &&  (y + i) < 480; i++) 
    {		
		if((y + i) < 0)//小于0不显示
		{
			continue;
		}
		offy = y + i;
		position1 = offy * 640l+ x;
		if ( offy * 5 % 256 > 251 )
		{			
			for ( j = 0 ; j < width && ( x + j ) < 640; j++)
			{
				if(( x + j ) < 0 )//小于0不显示
				{
					continue;
				}
				
				position = position1 + j ; //注意是乘以640
				page_new = position >> 15; //计算显示页
				position &= 0x0000ffffl;   //计算在一个页面上的偏移位置，整除65536的快速方案				
				if (page_new != page_old)  //更换页面
				{
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}				
				saveFile[ i * width + j ] = VideoBuffer[position];			
			}			
		}
		else
		{
			page_new = position1 >> 15; //计算显示页
			position1 &= 0x0000ffffl;   //计算在一个页面上的偏移位置，整除65536的快速方案				
			if (page_new != page_old)  //更换页面
			{
				SVGA_SelectPlane(page_new);
				page_old = page_new;
			}	
				
			for ( j = 0 ; j < width && ( x + j ) < 640; j++)
			{
				if(( x + j ) < 0 )//小于0不显示
				{
					continue;
				}				
				saveFile[ i * width + j ] = VideoBuffer[position1 + j];		
			}						
		}
    }		
}

void SVGA_SpeImgWhiteMask( const int x, const int y, const int width, const int height,const int * const saveFile )//指定图片掩色贴图//贴分数数字什么的
{
	/*循环体*/
	register int i;
	register int j;
	/*显存操作*/
	register int page_new; 
	long position, position1;
    /*用于加速换页*/
    register int     offy;
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;
	/*设置初始页面*/
	SVGA_SelectPlane(page_old);
	
	for(i=0; i<height && (y+i)<480; i++)
	{
		offy = y + i;
		position1 = offy * 640l+ x;
		if ( offy * 5 % 256 > 251 )
		{						
			for(j=0; j<width && (x+j)<640; j++)
			{
				if( ~(saveFile[ i * width + j ]) )//不是白色0xffff
				{	
					position = position1 + j;
					page_new = position >> 15;
					position &= 0x0000ffffl;
				
					if(page_new != page_old)
					{
						SVGA_SelectPlane(page_new);
						page_old = page_new;
					}	
					VideoBuffer[position] = saveFile[ i * width + j ];
				}			
			}	
		}
		else
		{
			page_new = position1 >> 15;
			position1 &= 0x0000ffffl;
				
			if(page_new != page_old)
			{
				SVGA_SelectPlane(page_new);
				page_old = page_new;
			}
					
			for(j=0; j<width && (x+j)<640; j++)
			{
				if( ~(saveFile[ i * width + j ]) )//不是白色0xffff
				{	
					VideoBuffer[position1 + j] = saveFile[ i * width + j ];
				}			
			}				
		}
	}	
}

void SVGA_AngFre( const int x, const int y, const float angle, const int * const saveFile )//画出任意角的图，默认宽高 45*20,xy为中心坐标//由于不是
{                                                                                          //整行连续写，不可用offy判断
	/*循环体*/
	register int i;
	register int j;
	/*显存操作*/
	register int page_new; 
	long position;
	/*小车参数*/
	int width = 45;
	int height = 20;
	int halfWidth = 22;
	int halfHeight = 10;

	float xx0, yy0;   /*为以xy为原点，小车转轴后的新的坐标，y轴正向朝上*/
	int xx, yy , xx1, yy1, dx, dy ;  /*xx，yy用于坐标取整，xx1，yy1用于补点*/

	float co = (float)cos(angle);
	float si = (float)sin(angle);
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;
	/*设置初始页面*/
	SVGA_SelectPlane(page_old);
	
	xx1 = (int)((-halfWidth) * co - halfHeight * si);    /*为xx1，yy1赋初值(-22,10)*/
	yy1 = (int)((-halfWidth) * si + halfHeight * co);
	
	for(i=0; i<height; i++)
	{	
		for(j=0; j<width; j++)
		{
			if( ~(saveFile[ i * width + j ]) )//不是白色0xffff
			{	
				xx0 = (j - halfWidth) * co - (halfHeight - i) * si;    /*为小车转轴后的新的坐标*/
				yy0 = (j - halfWidth) * si + (halfHeight - i) * co;				
				xx = (int)xx0;
				yy = (int)yy0;					
				dx = (xx0 - xx)>0 ? 1 : (-1);//算取整误差
				dy = (yy0 - yy)>0 ? 1 : (-1);

				if((y - yy ) >= 0 && (y - yy ) < 480 && (x + xx) >= 0 && (x + xx) < 640)//点在区域
				{					
					position = (y - yy) * 640l + x + xx ;
					page_new = position >> 15;
					position &= 0x0000ffffl;					
					if(page_new != page_old)
					{
						SVGA_SelectPlane(page_new);
						page_old = page_new;
					}	
					VideoBuffer[position] = saveFile[ i * width + j ];
				}				
				if(xx != xx1)//补点
				{
					if( (y - yy ) >= 0 && (y - yy ) < 480 && (x + xx + dx) >= 0 && (x + xx + dx) < 640
					    && yy >(-25)   &&       yy  < 25  &&   (xx + dx) >(-25) && (xx + dx) < 25 )
					{
						position = (y - yy ) * 640l + x + xx +dx;
						page_new = position >> 15;
						position &= 0x0000ffffl;						
						if(page_new != page_old)
						{
							SVGA_SelectPlane(page_new);
							page_old = page_new;
						}	
						VideoBuffer[position] = saveFile[ i * width + j ];						
					}
				}				
				if(yy != yy1)
				{
					if( (y - yy - dy) >= 0 && (y - yy - dy) < 480 && (x + xx) >= 0 && (x + xx) < 640
					    && (yy + dy)>(-25) &&    (yy + dy)  < 25  &&    xx >(-25)  && xx < 25 )
					{
						position = (y - yy - dy) * 640l + x + xx;
						page_new = position >> 15;
						position &= 0x0000ffffl;						
						if(page_new != page_old)
						{
							SVGA_SelectPlane(page_new);
							page_old = page_new;
						}	
						VideoBuffer[position] = saveFile[ i * width + j ];
					}	
				}									
				xx1 = xx;
				yy1 = yy;
			}// end if
		}
	}	
}


void SVGA_DoubleFre(const int x, const int y, const float angle, int width, int height, const int * const saveFile)//画出任意角,任意大小的图
{
	/*循环体*/
	register int i;
	register int j;
	/*显存操作*/
	register int page_new; 
	long position;
	/*参数*/

	int halfWidth = width/2;
	int halfHeight = height/2;

	float xx0, yy0;   /*为以xy为原点，转轴后的新的坐标，y轴正向朝上*/
	int xx, yy , xx1, yy1, dx, dy ;  /*xx，yy用于坐标取整，xx1，yy1用于补点*/

	float co = (float)cos(angle);
	float si = (float)sin(angle);
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;
	/*设置初始页面*/
	SVGA_SelectPlane(page_old);
	
	xx1 = (int)((-halfWidth) * co - halfHeight * si);    /*为xx1，yy1赋初值(-halfWidth,halfHeight)*/
	yy1 = (int)((-halfWidth) * si + halfHeight * co);
	
	for(i=0; i<height; i++)
	{
		for(j=0; j<width; j++)
		{
			if( ~(saveFile[ i * width + j ]) )//不是白色0xffff
			{	
				xx0 = (j - halfWidth) * co - (halfHeight - i) * si;    /*为转轴后的新的坐标*/
				yy0 = (j - halfWidth) * si + (halfHeight - i) * co;				
				xx = (int)xx0;
				yy = (int)yy0;					
				dx = (xx0 - xx)>0 ? 1 : (-1);//算取整误差
				dy = (yy0 - yy)>0 ? 1 : (-1);

				if((y - yy ) >= 0 && (y - yy ) < 480 && (x + xx) >= 0 && (x + xx) < 640)//点在区域
				{					
					position = (y - yy ) * 640l + x + xx ;
					page_new = position >> 15;
					position &= 0x0000ffffl;
					if(page_new != page_old)
					{
						SVGA_SelectPlane(page_new);
						page_old = page_new;
					}	
					VideoBuffer[position] = saveFile[ i * width + j ];
				}				
				if(xx != xx1)//补点  因为出现缺口的原因是贴的点与原来的点想，x,y坐标均不同
				{
					if( (y - yy ) >= 0 && (y - yy ) < 480 && (x + xx + dx) >= 0 && (x + xx + dx) < 640)
					    /*&& yy >(-25)   &&       yy  < 25  &&   (xx + dx) >(-25) && (xx + dx) < 25(此句原为防止汽车贴出保存边界造成无法还原)*/ 
					{
						position = (y - yy ) * 640l + x + xx +dx;
						page_new = position >> 15;
						position &= 0x0000ffffl;						
						if(page_new != page_old)
						{
							SVGA_SelectPlane(page_new);
							page_old = page_new;
						}	
						VideoBuffer[position] = saveFile[ i * width + j ];						
					}
				}				
				if(yy != yy1)
				{
					if( (y - yy - dy) >= 0 && (y - yy - dy) < 480 && (x + xx) >= 0 && (x + xx) < 640 )
					{
						position = (y - yy - dy) * 640l + x + xx;
						page_new = position >> 15;
						position &= 0x0000ffffl;						
						if(page_new != page_old)
						{
							SVGA_SelectPlane(page_new);
							page_old = page_new;
						}	
						VideoBuffer[position] = saveFile[ i * width + j ];
					}	
				}					
				xx1 = xx;
				yy1 = yy;
			}// end if
		}
	}	
}


int CheckAngFre(const int x, const int y, const float angle, const int * const saveFile)//判断转向后车覆盖的像素点是否与敏感color相同，并返回像素值
{                                                                                          //否则返回0  黑色不可当敏感颜色
	/*循环体*/
	register int i;
	register int j;
	/*显存操作*/
	register int page_new; 
	long position;
	/*小车形状参数*/
	int width = 45;
	int height = 20;
	int halfWidth = 22;
	int halfHeight = 10;

	float xx0, yy0;   /*为以xy为原点，小车转轴后的新的坐标，y轴正向朝上*/
	int xx, yy;

	float co = (float)cos(angle);
	float si = (float)sin(angle);
	
	int color1 =  -128;//0xff80;//像素敏感值
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;
	/*设置初始页面*/
	SVGA_SelectPlane(page_old);
	
	for(i=0; i<height; i++)
	{
		for(j=0; j<width; j++)
		{
			if( ~(saveFile[ i * width + j ]) )//不是白色0xffff
			{	
				xx0 = (j - halfWidth) * co - (halfHeight - i) * si;    /*为小车转轴后的新的坐标*/
				yy0 = (j - halfWidth) * si + (halfHeight - i) * co;				
				xx = (int)xx0;
				yy = (int)yy0;					
				if((y - yy) >= 0 && (y - yy) < 480 && (x + xx) >= 0 && (x + xx) < 640)//点在区域
				{					
					position = (y - yy ) * 640l + x + xx ;
					page_new = position >> 15;
					position &= 0x0000ffffl;				
					if(page_new != page_old)
					{
						SVGA_SelectPlane(page_new);
						page_old = page_new;
					}						

					if( VideoBuffer[position] == color1 )
					{
						return color1;
					}
				}
			}// end if
		}
	}
	return 0;	
}

void Film(const char *path, int fraNum)//文件夹路径 例 film\\start\\,  末尾一定要加
{
	char *pathTemp, *pSub, *pTail, tail[5]=".bmp";
	int i, length;
	
	length = strlen(path);	
	if(fraNum > 999)
	{
		//Error(FILM_ERROR);
	}
	
	pathTemp = (char*)malloc(length + 1 + 3 + 5);//1是存\0， 3是存数字，4存.bmp
	if(pathTemp == NULL)
	{
		//Error(MEM_LACK);
	}
	
	strcpy(pathTemp, path);
	pSub = &(pathTemp[length]);
	
	for(i=1; i<=fraNum; i++)
	{
		itoa(i, pSub, 10);
		
		length = strlen(pSub);
		pTail = &(pSub[length]);
		strcpy(pTail, tail);
		
		SVGA_PartBmp(0,480,0,640,0,0, pathTemp);
	}	
	free(pathTemp);
}

void ZoomPic(const int  x, const int  y, float scale, const char *filename)//放缩图片 
{
	long width, height;
	int w, h;//w,h为放缩后宽高
    /*文件流*/
    FILE *fp;
    /*一行640个像素的颜色数据*/
    auto     int     buffer[640];
    auto     long    lineInts;//每行int型数
    /*循环体使用*/
    register int     i;
    register int     j;
	int             fi;//i对应的实际图片的行数
	int             fj;//j对应的实际图片的列数
    /*这个量仅用于换页，减少一定计算量*/
    register int      spOffsety;
    /*显存位置,使用两个是为了计算位面信息使用*/
    auto     long     position1, position;
    /*位面信息*/
    register int     page_new = 0;
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;
	/*设置初始页面*/
	SVGA_SelectPlane(page_old);
	/*系数限制*/
	if(scale <0)
	{
		//Error(ZOOM_PIC_ERROR);
	}	
	/*获取宽高*/
	SVGA_BMPInfo(filename, &width, &height);
    /*打开文件*/
	fp = OpenFile(filename, "rb");	
    /*拼凑4字节倍数修正宽度*/
	lineInts = width;
	if(lineInts % 2)
	{
		lineInts += 1;
	}		
	/*定位像素信息*/
    //fseek(fp,70l,SEEK_SET);
    /*直接写显存*/
	w = (int)(width * scale);
	h = (int)(height * scale);	
    for ( j = h - 1; j >= 0 && (y + j) >= 0; j--)
    {			
		spOffsety = y + j;//要显示的行序号
		if(spOffsety > 479)//越界
		{
			continue;
		}			
		position = spOffsety * 640l + x;//显示首个像素在屏幕坐标//注意有负数
		fj = (int)(j/scale);//要读取的图片中的行号 //认为fj总小于height		
		fseek(fp,70l+2*lineInts*(height-1-fj),SEEK_SET);
		fread(buffer,2,lineInts,fp);	

			for ( i = 0; i < w && ( x + i ) < 640; i++)
			{
				if(( x + i ) < 0 )//小于0不显示
				{
					continue;
				}				
				fi = (int)(i/scale);//要读取的图片中的列号 //认为fi总小于width
				position1 = position + i; //计算要显示点的显存位置
				page_new = position1 >> 15; //计算显示页
				position1 &= 0x00007fffl;//计算在一个页面上的偏移位置，整除65536的快速方案
				if (page_new != page_old) //更换页面
				{
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}

				VideoBuffer[ position1 ] = buffer[ fi ]; //写到显存位置			
			}

    }
    /*关闭文件*/
	CloseFile(fp);
}

void BrightPic(int x, int y, float brightness, const char *filename)//brightness为亮度 0~2 0为黑，2为白
{
	/*颜色缓存*/
	int color;
    /*一行640个像素的颜色数据*/
    auto     int     buffer[640];
	auto     long    linebytes;
	auto     long    lineInts;
    /*循环体使用*/
    register int      i;
    register int      j;
    /*用于换页，减少一定计算量*/
    auto     int      spOffsety;
    /*BMP信息，图像宽高*/
    auto     long     Width;
    auto     long     Height;
    /*文件流*/
    FILE *fp;
    /*显存操作*/
    auto     long     position1, position;
    register int      page_new = 0;	
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;
	/*选择初始页面*/
	SVGA_SelectPlane(page_old);
    /*打开文件*/
	fp = OpenFile(filename, "rb");
    /*获取BMP的宽高信息*/
	SVGA_BMPInfo(filename, &Width, &Height);
	/*亮度限制*/
	if(brightness<0)
	{
		brightness=0;
	}
	if(brightness>2)
	{
		brightness=2;
	}	
    /*拼凑4字节倍数修正宽度*/
	linebytes = Width * 2;
	if (linebytes % 4) linebytes += 2;
	lineInts = linebytes/2;
    /*直接写显存*/
    fseek(fp,70l, SEEK_SET);
    for ( j = Height - 1; j >= 0; j--)
    {		
		fread(buffer,2,lineInts,fp);
		spOffsety = y + j;
		position = spOffsety * 640l + x;			
		if (  spOffsety * 5 % 256 > 251  )// spOffsety对51.2取余，都同乘5，此时表示算上第spOffsety行用了此页的行数，y=spOffsety表示第spOffsety+1行，
		{                                 //算上这一行后若仍小于51.2，则整行都处于同一页，得式子 spOffsety%51.2 + 1 < 51.2 ，同乘5即得
			for ( i = 0; i < Width; i++)
			{
				position1  = position + i; //计算要显示点的显存位置
				page_new = position1 >> 15; //计算显示页
				position1 &= 0x00007fffl;//计算在一个页面上的偏移位置，整除65536的快速方案
				if (page_new != page_old) //更换页面
				{
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}
				if(brightness<1)//要变暗
				{
					color = PixelMix(buffer[i], brightness, 0x0000, 1-brightness);
				}
				if(brightness>1)//要变亮
				{
					float temp;
					
					temp = brightness - 1;
					color = PixelMix(buffer[i], 1-temp, 0xffff, temp);
				}	
				if(brightness==1)
				{
					color=buffer[i];
				}
				VideoBuffer[position1] = color; //写到显存位置
			}
		}
		else
		{				
			page_new = position >> 15; //计算显示页
			position &= 0x00007fffl;//计算在一个页面上的偏移位置，整除65536的快速方案
			if (page_new != page_old) //更换页面
			{
				SVGA_SelectPlane(page_new);
				page_old = page_new;
			}
			for ( i = 0; i < Width; i++)
			{			
				if(brightness<1)//要变暗
				{
					color = PixelMix(buffer[i], brightness, 0x0000, 1-brightness);
				}
				if(brightness>1)//要变亮
				{
					float temp;
					
					temp = brightness - 1;
					color = PixelMix(buffer[i], 1-temp, 0xffff, temp);
				}	
				if(brightness==1)
				{
					color=buffer[i];
				}				
				VideoBuffer[position+i] = color; //写到显存位置
			}			
		}		
    }
    /*关闭文件*/
	CloseFile(fp);
}

void HollowPic(int x, int y, int hTop, int hBottom, int hLeft, int hRight, const char *filename)//使图片空心 //h前缀表示空心在图片中的上下左右坐标
{
    /*一行640个像素的颜色数据*/
    auto     int     buffer[640];
	auto     long    linebytes;
	auto     long    lineInts;
    /*循环体使用*/
    register int      i;
    register int      j;
    /*用于换页，减少一定计算量*/
    auto     int      spOffsety;
    /*BMP信息，图像宽高*/
    auto     long     Width;
    auto     long     Height;
    /*文件流*/
    FILE *fp;
    /*显存操作*/
    auto     long     position1, position;
    register int      page_new = 0;	
	/*显存指针*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*页面信息*/
	int page_old=0;
	/*选择初始页面*/
	SVGA_SelectPlane(page_old);
    /*打开文件*/
	fp = OpenFile(filename, "rb");
    /*获取BMP的宽高信息*/
	SVGA_BMPInfo(filename, &Width, &Height);
	/*空心部分限制*/
	if(hTop<0 || hBottom>Height-1 || hLeft<0 || hRight>Width-1)
	{
		//Error(HOLLOW_PIC_ERROR);
	}
    /*拼凑4字节倍数修正宽度*/
	linebytes = Width * 2;
	if (linebytes % 4) linebytes += 2;
	lineInts = linebytes/2;
    /*直接写显存*/
    fseek(fp,70l, SEEK_SET);
    for ( j = Height - 1; j >= 0; j--)
    {		
		fread(buffer,2,lineInts,fp);
		spOffsety = y + j;
		position = spOffsety * 640l + x;			
		if (  spOffsety * 5 % 256 > 251  )// spOffsety对51.2取余，都同乘5，此时表示算上第spOffsety行用了此页的行数，y=spOffsety表示第spOffsety+1行，
		{                                 //算上这一行后若仍小于51.2，则整行都处于同一页，得式子 spOffsety%51.2 + 1 < 51.2 ，同乘5即得
			for ( i = 0; i < Width; i++)
			{
				if(j<=hBottom && j>=hTop && i>=hLeft && i<=hRight)
				{
					continue;
				}
				position1  = position + i; //计算要显示点的显存位置
				page_new = position1 >> 15; //计算显示页
				position1 &= 0x00007fffl;//计算在一个页面上的偏移位置，整除65536的快速方案
				if (page_new != page_old) //更换页面
				{
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}
				VideoBuffer[position1] = buffer[i]; //写到显存位置
			}
		}
		else
		{				
			page_new = position >> 15; //计算显示页
			position &= 0x00007fffl;//计算在一个页面上的偏移位置，整除65536的快速方案
			if (page_new != page_old) //更换页面
			{
				SVGA_SelectPlane(page_new);
				page_old = page_new;
			}
			for ( i = 0; i < Width; i++)
			{
				if(j<=hBottom && j>=hTop && i>=hLeft && i<=hRight)
				{
					continue;
				}				
				VideoBuffer[position+i] = buffer[i]; //写到显存位置
			}			
		}		
    }
    /*关闭文件*/
	CloseFile(fp);
}

int PixelMix(int pixel1, float scale1, int pixel2, float scale2)
{
	RGBPIXEL rgbpix1, rgbpix2, rgbpix;	
	int pixel;
	
	if( scale1+scale2>(1+1e-4) || scale1+scale2<(1-1e-4))
	{
		//Error(PIXEL_MIX_ERROR);
	}
	
	IntToRGB(&pixel1, &rgbpix1);
	IntToRGB(&pixel2, &rgbpix2);
	rgbpix.BLUE = (unsigned char)((rgbpix1.BLUE) * scale1 + (rgbpix2.BLUE) * scale2);
	rgbpix.GREEN = (unsigned char)((rgbpix1.GREEN) * scale1 + (rgbpix2.GREEN) * scale2);
	rgbpix.RED = (unsigned char)((rgbpix1.RED) * scale1 + (rgbpix2.RED) * scale2);
	RGBToInt(&rgbpix, &pixel);
	return pixel;
}

void IntToRGB(const int *ppixel, RGBPIXEL *prgbpix)//转换像素格式
{
	register unsigned int pixTemp;
	/*转换*/
	pixTemp = *ppixel;
	
	prgbpix->BLUE = pixTemp & 0x001f;
	pixTemp >>= 5;
	prgbpix->GREEN = pixTemp & 0x003f;
	pixTemp >>= 6;
	prgbpix->RED = pixTemp & 0x001f;
}

void RGBToInt(const RGBPIXEL *prgbpix, int *ppixel)//转换像素格式
{
	register unsigned int pixTemp, temp;
	
	pixTemp = prgbpix->BLUE;
	
	temp =  prgbpix->GREEN;
	temp <<= 5;
	pixTemp |= temp;
	
	temp =  prgbpix->RED;
	temp <<= 11;
	pixTemp |= temp;

	*ppixel = pixTemp;

}
