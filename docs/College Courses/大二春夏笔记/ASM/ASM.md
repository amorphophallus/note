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
    - `ss:sp` 指向堆栈的顶端
- bx
    - 因为 sp 用于特定用途，偏移地址寄存器少了一个，就把通用寄存器中的一个拿来顶替

ip: instruction pointer，指令指针

- cs + ip: cs 用于保存将要执行的指令的段地址，ip 用于保存将要执行的指令的偏移地址，cs + ip 确定将要执行的指令的逻辑地址

##### FL

FL: flag，标志寄存器，16 个 bit 分别表示不同含义，有的可以指示指令执行后的状态，有的可以控制 CPU 行为

![ASM](./imgs/2023-04-19-20-30-55.png)

- FL[0]: 称为 CF，存储当前指令的进位（在加法中表示进位，在减法中表示借位，在移位中表示最后被移出去的位，但本质是一样的）

```asm
mov ax 0FFFFh
add ax, 1
jnc no_carry_flag
jc has_carry_flag

no_carry_flag:
has_carry_flag:
```

- CF 相关指令
    - jc, jnc: 根据 CF 进行跳转
    - adc: 带进位加法（类似全加器），`adc ax, bx` 表示 `ax = ax + bx + CF`
    - clc: clear carry `CF = 0`
    - stc: set carry `CF = 1`
---

- FL[6]: ZF, zero flag，指令结果为 0 的时候置 1
    - `sub ax, ax` ZF=1
- ZF 相关指令
    - jz, jnz: 根据结果是否 0 进行跳转
        - `cmp ax, bx` + `je Label` 和 `sub ax, bx` + `jz Label` 在结果上是一样的

---

- FL[7]: SF, sign flag, 存储指令结果的最高位
- SF 相关指令：js, jns


##### 程序载入内存时的自动赋值

以下寄存器会在程序载入内存时被自动赋值

- cs=code
- ip=程序初始指令的偏移地址
- ss=stk
- sp=堆栈段的大小
- ds=es=psp段址

其中 **psp 段址** 是：长度为 100h 的一块内存，位于程序首段之前，其内容与程序内容无关，存放与 exe 相关的信息
- 命令行参数：`psp:80h` 一个字节存命令行参数的长度，从 `psp:81h` 开始连续存放命令行参数的字符
    - 如果程序名后面打了空格，那空格也会在参数字符串里
    - 参数字符串以回车结尾

**tips.**

1. 进行逻辑地址寻址之前 ds 一定要自己赋值
1. ds 初始值加 100h 等于程序首段段地址

#### 32 位寄存器

保持 16 位：cs, ds, es, ss

扩展到 12 位：eax, ebx, ecx, edx, esi, edi, ebp, esp, eip, EFL

#### 保护模式

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


### 汇编指令

#### 运算指令

1. add, sub, mul, div 无符号整数加减乘除
1. imul, idiv 有符号整数乘除 **（加减操作不需要区分有符号和无符号）**
1. fadd, fsub, fmul, fdiv 浮点数加减乘除

e.g. 无符号数乘法（**乘法只有一个参数**）

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

#### 栈操作指令

- push
- pop

tips. 操作数只能是 16 位或者 32 位数据，相应地 ss 减去 2 或者 4。

```asm
    ; 保存 16位数据
    push ax
    push word ptr ds:[di]
    ; 保存 32 位数据
    push eax
    push dword ptr ds:[di]
    ; 保存 8 位数据，曲线救国
    push ax
    pop bx
    mov al, bl
```

##### 栈空间的分配

```asm
stk segment stack
db 200h dup('S')
stk ends
```

- 堆栈只能定义一个，用 `stack` 关键字表示
- 可以用无名数组填充堆栈，比如上面的代码表示堆栈空间大小 200h Byte
    - 不定义名称对内存中的数据没有任何影响，但是在程序里就不能通过变量名访问这块内存了
- 可以不在程序中 `assume ss:stk`，因为 assume 是为程序中的寻址操作服务的，如果不需要通过 push, pop 以外的操作访问堆栈，就不需要加 assume
- 程序载入内存时 ss 和 sp 会自动赋值

---

如果用户没有分配栈空间，

- ss=首段段地址
- sp=0

相当于把段的末尾当做堆栈空间，对于 16 位寄存器来说，`sp-2 = 0-2 = 0xFFFE`

即使用户程序不需要使用 push pop，程序本身在进行 **时钟中断、键盘缓冲** 等操作时也会用到栈空间。

##### 压栈弹栈的实现

`push ax` (16 bit)

1. `sub sp, 2`
1. `mov ss:[sp], ax`

`pop ax` (16 bit)

1. `mov ax, ss:[sp]`
1. `add sp, 2`

push 和 pop 32 bit 数据同理

#### 其他常用指令


1. mov
    - `mov word ptr [0426],0001` 把 16 位数据 0x0001 移动到地址 0x0426 的内存中。[] 表示取地址，相当于 C 中的 *。
1. nop(0x90)：no operation 用于删除机器码并保持跳转指令的正确性
1. cli: clear interrupt 不允许中断（在 windows 下是特权指令，用户程序不允许操作）


### 汇编语言

1. 常数若以字符开头，需要添加前导零，用以与变量名进行区分。e.g. `0Fh`
2. 换行符
    - Windows 下：`\r` (0Dh) 回到行首，`\n` (0Ah) 光标到下一行的同一列
    - Linux 下： `\n` 承担了以上两个任务


#### 逻辑地址表示法

##### 段地址 + 偏移地址

段地址：5 位 16 进制段首地址的前 4 位

- 段首的要求：5 位 16 进制段地址的最低位必须为 0
- 段长的要求：最大段长 10000h
    - 假设段首地址是 `12340h`，则这个段里的所有地址分别是 `1234:0000` 到 `1234:FFFF`
- 段和段之间可以重叠，`1233:0068==1234:0058==1235:0048`
- 段地址适用于：变量、数组、标号

偏移地址：在段地址的基础上，加上的一个偏移量

p.s. 逻辑地址产生的历史原因：8086 CPU 没有 4 位以上的寄存器，只能把一个 5 位地址拆成两个 4 位表示

p.s. 每个地址存储 1 个 Byte 的数据

##### 表示方法

正确的：

- 取地址：`ds:bx+3`
- 取内容：`ds:[bx+3]`
    - `[bx+3]`，等价于 `ds:[bx+3]`，其中 ds 是隐含的
- `abc[1]`，其中 abc 是 data 段中的数组，属于直接寻址，会被编译成 `ds:[offset abc + 1]` 然后变成例如 `1000h:[0+1]`
    - `[abc+1]` 等价
    - `mov bx, offset abc` + `[bx+1]` 等价 
    - `mov bx, offset abc` + `mov si, 1` + `[bx+si]` 等价
    - 注意在 C 中指针加数字 `abc + 1` 的含义是 `abc + 1 * sizeof(*abc)`。但在汇编中指针加数字和数字加数字没有任何区别，`abc + 1` 永远表示 abc 偏移一个 byte。例如，如果 `xyz` 是一个 `dd` 数组，那么 xyz 的第二个元素地址为 `xyz + 4`。

错误的：

- 不能用常数表示段地址：`1000h:[2000h]`

##### 寻址方式分类

1. 直接寻址：偏移地址只用常数表示。例如 `[1000h]`, `ds:[2000h]`
1. 间接寻址：偏移地址可以由寄存器和常数表示。
    - 只允许 bx, bp, si, di 四个寄存器出现在方括号里。例如 `[ax]` 是错误的
    - 寄存器相加时只允许 b 开头的寄存器和 i 结尾的寄存器、例如 `[bx+si+2]` 是正确的，`[bx+bp]` 是错误的。

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

---

p.s. 可以在 code segment 中定义变量，但是必须保证程序运行时跳过定义变量的内存。

##### 定义数组变量

使用 dup 进行重复填充

```asm
data segment
s db 1, 2, 3, 4
t db 200h dup('S')
data ends
```

#### byte ptr

- 汇编语言的多数指令要求两个操作数等宽
- 汇编语言中常数没有明确的宽度

`mov ds:[bx], 0` 根据前两条规律，可以得出：指令的两个操作数宽度均不明确会报错

`mov ds:[bx], al` 将 8 bit 数据存到 `ds:bx`

`mov ds:[bx], ax` 将 16 bit 数据存到 `ds:bx`

`mov byte ptr ds:[bx], 0` 规定 `ds:bx` 是一个指向 8 bit 数据的指针，相当于 C 中的强制类型转换 `*(char*)(ds:bx) = 0;`

- 指针修饰符有 `byte ptr`, `word ptr` 和 `dword ptr` 三种
- 指针修饰符只能修饰内存位置，不能修饰常数。例如 `byte ptr 0` 会报错。

#### assume

1. `assume ds:data` 的作用：告诉编译器把变量或标号的段地址替换成对应的段寄存器，但并不会对段地址进行赋值。
    - 编译后不会生成机器码，称为“编译指示语句”
    - 需要提前对 ds 进行赋值
    - 没有 assume 就无法使用 `[bx+3]` 的简略写法 ？？？
    - 同一个段名和多个段寄存器建立关联，选择寄存器的优先级为 `ds > es > ss > cs`，即 `assume ds:data, es:data` 相当于 `assume ds:data`
1. `assume cs:code` 的作用：告诉编译器把变量或标号的段地址替换成对应的段寄存器，但并不会对段地址进行赋值。
    - 允许存在多个 code 段
    - 没有 assume 就无法对代码段中的标号进行寻址
    - 不需要提前对 cs 进行赋值，即使程序运行途中 cs 发生改变（跳转到不同的代码段），cs 也会由程序自行修改。


#### 写入显卡内存实现程序输出

详见：
- 写入显存实现输出字符 printscr.asm & printscr.c
- 写入显存实现输出图形 prtshape.asm


### DOS Interrupt

#### getchar

`int 21h(AH=01h)`: 从 stdin 读取一个字符，保存在 AL 中，相当于 getchar()

```asm
mov ah, 1
int 21h
cmp al, 'A'
```

和 `int 16h(AH=00h)` 的区别
- 只能读取可见的字符
- 读取的字符会显示在屏幕上

#### putchar

`int 21h(AH=02h)`: 把 DL 中的数据输出到 stdout 中，相当于 putchar()

```asm
mov ah, 2
mov dl, 'U'
int 21h
```

#### exit

`int 21h(AH=4Ch)`: 结束程序，返回 AL 中的数值

```asm
exit:
    mov ah, 4Ch
    mov al, 0
    int 21h
```

#### keyboard interrupt

`int 16h(AH=00h)`：接收键盘输入，存在 AX 中（16 位编码），属于 BIOS 中断
`int 16h(AH=01h)`：检测键盘缓冲区是否为空，若为空则 ZF=1，非空则 ZF=0(zero flag，是 FL 寄存器中的一个 bit)

```asm
again:
    ; do something
    mov ah, 1
    int 16h     ; 检测键盘缓冲区
    jz no_key
has_key:
    mov ah, 1   ; 如果键盘缓冲区中有数据，则读取按键信息
    int 16h
no_key:
    jmp again   ; 如果键盘缓冲区为空，则重复执行缓冲区检测流程
```

## 工具

### Turbo C & Turbo Debugger

- turbo C 编辑 + 编译链接(tcc，16 位编译器) + 调试
    - windows + R -> command -> tc + 文件名
- turbo debugger(td)：只能调试 16 位 DOS 程序(.exe)
    - windows + R -> command -> td + 程序名(.exe)

1. 在 command 中用 `TD xxx.exe` 命令打开 exe 文件
2. TD 界面
    - 左上：汇编程序(cs)
    - 左下：内存空间(ds)
    - 右上：寄存器（例如: ax, bx）
    - 右下：栈空间
3. 设置断点：F2 在光标位置设置一个断点
4. 跟踪进入函数：F7
5. 搜索内存地址：选中左下角框 -> ctrl+g -> 输入内存位置的逻辑地址例如 `ds:0426`
    - 搜索代码地址同理：选中左上角框 -> ctrl+g -> 输入代码位置的逻辑地址例如 `cs:0426`
    - 并不一定要左上角显示代码，左下角显示数据，只是这样看起来比较舒服
6. 切换寄存器位数：
    - 右键 -> 可以切换 16 位和 32 位
    - ctrl+R
7. F9：运行程序
8. F4：运行到光标处暂停
1. alt-X：退出
1. alt+F5：显示 user screen（查看程序输出），然后 esc 返回 TD 界面。

### OllyDbg 调试 32 位可执行程序

==OllyDbg 打开 exe、设置断点、调试（运行到断点etc）、修改汇编代码==

1. F2：运行
2. 

### MASM32

编译汇编语言的集成环境

- D:\masm32\qeditor.exe
- open -> 选择 `sum.asm` -> project -> build all -> 32 位程序 `sum.exe`

### MASM

MASM是Microsoft Macro Assembler的缩写，是微软公司为x86微处理器家族开发的汇编开发环境，拥有可视化的开发界面，使开发人员不必再使用DOS环境进行汇编的开发，编译速度快，支持80x86汇编以及Win32Asm，是Windows下开发汇编的利器。

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

### Bochs 虚拟机

#### 用 bochs 虚拟机运行 dos 系统

1. bochs\bochsdbg.exe 双击启动系统
1. Load -> dos.bxrc -> Start 加载配置文件，启动虚拟机，虚拟机有三个窗口：
    - 在 console 窗口可以看到 bochs 运行的日志
    - bochs enhanced debugger 是 bochs 内置的调试器，是凌驾于虚拟机之上而不是嵌入在虚拟机中的，原则上可以设置无限多的硬件断点和软件断点
    - display 窗口就是虚拟机的命令行界面了
1. 点击 Continue，在 Display 界面看到 dos 的开机启动界面
    - 未点击 continue 时，bochs enhanced debugger 中 PC 停留在 `F000:0000FFF0` 位置处，该地址映射到 ROM 上，是开机启动代码
1. bochs\dos.img 点击即可查看 dos 镜像中的文件，可以直接把文件拖到里面。

tips：Bochs 虚拟机用解释的方式模拟执行指令。
- 可以调试 BIOS 启动的代码，可以调试 windows, linux 等系统
- 后续的保护模式代码需要在 bochs enhanced debugger 中调试
- 解释型虚拟机的难点：处理外界端口。比如键盘、显卡、硬盘，需要能够处理外部中断和进行读写，并且要支持多平台。
- 相似：游戏机的虚拟机，例如 wii 虚拟机。

tips：可以在 windows 物理机下运行，也可以在 XP 虚拟机的环境中运行 ~~（虚拟机里跑虚拟机）~~

#### 用 winimage 实现物理机和虚拟机交换文件

在 XP 虚拟机中：

安装好 winimage 后，双击bochs\dos.img可以自动打开dos虚拟机的硬盘镜像，然后就可以拖动鼠标把物理机的文件拖到dos.img\masm目录内，或者拖出来。

---

在 windows 10 中：

双击 winimage.exe 打开，把 dos.img 文件拖入 winimage 中，然后就可以通过拖动进行文件交换。

#### 使用 bochs enhanced debugger 设置断点

1. 首先点击 break 暂停虚拟机的运行，让 debugger 接管程序的运行
1. `watch r/w addr <len> <if> <cond>` 设置硬件断点
    - 注意 addr 只能使用物理地址
    - len 断点的长度，单位 byte
    - e.g. `watch w 0x67c3 1` 是 soft-ICE 中等会要设置断点的地址
1. 点击 continue 重新把控制权交给虚拟机
1. 当虚拟机对 watch 的地址执行写入操作时，bochs enhanced debugger 自动 break 并显示 `caught write watch point` 日志
    - ctrl+D 或者 view-disassemble，然后输入地址查看对应地址的汇编代码。触发断点的是高亮指令的上一条，例如 `mov byte ptr es:[ebx], cl`
    - 怎么找到被修改的地址呢？需要用到 gdt 表。例如上述指令写入的位置就在 `gdt[es] + ebx` 的位置
1. `info gdt` 显示 gdt 表，或者在 view 中找 gdt，快捷键 ctrl+F2
1. `info sr` 显示系统寄存器，gdtr 存储 gdt 表的地址。 `d gdtr + es` （代入数字）显示 `gdt[0x20]`。gdt 表的看法详见“保护模式”章节。

~~究极套娃：td 可以调试程序，soft-ICE 可以调试 td，bochs enhanced debugger 可以调试 soft-ICE~~

tips：使用 `help` 查看所有命令，`help watch` 查看命令的具体信息

### Soft-ICE 调试器

Bochs 虚拟机内置的调试器

#### 断点的分类

- 软件断点：software breakpoint，会把设置断点的指令首字节改为 `0CCh`，即 `int 3`，调试器运行程序到此处时会停住
- 硬件断点：hardware breakpoint，有三种类型（bpmp = breakpoint on memory byte）
    - `bpmp addr r`: 当 addr 地址处的变量值被读取时断
        - 硬件中实现的是 `rw`，即在读或者写的时候都断。然后在软件层面判断写之前的数据和写之后的数据是否相等，如果相等则判断为是被读访问。
    - `bpmp addr w`: 当 addr 地址处的变量值被写入时断
    - `bpmp addr x`: 当 addr 地址处的指令被执行时断

80386 以上的 cpu 设计了 dr(debug register)，在硬件上支持硬件断点，会把断点地址保存在 dr0, dr1, dr2, dr3 四个寄存器，再把断点条件保存在 dr6, dr7。所以硬件断点最多只能设置 4 个。

#### 使用 soft-ICE 调试 td & 设置硬件断点

1. ctrl+D：唤起 soft-ICE
1. 从上到下四个窗口：寄存器窗口、数据窗口、代码窗口、命令窗口
1. F5：print user screen
1. F8：执行一条指令
1. 在命令窗口中输入 `D cs:0` 在数据窗口中显示指定位置的数据（大小写不敏感）
1. 在命令窗口中输入 `bpmb 5386:3 w` 在指定位置设置硬件断点
    - 如果被调试程序执行了写指令，则会唤起 soft-ICE，并显示造成中断的写指令
1. 在命令窗口中输入 `BL` 查看已经设置的硬件断点
    - 显示 `BPMB 5387:0000 W C=01`，C 表示第几次写的时候触发中断
1. 在命令窗口中输入 `x` 或者直接 ctrl+D 回到被调试程序
1. 在硬件断点触发时，bochs 会自动唤起 soft-ICE，程序窗口中高亮代码的上一句就是触发断点的语句，例如 `mov es:[bx], al`
    - 可以在 soft-ICE 的寄存器窗口查看 es, ebx, eax 的值
    - 在命令窗口输入 `d es:bx` 数据窗口跳转到地址（可以直接使用寄存器中的值）
1. `bc 1` 清除第一个硬件断点，`bc *` 清除所有硬件断点
1. `bd 1` 或者 `bd *` （breakpoint disable）禁用断点，`be 1` 或者 `be *` （breakpoint enable）启用断点。禁用的断点在 `bl` 中显示，前面会打上星号标识

tips：soft-ICE 如何实现硬件断点？因为 bochs 是解释型的，所以可以在执行所有可能写入内存的指令时，都通过比较判断设置了硬件断点的位置有没有被写入。

#### 使用 soft-ICE 调试用户程序 exe & 设置软件断点

1. `ldr int3.exe` 用 soft-ICE 打开程序
1. 在命令窗口输入 `ec` 进入代码窗口，F2 在当前指令位置设置软件断点，再 F2 取消断点。再次输入 `ec` 回到命令窗口
1. 在命令窗口输入 `bpx 1234:5678` 在指定位置设置软件断点
1. 再次输入设置断点的指令去除软件断点，或者 `bc 1` 清除编号为 1 的软件断点，`bc *` 清除所有断点
1. F7 执行一条指令

#### 其他命令

1. `wc 8`, `wd 4` 调节代码窗口、数据窗口的长度
1. 在命令窗口中输入 `cls` 清除命令窗口屏幕
1. 上下箭头：调取指令历史记录

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
    - `ds:[bx+3]` 可以简化为 `[bx+3]`，ds 是隐含在 `assume ds:data` 中的。在编译过程中 `[bx+3]` 会先被转化成 `data:[bx+3]` 然后再转化成 `ds:[bx+3]`
3. ds：数据段寄存器，只接受寄存器赋值，不能用常数赋值。因为在硬件设计时被简化了
4. `assume ds:data` 的作用：告诉编译器把变量或标号的段地址替换成对应的段寄存器，但并不会对段地址进行赋值。
    - 编译后不会生成机器码，称为“编译指示语句”
    - 需要提前对 ds 进行赋值
    - 没有 assume 就无法使用 `[bx+3]` 的简略写法 ？？？
    - 同一个段名和多个段寄存器建立关联，选择寄存器的优先级为 `ds > es > ss > cs`，即 `assume ds:data, es:data` 相当于 `assume ds:data`
5. `assume cs:code` 的作用：告诉编译器把变量或标号的段地址替换成对应的段寄存器，但并不会对段地址进行赋值。
    - 允许存在多个 code 段
    - 没有 assume 就无法对代码段中的标号进行寻址
    - 不需要提前对 cs 进行赋值，即使程序运行途中 cs 发生改变（跳转到不同的代码段），cs 也会由程序自行修改。


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

### 理解内存的间接寻址方式

有以下的 C 结构体

```c
struct Node{
    char name[8];
    short int score;
}a[10];
```

需要用汇编语言获取 `a[2].score` 的值

```asm
mov ds, seg a       ; ds 是 a 的段地址
mov bx, offset a    ; bx 是 a[0] 和段首的偏移距离
mov si, 20          ; si 是 a[2] 和 a[0] 的偏移距离，即 sizeof(Node) * 2
mov ax, ds:[bx+si+8]    ; 8 是 a[2].score 和 a[2].name 的偏移举例
                        ; 最终获取 a[2].score
```

这个例子说明了间接寻址方式的必要性。

tips: 可以把 b 理解位 base，数组的首地址；i 理解为 index，数组元素的偏移量。



### 多个代码段之间的跳转 jump.asm

实验目的：了解 assume 语句的作用

1. jmp 和 call 指令分为 near 和 far 两种。不同代码段之间跳转需要加上 `far ptr` 支持段间跳转，否则会报错 `error A2064 Near jmp/call to different cs`
1. 跳转到其他代码段之后，cs 会自动修改。所以每个代码段只需要将自己的段名 assume 成 cs 就行了。

```asm
code1 segment
assume cs:code1
main1:
    mov ah, 2
    mov dl, '1'
    int 21h
    jmp far ptr main2 ; 会被编译成 code2:main2
code1 ends

code2 segment
assume cs:code2
main2:
    mov dl, '2'
    int 21h
    jmp far ptr main1 ; 会被编译成 code1:main1
code2 ends

end main1
```

### 检验软件断点对程序的更改 breakp.asm

主要思想是：用读取内存中数据的同样方法，读取代码段中的指令数据

程序现象：如果直接运行程序，会在终端中输出 `n`，如果在 break_point 处加上断点并调试，则会输出 `y`。

```asm
code segment
assume cs:code
break_point:
    mov ah, 2   ; 程序检测这句话上有没有设置断点
    mov al, byte ptr [break_point]
    cmp al, 0CCh
    jne no_break_point
have_break_point:
    mov dl, 'y'
    int 21h
    jmp done
no_break_point:
    mov dl, 'n'
    int 21h
done:
    mov ah, 4Ch
    mov al, 0
    int 21h
code ends

end break_point
```

tips: `[break_point]` 会首先被编译器转化为 `code:[break_point]` 然后根据 assume 转化为 `cs:[break_point]`。可以直接在程序中写明 `cs:[break_point]`，等价，但能够补充说明这是代码段中的标签而不是数据段中的变量。

tips: `byte ptr cs:[break_point]` 的含义是将 `cs:break_point` 强制类型转换为一个指向 8 bit 数据的指针，然后用 `[]` 取出其中的内容。所以最终效果就是取出了 break_point 处命令的第 1 个字节。

### 写入显存实现输出字符 printscr.asm & printscr.c

1. 终端的屏幕是一个 25 行 80 列的矩形，坐标 `(0, 0)` 到 `(79, 24)` 每个位置可以放一个字符
    - 通过显存显示字符不需要操作系统的支持，而是硬件中就实现好了的
1. 写入显存的代码
    ```asm
    mov ax, 0B800h
    mov es, ax
    mov bx, 0
    mov byte ptr es:[bx], 'A'
    mov byte ptr es:[bx+1], 74h ; 写一个白底红字的 A
    mov byte ptr es:[bx+2], 'B'
    mov byte ptr es:[bx+3], 72h ; 写一个白底绿字的 B
    ```
    - `0B800h` 是显存的段地址（文字模式），是一个常数值。`0A000h` 是图形模式的显卡段地址
    - (x, y) 坐标对应的偏移地址计算公式 `addr = (y * 80 + x) * 2`
    - `74h` 表示显示的颜色，高 4 位 7 表示前景色是白色，低 4 位 4 表示背景色是红色
    - `7` 的 4 个 bit 分别表示：
        1. 是否加强颜色：例如 0100 表示普通的红色，1100 表示增强的红色
        1. 红(R)
        1. 绿(G)
        1. 蓝(B)：例如 0111 表示白色，0000 表示黑色，0001 表示蓝色

---

p.s. 为什么显存会和内存地址一样使用逻辑地址进行寻址？

因为部分内存地址被 **映射** 到显存上，通过逻辑地址可以方便地访问显存。

在 dos 系统中：
- `0000:0000` ~ `9000:FFFF` 没有映射，就是 RAM，存储 dos 及用户程序，长度为 640KB
- `A000:0000` ~ `B800:FFFF` 映射到显存
- `C000:0000` ~ `F000:FFFF` 映射到 ROM

映射是在系统启动前，运行 ROM 中的 POST(power on self test) 代码的过程中完成的。
- p.s.s. ROM 中还固化了 BIOS(basic input output system)，比如 `int 10h` 和 `int 16h` 函数集就定义在 BIOS 中，分别负责屏幕输出和键盘输入。这两组中断函数无需依赖操作系统就能运行，控制操作系统启动前的键盘输入（选择开机选项等）、屏幕输出（开机信息等）。

---

程序功能：在屏幕上显示 2000 个白底蓝字的 A。
- 输入任意字符返回终端，输入 `cls` 清空屏幕

```asm

code segment
assume cs:code
main:
    mov ax, 0B800h
    mov es, ax      ; 段地址
    mov di, 0       ; 偏移地址
    mov al, 'A'     ; 填充字符
    mov ah, 71h     ; 填充颜色
    mov cx, 2000    ; 循环次数
again:
    mov word ptr es:[di], ax ; 同时写入了字符和颜色
                             ; 注意低 8 位写在前面，高 8 位写在后面
                             ; 'A' 在内存中排在前面，所以应该写到低 8 位 al
    add di, 2
    dec cx
    jnz again
exit:
    mov ah, 1
    int 21h         ; 等待输入一个字符
                    ; 否则直接退出程序，终端会写东西
    mov ah, 4Ch
    mov al, 0
    int 21h         ; 退出程序
code ends
end main
```

p.s. 可以用 C 语言实现上述代码
- `p = (unsigned char far *)0xB8000000` 获取显存地址
- 使用 `tc printscr.c` 进行编译链接

```c
#include <stdio.h>
int main()
{
    unsigned char far * p = (unsigned char far *)0xB8000000;
    int i;
    for (i = 0; i < 2000; ++ i){
        *p = 'A';
        *(p+1) = 0x71;
        p += 2;
    }
    getchar();
    return 0;
}
```

### 写入显存实现输出图形 prtshape.asm

1. 终端屏幕可以看成一个 320 列 200 行的矩形，坐标 `(0, 0)` 到 `(319, 199)`，每个坐标是一个像素点
    - 320 * 200 * 256 虽然分辨率不高，但是所有显存地址可以都放在一个段内，方便编程
1. 切换图形模式的代码
    ```asm
    mov ah, 0   ; int 10h 的 0 号功能：切换图形模式
    mov al, 13h ; 图形模式选择: 320 * 200 * 256 色
    int 10h     ; BIOS 中的函数
    ```
    - 其他图形 or 文本模式：
        - `al=12h`: 640 * 480 * 16 色模式，将每个像素的 4 bit 信息分别存在不同的段里。总共有 4 个段，每个段中使用 640 * 480 个 bit
        - `al=3`： 80 * 25 文本模式。**附带清屏效果**
        - 在 xp 桌面 - 中断大全中查找其他图形模式
1. 写入显存的代码
    ```asm
    mov ax, 0A000h
    mov es, ax
    mov byte ptr es:[0], 4 ; 画一个红色的像素点
    mov byte ptr es:[1], 2 ; 画一个绿色的像素点
    ```
    - `0A000h` 是图形模式的显卡段地址
    - (x, y) 坐标对应的偏移地址计算公式 `addr = y * 320 + x`
    - 4 和 2 表示要画的颜色，因为要画就是把整个像素点全部填满，所以只需要颜色信息
    - `7` 的 4 个 bit 分别表示：
        1. 是否加强颜色：例如 0100 表示普通的红色，1100 表示增强的红色
        1. 红(R)
        1. 绿(G)
        1. 蓝(B)：例如 0111 表示白色，0000 表示黑色，0001 表示蓝色
1. 显示图形的代码
    ```asm
        shl ax ; ax 里存的是图形的某一行内容
               ; 左移之后将要输出的位被移到了溢出位，可以通过 jnc 检查溢出
        jnc no_dot
    is_dot:
        ; 画点
    no_dot:
    ```

---

程序功能：在屏幕正中间画一个 160 * 100 的红色矩形。

```asm
code segment
assume cs:code
main:
    mov ah, 0   ; int 10h 的 0 号功能：切换图形模式
    mov al, 13h ; 图形模式选择: 320 * 200 * 256 色
    int 10h     ; BIOS 中的函数
    mov ax, 0A000h
    mov es, ax
    mov di, 16080 ; 左上角点坐标 (80, 50)，偏移地址
    mov cx, 100
col_loop:
    push di
    mov ax, 160
row_loop:
    mov byte ptr es:[di], 4
    inc di
    dec ax
    jnz row_loop
    pop di
    add di, 320
    dec cx
    jnz col_loop
exit:
    mov ah, 1
    int 21h         ; 等待输入一个字符
                    ; 否则直接退出程序，终端会写东西
    mov ah, 0
    mov al, 3
    int 10h         ; 切换回文本模式，不然返回终端之后屏幕就花了
    mov ah, 4Ch
    mov al, 0
    int 21h         ; 退出程序
code ends
end main
```

### 播放动画 & 键盘控制 pushblk.asm

控制播放速度的方法：

1. 使用循环进行延时，控制动画播放速度
1. 使用时钟中断控制动画播放速度

处理键盘控制的方法：使用 BIOS 的键盘中断

---

补充知识点

1. 多线程 & 多进程
    - 多线程：同个程序多个函数同时执行。线程的分配由程序决定
    - 多进程：cpu 同时执行多个程序。进程的分配由操作系统决定

---

程序功能：使用上下左右键控制屏幕上的方块进行移动

```asm
data segment
x dw 0
y dw 0
data ends

code segment
assume cs:code, ds:data

; 函数功能: 将 cx 中存的字符数据显示在 (x, y) 位置
func_draw:
    ;根据(x,y)计算bx
    ;bx=(y*80+x)*2
    mov ax, [y]
    mov bp, 80
    mul bp; dx:ax = ax*bp, 其中dx=0
    add ax, [x]; ax=y*80+x
    add ax, ax ; ax=(y*80+x)*2
    mov bx, ax
    mov es:[bx], cx
    ret

main:
    mov ax, data
    mov ds, ax
    mov ah, 0
    mov al, 3
    int 10h; 能达到清屏的效果
    mov ax, 0B800h
    mov es, ax
draw:
    mov cx, 1720h
    call func_draw  ; 画一个方块
check_key:
    ;刷新屏幕的画面
    mov ah, 1
    int 16h
    jnz has_key
    jmp check_key
has_key:
    mov cx, 0020h   ; 用黑色填充
    call func_draw
    mov ah, 0
    int 16h
    cmp ax, 4800h
    je is_up
    cmp ax, 5000h
    je is_down
    cmp ax, 4B00h
    je is_left
    cmp ax, 4D00h
    je is_right
    jmp exit
is_up:
    cmp [y], 0
    je check_key
    dec [y]
    jmp draw
is_down:
    cmp [y], 24
    je check_key
    inc [y]
    jmp draw
is_left:
    cmp [x], 0
    je check_key
    dec [x]
    jmp draw
is_right:
    cmp [x], 79
    je check_key
    inc [x]
    jmp draw
exit:
    mov ah, 4Ch
    int 21h
code ends
end main
```