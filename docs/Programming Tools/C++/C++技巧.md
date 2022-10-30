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

> 参考：[重载构造函数教程](http://c.biancheng.net/view/2221.html)

举例：

```cpp

```

使用可选参数：注意只在函数声明处写默认值，在定义函数时不要再加

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