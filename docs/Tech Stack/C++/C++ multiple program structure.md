# C++ 多文件组织结构

[TOC]

## 基本结构

一个较多较复杂的源程序可以划分为多个部分，通常分为一个头文件和两个源代码文件。

头文件中通常包含：

1. 各种 **声明** ：函数原型声明、类声明、内联函数声明、结构体声明、模板声明等。也可以用 `extern` 声明一些需要在外部使用的变量。
2. 用 `const` 或者 `#define` 定义的符号常量。

第一个源代码文件包含与类、结构体、模板相关的函数 **实现** 代码。**不需要 include 头文件。**

第二个源代码文件包含 **调用** 与类、结构体、模板相关的函数代码，用于测试运行程序。**需要 include 头文件。**

[一个可供参考的例子](https://blog.csdn.net/Mark7758/article/details/109501965)

## 注意事项

### 防止重复引用头文件

[参考博客](https://blog.csdn.net/Lyncai/article/details/114698722)

使用 `ifndef` 等命令，保证头文件最多只会被包含一次

```cpp
// function.h
#ifndef FUNCTION_H
#define FUNCTION_H

/*Content of function.h*/

#endif
```

### 共享变量 extern

使用 extern 声明：**一次声明，一次定义，多次使用**

extern 声明变量，但不分配地址，而是会到参与编译的所有文件中寻找已定义的同名变量。

```cpp
// a.h
extern int a[];
// A.cpp
int a[N];
// B.cpp
a[0] = 0;
```

[参考博客](https://blog.csdn.net/qq_27942333/article/details/84719737)