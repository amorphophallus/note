# CMake & makefile 的编写 & GCC 编译命令

[TOC]

> 参考资料：[非常详细的教程](https://makefiletutorial.com/)

makefile定义了一系列规则来指定：哪些文件需要先编译，哪些文件需要后编译，哪些文件需要重新编译，甚至更复杂的操作。

## Makefile

[参考博客](https://zhuanlan.zhihu.com/p/61407372)

1. 新建 `makefile` 或者 `Makefile` 文件

2. 基本格式

```makefile
# 格式
target... : prerequisites...
    command

# 举例
main : main.o get.o set.o show.o
    gcc -o main main.o get.o set.o show.o

# 定义变量
obj = main.o set.o get.o show.o update.o

main : $(obj)
    gcc -o main $(obj)

# 引用
include test.mk my.mk
```

3. 编译命令 `make`
4. 进阶技巧

```makefile
# the all target (used if there are multiple final targets)
all: one two three

one:
    touch one
two:
    touch two
three:
    touch three

# multiple targets
f1.o f2.o:
	echo $@ # $@ is an automatic variable that contains the target name

# automatic variables
hey: one two
	# Outputs "hey", since this is the target name
	echo $@

	# Outputs all prerequisites newer than the target
	echo $?

	# Outputs all prerequisites
	echo $^

# * wildcard
thing_right := $(wildcard *.o)
```


### 注意事项

1. Makefile 要注意缩进：command 如果不与 target 和 prerequisites... 在同一行，需要以 tab 开头
2. Linux 下编译命令为 `make`，windows 下命令为 `mingw32-make`

### 工作原理

1. If there's no target supplied as an argument to the `make` command, the first target is run. Otherwise the argument is considered the final target.
2. `Make` will only run if the target doesn't exist, or prerequisites is newer than the target file.
    - notice that `make` can't determine which file is required by the target through the commands. Prerequisites should be mentioned manually.
    - To make this happen, it uses the filesystem timestamps as a proxy to determine if something has changed. 

### Examples & Skills

#### 1 How Make Works

```makefile
blah: blah.o
	cc blah.o -o blah # Runs third

blah.o: blah.c
	cc -c blah.c -o blah.o # Runs second

# Typically blah.c would already exist, but I want to limit any additional required files
blah.c:
	echo "int main() { return 0; }" > blah.c # Runs first
```

If you delete `blah.c`, all three targets will be rerun. If you edit it (and thus change the timestamp to newer than `blah.o`), the first two targets will run. If you run touch `blah.o` (and thus change the timestamp to newer than blah), then only the first target will run. If you change nothing, none of the targets will run. Try it out!

#### 2 Make clean & .PHONY


`clean` is often used as a **target** that removes the output of other targets, but it is not a special word in Make. You can run `make` and `make clean` on this to create and delete some_file.

Adding `.PHONY` to a target will prevent Make from confusing the phony target with a file name. In this example, if the file `clean` is created, `make clean` will still be run. Technically, I should have used it in every example with all or clean, but I didn't to keep the examples clean. Additionally, "phony" targets typically have names that are rarely file names, and in practice many people skip this.

```makefile
some_file:
	touch some_file
	touch clean

.PHONY: clean
clean:
	rm -f some_file
	rm -f clean
```

### Implicit Rules

The important variables used by implicit rules are:

1. `CC`: Program for compiling C programs; default `cc`
1. `CXX`: Program for compiling C++ programs; default `g++`
1. `CFLAGS`: Extra flags to give to the C compiler
1. `CXXFLAGS`: Extra flags to give to the C++ compiler
1. `CPPFLAGS`: Extra flags to give to the C preprocessor
1. `LDFLAGS`: Extra flags to give to compilers when they are supposed to invoke the linker

e.g.

1. Compiling a C program: `$(CC) -c $(CPPFLAGS) $(CFLAGS) $^ -o $@`
1. Compiling a C++ program: `$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $^ -o $@`
1. Linking a single object file: n is made automatically from n.o by running the command `$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@`

## gcc 编译命令

> [菜鸟教程](https://www.runoob.com/w3cnote/gcc-parameter-detail.html)
> [standard 一览](http://c.biancheng.net/view/8053.html)

### `-c`

只激活预处理,编译,和汇编,也就是他只把程序做成obj文件

例子用法:

```makefile
gcc -c hello.c 
```

### `-o`

制定目标名称, 默认的时候, gcc 编译出来的文件是 a.out, 很难听, 如果你和我有同感，改掉它, 哈哈。

例子用法:

```makefile
gcc -o hello hello.c
gcc -o hello.asm -S hello.c
```

### `-std=<standard>`

指定要使用的编译标准。

具体的查看 [这个网页](http://c.biancheng.net/view/8053.html)


## CMake

### VCPKG

VCPKG 是 C++ 的包管理工具，VCPKG 配合 CMake 使用可以让 C++ 调库变得更加便捷

安装和配置：
- [vcpkg 官方文档](https://github.com/microsoft/vcpkg/blob/master/README_zh_CN.md)：clone repo，下载脚本
- [vcpkg 换源](https://zhuanlan.zhihu.com/p/383683670)
- [vcpkg 配置](https://zhuanlan.zhihu.com/p/447391308)：设置默认 x64
- [vcpkg+vscode+CMake 工程](https://zhuanlan.zhihu.com/p/430835667)：配置 VSCode CMake 插件，新建 CMake 项目的流程（举了一个例子）
- [vcpkg+vscode 开发环境配置](https://zhuanlan.zhihu.com/p/350194582)：安装库和综合的指令（综合之后可以直接在 VS 中调用）

vcpkg 在 CMake 中的使用：
- 配置 VSCode CMake 插件
	```json
	"cmake.configureSettings": {
		"CMAKE_TOOLCHAIN_FILE": "F:/vcpkg/scripts/buildsystems/vcpkg.cmake",
		"VCPKG_TARGET_TRIPLET": "x64-windows"
	}
	```
	或者在 `CMakeLists.txt` 中包含以下命令
	```cmake
	SET(CMAKE_TOOLCHAIN_FILE "F:/vcpkg/scripts/buildsystems/vcpkg.cmake")
	```
	或者在 CMake 命令中添加参数
	```shell
	cmake \
		-B [build directory] \
		-S . \
		-DCMAKE_TOOLCHAIN_FILE="[path to vcpkg]/scripts/buildsystems/vcpkg.cmake"
	```
	这些方法的效果都是一样的，就是设置 CMake 编译的参数，让 CMake 能找到用 vcpkg 下载的文件
- `vcpkg install xlnt`，如果已经安装过了不会重复安装，会提示在 CMake 文件中要写哪些话，把这些话复制到 `CMakeLists.txt` 中
	```cmake
	find_package(Xlnt CONFIG REQUIRED)
    target_link_libraries(main PRIVATE xlnt::xlnt)
	```
- 在源文件中直接 `#include <xlnt/...>` 会提示补全 xlnt 库包含的头文件

### CMake 命令

[CMake 教程](https://zhuanlan.zhihu.com/p/534439206)

常用命令：CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.15)

# 设置 project name
project(Tutorial)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加变量
set(SRC_LIST a.cpp b.cpp c.cpp)

# 查找指定目录下的所有源文件并添加到变量
aux_source_directory(<dir> <variable>)

# 添加子目录，这样 math 目录下的 CMakeLists.txt 文件和源代码也会被处理
add_subdirectory(math)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SRC_LIST})

# 生成静态链接库
add_library(MathFunctions mysqrt.cpp)
```

### VSCode CMake 插件

使用 VSCode 插件快速创建一个 CMake 项目