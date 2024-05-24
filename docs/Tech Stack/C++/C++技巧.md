# C++ 使用技巧

[TOC]

## 将函数作为参数传入

[参考博客](https://blog.csdn.net/zj1131190425/article/details/88528948)

声明和实现：

```cpp
pid timer(int (*func)(int, int, int[N][N]), int n, int m, int mat[N][N], int k);

pid timer(int (*func)(int, int, int[N][N]), int n, int m, int mat[N][N], int k){
    for (int i = 0; i < k; ++ i)
        ret = func(n, m, mat);
}
```

调用：

```cpp
ret_N3 = timer(brute_force_N6, n, m, mat, k3);
```

## 二进制文件读写：fopen, fread & fwrite + Malloc

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

```c
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

## C++ 比 C 新增的特性

### struct 内嵌函数

> 参考资料：[struct 内嵌函数](https://blog.csdn.net/qq_43566054/article/details/104211794)

*这是 C 和 C++ 一个不同的点。* 需要注意

### struct 定义的语法(typedef struct)

在 C 中，如果不 typedef 则每次声明新的 struct 实例都要使用 `struct STRUCT_NAME` 语法。

```cpp
// C flavor
typedef struct _MY_STRUCT{} MY_STRUCT;
// cpp flavor
struct MY_STRUCT{}
```

用 typedef 重命名一个指针。下面的例子中 pNode 定义的就是一个指向结构体的指针

```c
typedef struct tagNode 
{
　char *pItem;
　struct tagNode *pNext;
} *pNode;
```


### 函数引用传参 &

C 里只能传指针，但 C++ 可以直接引用

例如：传入一个指针的引用

```cpp
int test(int* &p);
```

### 强转类型报错

C 中只会给警告，但是 C++ 必须要手动转类型。

```cpp
bmp.fileHeader = (BITMAPFILEHEADER*)bmp.buffer; // C++ 中不转类型会报错
char* p = (char*)"abc"; // C++ 中不转类型会 warning
```

## 动态分配内存

### malloc 报错

问题：

1. `corrupted size vs. prev_size`
2. `malloc(): corrupted top size`

原因：

两个报错的原因一样，都是内存溢出，使用了未分配并不存在的内存。

## class 操作

### 重载运算符

语法格式：

```cpp
<返回类型说明符> operator <运算符符号>(<参数表>)
{
    <函数体>
}
```

举例说明：

```cpp
// 定义为成员函数
Box operator+(const Box&);
// 定义为非成员函数 
Box operator+(const Box&, const Box&);
```

备注：

1. 在 operator 前加上 & 表示引用返回值，比如重载下标运算符 `Box & operator [] (...)` 之后就可以使用 `box[i] = 1` 进行赋值操作
2. 重载运算符分为类内重载和类外重载（用友元函数的方法实现）
3. [重载运算符中的 const 分析](https://blog.csdn.net/weixin_43734095/article/details/104465307)：`const Point operator+(const Point &point) const;`
    - 第一个 const: 表示返回值是常量，不加这个 const `(p1 + p2) = Point(40, 50);` 不会报错，不符合语义
    - 第二个 const: 扩大接受参数的范围，表示可以接收常数参数，不加这个 const 则 *变量+常量* 会报错
    - 第三个 const: 使得该函数可以被 const 对象所调用，不加这个 const 则 *常量+变量* 会报错
4. [重载运算符中的 & 分析]():``
    - to be continued

应用举例：

```cpp

```

> 参考： [重载 [] + 两种不同返回值重载同一个运算符](http://c.biancheng.net/view/2312.html)

### 构造函数

使用初始化列表来初始化字段:

```cpp
MyClass::MyClass( double a, double b, double c): X(a), Y(b), Z(c)
{
  // ...
}
```

---

复制构造函数：

```cpp
BMP::BMP(const BMP & bmp){
    // allocate memory to contain the whole file:
    this->buffer = (unsigned char*) malloc (sizeof(unsigned char) * bmp.fileHeader.bfSize);
    if (this->buffer == NULL) {fputs ("Memory error",stderr); exit (2);}
    // copy data and initialize
    memcpy(this->buffer, bmp.buffer, bmp.fileHeader.bfSize);
    this->initBmp();
}
```

注意：若没有显示定义复制构造函数，则系统会默认创建一个复制构造函数，当类中有指针成员时，由系统默认创建的复制构造函数会存在“浅拷贝”的风险，因此必须显示定义复制构造函数。

---

使用 **可选参数** ：注意只在函数声明处写默认值，在定义函数时不要再加

```cpp
class Box{
public:
    Box(int h=2,int w=2,int l=2);//在声明构造函数时指定默认参数
private:
    int height,width,length;
};
Box::Box(int h,int w,int len){//在定义函数时可以不指定默认参数
    height=h;
    width=w;
    length=len;
}
```

---

区分构造函数和结构体赋值语句：

```c
BMP bmp(100, 100);
BMP bmp2 = bmp;
BMP bmp3; bmp3 = bmp;
```

对于 bmp2 调用了复制构造函数，对于 bmp3 则做了结构体的赋值操作。后者可能造成的深浅拷贝问题和默认复制构造函数所产生的相同,可以用重载运算符来解决。

```c
BMP bmp = BMP(100, 100, 0, 0, 255);
printf("%p\n", &bmp);
printf("%p\n", bmp.buffer);
bmp = BMP(100, 100, 0, 0, 255);
printf("%p\n", &bmp);
printf("%p\n", bmp.buffer);
```

再举一例，假设这里没有重载等于号。第一次调用构造函数来初始化，生成一个 BMP 实例，名为 bmp。第二次调用构造函数生成了一个新的 BMP 实例，并把其值赋给 bmp 变量，此时存在两个 BMP 类实例。

所以两次输出 bmp 的地址不变，但是 buffer 指向的地址变了。实际上存在两片 buffer，但是有一个 buffer 已经没有实际的指针变量指向他了。所以有一片 buffer 的地址不会被析构函数释放，导致内存泄露。

解决办法是重载等于号，把等于号的赋值改成深拷贝，即 realloc bmp 中分配的地址，把指针指向的内容复制一份给 bmp。

---



### 析构函数

析构函数（destructor）会在每次删除所创建的对象时执行。在程序正常结束时默认会使所有对象消亡。

将动态分配的内存全部存在 class 内，能够有效避免内存泄露。

举例：

```cpp
class String{
private:
    char* p;
public:
    String(int n);
    ~String();
};

String::~String(){
    delete[] p;
}

String::String(int n){
    p = new char[n];
}
```

### template

note: template 不支持声明和定义在不同的文件里