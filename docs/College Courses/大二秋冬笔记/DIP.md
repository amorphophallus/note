# 图像信息处理

[TOC]

## BMP

### BMP 文件结构

1. 位图文件头 BitMapFileHeader
2. 位图信息头 BitMapInfoHeader
3. 调色板 Palette
4. 实际位图数据 ImageData

#### 位图文件头

```c
typedef struct tagBITMAPFILEHEADER
{
    unsigned short bfType;        // 指定文件类型，必须是0x424D，即字符串"BM"，也就是说所有.bmp文件的头两个字节都是"BM" (0-1字节)
    unsigned int   bfSize;        // 文件大小,包括这14个字节,以字节为单位(2-5字节)
    unsigned short bfReserved1;   // 保留，必须设置为0 (6-7字节)
    unsigned short bfReserved2;   // 保留，必须设置为0 (8-9字节)
    unsigned int   bfOffBits;     // 从文件头到像素数据的偏移(10-13字节)
} BITMAPFILEHEADER; // 共 14 字节
// WORD == unsigned short == 16bit
// DWORD == unsigned int == 32bit
```

#### 位图信息头

```c
typedef struct tagBITMAPINFOHEADER
{
    unsigned int    biSize;          // 此结构体的大小，为40 (14-17字节)
    long            biWidth;         // 图像的宽,单位是像素  (18-21字节)
    long            biHeight;        // 图像的高，单位是像素  (22-25字节)
    unsigned short  biPlanes;        // 表示bmp图片的平面属，显然显示器只有一个平面，所以恒等于1 (26-27字节)
    unsigned short  biBitCount;      // 一像素所占的位数，常用的值为1（黑白二色图）,4（16色图）,8（256色）,24（真彩色图）（新的.bmp格式支持32位色）   (28-29字节)
    unsigned int    biCompression;   // 指定位图是否压缩，有效的值为BI_RGB，BI_RLE8，BI_RLE4，BI_BITFIELDS（都是一些Windows定义好的常量）。我们今后所讨论的只有第一种不压缩的情况，即biCompression为BI_RGB的情况。 (30-33字节)
    unsigned int    biSizeImage;     // 像素数据所占大小, 这个值应该等于上面文件头结构中bfSize-bfOffBits (34-37字节)
    long            biXPelsPerMeter; // 说明水平分辨率，用象素/米表示。一般为0 (38-41字节)
    long            biYPelsPerMeter; // 说明垂直分辨率，用象素/米表示。一般为0 (42-45字节)
    unsigned int    biClrUsed;       // 说明位图实际使用的彩色表中的颜色索引数（设为0的话，则说明使用所有调色板项）。 (46-49字节)
    unsigned int    biClrImportant;  // 说明对图象显示有重要影响的颜色索引的数目，如果是0，表示都重要。(50-53字节)
} BITMAPINFOHEADER;
// BI_RGB == 0
// 要注意的是：上述公式中的biWidth'必须是4的整倍数（所以不是biWidth，而是biWidth'，表示大于或等于biWidth的，离4最近的整倍数。举个例子，如果biWidth=240，则biWidth'=240；如果biWidth=241，biWidth'=244）如果biCompression为BI_RGB，则该项可能为零
```

#### 调色板



#### 实际位图数据

### 读取和写入 BMP