# makefile 的编写和 GCC 编译命令

[TOC]

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


### 注意事项

1. Makefile 要注意缩进：command 如果不与 target 和 prerequisites... 在同一行，需要以 tab 开头
2. Linux 下编译命令为 `make`，windows 下命令为 `mingw32-make`

### 工作流程

1. make命令会在当前目录下找名字为Makefile或makefile的文件；
2. 在Makefile文件中找第一个target，并将其作为最终目标文件也就是示例的main，所有的后续都是为了生成这个目标文件而执行；
3. 如果main文件不存在，或者main依赖的文件修改时间更新，就会执行command来生成main；如果main依赖的文件如main.o也不存在，那么就会寻找main.o的依赖文件，根据command生成main.o文件；
4. 最终的依赖文件就是.c,.h文件，如果这些文件不存在，就会报错。
5. make一层一层根据定义的依赖关系，最终编译出第一个目标文件，结束。

## gcc 编译命令

[参考博客](https://www.cnblogs.com/ibyte/p/5828445.html)


