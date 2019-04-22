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
**��������SVGA_VBEInfo
**������
**    VBEInfo * info        ָ��Ŀ����Ϣλ�õ�ָ��
**���ܣ���ȡVBEӲ����Ϣ
********************************/
/* int SVGA_VBEInfo(VBEInfo * info)
{
    short segx = FP_SEG(info);
    short offx = FP_OFF(info);

    _AX = 0x4F00;   //���ܺ�
    _ES = segx;
    _DI = offx;     //ES:DIָ��ģʽ��Ϣ���ָ��
    __int__(0x10);
    return _AX;
} */

/********************************
**��������SVGA_ModeInfo
**������
**    ModeInfo * info        ָ��Ŀ����Ϣλ�õ�ָ��
**���ܣ���ȡVESA��SVGA����ģʽ��Ϣ
********************************/
/* int SVGA_ModeInfo(ModeInfo * info)
{
    short segx = FP_SEG(info);
    short offx = FP_OFF(info);

    _AX = 0x4F01;   //���ܺ�
    _CX = 0x111;    //��ʾģʽ
    _ES = segx;
    _DI = offx;     //ES:DIָ��ģʽ��Ϣ���ָ��
    __int__(0x10);
    return _AX;
} */

/********************************
**��������SVGA_SelectPlane
**������
**    register char page        Ŀ��λ��
**���ܣ�ѡ����λ��
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
**��������SVGA_SetMode
**������
**    const int vmode            Ŀ��ģʽ
**����ֵ��
**    extern unsigned char    ����ʼ���ɹ�����ֵ0x4F����ʼ��ʧ�ܷ�������ֵ
**���ܣ���ʼ��SVGAģʽ
**    vmode=0x101 640*480*256ɫ
**    vmode=0x103 800*600*256ɫ
**    vmode=0X111 640*480*16Bɫ
**    vmode=0X112 640*480*24Bɫ
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
**��������SVGA_GetMode
**����ֵ��
**    unsigned int    ��ǰ��ʾģʽ���жϺ�
**���ܣ���ȡ��ǰ����ģʽ
********************************/
extern unsigned int 
SVGA_GetMode(void)
{   
    _AX = 0x4f03;
    __int__(0x10); 
    return _BX; 
} 

/********************************
**��������SVGA_SetDisplay
**����ֵ��
**    unsigned int    VBE ����״̬
**���ܣ��޸���ʾ����λ��
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
**��������SVGA_PartBmp
**������
**    const int  top          ͼƬ���ֵ��ϱ߽�������bmpͼƬ�е�����
**    const int  bottom       ͼƬ���ֵ��±߽�������bmpͼƬ�е�����
**    const int  left         ͼƬ���ֵ���߽�������bmpͼƬ�е�����
**    const int  right        ͼƬ���ֵ��ұ߽�������bmpͼƬ�е�����
**    const int  Offsetx      ͼƬ��ʾ����Ļ��λ�õ���߽�����
**    const int  Offsety      ͼƬ��ʾ����Ļ��λ�õ��ϱ߽�����
**    const char *filename    ָ�����������õ�ɫ���ͼƬ
**���ܣ���������ָ��λ�û�ָ���ļ���ָ�����֣������������õ�ɫ��
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
    /*һ��640�����ص���ɫ����*/
    auto     int     buffer[640];
	auto     long    linebytes;

    /*�����ļ�·��*/
    auto     char     filepos[30];

    /*ѭ����ʹ��*/
    register int      i;
    register int      j;

    /*�������*/
    auto     int      ResX;
    auto     int      ResY;

    /*���ڻ�ҳ������һ��������*/
    auto     int      spOffsety;

    /*BMP��Ϣ��ͼ����*/
    auto     long     Width;
    auto     long     Height;

    /*ѡ��Ĳ��ֵĿ��*/
    auto     long     partWidth;
    auto     long     partHeight;

    /*�ļ���*/
    FILE *fp;

    /*�Դ����*/
    auto     long     position1, position;
    register int      page_new = 0;	
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;

	SVGA_SelectPlane(page_old);

    strcpy(filepos,filename);
	// /*����*/
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
    /*���ļ�*/
    if ((fp = fopen(filepos,"rb")) == NULL)
    {
        SVGA_ENtext16(0, 20, filename, _RED);	
	    getch();
		fclose(fp);
		return;
    }

    /*��ȡBMP�Ŀ����Ϣ*/
    fseek(fp,18,SEEK_SET);
    fread(&Width,4,1,fp);
    fread(&Height,4,1,fp);

    /*Ŀ���ļ���ȡ���ֵĿ��*/
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

    /*���ÿ������*/
    if ((partWidth + Offsetx) > 640)
	ResX = 640 - Offsetx;
    else ResX = partWidth;
    if ((partHeight + Offsety) > 480)
	ResY = 480 - Offsety;
    else ResY = partHeight;

    /*ƴ��4�ֽڱ����������*/
	linebytes = Width * 2;
	if (linebytes % 4) linebytes += 2;

    fseek(fp,70 + linebytes * (Height - bottom) + left * 2l, SEEK_SET);
    /*ֱ��д�Դ�*/
    for ( j = partHeight - 1; j >= 0 && (Offsety + j) >= 0; j--)
    {
		fread(buffer,2,partWidth,fp);
		spOffsety = Offsety + j;
		if(spOffsety > 479)//Խ��
		{
			continue;
		}			
		
		
		if (j < ResY)
		{
			position = spOffsety * 640l + Offsetx;
			
			if (  spOffsety * 5 % 256 > 251  )// spOffsety��51.2ȡ�࣬��ͬ��5����ʱ��ʾ���ϵ�spOffsety�����˴�ҳ��������y=spOffsety��ʾ��spOffsety+1�У�
			{                                 //������һ�к�����С��51.2�������ж�����ͬһҳ����ʽ�� spOffsety%51.2 + 1 < 51.2 ��ͬ��5����
				for ( i = 0; i < ResX && i+Offsetx < 640; i++)
				{
				if(( Offsetx + i ) < 0 )//С��0����ʾ
				{
					continue;
				}						
					position1  = position + i; //����Ҫ��ʾ����Դ�λ��
					page_new = position1 >> 15; //������ʾҳ
					position1 &= 0x0000ffffl;//������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���
					if (page_new != page_old) //����ҳ��
					{
						SVGA_SelectPlane(page_new);
						page_old = page_new;
					}
					VideoBuffer[position1] = buffer[i]; //д���Դ�λ��
				}
			}

			else
			{				
				page_new = position >> 15; //������ʾҳ
				position &= 0x0000ffffl;//������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���
				if (page_new != page_old) //����ҳ��
				{					
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}
				for ( i = 0; i < ResX && i+Offsetx < 640; i++)
				{	
				if(( Offsetx + i ) < 0 )//С��0����ʾ
				{
					continue;
				}					
					VideoBuffer[position+i] = buffer[i]; //д���Դ�λ��	
				}			
			}
		}
		fseek(fp,linebytes - partWidth * 2l,SEEK_CUR);
    }
    /*�ر��ļ�*/
    if (fclose(fp)==-1)
    {
      //	printf("Fail to close file");
    }
}

/********************************
**��������SVGA_ImportBmp
**������
**    const char *filename   ָ���ļ���·��
**    int saveColor[1024]    �洢ָ���ļ�������
**���ܣ���������ָ��32*32��С��bmp�ļ������ڴ���
********************************/
void
SVGA_ImportBmp( const char *filename, int saveColor[1024] )
{
    /*�����ļ�·��*/
    auto     char     filepos[30];
    /*ѭ����*/
    register int      j;
	register int      i;
    /*BMP��Ϣ��ͼ����*/
    auto     long     Width;
    auto     long     Height;
    /*�ļ���*/
    FILE *fp;

    strcpy(filepos,filename);

    /*���ļ�*/
    if ((fp = fopen(filepos,"rb")) == NULL)
    {
       //	printf("Fail to open file in Function ImportBmp  ");
	fclose(fp);
	return;
    }

    /*��ȡBMP�Ŀ����Ϣ*/
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
    /*�����ڴ�*/
    for ( j = 31; j >= 0; j--)
    {
		for ( i = 0; i < 32; i++)
		{
			fread(&saveColor[ j * 32 + i ], 2, 1, fp);
		}
    }

    /*�ر��ļ�*/
    if (fclose(fp) == -1)
    {
       //	printf("Fail to close file");
    }
}




/********************************
**��������SVGA_Rectangular
**������
**    const int top       Ŀ����ε��Ͻ�������
**    const int bottom    Ŀ����ε��½�������
**    const int left      Ŀ����ε����������
**    const int right     Ŀ����ε��ҽ�������
**    const int color     ���ߵ���ɫ
**���ܣ�����SVGA_Dot��(left,top)��(right,bottom)������
********************************/
void
SVGA_Rectangular(const int  top,
		 const int  bottom,
		 const int  left,
		 const int  right,
		 const int color)
{
    /*ѭ����*/
    register int     i;
    register int     j;
    /*���δ�С*/
    auto     int     ResY;
    auto     int     ResX;
    /*�Դ����*/
    auto     long     position1, position;
    register int     page_new = 0;
    /*���ڻ�ҳ������һ��������*/
    auto     int      spOffsety;
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;
	/*���ó�ʼҳ��*/
	SVGA_SelectPlane(page_old);
	/*������δ�С*/
    ResY = bottom - top;
    ResX = right - left;

	for ( i = 0;i< ResY && (top + i) < 481; i++)
    {
		spOffsety = top +i;
		position = ( top + i ) * 640l + left;
	    if (  spOffsety * 5 % 256 > 251  )// spOffsety��51.2ȡ�࣬��ͬ��5����ʱ��ʾ���ϵ�spOffsety�����˴�ҳ��������y=spOffsety��ʾ��spOffsety+1�У�
	    {                                 //������һ�к�����С��51.2�������ж�����ͬһҳ����ʽ�� spOffsety%51.2 + 1 < 51.2 ��ͬ��5����
			for ( j = 0; j < ResX && (left + j) < 641; j++)
			{
				position1 = position + j;
				page_new = position1 >> 15; /*������ʾҳ*/
				position1 &= 0x0000ffffl;    /*������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���*/
				if (page_new != page_old)     /*����ҳ��*/
				{
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}
				VideoBuffer[position1] = color;
			}
		}
		else
		{
			page_new = position >> 15; /*������ʾҳ*/
			position &= 0x0000ffffl;    /*������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���*/
			if (page_new != page_old)     /*����ҳ��*/
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
**��������SVGA_MaskBmp
**������
**    const int  top           ָ��������ʾͼ�ε���Ļ��Χ���Ͻ�
**    const int  bottom        ָ��������ʾͼ�ε���Ļ��Χ���½�
**    const int  left          ָ��������ʾͼ�ε���Ļ��Χ�����
**    const int  right         ָ��������ʾͼ�ε���Ļ��Χ���ҽ�
**    const int  Offsetx       ��ʾͼƬ������λ������Ļ�ϵĺ�����
**    const int  Offsety       ��ʾͼƬ������λ������Ļ�ϵ�������
**    const char *filename     Ҫ��ʾͼƬ��·��
**    const int  MaskColor     ͼƬ�Ϻ������ɫֵ��ͬ�Ĳ��ֲ�����ʾ
**���ܣ�����������(Offsetx,Offsety)��BMP��ͨ��top,bottom,right,left�趨ͼ�εķ�Χ�������õ�ɫ�壬MaskColor͸��
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
    /*�ļ���*/
    FILE *fp;

    /*һ��640�����ص���ɫ����*/
    auto     int     buffer[640];
    auto     long    linebytes;

    /*�洢�ļ�·������ֹ������Ϊ�޸�·���ַ������µĴ���*/
    auto     char     filepos[30];

    /*ѭ����ʹ��*/
    register int     i;
    register int     j;

    /*ͼ��λ������*/
    auto     int     ResX;
    auto     int     ResY;

    /*����������ڻ�ҳ������һ��������*/
    register int      spOffsety;

    /*�Դ�λ��,ʹ��������Ϊ�˼���λ����Ϣʹ��*/
    auto     long     position1, position;

    /*BMP��Ϣ��ͼ����*/
    auto     long     Width;
    auto     long     Height;

    /*λ����Ϣ*/
    register int     page_new = 0;
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;
	/*���ó�ʼҳ��*/
	SVGA_SelectPlane(page_old);
    /*��ȡ�ļ�·��*/
    strcpy(filepos,filename);

    /*���ļ�*/
    if ((fp = fopen(filepos,"rb")) == NULL)
    {
       //printf("Fail to open file in Function MaskBmp  ");
	fclose(fp);
	return;
    }

    /*��ȡBMP�Ŀ����Ϣ*/
    fseek(fp,18,SEEK_SET);
    fread(&Width,4,1,fp);
    fread(&Height,4,1,fp);

    /*���ÿ������*/
    if ((Width + Offsetx) > right)
	ResX = right - Offsetx;
    else ResX = Width;

    if ((Height + Offsety) > bottom)
	ResY = bottom - Offsety;
    else ResY = Height;

    /*ƴ��4�ֽڱ���������ȣ�ע�Ȿ���ֻ�ı�Width��ֵ��Ӧ���ȼ���ResX*/
	linebytes = Width;
	if (linebytes % 2) linebytes += 1;

    fseek(fp,70l,SEEK_SET);
    /*ֱ��д�Դ�*/
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
					position1 = position + i; //����Ҫ��ʾ����Դ�λ��

					page_new = position1 >> 15; //������ʾҳ
					position1 &= 0x0000ffffl;//������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���
					if (page_new != page_old) //����ҳ��
					{
						SVGA_SelectPlane(page_new);
						page_old = page_new;
					}
					if ((buffer[i] != MaskColor) && (i + Offsetx) > left)
						VideoBuffer[ position1 ] = buffer[ i ]; //д���Դ�λ��
				}
			}

			else
			{
				page_new = position >> 15; //������ʾҳ

				position &= 0x0000ffffl;//������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���
				if (page_new != page_old) //����ҳ��
				{
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}
				for ( i = 0; i < ResX; i++)
				{
					if ((buffer[i] != MaskColor) && (i + Offsetx) > left)
						VideoBuffer[ position + i ] = buffer[ i ]; //д���Դ�λ��
				}
				
			}
		}
    }
    /*�ر��ļ�*/
    if (fclose(fp) == -1)
    {
       //	printf("Fail to close file");
    }
}

/********************************
**��������SVGA_ImgBlackMask
**������
**    const int x              ָ��Ҫ��ʾͼ������Ļ�ϵĺ�����
**    const int y              ָ��Ҫ��ʾͼ������Ļ�ϵ�������
**    const int color[1024]    �洢ͼ�ε�����
**���ܣ���������ָ��32*32��С���ڴ���ͼ��д���Դ棬���ɫ���ֲ���ʾ
********************************/
void
SVGA_ImgBlackMask(  const int x,
		    const int y,
		    const int color[1024])
{
    /*ѭ����*/
    register int     i;
    register int     j;
    /*���ڼ��ٻ�ҳ*/
    register int     offy;
    /*�Դ����*/
    auto     long     position1, position;
    register int      page_new = 0;
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;
	/*���ó�ʼҳ��*/
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
					page_new = position1 >> 15; //������ʾҳ
					position1 &= 0x00007fffl;//������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���
					if (page_new != page_old) //����ҳ��
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
			page_new = position >> 15; //������ʾҳ
			position &= 0x00007fffl;//������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���
			if (page_new != page_old) //����ҳ��
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
**��������SVGA_CHtext16
**������
**    const int  x         ָ��Ҫ��ʾ�������������Ļ�ϵ�λ��
**    const int  y         ָ��Ҫ��ʾ�������Ҷ�����Ļ�ϵ�λ��
**    const char *s        ��������ʾҪ��ʾ������
**    const int  color     colorָ��Ҫ��ʾ���ֵ���ɫ
**���ܣ�����������SVGA_Dot���16*16��С�ĺ���
********************************/
void
SVGA_CHtext16(  const int  x,
		const int  y,
		const char s[],
		const int color )//����25������
{
    /*�ļ���*/
    FILE *fp;
    /*ѭ����ʹ��*/
    register int     i;
    register int     j;
    register int     k;
    auto     int     l = 0;
    auto     int     startX = x;
    /*���ֿ����*/
    register unsigned char qh;
    register unsigned char wh;
    register unsigned long location;
    auto     char    buffer[32];
    /*�����ַ���*/
    auto     char    string[51];
    /*�Դ����*/
    auto     long    position1;
    register int     page_new = 0;
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;
	/*���ó�ʼҳ��*/
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
		location = (94 * (qh - 1) + (wh - 1)) * 32L; //����λ����
		fseek(fp,location,SEEK_SET);
		fread(buffer,32,1,fp);           //����������Ϣ
		for ( i = 0; i < 16; i++)
		{
			for ( j = 0; j < 2; j++)
			{
				for ( k = 0; k < 8; k++)
				{
					if ((buffer[i * 2 + j] >> (7 - k)) & 0x1)  //Ϊ1��λ��ʾ
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
**��������SVGA_ENtext16
**������
**    const int  x        ָ��Ҫ��ʾ�������������Ļ�ϵ�λ��
**    const int  y        ָ��Ҫ��ʾ�������Ҷ�����Ļ�ϵ�λ��
**    const char *s       ��������ʾҪ��ʾ������
**    const int  color    colorָ��Ҫ��ʾ���ֵ���ɫ
**���ܣ�����SVGA_Dot���8*16��С��ASC�ַ�
********************************/
void
SVGA_ENtext16( const int  x,
	       const int  y,
	       const char s[],
	       const int  color )//����40
{
    /*�ļ���*/
    FILE *fp;
    /*ѭ����*/
    register int     i;
    register int     j;
    register int     k;
    register int     l;
    register int     startX;
    /*�ֿ����*/
    register unsigned char     wh;
    register unsigned long    position;
    auto     char    buffer[32];
    /*�����ַ���*/
    auto     char    string[41];
    /*�Դ����*/
    auto     long    position1;
    register int     page_new = 0;
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;
	/*���ó�ʼҳ��*/
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
		position = wh * 16L;                         //����λ����
		fseek(fp,position,SEEK_SET);
		fread(buffer,16,1,fp);                        //����������Ϣ
		for ( i = 0; i < 16; i++)
		{
			for ( k = 0; k < 8; k++)
			{
				if ((buffer[i] >> (7 - k)) & 0x1)    //Ϊ1��λ��ʾ
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
**��������SVGA_ENtextch16
**������
**    const int  x        ָ��Ҫ��ʾ�������������Ļ�ϵ�λ��
**    const int  y        ָ��Ҫ��ʾ�������Ҷ�����Ļ�ϵ�λ��
**    const char s        Ҫ������ַ�
**    const int  color    colorָ��Ҫ��ʾ���ֵ���ɫ
**���ܣ�����SVGA_Dot���8*16��С��ASC�ַ�
********************************/
void
SVGA_ENtextch16( const int  x,
	       const int  y,
	       const char s,
	       const int  color )//����40
{
    /*�ļ���*/
    FILE *fp;
    /*ѭ����*/
    register int     i;
    register int     j;
    register int     k;
    register int     l;
    register int     startX;
    /*�ֿ����*/
    register unsigned char     wh;
    register unsigned long    position;
    auto     char    buffer[32];
    /*�����ַ���*/
    auto     char    string[41];
    /*�Դ����*/
    auto     long    position1;
    register int     page_new = 0;
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;
	/*���ó�ʼҳ��*/
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
		position = wh * 16L;                         //����λ����
		fseek(fp,position,SEEK_SET);
		fread(buffer,16,1,fp);                        //����������Ϣ
		for ( i = 0; i < 16; i++)
		{
			for ( k = 0; k < 8; k++)
			{
				if ((buffer[i] >> (7 - k)) & 0x1)    //Ϊ1��λ��ʾ
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
**��������SVGA_SaveArea
**������
**    const int x     Ŀ��λ�������
**    const int y     Ŀ��λ���Ͻ���
**    int str[1024]    ���ڼĴ�ͼ�ε�����
**���ܣ�����SVGA_GetDot��(x,y)��ȡ��Χ32*32�ĵ����Ϣ
**����MousePrint���������ʾ
********************************/
void
SVGA_SaveArea( const int x,
	       const int y,
	       int str[1024])
{
    /*ѭ����*/
    register int     i;
    register int     j;
    /*���ڼ��ٻ�ҳ*/
    auto     int     offy;
    /*�Դ����*/
    auto     long     position1, position;
    register int      page_new = 0;
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;
	/*���ó�ʼҳ��*/
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
**��������SVGA_RestoreArea
**������
**    int x         Ŀ��λ�������
**    int y         Ŀ��λ���Ͻ���
**    int str[1024]    ���ڼĴ�ͼ�ε�����
**���ܣ�����SVGA_Dot��(x,y)����Χ32*32�ĵ��ͼ��
**����MousePrint���������ʾ
********************************/
void
SVGA_RestoreArea(const int  x,
		 const int  y,
		 const int  str[1024])
{
    /*ѭ����*/
    register int     i;
    register int     j;
    /*���ڼ��ٻ�ҳ*/
    auto     int    offy;
    /*�Դ����*/
    auto     long     position1,position;
    register int     page_new = 0;
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;
	/*���ó�ʼҳ��*/
	SVGA_SelectPlane(page_old);
	
    for ( i = 0; i < 32 && (y + i) < 481; i++)
    {
		offy = y + i;
		position = offy * 640l + x;
		if (  offy * 5 % 256 > 251 )
		{
			for ( j = 0; j < 32 && (x + j) < 641; j++)
			{
				position1 = position + j; //����Ҫ��ʾ����Դ�λ��
				page_new = position1 >> 15; //������ʾҳ
				position1 &= 0x0000ffffl;//������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���
				if (page_new != page_old) //����ҳ��
				{
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}
				VideoBuffer[position1] = str[ 32 * i + j ];
			}
		}
		else
		{
			page_new = position >> 15; //������ʾҳ
			position &= 0x0000ffffl;//������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���
			if (page_new != page_old) //����ҳ��
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
**��������SVGA_BMPInfo
**������
**    const char * const filename   Ŀ���ļ�·��
**    int * const Width             ��¼��ȵ�ָ��
**    int * const Height            ��¼���ȵ�ָ��
**���ܣ���ȡĿ��bmp�ļ��ĳ�����Ϣ
********************************/
void
SVGA_BMPInfo(const char * const filename,
	     long * const Width,
	     long * const Height)
{
    /*�����ļ�·����Ϣ*/
    auto     char      filepos[30];

    /*�ļ���*/
	FILE  *fp;

    strcpy(filepos,filename);              //��ȡ�ļ�·��

    /*���ļ�*/
    if ((fp = fopen(filepos,"rb")) == NULL)
    {
       //	printf("Fail to open file");
	fclose(fp);
	return;
    }

    /*��ȡBMP�Ŀ����Ϣ*/
    fseek(fp,18,SEEK_SET);
    fread(Width,4,1,fp);
    fread(Height,4,1,fp);
	fclose(fp);
}
/******************************����Ϊ14����ǰ����***********************************************************/
//���и�������ͼ����Ƿȱ�����崦��ZoomPic()
/******************************************************************
**��������SVGA_ImgWhiteMask
**������
**    const int x              ָ��Ҫ��ʾͼ������Ļ�ϵĺ�����
**    const int y              ָ��Ҫ��ʾͼ������Ļ�ϵ�������
**    const int color[1024]    �洢ͼ�ε�����
**���ܣ���������ָ��32*32��С���ڴ���ͼ��д���Դ棬���ɫ���ֲ���ʾ
*****************************************************************/
void SVGA_ImgWhiteMask( const int x, const int y, const int color[1024] )//��ʱ����Ի������ͼ��
{
    /*ѭ����*/
    register int     i;		//������
    register int     j; 	//������
    /*���ڼ��ٻ�ҳ*/
    register int     offy;
    /*�Դ����*/
    auto     long    position, position1;
    register int    page_new = 0; 
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;
	/*���ó�ʼҳ��*/
	SVGA_SelectPlane(page_old);
	
    for ( i = 0; i < 32 && offy < 479; i++) //offx���439 // �������479��(���һ��)��ʼ��ͼ
    {		
		offy = y + i;
		position1 = offy * 640l+ x;
		if ( offy * 5 % 256 > 251 )
		{
			for ( j = 0 ; j < 32; j++)
			{
				if ( ~(color[ 32 * i + j ]) && ( x + j ) < 640) //offx���639
				{
					position = position1 + j ; //ע���ǳ���640
					page_new = position >> 15; //������ʾҳ
					position &= 0x0000ffffl;   //������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���
					if (page_new != page_old)  //����ҳ��
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
			page_new = position1 >> 15; //������ʾҳ
			position1 &= 0x0000ffffl;   //������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���
			if (page_new != page_old)  //����ҳ��
			{
				SVGA_SelectPlane(page_new);
				page_old = page_new;
			}
					
			for ( j = 0 ; j < 32; j++)
			{
				if ( ~(color[ 32 * i + j ]) && ( x + j ) < 640) //offx���639
				{
					VideoBuffer[position1 + j] = color[ i * 32 + j ];
				}
			}			
		}
    }
}

void SVGA_ImportSpeBmp( const int width, const int height, const char * const filename, int * const saveFile )//����ָ����С��bmp�ļ�,����̫��
{
	/*ѭ����*/
	register int i;

	/*BMP��Ϣ��ͼ���ߣ�ͼ������ƫ����*/
	long realWidth;
	long realHeight;
	long bdOffset;
	
	/*�ж�ȡ��������*/
	long seekLen;//ÿ��ʵ����Ϣ��������Ϣ����ֽڼ�϶
	
	/*�ļ�����*/
	FILE *fp;	
	fp = OpenFile(filename, "rb");
	
	/*������Ƿ���ʵ�ʶ�Ӧ*/
	fseek(fp, 0x0012, SEEK_SET);//�ļ���Ϣָ���Ƶ������Ϣλ��
	fread(&realWidth, 4, 1, fp);
	fread(&realHeight, 4, 1, fp);
	if( (width!=realWidth) || (height!=realHeight) )
	{
		//Error(ERROR);
	}
	
	/*�ж�4�ֽڱ������*/
	if((width % 2) == 1)//ÿ��ʵ����Ϣ��������Ϣ����2�ֽڼ�϶
	{
		seekLen = 2;
	}
	else
	{
		seekLen = 0;
	}
		
	/*����ͼ������ƫ����*/
	fseek(fp, 0x000a, SEEK_SET);
	fread(&bdOffset, 4, 1, fp);
	
	/*�����ڴ�*/
	fseek(fp, bdOffset, SEEK_SET);
	for(i = height - 1; i >= 0; i--)
	{
		fread(&saveFile[ i * width ], 2, width, fp);
		
		if(i)
		{
			fseek(fp, seekLen, SEEK_CUR);
		}
	}
		
	/*�ر��ļ�*/
	CloseFile(fp);	
}

void SVGA_RestoreSpeArea( const int x, const int y, const int width, const int height, const int * const saveFile )//��ԭָ����С������ͼ��
{
    /*ѭ����*/
    register int     i;		//������
    register int     j; 	//������

    /*�Դ����*/
    auto     long    position, position1;
    register char    page_new = 0; 
    /*���ڼ��ٻ�ҳ*/
    register int     offy;
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;
	/*���ó�ʼҳ��*/
	SVGA_SelectPlane(page_old);
	
    for ( i = 0; i < height && (y + i) < 480; i++) 
    {	
		if((y + i) < 0)//С��0����ʾ
		{
			continue;
		}
		offy = y + i;
		position1 = offy * 640l+ x;
		if ( offy * 5 % 256 > 251 )
		{			
			for ( j = 0 ; j < width && ( x + j ) < 640; j++)
			{
				if(( x + j ) < 0 )//С��0����ʾ
				{
					continue;
				}
				
				position = position1 + j ; //ע���ǳ���640
				page_new = position >> 15; //������ʾҳ
				position &= 0x0000ffffl;   //������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���				
				if (page_new != page_old)  //����ҳ��
				{
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}				
				VideoBuffer[position] = saveFile[ i * width + j ];			
			}			
		}
		else
		{
			page_new = position1 >> 15; //������ʾҳ
			position1 &= 0x0000ffffl;   //������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���				
			if (page_new != page_old)  //����ҳ��
			{
				SVGA_SelectPlane(page_new);
				page_old = page_new;
			}	
				
			for ( j = 0 ; j < width && ( x + j ) < 640; j++)
			{
				if(( x + j ) < 0 )//С��0����ʾ
				{
					continue;
				}				
				VideoBuffer[position1 + j] = saveFile[ i * width + j ];			
			}						
		}
    }	
}

void SVGA_SaveSpeArea( const int x, const int y, const int width, const int height, int * const saveFile )//����ָ����С������ͼ��������̫��
{
    /*ѭ����*/
    register int     i;		//������
    register int     j; 	//������
	
    /*�Դ����*/
    auto     long    position, position1;
    register char    page_new = 0; 
    /*���ڼ��ٻ�ҳ*/
    register int     offy;
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;
	/*���ó�ʼҳ��*/
	SVGA_SelectPlane(page_old);
	
    for ( i = 0; i < height &&  (y + i) < 480; i++) 
    {		
		if((y + i) < 0)//С��0����ʾ
		{
			continue;
		}
		offy = y + i;
		position1 = offy * 640l+ x;
		if ( offy * 5 % 256 > 251 )
		{			
			for ( j = 0 ; j < width && ( x + j ) < 640; j++)
			{
				if(( x + j ) < 0 )//С��0����ʾ
				{
					continue;
				}
				
				position = position1 + j ; //ע���ǳ���640
				page_new = position >> 15; //������ʾҳ
				position &= 0x0000ffffl;   //������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���				
				if (page_new != page_old)  //����ҳ��
				{
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}				
				saveFile[ i * width + j ] = VideoBuffer[position];			
			}			
		}
		else
		{
			page_new = position1 >> 15; //������ʾҳ
			position1 &= 0x0000ffffl;   //������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���				
			if (page_new != page_old)  //����ҳ��
			{
				SVGA_SelectPlane(page_new);
				page_old = page_new;
			}	
				
			for ( j = 0 ; j < width && ( x + j ) < 640; j++)
			{
				if(( x + j ) < 0 )//С��0����ʾ
				{
					continue;
				}				
				saveFile[ i * width + j ] = VideoBuffer[position1 + j];		
			}						
		}
    }		
}

void SVGA_SpeImgWhiteMask( const int x, const int y, const int width, const int height,const int * const saveFile )//ָ��ͼƬ��ɫ��ͼ//����������ʲô��
{
	/*ѭ����*/
	register int i;
	register int j;
	/*�Դ����*/
	register int page_new; 
	long position, position1;
    /*���ڼ��ٻ�ҳ*/
    register int     offy;
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;
	/*���ó�ʼҳ��*/
	SVGA_SelectPlane(page_old);
	
	for(i=0; i<height && (y+i)<480; i++)
	{
		offy = y + i;
		position1 = offy * 640l+ x;
		if ( offy * 5 % 256 > 251 )
		{						
			for(j=0; j<width && (x+j)<640; j++)
			{
				if( ~(saveFile[ i * width + j ]) )//���ǰ�ɫ0xffff
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
				if( ~(saveFile[ i * width + j ]) )//���ǰ�ɫ0xffff
				{	
					VideoBuffer[position1 + j] = saveFile[ i * width + j ];
				}			
			}				
		}
	}	
}

void SVGA_AngFre( const int x, const int y, const float angle, const int * const saveFile )//��������ǵ�ͼ��Ĭ�Ͽ�� 45*20,xyΪ��������//���ڲ���
{                                                                                          //��������д��������offy�ж�
	/*ѭ����*/
	register int i;
	register int j;
	/*�Դ����*/
	register int page_new; 
	long position;
	/*С������*/
	int width = 45;
	int height = 20;
	int halfWidth = 22;
	int halfHeight = 10;

	float xx0, yy0;   /*Ϊ��xyΪԭ�㣬С��ת�����µ����꣬y��������*/
	int xx, yy , xx1, yy1, dx, dy ;  /*xx��yy��������ȡ����xx1��yy1���ڲ���*/

	float co = (float)cos(angle);
	float si = (float)sin(angle);
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;
	/*���ó�ʼҳ��*/
	SVGA_SelectPlane(page_old);
	
	xx1 = (int)((-halfWidth) * co - halfHeight * si);    /*Ϊxx1��yy1����ֵ(-22,10)*/
	yy1 = (int)((-halfWidth) * si + halfHeight * co);
	
	for(i=0; i<height; i++)
	{	
		for(j=0; j<width; j++)
		{
			if( ~(saveFile[ i * width + j ]) )//���ǰ�ɫ0xffff
			{	
				xx0 = (j - halfWidth) * co - (halfHeight - i) * si;    /*ΪС��ת�����µ�����*/
				yy0 = (j - halfWidth) * si + (halfHeight - i) * co;				
				xx = (int)xx0;
				yy = (int)yy0;					
				dx = (xx0 - xx)>0 ? 1 : (-1);//��ȡ�����
				dy = (yy0 - yy)>0 ? 1 : (-1);

				if((y - yy ) >= 0 && (y - yy ) < 480 && (x + xx) >= 0 && (x + xx) < 640)//��������
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
				if(xx != xx1)//����
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


void SVGA_DoubleFre(const int x, const int y, const float angle, int width, int height, const int * const saveFile)//���������,�����С��ͼ
{
	/*ѭ����*/
	register int i;
	register int j;
	/*�Դ����*/
	register int page_new; 
	long position;
	/*����*/

	int halfWidth = width/2;
	int halfHeight = height/2;

	float xx0, yy0;   /*Ϊ��xyΪԭ�㣬ת�����µ����꣬y��������*/
	int xx, yy , xx1, yy1, dx, dy ;  /*xx��yy��������ȡ����xx1��yy1���ڲ���*/

	float co = (float)cos(angle);
	float si = (float)sin(angle);
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;
	/*���ó�ʼҳ��*/
	SVGA_SelectPlane(page_old);
	
	xx1 = (int)((-halfWidth) * co - halfHeight * si);    /*Ϊxx1��yy1����ֵ(-halfWidth,halfHeight)*/
	yy1 = (int)((-halfWidth) * si + halfHeight * co);
	
	for(i=0; i<height; i++)
	{
		for(j=0; j<width; j++)
		{
			if( ~(saveFile[ i * width + j ]) )//���ǰ�ɫ0xffff
			{	
				xx0 = (j - halfWidth) * co - (halfHeight - i) * si;    /*Ϊת�����µ�����*/
				yy0 = (j - halfWidth) * si + (halfHeight - i) * co;				
				xx = (int)xx0;
				yy = (int)yy0;					
				dx = (xx0 - xx)>0 ? 1 : (-1);//��ȡ�����
				dy = (yy0 - yy)>0 ? 1 : (-1);

				if((y - yy ) >= 0 && (y - yy ) < 480 && (x + xx) >= 0 && (x + xx) < 640)//��������
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
				if(xx != xx1)//����  ��Ϊ����ȱ�ڵ�ԭ�������ĵ���ԭ���ĵ��룬x,y�������ͬ
				{
					if( (y - yy ) >= 0 && (y - yy ) < 480 && (x + xx + dx) >= 0 && (x + xx + dx) < 640)
					    /*&& yy >(-25)   &&       yy  < 25  &&   (xx + dx) >(-25) && (xx + dx) < 25(�˾�ԭΪ��ֹ������������߽�����޷���ԭ)*/ 
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


int CheckAngFre(const int x, const int y, const float angle, const int * const saveFile)//�ж�ת��󳵸��ǵ����ص��Ƿ�������color��ͬ������������ֵ
{                                                                                          //���򷵻�0  ��ɫ���ɵ�������ɫ
	/*ѭ����*/
	register int i;
	register int j;
	/*�Դ����*/
	register int page_new; 
	long position;
	/*С����״����*/
	int width = 45;
	int height = 20;
	int halfWidth = 22;
	int halfHeight = 10;

	float xx0, yy0;   /*Ϊ��xyΪԭ�㣬С��ת�����µ����꣬y��������*/
	int xx, yy;

	float co = (float)cos(angle);
	float si = (float)sin(angle);
	
	int color1 =  -128;//0xff80;//��������ֵ
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;
	/*���ó�ʼҳ��*/
	SVGA_SelectPlane(page_old);
	
	for(i=0; i<height; i++)
	{
		for(j=0; j<width; j++)
		{
			if( ~(saveFile[ i * width + j ]) )//���ǰ�ɫ0xffff
			{	
				xx0 = (j - halfWidth) * co - (halfHeight - i) * si;    /*ΪС��ת�����µ�����*/
				yy0 = (j - halfWidth) * si + (halfHeight - i) * co;				
				xx = (int)xx0;
				yy = (int)yy0;					
				if((y - yy) >= 0 && (y - yy) < 480 && (x + xx) >= 0 && (x + xx) < 640)//��������
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

void Film(const char *path, int fraNum)//�ļ���·�� �� film\\start\\,  ĩβһ��Ҫ��
{
	char *pathTemp, *pSub, *pTail, tail[5]=".bmp";
	int i, length;
	
	length = strlen(path);	
	if(fraNum > 999)
	{
		//Error(FILM_ERROR);
	}
	
	pathTemp = (char*)malloc(length + 1 + 3 + 5);//1�Ǵ�\0�� 3�Ǵ����֣�4��.bmp
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

void ZoomPic(const int  x, const int  y, float scale, const char *filename)//����ͼƬ 
{
	long width, height;
	int w, h;//w,hΪ��������
    /*�ļ���*/
    FILE *fp;
    /*һ��640�����ص���ɫ����*/
    auto     int     buffer[640];
    auto     long    lineInts;//ÿ��int����
    /*ѭ����ʹ��*/
    register int     i;
    register int     j;
	int             fi;//i��Ӧ��ʵ��ͼƬ������
	int             fj;//j��Ӧ��ʵ��ͼƬ������
    /*����������ڻ�ҳ������һ��������*/
    register int      spOffsety;
    /*�Դ�λ��,ʹ��������Ϊ�˼���λ����Ϣʹ��*/
    auto     long     position1, position;
    /*λ����Ϣ*/
    register int     page_new = 0;
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;
	/*���ó�ʼҳ��*/
	SVGA_SelectPlane(page_old);
	/*ϵ������*/
	if(scale <0)
	{
		//Error(ZOOM_PIC_ERROR);
	}	
	/*��ȡ���*/
	SVGA_BMPInfo(filename, &width, &height);
    /*���ļ�*/
	fp = OpenFile(filename, "rb");	
    /*ƴ��4�ֽڱ����������*/
	lineInts = width;
	if(lineInts % 2)
	{
		lineInts += 1;
	}		
	/*��λ������Ϣ*/
    //fseek(fp,70l,SEEK_SET);
    /*ֱ��д�Դ�*/
	w = (int)(width * scale);
	h = (int)(height * scale);	
    for ( j = h - 1; j >= 0 && (y + j) >= 0; j--)
    {			
		spOffsety = y + j;//Ҫ��ʾ�������
		if(spOffsety > 479)//Խ��
		{
			continue;
		}			
		position = spOffsety * 640l + x;//��ʾ�׸���������Ļ����//ע���и���
		fj = (int)(j/scale);//Ҫ��ȡ��ͼƬ�е��к� //��Ϊfj��С��height		
		fseek(fp,70l+2*lineInts*(height-1-fj),SEEK_SET);
		fread(buffer,2,lineInts,fp);	

			for ( i = 0; i < w && ( x + i ) < 640; i++)
			{
				if(( x + i ) < 0 )//С��0����ʾ
				{
					continue;
				}				
				fi = (int)(i/scale);//Ҫ��ȡ��ͼƬ�е��к� //��Ϊfi��С��width
				position1 = position + i; //����Ҫ��ʾ����Դ�λ��
				page_new = position1 >> 15; //������ʾҳ
				position1 &= 0x00007fffl;//������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���
				if (page_new != page_old) //����ҳ��
				{
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}

				VideoBuffer[ position1 ] = buffer[ fi ]; //д���Դ�λ��			
			}

    }
    /*�ر��ļ�*/
	CloseFile(fp);
}

void BrightPic(int x, int y, float brightness, const char *filename)//brightnessΪ���� 0~2 0Ϊ�ڣ�2Ϊ��
{
	/*��ɫ����*/
	int color;
    /*һ��640�����ص���ɫ����*/
    auto     int     buffer[640];
	auto     long    linebytes;
	auto     long    lineInts;
    /*ѭ����ʹ��*/
    register int      i;
    register int      j;
    /*���ڻ�ҳ������һ��������*/
    auto     int      spOffsety;
    /*BMP��Ϣ��ͼ����*/
    auto     long     Width;
    auto     long     Height;
    /*�ļ���*/
    FILE *fp;
    /*�Դ����*/
    auto     long     position1, position;
    register int      page_new = 0;	
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;
	/*ѡ���ʼҳ��*/
	SVGA_SelectPlane(page_old);
    /*���ļ�*/
	fp = OpenFile(filename, "rb");
    /*��ȡBMP�Ŀ����Ϣ*/
	SVGA_BMPInfo(filename, &Width, &Height);
	/*��������*/
	if(brightness<0)
	{
		brightness=0;
	}
	if(brightness>2)
	{
		brightness=2;
	}	
    /*ƴ��4�ֽڱ����������*/
	linebytes = Width * 2;
	if (linebytes % 4) linebytes += 2;
	lineInts = linebytes/2;
    /*ֱ��д�Դ�*/
    fseek(fp,70l, SEEK_SET);
    for ( j = Height - 1; j >= 0; j--)
    {		
		fread(buffer,2,lineInts,fp);
		spOffsety = y + j;
		position = spOffsety * 640l + x;			
		if (  spOffsety * 5 % 256 > 251  )// spOffsety��51.2ȡ�࣬��ͬ��5����ʱ��ʾ���ϵ�spOffsety�����˴�ҳ��������y=spOffsety��ʾ��spOffsety+1�У�
		{                                 //������һ�к�����С��51.2�������ж�����ͬһҳ����ʽ�� spOffsety%51.2 + 1 < 51.2 ��ͬ��5����
			for ( i = 0; i < Width; i++)
			{
				position1  = position + i; //����Ҫ��ʾ����Դ�λ��
				page_new = position1 >> 15; //������ʾҳ
				position1 &= 0x00007fffl;//������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���
				if (page_new != page_old) //����ҳ��
				{
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}
				if(brightness<1)//Ҫ�䰵
				{
					color = PixelMix(buffer[i], brightness, 0x0000, 1-brightness);
				}
				if(brightness>1)//Ҫ����
				{
					float temp;
					
					temp = brightness - 1;
					color = PixelMix(buffer[i], 1-temp, 0xffff, temp);
				}	
				if(brightness==1)
				{
					color=buffer[i];
				}
				VideoBuffer[position1] = color; //д���Դ�λ��
			}
		}
		else
		{				
			page_new = position >> 15; //������ʾҳ
			position &= 0x00007fffl;//������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���
			if (page_new != page_old) //����ҳ��
			{
				SVGA_SelectPlane(page_new);
				page_old = page_new;
			}
			for ( i = 0; i < Width; i++)
			{			
				if(brightness<1)//Ҫ�䰵
				{
					color = PixelMix(buffer[i], brightness, 0x0000, 1-brightness);
				}
				if(brightness>1)//Ҫ����
				{
					float temp;
					
					temp = brightness - 1;
					color = PixelMix(buffer[i], 1-temp, 0xffff, temp);
				}	
				if(brightness==1)
				{
					color=buffer[i];
				}				
				VideoBuffer[position+i] = color; //д���Դ�λ��
			}			
		}		
    }
    /*�ر��ļ�*/
	CloseFile(fp);
}

void HollowPic(int x, int y, int hTop, int hBottom, int hLeft, int hRight, const char *filename)//ʹͼƬ���� //hǰ׺��ʾ������ͼƬ�е�������������
{
    /*һ��640�����ص���ɫ����*/
    auto     int     buffer[640];
	auto     long    linebytes;
	auto     long    lineInts;
    /*ѭ����ʹ��*/
    register int      i;
    register int      j;
    /*���ڻ�ҳ������һ��������*/
    auto     int      spOffsety;
    /*BMP��Ϣ��ͼ����*/
    auto     long     Width;
    auto     long     Height;
    /*�ļ���*/
    FILE *fp;
    /*�Դ����*/
    auto     long     position1, position;
    register int      page_new = 0;	
	/*�Դ�ָ��*/
	int far * const VideoBuffer = (int far *)0xA0000000L;
	/*ҳ����Ϣ*/
	int page_old=0;
	/*ѡ���ʼҳ��*/
	SVGA_SelectPlane(page_old);
    /*���ļ�*/
	fp = OpenFile(filename, "rb");
    /*��ȡBMP�Ŀ����Ϣ*/
	SVGA_BMPInfo(filename, &Width, &Height);
	/*���Ĳ�������*/
	if(hTop<0 || hBottom>Height-1 || hLeft<0 || hRight>Width-1)
	{
		//Error(HOLLOW_PIC_ERROR);
	}
    /*ƴ��4�ֽڱ����������*/
	linebytes = Width * 2;
	if (linebytes % 4) linebytes += 2;
	lineInts = linebytes/2;
    /*ֱ��д�Դ�*/
    fseek(fp,70l, SEEK_SET);
    for ( j = Height - 1; j >= 0; j--)
    {		
		fread(buffer,2,lineInts,fp);
		spOffsety = y + j;
		position = spOffsety * 640l + x;			
		if (  spOffsety * 5 % 256 > 251  )// spOffsety��51.2ȡ�࣬��ͬ��5����ʱ��ʾ���ϵ�spOffsety�����˴�ҳ��������y=spOffsety��ʾ��spOffsety+1�У�
		{                                 //������һ�к�����С��51.2�������ж�����ͬһҳ����ʽ�� spOffsety%51.2 + 1 < 51.2 ��ͬ��5����
			for ( i = 0; i < Width; i++)
			{
				if(j<=hBottom && j>=hTop && i>=hLeft && i<=hRight)
				{
					continue;
				}
				position1  = position + i; //����Ҫ��ʾ����Դ�λ��
				page_new = position1 >> 15; //������ʾҳ
				position1 &= 0x00007fffl;//������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���
				if (page_new != page_old) //����ҳ��
				{
					SVGA_SelectPlane(page_new);
					page_old = page_new;
				}
				VideoBuffer[position1] = buffer[i]; //д���Դ�λ��
			}
		}
		else
		{				
			page_new = position >> 15; //������ʾҳ
			position &= 0x00007fffl;//������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���
			if (page_new != page_old) //����ҳ��
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
				VideoBuffer[position+i] = buffer[i]; //д���Դ�λ��
			}			
		}		
    }
    /*�ر��ļ�*/
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

void IntToRGB(const int *ppixel, RGBPIXEL *prgbpix)//ת�����ظ�ʽ
{
	register unsigned int pixTemp;
	/*ת��*/
	pixTemp = *ppixel;
	
	prgbpix->BLUE = pixTemp & 0x001f;
	pixTemp >>= 5;
	prgbpix->GREEN = pixTemp & 0x003f;
	pixTemp >>= 6;
	prgbpix->RED = pixTemp & 0x001f;
}

void RGBToInt(const RGBPIXEL *prgbpix, int *ppixel)//ת�����ظ�ʽ
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
