# 图像信息处理

[TOC]

## Chapter 1 基础知识

### 图像格式

- PNG 常用于网络
- BMP：可以压缩（rle），但是一般都不压缩
    - color image: RGB 各一个 Byte，最常见的 BMP 就是 24 位真彩色图
    - greyScale: 8 位 256 个灰度（业界规定， **所有设备的灰度只有 256 级** ）
    - **dpi** = dot per inch （打印的参数）（200 dpi 显示效果足够优秀）
        - 视网膜屏幕：dpi 接近视网膜上的细胞数
- JPEG:
    1. 压缩策略：
        - Different manipulations for *high-frequency signal* and *low-frequency signal*.
        - According to the requirement of compression ratio, remove information from high frequency to low frequency. 
    2. 大幅面高质量打印：国外进口 -> 有研究空间
    3. 缺点：文字等细节容易看出问题的，适合用矢量图
- TIFF: 用于 CAD、GIS(geographic information system)，分为 public 和 private （压缩方式或者加密方式），便于公司进行开发
- GIF(graphics interchange format): 使用LZW encoding method

### 有关颜色、成像的生物和物理知识

成像：
- 小孔成像：孔太大，图像模糊；孔太小（光圈(Sperture)太小），进光量不够，产生衍射，且相机抖动对成像效果的影响更大
- 透镜（胶卷相机）：
    - circle of confusion: 未聚焦在像屏上
    - depth of a field（景深）：相机能够清晰拍摄的距离范围
        - 小光圈 -> 大景深 -> 风景照（需要清晰显示远近的信息）
        - 大光圈 -> 小景深 -> 背景虚化
        - 原理：进光少，circle of confusion 小，眼睛无法分辨则不认为是模糊
- **数码相机** ：
    - DSP：处理数字信号，降噪（ *国内核心技术落后* ）
    - 处理过程：![](img/DC%20image%20process.PNG)

颜色的物理意义：
- 鸡尾酒会问题（图像、声音 etc） [科普](https://zhuanlan.zhihu.com/p/58505511)
- **color vision** : the feeling of human brain when lights of different wavelengths reach retina.
    - 棒状细胞(rod)：数量大，只感光
    - 锥状细胞(cone)：数量少，在光照充足的情况下能感受颜色，有三种，分别对红、绿、蓝光最敏感 -> **三原色理论的生理基础**
    - 色觉因人而异 + **人从对比度感知色彩** （如何让所有人看到相同的颜色 *目前仍未解决* ）
    - 如何产生不同颜色的光：产生不同波长的光波 or 色光按比例混合 [色彩空间基础（这篇还是非常全面的）](https://blog.csdn.net/u010468553/article/details/79614229)

- 紫边现象：胶片相机的边上因为透镜产生色散而导致的模糊
- priority vs sensitivity
    - priority 先 notice 到什么变化 : hue（色调）> saturation（饱和度）> lightness（亮度）
    - sensitivity 能感知多小的变化：亮度最敏感 -> HDR
    - *在视觉传达领域非常重要*


### 颜色空间 (color space)
- device dependent model:
    - RGB: additive，色光混合
    - CMY: subtractive，吸收部分色光，反射剩下的色光，多用于打印设备（CMYK 增加黑色）
    - HSV(HIS):
        1. hue（色调）
        1. saturation（饱和度）
        1. value / intensity（光强），和 YUV 里的 Y 是一样的
- device independent model:
    - CIE XYZ
    - CIE Lab
    - CIE YUV
- Transformation between color spaces
    - RGB<->CMY: ![](img/%E5%B9%BB%E7%81%AF%E7%89%8773.PNG)
    - RGB<->HSV: ![](img/%E5%B9%BB%E7%81%AF%E7%89%8774.PNG) ![](img/%E5%B9%BB%E7%81%AF%E7%89%8775.PNG) ![](img/%E5%B9%BB%E7%81%AF%E7%89%8776.PNG)
    - RGB<->CIE XYZ: 查表 transformation tables ![](img/%E5%B9%BB%E7%81%AF%E7%89%8777.PNG)
    - CIE XYZ<->CIE L*a*b* ![](img/%E5%B9%BB%E7%81%AF%E7%89%8778.PNG)
    - RGB<->CIE YUV ![](img/%E5%B9%BB%E7%81%AF%E7%89%8779.PNG)


## 存储图像的数据结构 & 图像处理方法

1. 矩阵：例如 multispectral image 多光谱图像
2. 链表：例如 RLE(Run Length Encoding)
    - 行 + (列开头 + 列结尾) + ...

---

1. windows API DIB
    - 逻辑屏幕 vs 物理屏幕
2. VC++: 可以借鉴群文件里的库，自己进行扩充
3. matlab: Image Processing Toolbox
4. PhotoShop
5. GIMP: 开源版本的 PhotoShop
6. 光影魔术手：支持批处理

（操作举例：直方图均衡化）

## Chapter 1 BMP

### BMP 文件结构

> 参考资料：[BMP 文件结构、读取和存储](https://zhuanlan.zhihu.com/p/122959774)

1. 位图文件头 BitMapFileHeader
2. 位图信息头 BitMapInfoHeader
3. 调色板 Palette
4. 实际位图数据 ImageData

#### 位图文件头

重要信息：
- `bfOffBits`: 找到 bitmap 的开头

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

upd. 补充了一个构造函数，修改成 C++ 语法

#### 位图信息头

重要信息：
- `biWidth`: 单位是 **像素**
- `biHeight`: 单位是 **像素**，`biHeight > 0` 表示图像是翻转的（在 bitmap 中依次存储的像素是 **左下到右上** ），`biHeight > 0` 则图像是正的
- `biClrUsed`: 决定了调色板的文件大小， `biClrUsed == 0` 表示调色板上所有的颜色都使用，即 bitmap 中直接存储 RGB

不重要信息：

- `biCompression`: 因为一般的 BMP 都不压缩，所以可以默认这个变量为 0

运算关系：
- `bfSize = bfOffBits + biSizeImage`
- 行字节数 `byteWidth = (biWidth * biBitCount / 8 + 3) / 4 * 4`，**byteWidth 必须是 4 的倍数** ，不够的字节用 `00` 补齐
- `biSizeImage = biHeight * byteWidth`
    - 常见错误：`biSizeImage != biHeight * biWidth * biBitCount`

```c
struct BITMAPINFOHEADER
{
    unsigned int    biSize;          // 此结构体的大小，为40 (14-17字节)
    long            biWidth;         // 图像的宽,单位是像素  (18-21字节)
    long            biHeight;        // 图像的高，单位是像素  (22-25字节)
    unsigned short  biPlanes;        // 表示bmp图片的平面属，显然显示器只有一个平面，所以恒等于1 (26-27字节)
    unsigned short  biBitCount;      // 一像素所占的位数，常用的值为1（黑白二色图）,4（16色图）,8（256色）,24（真彩色图）（新的.bmp格式支持32位色）   (28-29字节)
    unsigned int    biCompression;   // 指定位图是否压缩，有效的值为BI_RGB，BI_RLE8，BI_RLE4，BI_BITFIELDS（都是一些Windows定义好的常量）。我们今后所讨论的只有第一种不压缩的情况，即biCompression为BI_RGB的情况。 (30-33字节)
    unsigned int    biSizeImage;     // 像素数据所占大小 (34-37字节)
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

upd. 补充了一个构造函数，修改成 C++ 语法

#### 调色板

注意事项：
- 顺序是 **BGR** 而不是 RGB
- `biClrUsed` 决定了调色板的大小，例如灰度图可以有一个大小为 256 的调色板

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

对于用到调色板的位图，图象数据就是该像素颜在调色板中的索引值。对于真彩色图，图象数据就是实际的R,G,B值。

要注意两点：
1. 每一行的字节数必须是 **4的整倍数**，如果不是，则需要用 0 补齐。
2. 一般来说（biHeight > 0 时），.BMP文件的数据从下到上，从左到右的。也就是说，从文件中最先读到的是图象最下面一行的左边第一个像素，然后是左边第二个像素…接下来是倒数第二行左边第一个像素，左边第二个像素…依次类推，最后得到的是最上面一行的最右一个像素。

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

### HW1 中遇到的问题

1. 参数：指针的引用
2. bfType：[低端字节序和高端字节序](https://www.cnblogs.com/Philip-Tell-Truth/articles/5173941.html#:~:text=%E5%B0%8F%E7%AB%AF%E5%AD%97%E8%8A%82%E5%BA%8F%E6%8C%87%E4%BD%8E%E5%AD%97%E8%8A%82%E6%95%B0%E6%8D%AE%E5%AD%98%E6%94%BE%E5%9C%A8%E5%86%85%E5%AD%98%E4%BD%8E%E5%9C%B0%E5%9D%80%E5%A4%84%EF%BC%8C%E9%AB%98%E5%AD%97%E8%8A%82%E6%95%B0%E6%8D%AE%E5%AD%98%E6%94%BE%E5%9C%A8%E5%86%85%E5%AD%98%E9%AB%98%E5%9C%B0%E5%9D%80%E5%A4%84%EF%BC%9B%E5%A4%A7%E7%AB%AF%E5%AD%97%E8%8A%82%E5%BA%8F%E6%98%AF%E9%AB%98%E5%AD%97%E8%8A%82%E6%95%B0%E6%8D%AE%E5%AD%98%E6%94%BE%E5%9C%A8%E4%BD%8E%E5%9C%B0%E5%9D%80%E5%A4%84%EF%BC%8C%E4%BD%8E%E5%AD%97%E8%8A%82%E6%95%B0%E6%8D%AE%E5%AD%98%E6%94%BE%E5%9C%A8%E9%AB%98%E5%9C%B0%E5%9D%80%E5%A4%84%E3%80%82,%E5%9F%BA%E4%BA%8EX86%E5%B9%B3%E5%8F%B0%E7%9A%84PC%E6%9C%BA%E6%98%AF%E5%B0%8F%E7%AB%AF%E5%AD%97%E8%8A%82%E5%BA%8F%E7%9A%84%EF%BC%8C%E8%80%8C%E6%9C%89%E7%9A%84%E5%B5%8C%E5%85%A5%E5%BC%8F%E5%B9%B3%E5%8F%B0%E5%88%99%E6%98%AF%E5%A4%A7%E7%AB%AF%E5%AD%97%E8%8A%82%E5%BA%8F%E7%9A%84%E3%80%82)
3. struct BITMAPFILEHEADER 的大小是 16 而不是 14
4. sizeof(指针) 返回的是指针的大小而不是数组的大小
5. 指针类型转换的语法
7. C++ 结构体内声明函数好像不能做，或许转向使用 class 封装会更好一点
8. 重载 BMP 类的运算符或许会更好一点,[struct 的构造函数](https://zhuanlan.zhihu.com/p/392077524)
9. RGB (0, 0, 0) 是黑，(255, 255, 255) 是白
10. `(i/3) / (int)bmp.infoHeader.biWidth` 注意类型转换，不然当成 unsigned int 计算，unsigned int 强转 double 会出问题，首位会被当成符号位，char 直接参与计算会被当成带符号整数,
11. 各种数据类型的内存大小，[struct 的内存分配](https://blog.csdn.net/weixin_41453492/article/details/101318522)



## 二值图像和形态学操作(Binary Image and Morphological Operation)

### 结构定义

优点：只留下需要的信息，且在某些需要打印的场景更为低廉

### Binarization

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


### HW2 中遇到的问题

1. padding
2. 大津法分块过于小会导致失去全局性质，过大可能导致有部分特点被光线等外部调价掩盖
    - 解决方案：local 局部大津法，对每一个点单独求一个

#### 用 photoshop 获取 24 位 BMP 图像素材

1. 图像 -> 模式 -> 选择格式和位数
2. 文件 -> 存储为 -> 在窗口中选择格式和位深度

## Chapter 3 灰度图像操作

### visibility & enhancement

1. greyScale perception: 256 级已经超过了人眼可以分辨的
1. Weber's Law:
    - 肉眼可见的灰度值差 visible threshold $\frac{\Delta I}{I}\approx 1...2\%$ 
    - 定理的定义范围有限，在亮度过大或者过小时不成立
    - 显示设备想要至少呈现出 256 级灰度，要求 $$\frac{I_{max}}{I_{min}}=(1+K_{weber})^{255}\approx13...156$$ 对比度 $\frac{I_{max}}{I_{min}}$ 值越大说明显示器效果越好
1. $\gamma$ 校正：
    - 最初用于想 CRT 显示器，后用于图像后期处理，$\gamma$ 越大 对比度越高
    - 曝光值 E
    - 现实世界：HDR(high dynamic range) 亮度范围 10^8 远超可以显示的亮度值 -> Dynamic range compression
1. 色调映射 (tone mapping) -> visibility enhancement（解决过曝和曝光不足）
1. 可视增强 - $\log$ 操作： $L_d = \frac{\log(L_w+1)}{\log(L_{max}+1)}$
    - $L_w$ 是实际亮度， $L_d$ 是显示亮度，$L_d$ 分布在 $[0,1]$ 上
    - 缺陷：对比度降低

### histogram 直方图 & histogram equalization 直方图均衡化

1. 直方图：
    - 灰度图直方图：直方图是一种统计图，表示每一个灰度级中像素数占总像素数的比例
    - 彩色图直方图：三通道各有一个直方图
        - 用例：以图搜图（仅根据颜色分布）
        - 用例：照片拼照片
    - 缺陷：忽略了结构信息（斑马皮肤和国际象棋棋盘）
    - 应用：图像压缩、增强、分割
1. 直方图均衡化：
    - 效果：增加对比度，使图像更清晰，颜色更鲜艳。比如说对于过曝和曝光不足的照片，灰度动态范围较小，灰度值集中，照片会看起来灰蒙蒙的，适合用直方图均衡化处理。
    - 连续：
        - 原始图像直方图 $r-P(r)$，满足 $\int_0^1 P(r)=1$
        - 求一个映射 $s = T(r)$ 使得 $\forall s, P(s) = 1$
        - $\int_{0}^{r}P(r)dr = \int_{0}^{s}P(s)ds = \int_{0}^{s}1\cdot ds=s$
        - 公式：$s=\int_{0}^{r}P(r)dr$
    - 离散：
        - $s_k = \sum_{i=0}^k P(r_k)$，原来灰度值为 $r_k$ 的像素点被重新分配灰度值 $s_k$
        - 递推：$s_k = s_{k-1} + P(r_k)$
        - 近似：将 $s_k$ 近似为数值最相近的灰度级 $r_l$
    - 缺陷：在连续条件下能做到完全均衡，但在离散条件下无法做到
    - 局部直方图均衡化
1. 附加操作：
    1. 直方图匹配：
        - 连续：做两次直方图均衡化 $s_k = T_1(r_{1k}) = T_2(r_{2k})$，则 $r_{2k} = T2^{-1}\cdot T1(r_{1k})$
        - 离散：根据两张对应表建立新的对应表
    1. histogram transformation：手动更改 $s=T(r)$ 函数调节亮度或对比度

