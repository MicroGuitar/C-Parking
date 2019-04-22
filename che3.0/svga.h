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

typedef struct _vbeinfo//VBE硬件信息共512字节
{
    char  VbeSignature[4];         //VBE签名
    short VbeVersion;             //VBE版本
    char  far * OemStringPtr;      //Oem信息指针
    char  Capabilities[4];         //硬件性能
    char  far * VideoModePtr;      //模式列表指针
    short TotalMemory;            //内存块数量
    short OemSoftwareRev;         //执行程序版本
    char  far * OemVendorNamePtr;  //生产厂商名
    char  far * OemProductNamePtr; //产品名
    char  far * OemProductRevPtr;  //产品版本
    char  Reserved[222];           //保留
    char  OemData[256];            //Oem数据
}VBEInfo;

typedef struct _modeinfo//VBE模式信息共256字节
{
    short ModeAttr;           //模式的属性
    char  WinAAttr;
    char  WinBAttr;            //窗口A,B的属性

    short WinGran;             //位面大小(窗口粒度),以KB为单位
    short WinSize;             //窗口大小,以KB为单位
    short WinASeg; 
    short WinBSeg;             //窗口A,B的起始段址
    char  far *BankFunc;       //换页调用入口指针

    short charsPerScanLine;    //每条水平扫描线所占的字节数
    short XRes, YRes;          //水平,垂直方向的分辨率
    char  XCharSize;
    char  YCharSize;           //字符的宽度和高度
    char  NumberOfplanes;      //位平面的个数
    char  BitsPerPixel;        //每像素的位数
    char  NumberOfBanks;       //CGA逻辑扫描线分组数
    char  MemoryModel;         //显示内存模式
    char  BankSize;            //CGA每组扫描线的大小
    char  NumberOfImagePages;  //可同时载入的最大满屏图像数
    char  reserve1;            //为页面功能保留

//对直接写颜色模式的定义区域
    char  RedMaskSize;         //红色所占的位数
    char  RedFieldPosition;    //红色的最低有效位位置
    char  GreenMaskSize;       //绿色所占位数
    char  GreenFieldPosition;  //绿色的最低有效位位置
    char  BlueMaskSize;        //蓝色所占位数
    char  BlueFieldPosition;   //蓝色最低有效位位置
    char  RsvMaskSize;         //保留色所占位数
    char  RsvFieldPosition;    //保留色的最低有效位位置
    char  DirectColorModeInfo; //直接颜色模式属性

//以下为VBE2.0版本以上定义
    char  far *PhyBasePtr;     //可使用的大的帧缓存时为指向其首址的32位物理地址
    long  OffScreenMenOffset;  //帧缓存首址的32位偏移量
    short OffScreenMemSize;    //可用的,连续的显示缓冲区,以KB为单位

//以下为VBE3.0版以上定义
    short LincharsPerScanLine;   //线形缓冲区中每条扫描线的长度,以字节为单位
    char  BnkNumberOfImagePages; //使用窗口功能时的显示页面数
    char  LinNumberOfImagePages; //使用大的线性缓冲区时的显示页面数
    char  LinRedMaskSize;        //使用大的线性缓冲区时红色所占位数
    char  LinRedFieldPosition;   //使用大的线性缓冲区时红色最低有效位位置
    char  LinGreenMaskSize;      //使用大的线性缓冲区时绿色所占的位数
    char  LinGreenFieldPosition; //使用大的线性缓冲区时绿色最低有效位位置
    char  LinBlueMaskSize;       //使用大的线性缓冲区时蓝色所占的位数
    char  LinBlueFieldPosition;  //使用大的线性缓冲区时蓝色最低有效位位置
    char  LinRsvMaskSize;        //使用大的线性缓冲区时保留色所占位数
    char  LinRsvFieldPosition;   //使用大的线性缓冲区时保留色最低有效位位置
    char  reserve2[194];         //保留
}ModeInfo;

typedef struct _rgbpixel//24位色像素点信息
{
	unsigned char BLUE;	
	unsigned char GREEN;
	unsigned char RED;
}RGBPIXEL;

/*****获取VBE模式信息*****/
// int 
// SVGA_ModeInfo(ModeInfo * info);

/*****获取VBE硬件信息*****/
// int 
// SVGA_VBEInfo(VBEInfo * info);

/*****设置显示模式，本程序中使用0x101设置640*480*256色模式*****/
extern unsigned char 
SVGA_SetMode(const int vmode);

/*****获取当前显示模式，程序返回当前的显示模式中断号*****/
extern unsigned int 
SVGA_GetMode(void);

/*****修改显示缓存位置*****/
// unsigned int 
// SVGA_SetDisplay(const int Frame);

/*****修改操作显存位置*****/
// unsigned int 
// SVGA_SetOperation(const int Frame);

/*****本函数设置工作位面*****/
void 
SVGA_SelectPlane(register char page);


/*****在指定位置画指定bmp文件的指定部分,(left,top)(right,bottom)分别为指定显示部分的左上位置和右下位置*****/
void 
SVGA_PartBmp(const int top, 
             const int bottom, 
             const int left, 
             const int right, 
             const int Offsetx, 
             const int Offsety, 
             const char *filename) ;

/*****本函数将指定32*32大小的bmp文件读到内存中*****/
void SVGA_ImportBmp( const char *filename,int saveColor[1024]);

/*****调用SVGA_Dot从(left,top)到(right,bottom)画矩形*****/
void 
SVGA_Rectangular(const int  top,
                 const int  bottom,
                 const int  left,
                 const int  right,
                 const int  color);



/*****由内存写显存,在(x,y)画范围32*32图形*****/
void 
SVGA_ImgBlackMask(const int x, 
                  const int y, 
                  const int color[1024]);
				  
/*****由内存写显存,在(x,y)画范围32*32图形*****/
void 
SVGA_ImgWhiteMask(const int x, 
                  const int y, 
                  const int color[1024]);				  

/*****在(x,y)输出16*16的中文字符，color为颜色*****/
void 
SVGA_CHtext16(const int  x,
              const int  y,
              const char s[],
              const int  color);

/*****在(x,y)输出8*16的ASC字符，color为颜色*****/
void 
SVGA_ENtext16(const int  x,
              const int  y,
              const char s[],
              const int  color);

/*****在(x,y)输出8*16的ASC字符，color为颜色*****/
void 
SVGA_ENtextch16(const int  x,
              const int  y,
              const char s,
              const int  color);

/*****用于鼠标显示，存储32*32的区域图形到内存*****/
void 
SVGA_SaveArea(const int x, 
              const int y, 
              int str[1024]);

/*****用于鼠标显示，写32*32的区域图形到显存*****/
void 
SVGA_RestoreArea(const int  x, 
                 const int  y, 
                 const int  str[1024]);

/*****获取目标bmp文件的长宽信息*****/
void 
SVGA_BMPInfo(const char * const filename,
             long * const Width,
             long * const Height);
/*****左上对齐(Offsetx,Offsety)切MaskColor透明画BMP，本函数不包含调色板的设定*****/
void 
SVGA_MaskBmp(const int  top, 
             const int  bottom,
             const int  left,
             const int  right,
             const int  Offsetx, 
             const int  Offsety, 
             const char *filename,
             const int  MaskColor);
/******************************以上为14级以前代码***********************************************************/
void SVGA_ImportSpeBmp( const int width, const int height, const char * const filename, int * const saveFile );	//将指定大小的图片载入内存		 
void SVGA_RestoreSpeArea( const int x, const int y, const int width, const int height, const int * const saveFile );//复原指定大小内存图像			 
void SVGA_SaveSpeArea( const int x, const int y, const int width, const int height, int * const saveFile );//保存指定大小图像
void SVGA_SpeImgWhiteMask( const int x, const int y, const int width, const int height,const int * const saveFile );//屏蔽白色贴内存图
void SVGA_AngFre( const int x, const int y, const float angle, const int * const saveFile );//任意角度贴内存图
void SVGA_DoubleFre(const int x, const int y, const float angle, int width, int height, const int * const saveFile);//任意角度任意大小
int CheckAngFre(const int x, const int y, const float angle, const int * const saveFile);//检查小车敏感像素
void Film(const char *path, int fraNum);//播放视频函数
void ZoomPic(const int  x, const int  y, float scale, const char *filename);//缩放图片函数
void HollowPic(int x, int y, int hTop, int hBottom, int hLeft, int hRight, const char *filename);//空心图片贴图
void BrightPic(int x, int y, float brightness, const char *filename);//调节图片亮度
int PixelMix(int pixel1, float scale1, int pixel2, float scale2);//像素混合
void IntToRGB(const int *ppixel, RGBPIXEL *prgbpix);//像素格式转换
void RGBToInt(const RGBPIXEL *prgbpix, int *ppixel);//像素格式转换
#endif