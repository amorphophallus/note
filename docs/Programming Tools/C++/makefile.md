# makefile 的编写和 GCC 编译命令

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