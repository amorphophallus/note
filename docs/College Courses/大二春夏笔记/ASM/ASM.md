# 汇编语言

[TOC]

## intro

1. 资源
    - [小白的主页](http://cc.zju.edu.cn/bhh) 包含课程资源
    - 邮箱：iceman@zju.edu.cn
    - 实验环境：bochs 虚拟机，进行保护模式的实验
    - 考试：程序填空可以多次提交
    - [看雪学院（国内讨论破解）](http://bbs.pediy.com)
    - [讨论汇编、破解的网站（x64dbg 开源软件创作者所在论坛）](http://www.52pojie.cn讨论破解http://forum.exetools.com)
    - [国外讨论破解](http://www.tuts4you.com)
    - [国外老的破解教程](http://www.woodmann.com/crackz)
    - [fravia 论坛镜像](http://cc.zju.edu.cn/bhh/fravia/index.htm)
    - [国外32位汇编网站](http://www.masn32.com)
    - [浙大信息安全小组AAA](https://zjusec.com)
    - [x86 and amd64 instruction reference](https://www.felixcloutier.com/x86/)
    - 推荐阅读：Intel 80386 Programmer's Reference Manual，[书的网页版](https://pdos.csail.mit.edu/6.828/2018/readings/i386/toc.htm)
2. 学习汇编语言的作用
    - 加深对高级编程语言的理解
    - 逆向(reverse-engineering)：跟踪 & 破解程序（激活码）、反跟踪
    - 混合语言编程：提升程序性能
3. 实验环境
    - XP 虚拟机：点击 `.vmx` 文件直接在 VMWare 中打开虚拟机
    - [虚拟机网络设置](https://blog.csdn.net/qq_47188967/article/details/126442372)
    - xp 桌面上的 dosbox86 是一个 DOS 环境
4. 编译链接过程（以 printf 为例）
    - 编译： `.c` -> `.obj` （obj 文件中是机器码，作者提供 obj 而不提供 c 文件可以有效保护知识产权）
    - 链接: 搜索 `cs.lib` （库文件，obj 文件的集合），复制 `printf.obj` 以及 `c0s.obj` 到 `main.obj` 生成 `main.exe`
        - 调用 `main.c` 之前会调用初始化模块，turbo C 的初始化函数在 `c0s.obj` 中
        - 调用 main 函数的汇编语言 `call 01FA`

## 知识点

### 硬件知识

1. 小端规则：低 Byte 在前，高 Byte 在后
2. eax & ax & ah & al：都是寄存器，eax 的低 16 位是 ax，ax 的高 8 位是 ah，ax 的低 8 位是 al
    - 寄存器在 cpu 内部，不在内存中，没有地址


#### 常见 16 位寄存器(14 个)

用于运算：(general registers)

- ax
- bx
- cx
- dx

存储段地址：(segment registers)

- cs: code segment
- ds: data segment
- es: extra segment，一个数据段存不下所有数据时用于补充
- ss: stack segment，存储堆栈区的段地址

存储偏移地址: 

- si
- di
- bp
- sp
- (bx 也可用)

ip: instruction pointer，指令指针

- cs + ip: cs 用于保存将要执行的指令的段地址，ip 用于保存将要执行的指令的偏移地址，cs + ip 确定将要执行的指令的逻辑地址

FL: flag，标志寄存器，16 个 bit 分别表示不同含义，有的可以指示指令执行后的状态，有的可以控制 CPU 行为

- FL[0]: 称为 CF，存储当前指令的进位

```asm
mov ax 0FFFFh
add ax, 1
jnc no_carry_flag
jc has_carry_flag

no_carry_flag:
has_carry_flag:
```

#### 32 位寄存器

保持 16 位：cs, ds, es, ss

扩展到 12 位：eax, ebx, ecx, edx, esi, edi, ebp, esp, eip, EFL

### 汇编指令

1. mov
    - `mov word ptr [0426],0001` 把 16 位数据 0x0001 移动到地址 0x0426 的内存中。[] 表示取地址，相当于 C 中的 *。

3. nop(0x90)：no operation 用于删除机器码并保持跳转指令的正确性
4. cli: clear interrupt 不允许中断（在 windows 下是特权指令，用户程序不允许操作）

#### 运算指令

1. add, sub, mul, div 无符号整数加减乘除
1. imul, idiv 有符号整数乘除 **（加减操作不需要区分有符号和无符号）**
1. fadd, fsub, fmul, fdiv 浮点数加减乘除

e.g. 无符号数乘法

```asm
mov ax, 0FFFFh ; 65535
mov bx, 0FFFFh ; 65535
mul bx  ; 使用 bx 作为操作数，隐含的信息是 mul 是一个 16 位乘法，另一个操作数默认是 ax
        ; 相当于 dx:ax = ax * bx
        ; 冒号表示高 16 位和低 16 位的连接，即溢出的值存放在 dx 中
        ; ax 同时作为被乘数和结果寄存器，也隐含在命令中
```

e.g. 有符号数乘法

```asm
mov ax, 0FFFFh ; -1
mov bx, 0FFFFh ; -1
mul bx  ; 结果为 ds = 0000h, ax = 0001h
```
e.g. 为什么高级语言不需要区分 mul, imul, fmul？

Ans：因为高级语言有变量类型，可以根据操作数类型选择操作模式。但汇编语言的变量只规定长度，不规定类型。例如以下两个变量定义是等价的：

```asm
a dw 0FFFFh
b dw -1     ; 在内存中都是一段长 16 位的全 1 的数据
```

#### 逻辑运算

- 位运算：and, or, xor, not
- 移位运算：shl, shr, rol, ror, sal, sar。对应左移(shift left)、右移(shift right)、循环左移(rotate lefts)、循环右移(rotate right)、算术左移（shift arithmetic left）、算术右移(shift arithmetic right)

e.g.

```asm
mov ah 10110110b
shl ah, 1   ; ah = 01101100b
```

p.s. **逻辑右移使用 zero-extension，算术右移使用 sign-extension**

#### 跳转指令

- jbe: jump if below or equal
- jb: jump if below
- ja: jump if above
- jae: jump if above or equal
- jmp: 无条件跳转

e.g. 

```asm
cmp ebx, 100
jbe next
```

如果 ebx 小于等于 100 则跳转到 next 位置


### 汇编语言

1. 常数若以字符开头，需要添加前导零，用以与变量名进行区分。e.g. `0Fh`
2. 换行符
    - Windows 下：`\r` (0Dh) 回到行首，`\n` (0Ah) 光标到下一行的同一列
    - Linux 下： `\n` 承担了以上两个任务


#### 逻辑地址表示法

段地址：5 位 16 进制段首地址的前 4 位

- 段首的要求：5 位 16 进制段地址的最低位必须为 0
- 段长的要求：最大段长 10000h
    - 假设段首地址是 `12340h`，则这个段里的所有地址分别是 `1234:0000` 到 `1234:FFFF`
- 段和段之间可以重叠，`1233:0068==1234:0058==1235:0048`
- 段地址适用于：变量、数组、标号

偏移地址：在段地址的基础上，加上的一个偏移量

逻辑地址产生的历史原因：8086 CPU 没有 4 位以上的寄存器，只能把一个 5 位地址拆成两个 4 位表示

运算符：

- 取地址：`ds:bx+3`
- 取内容：`ds:[bx+3]`

p.s. 每个地址存储 1 个 Byte 的数据

#### 重定位(relocating)

在编译过程中数组的 offset (3) 是可以知道的，但是 `seg s` 在编译的过程中是未知的，根据程序运行时内存的空闲区域而变化。

所以 `seg s` 会被编译成 s 的段地址和首段的段地址的差；在运行前由系统对程序进行修正，加上程序首段的段地址，这个过程称为 **重定位(relocating)** 。

例如在下面的程序中，用 qv 打开 exe 文件可以看到 `seg s` 被编译成 0，但用 td 打开 exe 文件，在运行中同样的位置是一个非 0 的不确定的数。

从文件头偏移 1E 处开始，每 4 个字节标识了一个重定位位置，以小端规则存储。例如 1E 处的内容为 `01 00 02 00`，假设程序运行时的 **真实首段地址** （注意不是文件头地址）为 `1000:0`，则表示 `1002:0001` 地址需要修改。

在文件头偏移 06 处存储了需要进行多少次重定位。例如 `01 00` 表示只有一个位置需要重定位。

在文件头偏移 08 处存储了文件头的长度。例如 `20 00` 表示文件头的长度为 `00200h`

#### 变量定义

| 变量名 | 内存位数 | 缩写含义 | C 中对应的数据类型 |
| -- | -- | -- | -- |
| db | 8 bit | byte | char |
| dw | 16 bit | word | short int |
| dd | 32 bit | double word | long int, float |
| dq | 64 bit | quadruple word | long long int, __int64, double |
| dt | 80 bit | ten bytes | long double |

e.g. `s db "ABC"` 定义一个数组，每个元素占 8 bit
e.g. `x dd 3.14` 定义一个 float

p.s. IEEE 754 标准浮点数：参考计组笔记中的 “浮点数 - IEEE754 标准” 章节

### DOS

16 位 CPU 运行在实模式(real mode)下，用户代码具有和操作系统一样的权限。

32 位 CPU 可以采用保护模式(protected mode)，用户代码不能越权访问操作系统等进程占用的内存空间。

32 位 CPU 中的寄存器：

- 保持 16 位：cs, ds, es, ss
- 扩展到 12 位：eax, ebx, ecx, edx, esi, edi, ebp, esp, eip, EFL

gdt(global descriptor table): 全局描述符表。数组，每个元素 8 Byte

```
t     -> gdt[0]
t+08h -> gdt[1]
t+10h -> gdt[2]
t+18h -> gdt[3]
```

现在假设这么一个情形：ds = 8, edi = 45678h，在内存中指向的地址是什么？

假设 gdt[1] 的 8 个字节如下：

| 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  |
| -- | -- | -- | -- | -- | -- | -- | -- |
| FF | FF | 00 | 00 | 10 | 93 | 0F | 00 |

取出其中的 7, 4, 3, 2 Byte 组成一个 8 位 16 进制数，与偏移地址相加得到逻辑地址

`00100000h + 45678h = 00145678h`

取出第 6 Byte 的低 4 位，加上 1 和 0 Byte，组成段的最大偏移地址 `FFFFFh`

第 6 Byte 的最高 bit 如果为 0，表示最大偏移量的单位是 bit；如果为 1，表示单位是 Page( = 4K)

第 5 Byte 用来规定段的类型、读写权限。例如 93h 表示：该段是数据段、可读、可写、要求访问者的权限是 ring0（最高权限级）

假设这是第 5 个 Byte 的数据，第 1 和 2 位规定了权限(ring0)

| 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  |
| -- | -- | -- | -- | -- | -- | -- | -- |
| 1 | 0 | 0 | 1 | 0 | 0 | 1 | 1 |

### DOS Interrupt

#### getchar

`int 21h(AH=01h)`: 从 stdin 读取一个字符，保存在 AL 中，相当于 getchar()

```
mov ah, 1
int 21h
cmp al, 'A'
```

#### putchar

`int 21h(AH=02h)`: 把 DL 中的数据输出到 stdout 中，相当于 putchar()

```
mov ah, 2
mov dl, 'U'
int 21h
```

#### exit

`int 21h(AH=4Ch)`: 结束程序，返回 AL 中的数值

```
exit:
    mov ah, 4Ch
    mov al, 0
    int 21h
```

## 工具

### Turbo C & Turbo Debugger

- turbo C 编辑 + 编译链接(tcc，16 位编译器) + 调试
    - windows + R -> command -> tc + 文件名
- turbo debugger(td)：只能调试 16 位 DOS 程序(.exe)
    - windows + R -> command -> td + 程序名(.exe)

==TB 打开 exe、搜索内存位置、搜索程序位置、修改汇编代码？==

1. 在 command 中用 `TD xxx.exe` 命令打开 exe 文件
2. TD 界面
    - 左上：汇编程序(cs)
    - 左下：内存空间(ds)
    - 右上：寄存器（例如: ax, bx）
    - 右下：
3. 设置断点：F2 在光标位置设置一个断点
4. 跟踪进入函数：F7
5. 搜索内存地址：选中左下角框 -> ctrl+g -> 输入内存位置的逻辑地址 `ds:0426`
    - 搜索代码地址同理
6. 切换寄存器位数：
    - 右键 -> 可以切换 16 位和 32 位
    - ctrl+R
7. F9：运行程序
8. F4：运行到光标处暂停

### OllyDbg

==OllyDbg 打开 exe、设置断点、调试（运行到断点etc）、修改汇编代码==

1. F2：运行
2. 

### MASM32

编译汇编语言的集成环境

- D:\masm32\qeditor.exe
- open -> 选择 `sum.asm` -> project -> build all -> 32 位程序 `sum.exe`

### MASM

编译 16 位汇编代码

- win+R -> command
- D: -> cd masm
- masm sum16.asm; 编译产生 obj 文件（可以省略后缀名）
- link sum16.obj; 链接产生 exe 文件（可以省略后缀名）
- td sum16.exe 在调试模式中运行

### 010 Editor

16 进制编辑器，用于修改 exe 文件

在 OllyDbg 中复制一段 *较长的* 机器码，用 010 Editor 打开 exe 文件，ctrl+F 搜索复制的机器码，保证代码段唯一后修改。

### QuickView

16 进制编辑器

1. 回车 / F4 / 点击下边栏的 Mode：切换显示模式
    - ASCII 模式
    - hex 模式
    - 汇编语言模式
        - tab：切换修改机器码和修改汇编代码
2. F2：切换 16 位模式和 32 位模式
3. F7：搜索
    - tab：切换 ASCII 搜索和 hex 搜索
4. F3：恢复
5. Alt+F9：保存修改
6. ctrl+home: 回到文件开头

### EditPlus

文本编辑器，用于打开 ASM 文件或者 C 语言源文件

### WinApiHelp

查看 Windows XP API。点击索引，输入函数名搜索。

### 中断大全

查看 DOS API（软件中断）

点击“中断大全”网页 -> interrupt -> 选择中断号

### DosBox86

一个虚拟的 DOS 环境。其中虚拟的 C 盘位于 `D:\DosBox86` 下，要用这个环境进行编译链接运行，需要把文件放到 `D:\DosBox86\MASM` 文件夹下。

## 实验

### 32 位汇编 sum.asm

功能：使用循环计算 $\sum_{i=1}^{100} i$

1. `invoke wsprint, offset result, offset format, eax`：调用操作系统内部函数（API），把 eax 中的内容按 format 指定的格式输出到 result 中
2. `invoke MessageBoxA, 0, offset result, offset prompt, 0`：调用操作系统内部函数，弹窗显示，标题 prompt，内容 result
3. `prompt db "The Result", 0`：定义变量
    - 单引号和双引号同义
    - 定义数组时不需要加方括号，和定义一般变量一样
    - 字符串不会自带 `\0`，需要自行加上 `, 0` 表示在字符串后加一个 ASCII 码值为 0 的字符
4. `result db 100 dup(0)`: 相当于 C 中的 `char result[100]={0};` dup 表示重复
5. 引导词(pseudo code)
    - `.data`: 表示下面开始定义变量
    - `.code`: 表示下面开始是程序指令
5. `end start`: 放在程序结尾，表示程序从哪个标号位置开始运行

```asm
.code
main：
	mov eax, 0	; e表示扩充, 有32位. 低16位是ax. ax的高8位是ah, 低8位是al.
	mov ebx, 1
next:
	add eax, ebx
	add ebx, 1
	cmp ebx, 100
	jbe next
; 下面的两个函数是API
; wsprintf(&result[0], &format[0], eax)就是将eax的值按照format格式输出到result上
; format是一个字符数组, 内容如"%d"
invoke wsprintf, offset result, offset format, eax
; MessageBoxA(0, result, prompt, 0)
; result是要显示的内容, prompt是标题
invole MessageBoxA, 0, offset result, offset prompt, 0
	ret
end main		; 第一条指令位于main:处
```

### 16 位汇编 case16.asm 在 DOS 系统中运行

功能：输入一个字符，使用分支语句判断是否是大写字母并输出

1. `.386`: 使用 32 位寄存器
1. `code segment use16`: 代码开始，使用 16 位地址（DOS 中无法使用 32 位地址）
1. `code ends`: 代码结束
1. `end begin`: 规定代码开始运行的位置

```asm
.386
code segment use16
assume cs:code
main:
	mov ah, 1
	int 21h			; AL = getchar()
					; int 21h代表一个函数集
					; AH=1表示调用该函数集中的1号子函数
	cmp al, 'A'
	jb	not_upper
	cmp	al, 'Z'
	ja	not_upper
is_upper:
	mov	ah, 2
	mov	dl, 'U'
	int 21h			; putchat(DL)
	jmp	exit
not_upper:
	mov	ah, 2
	mov	dl, 'o'
	int	21h
exit:
	mov	ah, 4Ch
	mov	al, 0
	int 21h			; exit(0)
code ends
end main
```

HW：输入字符，判断是大写字母、小写字母、数字、其他

### 破解 password.exe

方法 1：设置断点，在判断语句的附近找到用于比对的密码

方法 2：修改跳转语句，无条件跳转到密码正确的分支（暴力破解）（不能删除，用 nop 替换）

反制方法 2.1：exe 保护软件，压缩 exe 为另一个 exe 文件（例如 PeCompact, Vmprotect 保护程序不进入 Debug 模式）

方法3：破解 sn 函数的计算方法

反制方法 3.1：难以计算的 sn，例如 rsa

- sn = rsa(mac, 私钥)
- check rsa(sn, 公钥) ?= mac

反制方法 3.2：利用哈希函数保护密码，例如 md5

- 保存 密码'=md5(密码)，可以公开
- 再次登录时检查 密码'?= md5(输入密码)


### 16 位汇编 outstr.asm

功能：使用循环输出存放在 data 数据段的字符串

1. 在内存中存一个带回车的字符串 `s db "HelloWorld!", 0Dh, 0Ah, 0`
2. 偏移地址：`mov dl, s[bx]` 编译后变成 `mov dl, 3[bx]`，再变成 `mov dl, ds:[bx+3]`
    - 其中 ds 是数组元素的段地址(segment address)
    - 3 是 s 数组首地址关于段地址的偏移，编译过程中会被赋值
    - ds:bx+3 是数组元素的偏移地址
    - 相当于 C 语言中的 `*(ds: bx+3)`，C 允许这样的语法 `0[s+3]`，能够产生和 `s[3]` 一样的结果
    - `ds:[bx+3]` 可以简化为 `[bx+3]`，ds 是隐含的
3. ds：数据段寄存器，只接受寄存器赋值，不能用常数赋值。因为在硬件设计时被简化了

存储常数的代码：

```asm
data segment
a db "ABC"
s db "Hello$World!", 0Dh, 0Ah, 0
data ends
```

获取数组内容的代码：

```asm
mov ax, seg s
mov ds, ax
mov dl, s[bx]
```

完整代码：

```asm
data segment ; 数据段
a db "ABC"
s db "Hello$World!", 0Dh, 0Ah, 0 ; \r\n 回车
data ends

code segment ; 代码段
assume cs:code, ds:data
main:
    mov ax, seg s
    mov ds, ax ; 获取段地址存到 ds 里
    mov bx, 0 ; bx 用于遍历字符串 s
next:
    mov dl, s[bx] ; 经过编译后变成 mov dl, ds:[bx+3]
    cmp dl, 0
    je exit ; 读到字符串末尾的 0 就退出
    mov ah, 2
    int 21h ; 调用系统中断，输出字符
    add bx, 1
    jmp next ; bx 累加，重新开始循环
exit:
    mov ah, 4Ch
    int 21h ; 调用系统中断，退出程序
code ends
end main ; 表示程序从 main 开始运行
```

### 16 位汇编语言程序 to16.asm

功能：把一个 32 位二进制数转换为 16 进制输出，使用逻辑运算命令

1. `.386`: 使用 32 位寄存器，同时偏移地址默认为 32 位
2. `code/data segment use16`: 此段偏移地址为 16 位（DOS 中无法使用 32 位地址）
    - 两句话加起来的意思就是：用 32 位寄存器，但是一个地址只存 16 位数据

```asm
.386
data segment use16
a dd 56789ABCh
data ends

code segment use16
assume cs: code, ds: data
main:
    mov ax, data    ; 相当于 mov ax, seg a
                    ; 在 mov 命令中使用数据段的名字相当于取段地址
    mov ds, ax
    mov eax, a      ; 把 a 的值取到 eax 中，前提条件是 ds 中已经存储了 a 的段地址
    mov cx, 8       ; 循环次数
next:
    rol eax, 4
    mov edx, eax
    and edx, 0Fh    ; 通过 and 只保留最后 4 bit
    cmp edx, 10
    jae is_alpha
    add dl, '0'     ; dl 是 edx 的低 16 位
    jmp out_char
is_alpha:
    sub dl, 10
    add dl, 'A'
out_char:
    push eax        ; ah 是 eax 的一部分，会破坏 eax 中的原始数据，所以需要事先保存一下
    mov ah, 2
    int 21h         ; putchar(dl)
    pop eax
    dec cx          ; 等价于 sub cx, 1
                    ; 
    jnz next        ; 上一个写入的寄存器中的数据域与 0 比较
exit:
    mov ah, 4Ch
    int 21h         ; 退出程序
code ends
end main
```

p.s. 保存 eax 中数据的三种方法

1. 在其他寄存器中寄存
2. 在内存中定义的变量中寄存 `mov old_eax, eax`, `mov eax, old_eax`
    - 需要确保 ds 中存储的是 old_eax 的段地址，因为在前面已经操作过了，这里不用再操作
3. 在堆栈中寄存 `push eax`, `pop eax`