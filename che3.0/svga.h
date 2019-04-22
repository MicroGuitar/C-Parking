#ifndef __SVGA_H__
    #define __SVGA_H__

#define _RED 0xf800
#define _GREEN 0x07e0
#define _BLUE 0x001f
#define _WHITE 0xffff
#define _BLACK 0x0000
#define _GREY  0x7bef
#define _SENSITIVE -128
#define MAX_WIDTH 640

typedef struct _vbeinfo//VBEӲ����Ϣ��512�ֽ�
{
    char  VbeSignature[4];         //VBEǩ��
    short VbeVersion;             //VBE�汾
    char  far * OemStringPtr;      //Oem��Ϣָ��
    char  Capabilities[4];         //Ӳ������
    char  far * VideoModePtr;      //ģʽ�б�ָ��
    short TotalMemory;            //�ڴ������
    short OemSoftwareRev;         //ִ�г���汾
    char  far * OemVendorNamePtr;  //����������
    char  far * OemProductNamePtr; //��Ʒ��
    char  far * OemProductRevPtr;  //��Ʒ�汾
    char  Reserved[222];           //����
    char  OemData[256];            //Oem����
}VBEInfo;

typedef struct _modeinfo//VBEģʽ��Ϣ��256�ֽ�
{
    short ModeAttr;           //ģʽ������
    char  WinAAttr;
    char  WinBAttr;            //����A,B������

    short WinGran;             //λ���С(��������),��KBΪ��λ
    short WinSize;             //���ڴ�С,��KBΪ��λ
    short WinASeg; 
    short WinBSeg;             //����A,B����ʼ��ַ
    char  far *BankFunc;       //��ҳ�������ָ��

    short charsPerScanLine;    //ÿ��ˮƽɨ������ռ���ֽ���
    short XRes, YRes;          //ˮƽ,��ֱ����ķֱ���
    char  XCharSize;
    char  YCharSize;           //�ַ��Ŀ�Ⱥ͸߶�
    char  NumberOfplanes;      //λƽ��ĸ���
    char  BitsPerPixel;        //ÿ���ص�λ��
    char  NumberOfBanks;       //CGA�߼�ɨ���߷�����
    char  MemoryModel;         //��ʾ�ڴ�ģʽ
    char  BankSize;            //CGAÿ��ɨ���ߵĴ�С
    char  NumberOfImagePages;  //��ͬʱ������������ͼ����
    char  reserve1;            //Ϊҳ�湦�ܱ���

//��ֱ��д��ɫģʽ�Ķ�������
    char  RedMaskSize;         //��ɫ��ռ��λ��
    char  RedFieldPosition;    //��ɫ�������Чλλ��
    char  GreenMaskSize;       //��ɫ��ռλ��
    char  GreenFieldPosition;  //��ɫ�������Чλλ��
    char  BlueMaskSize;        //��ɫ��ռλ��
    char  BlueFieldPosition;   //��ɫ�����Чλλ��
    char  RsvMaskSize;         //����ɫ��ռλ��
    char  RsvFieldPosition;    //����ɫ�������Чλλ��
    char  DirectColorModeInfo; //ֱ����ɫģʽ����

//����ΪVBE2.0�汾���϶���
    char  far *PhyBasePtr;     //��ʹ�õĴ��֡����ʱΪָ������ַ��32λ�����ַ
    long  OffScreenMenOffset;  //֡������ַ��32λƫ����
    short OffScreenMemSize;    //���õ�,��������ʾ������,��KBΪ��λ

//����ΪVBE3.0�����϶���
    short LincharsPerScanLine;   //���λ�������ÿ��ɨ���ߵĳ���,���ֽ�Ϊ��λ
    char  BnkNumberOfImagePages; //ʹ�ô��ڹ���ʱ����ʾҳ����
    char  LinNumberOfImagePages; //ʹ�ô�����Ի�����ʱ����ʾҳ����
    char  LinRedMaskSize;        //ʹ�ô�����Ի�����ʱ��ɫ��ռλ��
    char  LinRedFieldPosition;   //ʹ�ô�����Ի�����ʱ��ɫ�����Чλλ��
    char  LinGreenMaskSize;      //ʹ�ô�����Ի�����ʱ��ɫ��ռ��λ��
    char  LinGreenFieldPosition; //ʹ�ô�����Ի�����ʱ��ɫ�����Чλλ��
    char  LinBlueMaskSize;       //ʹ�ô�����Ի�����ʱ��ɫ��ռ��λ��
    char  LinBlueFieldPosition;  //ʹ�ô�����Ի�����ʱ��ɫ�����Чλλ��
    char  LinRsvMaskSize;        //ʹ�ô�����Ի�����ʱ����ɫ��ռλ��
    char  LinRsvFieldPosition;   //ʹ�ô�����Ի�����ʱ����ɫ�����Чλλ��
    char  reserve2[194];         //����
}ModeInfo;

typedef struct _rgbpixel//24λɫ���ص���Ϣ
{
	unsigned char BLUE;	
	unsigned char GREEN;
	unsigned char RED;
}RGBPIXEL;

/*****��ȡVBEģʽ��Ϣ*****/
// int 
// SVGA_ModeInfo(ModeInfo * info);

/*****��ȡVBEӲ����Ϣ*****/
// int 
// SVGA_VBEInfo(VBEInfo * info);

/*****������ʾģʽ����������ʹ��0x101����640*480*256ɫģʽ*****/
extern unsigned char 
SVGA_SetMode(const int vmode);

/*****��ȡ��ǰ��ʾģʽ�����򷵻ص�ǰ����ʾģʽ�жϺ�*****/
extern unsigned int 
SVGA_GetMode(void);

/*****�޸���ʾ����λ��*****/
// unsigned int 
// SVGA_SetDisplay(const int Frame);

/*****�޸Ĳ����Դ�λ��*****/
// unsigned int 
// SVGA_SetOperation(const int Frame);

/*****���������ù���λ��*****/
void 
SVGA_SelectPlane(register char page);


/*****��ָ��λ�û�ָ��bmp�ļ���ָ������,(left,top)(right,bottom)�ֱ�Ϊָ����ʾ���ֵ�����λ�ú�����λ��*****/
void 
SVGA_PartBmp(const int top, 
             const int bottom, 
             const int left, 
             const int right, 
             const int Offsetx, 
             const int Offsety, 
             const char *filename) ;

/*****��������ָ��32*32��С��bmp�ļ������ڴ���*****/
void SVGA_ImportBmp( const char *filename,int saveColor[1024]);

/*****����SVGA_Dot��(left,top)��(right,bottom)������*****/
void 
SVGA_Rectangular(const int  top,
                 const int  bottom,
                 const int  left,
                 const int  right,
                 const int  color);



/*****���ڴ�д�Դ�,��(x,y)����Χ32*32ͼ��*****/
void 
SVGA_ImgBlackMask(const int x, 
                  const int y, 
                  const int color[1024]);
				  
/*****���ڴ�д�Դ�,��(x,y)����Χ32*32ͼ��*****/
void 
SVGA_ImgWhiteMask(const int x, 
                  const int y, 
                  const int color[1024]);				  

/*****��(x,y)���16*16�������ַ���colorΪ��ɫ*****/
void 
SVGA_CHtext16(const int  x,
              const int  y,
              const char s[],
              const int  color);

/*****��(x,y)���8*16��ASC�ַ���colorΪ��ɫ*****/
void 
SVGA_ENtext16(const int  x,
              const int  y,
              const char s[],
              const int  color);

/*****��(x,y)���8*16��ASC�ַ���colorΪ��ɫ*****/
void 
SVGA_ENtextch16(const int  x,
              const int  y,
              const char s,
              const int  color);

/*****���������ʾ���洢32*32������ͼ�ε��ڴ�*****/
void 
SVGA_SaveArea(const int x, 
              const int y, 
              int str[1024]);

/*****���������ʾ��д32*32������ͼ�ε��Դ�*****/
void 
SVGA_RestoreArea(const int  x, 
                 const int  y, 
                 const int  str[1024]);

/*****��ȡĿ��bmp�ļ��ĳ�����Ϣ*****/
void 
SVGA_BMPInfo(const char * const filename,
             long * const Width,
             long * const Height);
/*****���϶���(Offsetx,Offsety)��MaskColor͸����BMP����������������ɫ����趨*****/
void 
SVGA_MaskBmp(const int  top, 
             const int  bottom,
             const int  left,
             const int  right,
             const int  Offsetx, 
             const int  Offsety, 
             const char *filename,
             const int  MaskColor);
/******************************����Ϊ14����ǰ����***********************************************************/
void SVGA_ImportSpeBmp( const int width, const int height, const char * const filename, int * const saveFile );	//��ָ����С��ͼƬ�����ڴ�		 
void SVGA_RestoreSpeArea( const int x, const int y, const int width, const int height, const int * const saveFile );//��ԭָ����С�ڴ�ͼ��			 
void SVGA_SaveSpeArea( const int x, const int y, const int width, const int height, int * const saveFile );//����ָ����Сͼ��
void SVGA_SpeImgWhiteMask( const int x, const int y, const int width, const int height,const int * const saveFile );//���ΰ�ɫ���ڴ�ͼ
void SVGA_AngFre( const int x, const int y, const float angle, const int * const saveFile );//����Ƕ����ڴ�ͼ
void SVGA_DoubleFre(const int x, const int y, const float angle, int width, int height, const int * const saveFile);//����Ƕ������С
int CheckAngFre(const int x, const int y, const float angle, const int * const saveFile);//���С����������
void Film(const char *path, int fraNum);//������Ƶ����
void ZoomPic(const int  x, const int  y, float scale, const char *filename);//����ͼƬ����
void HollowPic(int x, int y, int hTop, int hBottom, int hLeft, int hRight, const char *filename);//����ͼƬ��ͼ
void BrightPic(int x, int y, float brightness, const char *filename);//����ͼƬ����
int PixelMix(int pixel1, float scale1, int pixel2, float scale2);//���ػ��
void IntToRGB(const int *ppixel, RGBPIXEL *prgbpix);//���ظ�ʽת��
void RGBToInt(const RGBPIXEL *prgbpix, int *ppixel);//���ظ�ʽת��
#endif