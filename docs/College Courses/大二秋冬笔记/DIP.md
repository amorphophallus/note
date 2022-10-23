# 图像信息处理

[TOC]


## BMP

### BMP 文件结构

> 参考资料：[BMP 文件结构、读取和存储](https://zhuanlan.zhihu.com/p/122959774)

1. 位图文件头 BitMapFileHeader
2. 位图信息头 BitMapInfoHeader
3. 调色板 Palette
4. 实际位图数据 ImageData

#### 位图文件头

upd. 补充了一个构造函数，修改成 C++ 语法

```c
struct BITMAPFILEHEADER
{
    unsigned short bfType;        // 指定文件类型，必须是0x424D，即字符串"BM"，也就是说所有.bmp文件的头两个字节都是"BM" (0-1字节)
    unsigned int   bfSize;        // 文件大小,包括这14个字节,以字节为单位(2-5字节)
    unsigned short bfReserved1;   // 保留，必须设置为0 (6-7字节)
    unsigned short bfReserved2;   // 保留，必须设置为0 (8-9字节)
    unsigned int   bfOffBits;     // 从文件头到像素数据的偏移(10-13字节)
    BITMAPFILEHEADER(){}
    BITMAPFILEHEADER(char * buffer){ // 构造函数，传入 BMP 文件的首地址
        this->bfType = *(unsigned short*)(buffer);
        this->bfSize = *(unsigned int*)(buffer+2);
        this->bfReserved1 = *(unsigned short*)(buffer+6);
        this->bfReserved2 = *(unsigned short*)(buffer+8);
        this->bfOffBits = *(unsigned int*)(buffer+10);
    }
}; // 共 14 字节
// WORD == unsigned short == 16bit
// DWORD == unsigned int == 32bit
```

#### 位图信息头

upd. 补充了一个构造函数，修改成 C++ 语法

```c
struct BITMAPINFOHEADER
{
    unsigned int    biSize;          // 此结构体的大小，为40 (14-17字节)
    long            biWidth;         // 图像的宽,单位是像素  (18-21字节)
    long            biHeight;        // 图像的高，单位是像素  (22-25字节)
    unsigned short  biPlanes;        // 表示bmp图片的平面属，显然显示器只有一个平面，所以恒等于1 (26-27字节)
    unsigned short  biBitCount;      // 一像素所占的位数，常用的值为1（黑白二色图）,4（16色图）,8（256色）,24（真彩色图）（新的.bmp格式支持32位色）   (28-29字节)
    unsigned int    biCompression;   // 指定位图是否压缩，有效的值为BI_RGB，BI_RLE8，BI_RLE4，BI_BITFIELDS（都是一些Windows定义好的常量）。我们今后所讨论的只有第一种不压缩的情况，即biCompression为BI_RGB的情况。 (30-33字节)
    unsigned int    biSizeImage;     // 像素数据所占大小, biSizeImage=biWidth'*biHeight (34-37字节)
    long            biXPelsPerMeter; // 说明水平分辨率，单位是象素/米。一般为0 (38-41字节)
    long            biYPelsPerMeter; // 说明垂直分辨率，单位是象素/米。一般为0 (42-45字节)
    unsigned int    biClrUsed;       // 指定本图象实际用到的颜色数，如果该值为零，则用到的颜色数为2的biBitCount次方，即使用所有调色板项。 (46-49字节)
    unsigned int    biClrImportant;  // 说明对图象显示有重要影响的颜色索引的数目，如果是0，表示都重要。(50-53字节)
    BITMAPINFOHEADER(){}
    BITMAPINFOHEADER(char * buffer){ // 构造函数，传入 BMP 文件的首地址
        this->biSize = *(unsigned int*)(buffer+14);
        this->biWidth = *(long*)(buffer+18);
        this->biHeight = *(long*)(buffer+22);
        this->biPlanes = *(unsigned short*)(buffer+26);
        this->biBitCount = *(unsigned short*)(buffer+28);
        this->biCompression = *(unsigned int*)(buffer+30);
        this->biSizeImage = *(unsigned int*)(buffer+34);
        this->biXPelsPerMeter = *(long*)(buffer+38);
        this->biYPelsPerMeter = *(long*)(buffer+42);
        this->biClrUsed = *(unsigned int*)(buffer+46);
        this->biClrImportant = *(unsigned int*)(buffer+50);
    }
};
// BI_RGB == 0
// 要注意的是：上述公式中的biWidth'必须是4的整倍数（所以不是biWidth，而是biWidth'，表示大于或等于biWidth的，离4最近的整倍数。举个例子，如果biWidth=240，则biWidth'=240；如果biWidth=241，biWidth'=244）如果biCompression为BI_RGB，则该项可能为零
```

#### 调色板

```c
typedef struct _PIXELINFO {
    unsigned char rgbBlue;   //该颜色的蓝色分量  (值范围为0-255)
    unsigned char rgbGreen;  //该颜色的绿色分量  (值范围为0-255)
    unsigned char rgbRed;    //该颜色的红色分量  (值范围为0-255)
    unsigned char rgbReserved;// 保留，必须为0
} PIXELINFO;
// 调色板实际上是一个数组，共有 biClrUsed 个元素,数组中每个元素的类型是一个RGBQUAD结构，占4个字节
// 有些位图，如真彩色图，是不需要调色板的
```

#### 实际位图数据

对于用到调色板的位图，图象数据就是该像素颜在调色板中的索引值，对于真彩色图，图象数据就是实际的R,G,B值。

要注意两点：
1. 每一行的字节数必须是4的整倍数，如果不是，则需要补齐。这在前面介绍biSizeImage时已经提到了。
2. 一般来说，.BMP文件的数据从下到上，从左到右的。也就是说，从文件中最先读到的是图象最下面一行的左边第一个像素，然后是左边第二个像素…接下来是倒数第二行左边第一个像素，左边第二个像素…依次类推，最后得到的是最上面一行的最右一个像素。

#### BMP 类

```c
struct BMP{
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    PIXELINFO * pixelInfo;
    char * imageData;
    char * buffer; // 动态分配空间存储二进制的 BMP 文件，一个 char 存一个 Byte
};
```


### 读取和存储 BMP

#### 二进制文件读写：fopen, fread & fwrite + Malloc

> 参考资料：
> 1. [fopen](https://cplusplus.com/reference/cstdio/fopen/)
> 2. [fread](https://cplusplus.com/reference/cstdio/fread/)
> 3. [fwrite](https://cplusplus.com/reference/cstdio/fwrite/)
> 4. [C dynamic memory allocation](https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/)

1. fopen
    - 常用格式：r, w, a, r+, w+, a+
    - 如果要编辑 **二进制文件**，必须要加上 **b** ，例如 rb
2. fread
    - 语法：`size_t fread ( void * ptr, size_t size, size_t count, FILE * stream );`
3. fwrite
    - 语法：`size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );`

可复用的二进制文件读写模板：

```cpp
#include<stdio.h>
#include<stdlib.h>

int readBitFile(char * & buffer, char * fileName);
int writeBitFile(char * buffer, int bufferSize, char * fileName);
int freeBitFile(char * buffer);

// 读入二进制文件
int readBitFile(char * & buffer, char * fileName){
    // open file & check
    FILE * file;
    int bufferSize;
    file = fopen(fileName, "rb");
    if (file == NULL){fputs("File Error!", stderr); exit(1);}

    // obtain file size
    fseek (file , 0 , SEEK_END); // 找到结尾
    bufferSize = ftell (file);
    rewind (file); // 回到文件开头

    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*bufferSize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copy the file into the buffer:
    size_t result = fread (buffer, 1, bufferSize, file);
    if (result != bufferSize) {fputs ("Reading error",stderr); exit (3);}

    // terminate
    fclose (file);
    return 0;
}

// 写入二进制文件
int writeBitFile(char * buffer, int bufferSize, char * fileName){
  FILE * file;
  file = fopen (fileName, "wb");
  size_t result = fwrite (buffer , sizeof(char), bufferSize, file);
  if (result != bufferSize) {fputs ("Writing error",stderr); exit(1);}
  fclose (file);
  return 0;
}

// 释放二进制文件内存
int freeBitFile(char * buffer){
    free (buffer);
    return 0;
}
```

#### BMP 文件读写

> 参考资料：
> 1. [memcpy](https://cplusplus.com/reference/cstring/memcpy/)

1. memcpy
    - 语法：`void * memcpy ( void * destination, const void * source, size_t num );`
    - num 的单位是 Byte

可复用的 BMP 文件信息获取模板：

```cpp
#include<stdio.h>
#include<stdlib.h>

int getBmpFile(BMP & bmp);

int getBmpFile(BMP & bmp){
    // get bitmap info
    bmp.fileHeader = BITMAPFILEHEADER(bmp.buffer);
    bmp.infoHeader = BITMAPINFOHEADER(bmp.buffer);
    if ((bmp.infoHeader).biClrUsed == 0) bmp.pixelInfo = NULL;
    else bmp.pixelInfo = (PIXELINFO*)(bmp.buffer + sizeof(bmp.fileHeader) + sizeof(bmp.infoHeader));
    bmp.imageData = bmp.buffer + (bmp.fileHeader).bfOffBits;

    // check validity
    char BM[2] = {'B', 'M'};
    if (bmp.fileHeader.bfType != *(unsigned short*)(BM)){fputs ("Format not BMP",stderr); exit(1);}
    return 0;
}
```

### 24 位 RGB 位图转换为 YUV

1. 遍历所有像素
2. 公式计算 Y，U, V (double or int)
3. 截断函数 clip Y
4. 新建 BMP 实例
5. 写入 BMP 实例

附加步骤：

1. 调整亮度 Y 并重新计算得到一个 RGB 图

## 问题

1. 参数：指针的引用
2. bfType：[低端字节序和高端字节序](https://www.cnblogs.com/Philip-Tell-Truth/articles/5173941.html#:~:text=%E5%B0%8F%E7%AB%AF%E5%AD%97%E8%8A%82%E5%BA%8F%E6%8C%87%E4%BD%8E%E5%AD%97%E8%8A%82%E6%95%B0%E6%8D%AE%E5%AD%98%E6%94%BE%E5%9C%A8%E5%86%85%E5%AD%98%E4%BD%8E%E5%9C%B0%E5%9D%80%E5%A4%84%EF%BC%8C%E9%AB%98%E5%AD%97%E8%8A%82%E6%95%B0%E6%8D%AE%E5%AD%98%E6%94%BE%E5%9C%A8%E5%86%85%E5%AD%98%E9%AB%98%E5%9C%B0%E5%9D%80%E5%A4%84%EF%BC%9B%E5%A4%A7%E7%AB%AF%E5%AD%97%E8%8A%82%E5%BA%8F%E6%98%AF%E9%AB%98%E5%AD%97%E8%8A%82%E6%95%B0%E6%8D%AE%E5%AD%98%E6%94%BE%E5%9C%A8%E4%BD%8E%E5%9C%B0%E5%9D%80%E5%A4%84%EF%BC%8C%E4%BD%8E%E5%AD%97%E8%8A%82%E6%95%B0%E6%8D%AE%E5%AD%98%E6%94%BE%E5%9C%A8%E9%AB%98%E5%9C%B0%E5%9D%80%E5%A4%84%E3%80%82,%E5%9F%BA%E4%BA%8EX86%E5%B9%B3%E5%8F%B0%E7%9A%84PC%E6%9C%BA%E6%98%AF%E5%B0%8F%E7%AB%AF%E5%AD%97%E8%8A%82%E5%BA%8F%E7%9A%84%EF%BC%8C%E8%80%8C%E6%9C%89%E7%9A%84%E5%B5%8C%E5%85%A5%E5%BC%8F%E5%B9%B3%E5%8F%B0%E5%88%99%E6%98%AF%E5%A4%A7%E7%AB%AF%E5%AD%97%E8%8A%82%E5%BA%8F%E7%9A%84%E3%80%82)
3. struct BITMAPFILEHEADER 的大小是 16 而不是 14
4. sizeof(指针) 返回的是指针的大小而不是数组的大小
5. 指针类型转换的语法
6. 文件大小 bfSize 错误的情况：
    - bfSize 可以从文件属性中获取，可以 bfSize = bfOffset + ImageSize，可以直接用 ultraedit 修改文件大小
    - 也可以通过 biSizeImage=biWidth'*biHeight 计算
7. C++ 结构体内声明函数好像不能做，或许转向使用 class 封装会更好一点
8. 重载 BMP 类的运算符或许会更好一点,[struct 的构造函数](https://zhuanlan.zhihu.com/p/392077524)
9. RGB (0, 0, 0) 是黑，(255, 255, 255) 是白
10. `(i/3) / (int)bmp.infoHeader.biWidth` 注意类型转换，不然当成 unsigned int 计算，unsigned int 强转 double 会出问题，首位会被当成符号位，char 直接参与计算会被当成带符号整数,
11. 各种数据类型的内存大小，[struct 的内存分配](https://blog.csdn.net/weixin_41453492/article/details/101318522)






## JPEG（10.4 网课）

主要思路：用小块 patch 拼凑整个图像，可以设置粒度

大幅面高质量打印：国外进口 -> 有研究空间

缺点：文字等细节容易看出问题的，适合用矢量图

补充：TIFF，用于 CAD、GIS(geographic information system)，分为 public 和 private （压缩方式或者加密方式），便于公司进行开发

补充：GIF(graphics interchange format)，LZW encoding method


## 存储图像的数据结构

1. 矩阵：例如 multispectral image 多光谱图像
2. 链表：例如 RLE(Run Length Encoding)
    - 行 + (列开头 + 列结尾) + ...


## 图像处理方法

1. windows API DIB
    - 逻辑屏幕 vs 物理屏幕
2. VC++: 可以借鉴群文件里的库，自己进行扩充
3. matlab: Image Processing Toolbox
4. PhotoShop
5. GIMP: 开源版本的 PhotoShop
6. 光影魔术手：支持批处理

（操作举例：直方图均衡化）

## 二值图像和形态学操作(Binary Image and Morphological Operation)

优点：只留下需要的信息，且在某些需要打印的场景更为低廉

获取：设置阈值 threshold
- 好的阈值：minimize 前景（背景）内部的方差 = maximize 两部分之间的差异
- 大津算法：枚举所有的 threshold，计算并求最小值
- 优化：全局大津法导致局部阴影无法识别 -> 扫描窗口，在每个 local window 中做大津法
- 再优化：去噪声？形状简化？形态学操作

应用：
1. 绿幕
2. 检测水淹的区域
3. 人脸识别（基于颜色，容易受外部光照的影响）

### dilation（膨胀）

A: binary image
B: structure element （结构元的选取非常灵活）

符号：圆圈里一个加号

实现： 若 A 和 B 有交，则把 B 的坐标原点放到图像中。

效果：
1. 补洞
2. 扩展

### erosion （腐蚀）

符号：圆圈里一个减号

实现：B 完全包含于 A 的前景中，则把 B 的坐标原点放到图像中。（考试中可以列表来判断是否包含）

padding：
1. 0 padding
2. 复制第一行第一列做 padding

效果：
1. 去小噪点
2. 去边界

### erosion & dilation

结合：erosion + dilation -> 去噪点 + 恢复边界大小

对偶性(duality)：
1. $(A-B)^c=A^c+B$
2. $(A+B)^c=A^c-B$

应用：
1. 提取边界 ($A-(A-B)$减去腐蚀后的部分)
2. 补洞
3. structure extraction

### opening

开操作 = 先腐蚀，再膨胀

符号：空心圆圈

效果：去掉小块，棱角平滑，并且保持整体面积大致不变

### closing

闭操作 = 先膨胀，再腐蚀

符号：小黑点

效果：补小洞和断开的边界，并且保持整体面积大致不变

---

应用：指纹识别 -> 先做开操作，再做闭操作


## 灰度图像操作