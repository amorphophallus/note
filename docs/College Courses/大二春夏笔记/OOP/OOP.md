# 面向对象程序设计

[TOC]

> todo: 学一学这篇博客的封装：[ADS B+ 树](https://blog.csdn.net/ZJU_fish1996/article/details/50890467)

## 笔记

### intro

1. 参考
    - 作业答案：[HW1-HW8](https://zhoutimemachine.github.io/2022/07/07/2022/oop-mid-review/) [HW9-HW13](https://zhoutimemachine.github.io/2022/07/07/2022/oop-final-review/)
    - 贺老师翻译的 C++ 相关文章：[知乎](https://www.zhihu.com/column/c_1561843704159232000)。贺老师的图书分享：[阿里云盘](https://www.aliyundrive.com/s/z5hLRAELpPP), 提取码: 5jm9。
    - [The Cherno C++](https://www.youtube.com/playlist?list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb) 超纲知识学习
    - [C++ 新闻](https://isocpp.org/) [cpp_reference](https://en.cppreference.com/w/)
    - MUD(multi-user dungeon) 游戏示例：NetHack，guidebook 很重要，[nethack 官网](https://nethack.org/), [nethack-wiki](https://nethackwiki.com/), [nethack 服务器](https://alt.org/nethack/), [快速上手文档](https://lug.ustc.edu.cn/planet/2021/09/nethack-gitgud/)，[所有按键列表](https://tieba.baidu.com/p/1438247556)
    - 助教-陆子仪：ziyilu@zju.edu.cn
    - 陈翔：xchencs@zju.edu.cn
2. 成绩
    - 期末考 50%
    - Lab 50%：单周项目，双周小题

### 变量

#### 引用 &

- 一般来说定义引用变量一定要赋初值
- 不需要赋初值的情景：函数参数，类中的引用变量。由函数的调用者，类的构造函数提供初值
- 引用只能赋初值，不能修改

![OOP](./imgs/2023-03-30-15-04-19.png)

- `int * &`: 引用一个指针
- `int & *`: 指向引用变量的指针

![OOP](./imgs/2023-03-30-15-01-09.png)

- `const int &`：不修改实参本身，也不复制，可以节约栈空间和省去复制变量的时间

```cpp
struct BigStruct{
    int a[10000];
};

void f(const BigStruct &);
```

#### 常量 const

![OOP](./imgs/2023-03-30-15-49-45.png)

![OOP](./imgs/2023-03-30-15-51-17.png)

举个例子，char 指针：

- 第一句和第二句是等价的，等号右边是一个 `const char *`，等号表示将 s1 和 s2 指向 data 区中的字符串常量头指针。如果要这么写，第二句意义更明确，比第一句更不容易犯错。
- 第三句和第四句是等价的，第三句的等号表示 char 数组的初始化（假设是局部变量），是在栈中分配数组的空间，然后把 data 区中的字符串常量 copy 到栈中。

```cpp
char * s1 = "Hello World!";
const char * s2 = "Hello World!";
char s3[] = "Hello World!";
char s4[]("Hello World!");

s1[0] = 'C'; // Error
s3[0] = 'C'; // OK
```

### 函数

#### 函数重载(overload)

条件：

- 返回值，函数名，作用域一样（三者有任意一个不一样都算是不同函数，不算重载）
- 参数不一样（参数一样，仅函数体不一样不允许，会报重复定义的错误）

```cpp
template<typename T>
void print_array(T arr[], int n){
    for (int i = 0; i < n; ++ i)
        std::cout << arr[i] << ' ';
    std::cout << endl;
}

template<typename T>
void print_array(T* arr[], int n){
    for (int i = 0; i < n; ++ i)
        std::cout << *arr[i] << ' ';
    std::cout << endl;
}
```

#### template

```cpp
template<typename T, typename Compare>
void selection_sort(T arr[], int n, Compare comp)
{
  for (int i = 0; i < n - 1; ++i)
  {
    int min_idx = min_element(arr, i, n, comp);
    if (min_idx != i)
      swap(arr[min_idx], arr[i]);
  }
}
```

- 存在 `std::Compare` 类型，比如优先队列中可以使用的 `less`, `priority_queue<int,vector<int>,less<int> > big_heap;`

### 类 Class

#### 重载运算符

第一种写法：在类外部重载

- 可以把 operator 看成一个函数，具有参数、函数体、返回值。但是参数和返回值的设置必须满足运算符原来的运算规则。
- 参考资料：[C++ 可重载运算符实例](https://www.runoob.com/cplusplus/cpp-overloading.html)，在网页的最底下。

```cpp
class Student{
public:
    int id;
    std::string name;
};

bool operator < (const Student& x, const Student& y){
    return x.id < y.id;
}

std::ostream& operator << (std::ostream& out, const Student& x){
    return out << '(' << x.id << ", " << x.name << ')';
}
```

第二种写法：在类内重载

- 类内重载是类的一个成员函数
- 成员函数可以在类内声明，在类外实现
- 输出流的类内重载：所谓“类内”，是 ostream 类内。因为 ostream 类在生命时用到了 template，在重载其运算符时需要和类使用一样的 template `template<typename _CharT, typename _Traits>`*（目前还不会重载）*

```cpp
class Student{
public:
    int id;
    std::string name;
    bool operator < (const Student& y){
        return this->id < y.id;
    }
    bool operator > (const Student&);
};

bool Student::operator > (const Student& y){
    return this->id > y.id;
}
```

#### 构造函数

- 可以重载多个构造函数

```cpp
class Rectangle{
private:
    int h, w;
public:
    double area;
    Rectangle():h(0), w(0){}
    Rectangle(int _h,int _w):h(_h),w(_w){}
    void get_area(){area = h * w;}
};

Rectangle r = Rectangle(2, 3);
Rectangle s;
```

- 编译器保证构造函数一定会被执行，可以保证对象一定被初始化

在 VC 中使用 debug 编译器，栈空间没有被初始化的变量会被填充 `0xCD`，国标码显示“烫”(`0xCCCC`)；堆中没有被初始化的变量会被填充 `0xCD`，国标码显示“烫”(`0xCDCD`)。

- default constructor：没有参数的 constructor

如果没有任何自定义的构造函数，编译器会自动加上 default constructor；但如果有自定义构造函数，那要用 default constructor 就必须自己写了。

#### 析构函数

析构函数（destructor）会在每次删除所创建的对象时执行。在程序正常结束时默认会使所有对象消亡。

将动态分配的内存全部存在 class 内，能够有效避免内存泄漏。

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

#### class 访问控制(private, protected, public)

类内成员变量 & 函数类型：

- private: 仅 class 内可以访问
- protected: class 内、子 class 可以访问，外界无法访问
- public: 全局都可以访问

一般数据为 private，访问函数为 public，防止随意修改破坏数据间的一些完整性约束。建立 class 的过程相当于一个建模的过程，将实例的属性和交互抽象成概念。

struct 就是一个默认所有成员为 public 的 class。是 C++ 为了兼容 C 的产物。

#### 类的继承

继承类型：

- 公有继承（public）：当一个类派生自公有基类时，基类的公有成员也是派生类的公有成员，基类的保护成员也是派生类的保护成员，基类的私有成员不能直接被派生类访问，但是可以通过调用基类的公有和保护成员来访问。
- 保护继承（protected）： 当一个类派生自保护基类时，基类的公有和保护成员将成为派生类的保护成员。
- 私有继承（private）：当一个类派生自私有基类时，基类的公有和保护成员将成为派生类的私有成员。

派生类不继承的情况：

- 基类的构造函数、析构函数和拷贝构造函数
- 基类的重载运算符
- 基类的友元函数

拓展阅读：

- [子类初始化列表不能初始化父类元素的原因 -> 初始化列表和构造函数的关系](https://blog.csdn.net/uestcyms/article/details/103509443)

```cpp
class Shape{
protected:
    int h, w;
public:
    double area;
    Shape():h(0), w(0){}
    Shape(int _h, int _w):h(_h), w(_w){}
};

class Rectangle: public Shape{
public:
    Rectangle():Shape(){}
    Rectangle(int _h,int _w):Shape(_h, _w){}
    void get_area(){area = h * w;}
};

class Triangle: public Shape{
public:
    Triangle():Shape(){}
    Triangle(int _h,int _w):Shape(_h, _w){}
    void get_area(){area = 0.5 * h * w;}
};
```

#### new & delete

##### new & delete 基本变量类型

- `[]` 是创建数组，`(), {}` 是初始化

```cpp
	int * a = new int[100];
	int * b = new int(1024);
	int * c = new int[100]{1, 2, 3, 4, 5};
	delete[] a;
	delete b;
	delete[] c;
```

- delete 为什么要分为 `delete` 和 `delete[]`？

free 的功能是释放一次 malloc 分配的所有地址，所以不管是分配单个变量 `malloc(sizeof(int))` 还是分配多个变量 `malloc(sizeof(int) * 100)` 都可以用一次 free 全部释放掉。

但是 delete 新增了功能，可以对动态分配的数组，单独析构和释放一个位置的内存。

##### new & delete 自定义变量类型

功能：

- new 的功能：分配内存，调用构造函数构造类的实体，返回对象的指针。
- delete 的功能：调用析构函数，释放内存。

e.g. new 不同的子类不能把内容存在同一个数组里，但可以把指针存在同一个数组里

- 错误写法：`Shape arr[] = {new Rectangle(1, 2), new Triangle(2, 4, 5)};`
    - 直接把子类赋值给基类，子类独有的变量消失
- 正确写法：`Shape * arr[] = {new Rectangle(1, 2), new Triangle(2, 4, 5)};`

new 和 malloc 的区别：

1. new is an operator, while malloc is a function.
2. new calls an appropriate constructor for object allocation, while malloc doesn't.
3. new returns a pointer with the appropriate type, while malloc only returns a void * pointer that needs to be typecasted to the appropriate type.

new 和 delete 数组的顺序问题：

- new 先分配空间，再按下标从小到大调用构造函数
- delete[] 先按下标从大到小调用析构函数，再释放空间

#### 多态 & 虚函数 & dynamic_cast

- 在编译时，编译器不**静态链接**到基类的函数，而是在程序中任意点可以根据所调用的对象类型来选择调用的函数，这称为**动态链接**
- 在虚函数不需要任何有意义的实现时，可以使用**纯虚函数**
- 使用 `Rectangle * rect = dynamic_cast<Rectangle*>(shape);` 来把指向派生类的基类指针转化为派生类指针

tips:

- 包含纯虚函数的类不能实例化为对象

```cpp
class Shape{
protected:
    int h, w;
public:
    double area;
    Shape():h(0), w(0){}
    Shape(int _h, int _w):h(_h), w(_w){}
    virtual void get_area() = 0;
};

class Rectangle: public Shape{
public:
    Rectangle():Shape(){}
    Rectangle(int _h,int _w):Shape(_h, _w){}
    void get_area(){area = h * w;}
};

class Triangle: public Shape{
public:
    Triangle():Shape(){}
    Triangle(int _h,int _w):Shape(_h, _w){}
    void get_area(){area = 0.5 * h * w;}
};

// main
Shape * arr[] = {new Rectangle(1, 2), new Triangle(2, 3)};
arr[0]->get_area();
arr[1]->get_area();
std::cout << arr[0]->area << " " << arr[1]->area << std::endl;	
```

#### friend 成员函数

- 类的**友元函数**定义在类外部，但有权访问类的所有私有（private）成员和保护（protected）成员。
- 类的**友元类**可以访问类的所有私有（private）成员和保护（protected）成员。

tips：

- friend 可以定义在类内任意位置，权限设置对 friend 无效

```cpp
class Student{
private:
    int id;
    std::string name;
public:
    Student(int x, std::string y):id(x), name(y){}
    friend bool operator < (const Student&, const Student&);
    friend std::ostream& operator << (std::ostream&, const Student&);
};

bool operator < (const Student& x, const Student& y){
    return x.id < y.id;
}

std::ostream& operator << (std::ostream& out, const Student& x){
    return out << '(' << x.id << ", " << x.name << ')';
}
```


#### static 实现对象间数据共享

- [在 class 中定义 static 成员变量](https://www.cnblogs.com/stevenshen123/p/11555758.html)
- [C++ 类成员函数中的静态变量的作用域](https://blog.csdn.net/su_787910081/article/details/42213245)

#### class 的多文件实现（声明和定义分离）(.h & .cpp)

- 类外实现成员函数，需要用 `::` 声明函数是成员函数
- `::` 单独使用用于跳出类，使用全局变量

![OOP](./imgs/2023-04-01-13-22-17.png)

- `.h` 文件中只能写声明，不能写定义和实现 

![OOP](./imgs/2023-04-01-13-23-47.png)

- 多文件实现的好处：主程序和类实现是两个不同的编译单元，以 `.h` 为沟通的接口。只修改主程序或者只修改类实现，另一部分不需要重新编译生成 object，只需要重新链接即可。
- [C 语言为什么只需要 include<stdio.h> 就能使用里面声明的函数? - 醉卧沙场的回答 - 知乎](https://www.zhihu.com/question/389126944/answer/1169709964)

#### #pragma once 防止重定义

```cpp
#pragma once
```

保证这个头文件只被编译一遍。相当于 C 中的

```c
#ifndef __INVERTED_INDEX__
#define __INVERTED_INDEX__

...

#endif
```

### 命名空间 namespace

#### 定义

```cpp
namespace my_space{

}
```


#### 使用

- 使用 `typedef` 或 `using`, `auto` 缩短变量类型的长度

```cpp
// 使用函数
using my_space::my_function;
// 使用整个 namespace
using namespace my_space;
```

### STL 标准模板库

#### 容器 Container

- sequantial
    - array & vector & deque: 不可变长，单端可变长，双端可变长
    - forward-list, list: 单向指针，双向指针链表
- associative
    - 底层用红黑树实现
    - set, multiset
    - map, multimap
- unordered associative:
    - 底层用哈希表实现
    - unordered_set, unordered_multiset, unordered_map, unordered_multimap
- adaptors
    - stack, queue, priority_queue

##### vector

- `[]` 运算符不会进行边界检测，一定会返回值。

```cpp
// 初始化和插入
vector<int> evens {2, 4, 6, 8};
evens.push_back(12);
evens.insert(evens.begin() + 4, 5, 10);

// 遍历 vector
for (vector<int>::iterator it = evens.begin(); it < evens.end(); it++) cout << *it << ", ";
for (auto it = evens.begin(); it < evens.end(); it++) cout << *it << ", ";
for (int e: evens) cout << e << ", ";
```

##### list

- `size()` 是线性的，`empty()` 才是 O(1)
- `erase(it)` 会使 it 失效，但会返回下一个迭代器，理想的使用方法是 `it = l.erase(it);`


##### map

- key 的数据类型必须能够比大小和判断相等。即自定义类型做 key 需要**重载小于号和等于号**。
- `[]` 运算符不会判断 key 是否存在，若不存在会插入并把 value 设置成默认值。
- set 和 map 中的元素默认是不可变的（因为修改元素会改变红黑树结构）。但是可以在变量前加 **`mutable`**，表示即使是在 const object 内这个 member 也是可以修改的，并保证 mutable 的成员不参与大小和相等的比较，即不会影响 object 在红黑树中的位置。

```cpp
// 定义和插入
map<string, int> price;
price["apple"] = 5;
cout << price["apple"] << endl;

// 遍历
for (pair<string, int> pair: price) cout << '{' << pair.first << ", " << pair.second << '}' << endl;
for (auto pair: price)              cout << '{' << pair.first << ", " << pair.second << '}' << endl;
for (auto [fruit, f_price]: price) cout << '{' << fruit << ", " << f_price << '}' << endl;
```

#### 算法 Algorithm

[参考阅读: STL world map](https://www.fluentcpp.com/getthemap/)

- 所有的范围都是左闭右开 `[begin, end)`

#### 迭代器 iterator

把各种不同的指针统一起来，使用统一的算法处理。

- random-access: 可以比大小
- contiguous-access：不能比大小

```cpp
// vector 的 back_inserter 迭代器，可以在尾部未定义的区域插入
vector<int> evens {1, 2, 3, 4};
copy(evens.begin(), evens.end(), back_inserter(evens));
// list 的 front_inserter 迭代器，在头部插入
list<int> l {1, 2, 3, 4};
copy(l.begin(), ,.end(), front_inserter(l)); // {4, 3, 2, 1, 1, 2, 3, 4}
// ostream_iterator
copy(evens.begin(), evens.end(), ostream_iterator<int>(cout, ", "));
```

自定义 iterator ==还不会==

```cpp

```

tips:

- [获取 iterator 指向的元素的地址](https://blog.csdn.net/cwdben/article/details/116034666)

### 其他

#### Memory Model

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-17%20220859.png)


### 工具

#### Dev-C++ 调试

[参考博客](https://www.jianshu.com/p/1602264dadf2)

#### CMake 跨平台构建工具

- it is not a build system itself; it generates another system's build files.

[CMake 教程](https://zhuanlan.zhihu.com/p/500002865)


## Homework Record

### HW1 Students I

#### 准备工作

前置知识：

1. `cout` 如何对齐
2. 如何使用 `ifstream, ofstream` 读写文件
3. 使用 `string` 进行字符串处理

项目需求：

1. 从文件中输入 10 个记录，向标准输出流中输出表格。
2. 使用 class 封装

参考资料：

1. [前人的代码](https://blog.csdn.net/u013046245/article/details/20035471)

#### cout 格式设置

[参考博客：C++的cout高阶格式化操作](https://www.cnblogs.com/devymex/archive/2010/09/06/1818754.html#:~:text=cout.setf%20%28ios%3A%3Aright%20%7C%20ios%3A%3Ahex%29%3B,%2F%2F%E8%AE%BE%E7%BD%AE16%E8%BF%9B%E5%88%B6%E5%8F%B3%E5%AF%B9%E9%BD%90%20cout.setf%20%28ios%3A%3Aright%2C%20ios%3A%3Aadjustfield%29%3B%20%2F%2F%E5%8F%96%E6%B6%88%E5%85%B6%E5%AE%83%E5%AF%B9%E9%BD%90%EF%BC%8C%E8%AE%BE%E7%BD%AE%E4%B8%BA%E5%8F%B3%E5%AF%B9%E9%BD%90)

1. `setf` : 在当前的格式状态上追加指定的格式
    - 参数：
        1. 第一个：追加设置的格式
        2. 第二个（可选）：删除的格式
    - 可选格式：
        1. 单独格式（可用 `|` 并列）：
            - 进制相关
                - `ios::dec`  以10进制表示整数
                - `ios::hex`  以16进制表示整数
                - `ios::oct`  以8进制表示整数
                - `ios::showbase`  为整数添加一个表示其进制的前缀，不显示前缀使用 `ios::noshowbase`
            - 缩进相关
                - `ios::internal`  在符号位和数值的中间插入需要数量的填充字符以使串两端对齐
                - `ios::left`  在串的末尾插入填充字符以使串居左对齐
                - `ios::right`  在串的前面插入填充字符以使串居右对齐
            - 浮点数表示相关
                - `ios::fixed`  将符点数按照普通定点格式处理（非科学计数法）
                - `ios::scientific`  将符点数按照科学计数法处理（带指数域）
                - `ios::showpoint`  在浮点数表示的小数中强制插入小数点（默认情况是浮点数表示的整数不显示小数点）
            - 其他
                - `ios::boolalpha`  将bool类型的值以true或flase表示，而不是1或0
                - `ios::showpos`  强制在正数前添加+号
                - `ios::skipws`  忽略前导的空格（主要用于输入流，如cin）
                - `ios::unitbuf`  在插入（每次输出）操作后清空缓存
                - `ios::uppercase`  强制大写字母
        2. 组合格式：
            - `ios::adjustfield`  对齐格式的组合位
            - `ios::basefield`  进制的组合位
            - `ios::floatfield`  浮点表示方式的组合位
    - e.g. 
        ```cpp
        cout.setf(ios::right | ios::hex); //设置16进制右对齐
        cout.setf(ios::right, ios::adjustfield); //取消其它对齐，设置为右对齐
        ```
2. `unsetf`: 在当前的格式状态上删除指定的格式
3. `flags`: 将当前格式状态全部替换为指定的格式
4. `setw`: 设置对齐宽度，但是仅对下一个输出内容有效
    - e.g. `cout.flags(ios::right); cout << setw(10) << -456.98 << "The End" << endl;`
5. `setfill`: 设置填充字符，对本语句及后续语句均有效
    - e.g. `cout << setfill('0') << setw(10) << 45698 << endl;`
6. `left/internal/right`: 设置对齐位置，对本语句及后续语句均有效
    - e.g. `cout << left << setw(10) << -456.98 << "The End" << endl; //左对齐`
7. `std::hex`（16进制）、`std::dec`（10进制）、`std::oct`（8进制）、`std::showbase`（显示进制前缀）、`std::noshowbase`（不显示进制前缀），对本语句及后续语句均有效
    - e.g. `cout << showbase << hex << setw(4) << 12 << setw(12) << -12 << endl;`
8. `setprecision`: 设置小数精度，对本语句及后续语句均有效

#### cout 格式设置函数的头文件和命名空间

1. 头文件
    1. `<iostream>`: 
    2. `<iomanip>`: 
2. 命名空间
    1. `std::` - 
    2. `std::ios::` - 

#### getline

- 参数
    1. 输入流（比如cin）
    2. 指定一个string对象
    3. 结束字符（默认 `\n`，getline不会读入默认或指定的结束字符，但在调用之后读取的位置已经跳过结束字符）
- e.g.
    - 2 个参数 ` getline(cin, str1);`
    - 3 个参数 ` getline(cin, str1, ' ');`

#### cout 缓冲区 & cout 和 printf 混用问题

1. 输出机制：
    - cout 将输出参数倒序调用并存放在栈里，一旦遇到 endl 或者 flush 或者程序结束，就清空缓冲区输出
        - e.g. `std::cout << i << " " << i++ << " " << i--;` 输出 `0 -1 0`
    - printf 输出参数的调用是一个 *undefined behavior*，不同编译器可能导致参数调用顺序不同。且 printf 没有缓冲区，语句执行完后直接输出。
        - e.g.
            ```cpp
            std::ios::sync_with_stdio(false);
            std::cout << "cout!";
            printf("printf!");
            ```
            输出的结果是 `printf!cout!`
2. `std::ios::sync_with_stdio();` 输入参数 true（默认也是 true）可解决 cout 和 printf 混用导致的输出顺序问题。
3. `std::unitbuf` 单缓冲区间即每次都直接输出`std::nounitbuf` 恢复到原来的缓冲方式

#### ifstream & ofstream & fstream 成员函数

[参考博客：C++文件读写详解（ofstream,ifstream,fstream）](https://blog.csdn.net/kingstar158/article/details/6859379)

![Alt text](./imgs/iostream_lib.gif)

1. 打开 & 关闭文件
    - `open`
        1. 第一个参数：文件名
        2. 第二个参数（可选，ifstream 默认位 in，ofstream 默认为 out，fstream 默认两个都有，可用 `|` 连接表示多选）：打开方式
            - `ios::in`	为输入(读)而打开文件
            - `ios::out`	为输出(写)而打开文件
            - `ios::ate`	初始位置：文件尾
            - `ios::app`	所有输出附加在文件末尾
            - `ios::trunc`	如果文件已存在则先删除该文件
            - `ios::binary`	二进制方式
        3. 第三个参数（可选）：文件类型
            - 0	普通文件，打开操作
            - 1	只读文件
            - 2	隐含文件
            - 4	系统文件
        - 可以用构造函数的语法打开文件 `fstream foi("foo.txt", ios::in|ios::out);`
        - e.g.
            ```cpp
            ofstream out;
            out.open("Hello.txt", ios::in|ios::out|ios::binary)                 //根据自己需要进行适当的选取
            ```
    - `close`: 即使忘记调用 close，析构函数也会自动调用关闭函数 close
2. 使用重载运算符 `<<` `>>` 读写，和用 cin 一样就行
    - ifstream 仅重载了 `>>`，ofstream 仅重载了 `<<`
3. 使用成员函数读写
    - getline 有两个同名函数，一个是 istream 的成员函数，一个是 iostream 中的函数
        - `fin.getline(str,LINE_LENGTH)` 参数为 std::string 和行的最长长度，成功读入返回值 1，超出长度返回 0
        - `getline(fin,s,'\n')`
    - read：读指定字节数
        - e.g. `char buffer[SIZE]; in.read (buffer, size);`
    - write：写指定字节数
        - e.g. `char buffer[SIZE]; out.write (buffer, size);`
4. 获取状态
    - `bad()`：如果在读写过程中出错，返回 true 。例如：当我们要对一个不是打开为写状态的文件进行写入时，或者我们要写入的设备没有剩余空间的时候。
    - `fail()`：除了与bad() 同样的情况下会返回 true 以外，加上格式错误时也返回true ，例如当想要读入一个整数，而获得了一个字母的时候。
    - `eof()`：如果读文件到达文件末尾，返回true。
    - `good()`：这是最通用的：如果调用以上任何一个函数返回true 的话，此函数返回 false。
    - `clear()`: 重置以上成员函数所检查的状态标志
4. 操作和查看流指针
    - `tellg()` 和` tellp()` 这两个成员函数不用传入参数，返回pos_type 类型的值(根据ANSI-C++ 标准) ，就是一个整数，代表当前 get 流指针的位置 (用 tellg) 或 put 流指针的位置(用 tellp).
    - `seekg()` 和 `seekp()` 这对函数分别用来改变流指针 get 和 put 的位置。
        - 可选参数 for seekdir
            - `ios::beg` 从流开始位置计算的位移
            - `ios::cur` 从流指针当前位置开始计算的位移
            - `ios::end` 从流末尾处开始计算的位移
        - 两种原型
            1. 从文件头开始计算位置：`seekg ( pos_type position );`
                - e.g. `seekg (12);`
            2. 从指定位置开始计算相对位置：`seekg ( off_type offset, seekdir direction );`
                - e.g. `in.seekg (-1, ios::end);`