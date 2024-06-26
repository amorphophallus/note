# 计算机组成与设计

[TOC]

## intro

1. 课程内容 ![Alt text](./imgs/CO_schedule.png)
2. 分数组成
    - Theory (70%)
        - Homework + Quiz 20%: Late submission get 10% off for each 3 days. No late than 6 days 
        - Midterm test 10%: 进度到 5.4 A Simple Implementation Scheme
        - Final Examination 40%: English, Close-book test with one A4 memo.
    - Lab assignments (30%)
3. reference
    - [实验指导](https://guahao31.github.io/2023_CO/)
    - verilog 学习资料
        - [菜鸟教程](https://www.runoob.com/w3cnote/verilog-tutorial.html)
        - [HDLBits](https://hdlbits.01xz.net/wiki/Main_Page)
        - 参考阅读中的 `Verilog-2012.pdf`: 波形测试没有任何问题，但是下板现象并不符合波形。可能的问题参见 ppt 17 - 31 页 [slides repo](https://github.com/Guahao31/for_Computer_Logic/tree/master/slides)
    - 绘制有限状态机图：[FSM designer](https://madebyevan.com/fsm/)
    - [马德 2021 计算机组成](https://classroom.zju.edu.cn/coursedetail?course_id=38071&tenant_code=112)
    - [RISC-V 在线指令翻译器](https://venus.cs61c.org/)

## chapter 1 Computer Abstractions

1. Eight Great Ideas
    - Design for Moore's law：根据设计流程长度，硬件设计需要适配几年后的晶体管大小
    - Use Abstraction to Simplify Design：分层，隐藏复杂度
    - Make the Common Case Fast
        - Amdahl's Law：当提升系统的一部分性能时，对整个系统性能的影响取决于:1、这一部分有多重要 2、这一部分性能提升了多少。以下公式通过计算*同一个程序*的运行时间提升来表示性能的提升。
            $$
            Speedup_{overall}=\frac{ExecTime_{old}}{ExecTime_{new}}\\
            =\frac1{((1-Fraction_{enhanced})+\frac{Fraction_{enhanced}}{Speedup_{enhanced}})}
            $$
    - Performance via Parallelism
    - Performance via Pipeline
    - Performance via Prediction：预测 CPU 行为的结果并提前进行下一条指令。在大规模循环逻辑中要尽量避免数据强依赖的分支(data-dependent branching). [阅读材料](https://zhuanlan.zhihu.com/p/22469702)
    - Hierarchy of Memories
    - Dependability via Redundancy：增加冗余保证可靠性，以防某台机器出错
2. 集成电路(integrated circuit)
    - 术语
        - wafer: 晶圆
        - die: 晶粒。die area 取决于电路设计需要。
        - chip: 芯片
        - yield: 良品率；defect rate: 缺陷率。
    - 制造流程：硅 -> 晶圆 -> 切割 -> 晶粒 -> 封装 -> packaged dies -> 芯片
    - 价格：晶粒越大缺陷率也会相应提升，且晶圆边缘浪费的材料增加 ![Alt text](./imgs/CO_integrated_circuit_cost.png)
3. 性能(performence)
    - 指标
        - response time
        - throughput: 吞吐量，即做的总工作量
    - 运行时间衡量指标
        - elapsed time: 程序运行的持续时间。在单核处理器的情况下，Elapsed Time = Cpu Time + Wait Time。在多核处理器的情况下，由于多个CPU同时处理任务所以可能会出现Cpu Time 大于Elapsed Time 的情况。
        - CPU time：进程所占用的处理器时间
    - CPU time 影响因素
        - clock cycle time(=1/clock rate)
        - CPI(Cycles per instruction)
            - weighted average CPI
            - 每条指令的执行时间不一样，CPI 取决于程序使用了哪些指令。与程序、编译器有关，与硬件无关。
        - MIPS(millions of instructions per second): CPI & MIPS varies between programs on a given CPU.
        - 举个例子![Alt text](./imgs/CO_CPU_time.png)
        - SPEC CPU benchmark: benchmark 是 CPU 性能测试，SPEC 是一家公司的测试标准（使用广泛）
    - three walls
        1. Power Wall: CMOS IC power = capacitive load * voltage $^2$ * frequency
            - low load -> low voltage
        2. Memory Wall
        3. ILP(instruction level parallelism) Wall: 

## chapter 3 ALU 设计

### 数字表示

1. two's biased notation: 在 two's complement 的基础上偏移一个固定的常数，不同的标准偏移常数不同。
    - $[X]_b=[X]_c+biased$ 如果偏移 $2^n$ 就是把符号位取反，IEEE754 标准偏移 $2^n-1$
2. sign extension: 把符号位填充到空位里
3. 比较运算
    - 对有符号和无符号整数需要不同的命令，因为相同的两个二进制数在有符号和无符号的情况下大小关系不同
    - signed integer
        - slt: set when less than
            - e.g. `slt rd, rs, rt` 如果 rs 小于 rt 就把 rd 置 1，否则置 0。
        - slti: set when less than immediate
    - unsigned integer
        - sltu
        - sltiu

### 算术运算

1. overflow
    - 溢出处理流程：
        - ALU硬件检测
        - Generation of an exception
        - Save the instruction address(not PC) in SEPC(special exception program counter)
        - Jump to specific routine in PC
    - 溢出判断条件：O = (A 的符号位 $\oplus$ Result 的符号位) & (B 的符号位 $\oplus$ Result 的符号位 $\oplus$ $sub / \overline{add}$)，O 为 1 表示有溢出 ![Alt text](./imgs/CO_overflow.png)
3. 逻辑运算
    - logical shift: sll / srl / slli / srli
        - 全称：shift left logical immediate
        - e.g. `slli x11, x9, 3` 表示 `x11=x9<<3`
    - and / or / xor, etc

**tips. 有符号整数的表示方法**
- sign-magnitude: 原码
- 2's complement: 补码
- saturating arithmetic: 只要有溢出就固定在最大值或者最小值的计算方法

### 加法器优化

1. 行波进位加法器
2. Carry Lookahead Adder
3. Carry Skip Adder：模块内用 carry lookahead，模块外用行波进位。是运行速度和硬件复杂度的折中方案。 ![Alt text](./imgs/CO_CSA.png)
4. Carry Select Adder：高位把 carry 是 0 和是 1 的情况都先做了，最后选一个输出，用空间换时间。 ![Alt text](./imgs/CO_CSA_.png)

### 初级 ALU 组件

功能：

1. and
2. or
3. add
4. subtract
5. compare：Binvert 和 CarryIn 设置成减法。把 Result 最高位传到最低位输出（ *如果有溢出则需要取反，详见上方溢出情况表* ）
6. overflow detection：需要 A，B，Result 的最高位（符号位作为输入）
7. zero detector：给 compare 增加一个判断相等的功能，只需要加一个大的或非门就行了。

最高位的模块比普通位多一个溢出检测：

![Alt text](./imgs/CO_ALU_mostsignificant.png)

行波进位 ALU 整体结构，可以看到 compare 从最高位到最低位的数据传输：

![Alt text](./imgs/CO_ALU_simplemodel.png)

### 乘法器优化

参考：

1. [wikipedia: booth algorithm](https://en.wikipedia.org/wiki/Booth%27s_multiplication_algorithm#How_it_works)
2. [博客园: 补码一位乘](https://www.cnblogs.com/xisheng/p/9260861.html#:~:text=%E8%A1%A5%E7%A0%81%E4%B8%80%E4%BD%8D%E4%B9%98%E6%B3%95%E8%BF%90%E7%AE%97%E8%A7%84%E5%88%99%20%281%29%20%E5%A6%82%E6%9E%9C%20yn%20%3D%20yn%2B1%EF%BC%8C%E9%83%A8%E5%88%86%E7%A7%AF%20%5B%20zi,%E5%A6%82%E6%9E%9C%20yn%20yn%2B1%20%3D%2010%EF%BC%8C%E9%83%A8%E5%88%86%E7%A7%AF%E5%8A%A0%5B%20-%20x%5D%E8%A1%A5%EF%BC%88%E6%88%96%E5%87%8F%20%5Bx%5D%E8%A1%A5%EF%BC%89%EF%BC%8C%E5%86%8D%E5%8F%B3%E7%A7%BB%E4%B8%80%E4%BD%8D%EF%BC%9B)
3. [CSDN: 补码一位乘](https://blog.csdn.net/qq_43355372/article/details/100540759)

笔记：

1. 基础版 ![Alt text](./imgs/CO_multiplierV1.png)
2. 优化 1：因为每次只对 32 个 bit 做加法， ALU 的位数可以减半![Alt text](./imgs/CO_multiplierV2.png)
3. 优化 2：multiplier 右移且最低位丢弃，最高位无意义，所以可以把 Product 和Multiplier 的寄存器拼在一起，节省一半空间 ![Alt text](./imgs/CO_multiplierV3.png)
4. 有符号数乘法基础版：取出符号位，转化为无符号数乘法
5. Booth 算法：
    - **性质 1**：负小数的补码和原码换算（不包含符号位）
        - 方法1：整数部分取反加一，小数部分直接加。
        - 方法2：左移转换为整数，取反加一，再右移回去
        - e.g. 假设 $z$ 有 n 位整数 m 位小数，$z=-(2^n-[z]_{补整})+[z]_{补小}=-(2^n-[z]_{补整}-[z]_{补小})=-(2^n-[z]_{补})=-(2^{n+m}-2^m*[z]_{补})*2^{-m}$
    - **推论 1**：若纯小数 $z$ 的补码为 $z_0.z_1z_2\dots z_n$，其中 $z_0$ 是符号位，则 $z=-z_0+0.z_1z_2\dots z_n$
    - **性质 2**：负数 x 补码右移 1 位的结果为 `x/2`（右移使用 sign extension）；负数 x 补码左移 1 位的结果为 2x；减去 x 的补码相当于加上 $-x$ 的补码。对于正数来说上述结论显然成立。
    - **推论 2**：一个数 $x\in\mathbb{Q}$ 的补码 $[x]_{补}$ 乘以一个数的真实值 $z\in\mathbb{Q}$ 为结果 $xz$ 的补码。
        - 原因是：把 z 进行二进制拆分 $z=\sum_i z_i 2^i, z_i\in\{-1, 0, 1\}$，对于每一个项，把 x 进行移位后与 $z_i$ 相乘，可以保证移位和乘法过后的值是结果的补码，最后把所有结果相加，仍保证是补码。
    - **结论**：一个带符号位的数 $x$ 和一个带符号位的纯小数 $z$ 相乘，结果的补码为 $[xz]_{补} = [x]_{补} * (-z_0 + \sum_{i=1}^n z_i 2^{-i})$
    - **推广**：两个 n 位（包含符号位）的整数相乘，结果的补码为 $[x]_{补} * (-z_{n-1}) * 2^{n-1} + [x]_{补} * (z_{n-2}z_{n-3}\dots z_0)$
    - **优化**：用 $2^n-2^m$ 的形式代替一堆连续的 1，即从低位向高位扫描，如果当前位 `cur` 和低一位 `last` 是 10 则做减法，是 01 则做加法。并且这种方法不用特判最高位，看起来非常优美。
6. fast multiplication：multiple adders 空间换时间

tips：booth 算法快速理解。首先 x 的补码乘以 y 的实际值等于 xy 的补码。然后 y 的实际值可以通过 y 的补码计算：y 的补码除了符号位之外的其他位减去符号位，即 $-y_{n-1}+y_{n-2}y_{n-3}\dots y_0$。

tips：booth 算法的实现。可以使用和 V3 相同的优化，只需要一半位数的 ALU，但是必须要保证 ALU 可以做减法，结果右移时做 sign extension。

### 除法器优化

1. 基础版
    1. check for 0 divisor
    2. 把 divisor 从高位不断右移，用 Remainder 减去 Divisor 如果得到负数就重新加回去，以下为 7/2 的例子 ![Alt text](./imgs/CO_divisorV1.png)
2. 优化 1：Divisor 不动，Remainder 左移，ALU 位数减半
3. 优化 2：Remainder 左移一位后最低位无意义，可以用于存放商，省去商的寄存器空间 ![Alt text](./imgs/CO_divisorV3.png)
4. 有符号数除法：**要求 Remainder 与 Dividend（被除数） 符号一致**
5. fast division：SRT 除法（查表）

### 浮点数

#### IEEE745 标准

- 存储格式（注意 bias） ![Alt text](./imgs/CO_IEEE_Floating_point.png)
- 表示范围（注意排除保留的 exponential）![Alt text](./imgs/CO_floating_point_range.png)
- denormal number
    - exponential 全 0：存储极小值 ![Alt text](./imgs/CO_floating_point_zero.png)
    - exponential 全 1：无穷和 NaN ![Alt text](./imgs/CO_floating_point_nan.png)

**tips. 溢出的分类**
- overflow: 数值超过上界或者下界
- underflow: 数值绝对值太小不能表示

#### 浮点数加法

算法流程：

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-15%20105719.png)

硬件实现：
- Control 根据 ALU 中 exponent 大小比较的结果，选择大的那个作为结果，并把小的 significand 进行右移

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-15%20105812.png)

举例：

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-15%20110135.png)

#### 浮点数加法器的实现

[参考博客](https://blog.csdn.net/qq_44837820/article/details/122535692)

**实现的加法器功能：**

1.	操作数是单精度浮点数
2.	处理不规则浮点数的方法：
    1. 如果较大数为inf或者nan就直接输出较大数
    1. 如果较小数为极小值，就忽略这个数，直接输出较大数
3.	舍入处理：舍去的位为0就舍掉，舍去的位为1就进位


**整体思路：**

1.	用组合逻辑实现对阶、加法等操作；用时序逻辑实现移位
2.	先找出绝对值更大的数，这样做的好处是：首先符号就可以定下来了；其次只需要对较小数进行移位，省掉一半的移位电路。

p.s. 也可以用组合逻辑实现移位，只要用mux判断结果最高位移到小数点前需要多少步就行了，这样的话整个浮点数加法器就不需要输入时钟了。但最终没有实现这种全组合逻辑的，因为最开始被ppt上模块输入的clk迷惑了，以为不用时序不行。

**实现细节：**

1.	第0个时钟周期：
    1. 检查不规则浮点数
    1. 比较大小：把指数和尾数连在一起当作一个无符号二进制数比大小，选出较大数和较小数（这样如果两个操作数阶数相等，则选出的较大数是尾数较大的那个，保证选出的较大数的绝对值大于等于较小数的绝对值）。
    1. 取出尾数，补上前导1
    1. 浮点数对阶：较小数右移，移动位数为指数之差；较大数不动（在补的1前面再放一个前导0，因为较大数绝对值更大，所以溢出最多只会溢出到前1位）。
    1. 符号处理：结果的符号一定为较大数的符号。如果两个操作数的符号不同，就把较小数取反，否则较小数不变。
    1. 做加法。如果前导0变成1了就右移一位，指数加一，做进位；否则不动。去除最高位把结果送到normalization的电路。
2.	第1到n个时钟周期：
    1. 如果最高位不是1，指数减一，尾数左移。
    1. 如果最高位是1，退出循环。
3.	输出
    1. 如果较大数为inf或者nan就直接输出较大数
    1. 如果较小数为极小值，就忽略这个数，直接输出较大数


#### 浮点数乘法

算法流程：
- 步骤 1 中 exponent 相加需要减去 bias
- 步骤 3 中一定是右移，因为两个大于等于 1 的数相乘一定大于等于 1
- 除法的流程和乘法类似

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-15%20110238.png)

硬件实现：

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-15%20110705.png)

举例：

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-15%20110730.png)

#### RISC-V 中的浮点数

浮点数寄存器
- 浮点数运算使用专门的浮点数寄存器
- 寄存器为双精度，单精度数存在低 32 bit
- 有专门存常浮点数的寄存器，因为使用频繁，可以加速运算，如 x0 存 0

#### 精度控制

1. 4 种 round mode ![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-15%20112535.png)
    - round to nearest even: `x.5` **有一半概率向上取整，一半概率向下取整，尽可能减少 rounding 对结果造成的误差**
2. 运算过程中的 3 个 extra bit
    - guard & round: 在有效数字之后再多存两位 ~~（感觉 round 位意义不大）~~
    - sticky: 在 guard & round 右边非零就存 1，全 0 就存 0，用于区分 `x.5000000` 和 `x.5000001` 的进位 
    - 举个例子：**round to the nearest even**，`0.grs` 大于 0.5 就向上进位，小于 0.5 就向下取整，如果等于 0.5 就往最近的偶数取整。
    ![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-15%20113257.png)

## chapter 2 RISC-V 指令

### Instruction Characteristics

- 指令只能对寄存器进行运算，除了 Load 和 Store 之外别的指令都不访问 Memory
- 等长指令（RISC 一般定长，CISC 不定长）
- 补：指令（程序）和数据一样，都以二进制数形式存在内存中

处理器内部的数据存储形式 * 3（不包含 memory）

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-15%20164018.png)

指令的操作数类型：
- `x-x` 表示 operands 中有哪些类型，例如 register-register 表示只对寄存器内的数据进行运算

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-15%20164129.png)

### 操作数(operand)类型

- register operand
- memory operand
    - little endian
    - memory alignment：同一个数据尽量对齐放在同一个 word(4 Byte) 里
- immediate operand: *make common case faster*
    - **立即数是有符号整数**



**RISC-V 中的寄存器 & 内存地址：**
- 如果 preserved on call 为 yes，子函数必须保证函数返回时这些寄存器的值和进入函数时一样；如果 preserved on call 为 no，父函数必须自行保存这些寄存器的值，子函数可以随意调用。[这篇文章里有解释和具体例子](https://danielmangum.com/posts/risc-v-bytes-caller-callee-registers/)
- **寄存器位数为 64 位**
- **一个内存地址存 1Byte 数据**，所以数组的偏移地址需要数组编号再乘上数组元素长度

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-15%20164620.png)

大小端：

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-15%20165017.png)

### 指令格式(format)

1. R-format ![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-20%20081956.png)
1. I-format ![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-20%20082214.png)
    - 立即数是有符号数，所以只有 `addi` 没有 `subi`
1. S-format ![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-20%20082538.png)
    - sd 的例子中，偏移量 `S_imm` 是由两段立即数和符号拓展组成的
    - 把 x9 中的内容存到 x22 中所存基地址偏移 S_imm 个地址的位置

需要掌握：
- 汇编
- 反汇编：根据机器码（32 位二进制数）写汇编代码


#### 所有指令格式

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-20%20083308.png)


#### 常用指令表

- 表格中的横线划分了不同的 opcode，opcode 大致决定了指令的格式，funct3 和 funct7 补充判定指令类型

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-20%20083714.png)

**encoding**，包含一部分 RV64I 的指令

![计组](./imgs/2023-04-18-10-56-27.png)

### 指令具体介绍

#### logical instructions

- 右移分为逻辑右移 `srl` 和算数右移 `sra`，前者 zero-extention, 后者 sign-extention
- AND 指令可用于实现掩码(mask)
- 没有 NOT 指令，用 `xori x1, x1, -1` 实现（x1 和立即数 -1 异或存到 x1 里）

**tips. 立即数会进行符号拓展！所以 xori -1 可以对所有位都取反**

#### branch instructions

- `blt` 和 `bltu` 的区别：带 u 的表示把用于比较的数看成无符号数
- 分支跳转语句可以实现：if-else, switch-case, 循环
- **寻址方式：PC-relative**，PC + offset

e.g. 用无符号数大小比较来同时判断上界和 0 下界

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-29%20103406.png)

##### 分支语句的寻址 Branch Addressing

**注意** B-type 和 J-type 的寻址只能找到偶数，地址最后一位补 0

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-29%20171501.png)

![计组](./imgs/2023-03-29-18-03-03.png)

##### 利用 jal 和 jalr 实现更远距离的条件跳转

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-29%20171726.png)

#### procedure call instructions

##### 命令

1. jal x1, ProcedureAddress(Label): jump to 
ProcedureAddress and write return address to x1
1. jalr x0, 0(x1): branches to the address stored in 
register x1 and write return address to x0

tips：

- `jal` 和 `bne x0, x0, NEXT` 的区别：都表示无条件跳转，区别在是否保存 PC，前者用于实现函数跳转(jump and link)
- x1 常用于保存函数返回地址(return address)
- x10 到 x17 常用于传参和返回值，属于 temporary register

##### preserved(saved) 和 not preserved(temporary)

如果 preserved on call 为 yes，子函数必须保证函数返回时这些寄存器的值和进入函数时一样；如果 preserved on call 为 no，父函数必须自行保存这些寄存器的值，子函数可以随意调用。

##### 栈里存了哪些数据？

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-29%20142928.png)

- fp 的作用：快速恢复 sp，一般会被优化掉

##### 堆里存了哪些数据？ & Memory Layout

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-29%20143724.png)

##### e.g. 函数调用例子：计算阶乘

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-29%20111633.png)

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-29%20112512.png)

- 为什么 x10 需要保存但是在返回时不需要恢复? 因为 x10 同时作为函数参数 n 和返回值的寄存器，在进入函数之后需要保存 n 用于后续的计算，在返回之前需要把计算结果存在 x10 里。
- 为什么 x1 需要保存，但只在第二个分支里需要恢复，在第一个分支里不需要恢复？因为第二个分支在返回前递归调用了函数，导致 x1 被修改，需要从栈里恢复；但是进入第一个分支的函数是一个 leaf procedure，可以省去恢复 return address 的步骤。
- sp 和 ra 是 preserved register 因为这两个寄存器在进入函数和函数返回时值永远相同。
- 为什么保存一个寄存器 sp 偏移 8 位？因为寄存器为 64 位，一个内存地址存储 1 个 Byte。

##### e.g. 函数调用例子：复制字符串(strcpy)

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-29%20114755.png)

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-29%20114810.png)

- 优化 1：不需要用寄存器存 i，只需要地址累加就行了
- 优化 2：优先使用 temporary register，再使用需要保存的 register，减少内存读写
- `jal x0, L1` 和使用 `beq x0, x0` 的无条件跳转是一样的，因为 x0 有写保护永远是 0
- 补充知识点：字符编码(ASCII, Latin-1, Unicode)，字符串编码(结束符，存长度)

##### e.g. 用 `jalr` 实现远距离跳转，或者跳转到不固定的位置

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-29%20103736.png)

- 实现 switch-case 语句

##### 编译器的 Basic Block 优化

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-29%20104541.png)

#### compare operations

- `slt, slti, sltu, sltiu`，把比较结果(0 / 1) 保存到 rd 里
- 注意：相同的数据，看成有符号数和无符号数比较大小结果不同，例如 -1 和 1 比较大小。

#### load & store

##### 基址寻址方式

- 易于实现数组元素寻址
- `ld $x6, 0(x5)` 把 x5 所存的地址，偏移 0 Byte，把值 load 到 x6 里

**tips. 立即数是有符号数**

e.g. 读取数组元素值

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-15%20165311.png)

##### 命令

根据数据长度、有无符号（使用 zero-extension 或者 sign-extension）分类

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-29%20113751.png)

##### 立即数拓展

- U-type: 用于填充 32 位数据的高 20 位
- `lui`: Load upper immediate , load a 20-bit constant into bits 12 through 31 of a register

通过 lui 和 addi 指令将一个 32 位立即数填充到寄存器中

##### RISC-V 寻址方式总结

![计组](./imgs/2023-03-29-19-50-23.png)

#### parallelism & sychronization (原子指令)

指令：

1. `lr.d`: load-reserved doubleword
1. `sc.d`: store-conditional doubleword

![计组](./imgs/2023-03-29-19-57-23.png)

### 从高级语言程序到运行可执行文件

#### 全过程

![计组](./imgs/2023-03-29-20-09-54.png)

#### Object

目标文件，包含以下 6 部分

![计组](./imgs/2023-03-29-20-14-21.png)

![计组](./imgs/2023-03-29-20-14-36.png)

一个示例的 object

![计组](./imgs/2023-03-29-20-15-58.png)

#### Linking

将多个目标文件间组合起来，3 个步骤：

1. Place code and data modules symbolically in memory.
2. Determine the addresses of data and instruction labels.（完善 relocation information，替换指令中的地址）
3. Patch both the internal and external references.

例子：

![计组](./imgs/2023-03-29-23-01-29.png)

动态链接：Only link/load library procedure when it is called

e.g. dll: dynamic link library 动态链接库

e.g. JVM: Java 代码运行在虚拟机里，保证了 Java 的强可移植性

#### Loading

1. Reads the executable file header to determine size of the text and data segments.
2. Creates an address space large enough for the text and data.
3. Copies the instructions and data from the executable file into memory.
4. Copies the parameters (if any) to the main program onto the stack.
5. Initializes the processor registers and sets the stack pointer to the first free 
location.
6. Branches to a start-up routine that copies the parameters into the argument registers and calls the main routine of the program. When the main routine returns, the start-up routine terminates the program with an exit system call.


### 其他

e.g. Sort

书 2.13 节，135 页

![计组](./imgs/2023-03-29-23-16-20.png)

![计组](./imgs/2023-03-29-23-14-31.png)

p.s. 数组和指针的区别：指针寻址比数组寻址更直接，数组寻址需要用基地址加上偏移地址。例如：比较两种数组清零的方法。

p.s. 指令集分类：RV64I, RV32I, RV64M, RV64A, ...

兼容基础指令的基础上加上新的特性。

![计组](./imgs/2023-03-29-23-38-07.png)

p.s. 一些规律：powerful instruction 不等于 higher performance, 比如说 x86。市场成功的指令集不一定最高效简洁，比如 x86。

## chapter 4-1 单周期 CPU

### 4.1 Introduction

![计组](./imgs/2023-04-03-08-20-15.png)

- 单周期：所有的指令时间都是一个时钟周期（clock cycle就会很长）
- 多周期：更灵活
---

- 指令执行的过程
- 指令执行过程中 ALU 的作用

![计组](./imgs/2023-04-03-08-21-28.png)

---

datapath 的基本部件

![计组](./imgs/2023-04-03-08-37-19.png)

- memory 分为 instruction memory(只读，用 ROM 实现) 和 data memory(读写，用 RAM 实现)，是为了单周期处理器在同一个周期内进行取指令和读写内存。
- 立即数生成器的输入就是整条指令，内部会根据指令类型把零散的立即数拼起来并进行 sign-extension 后输出。
- ALU 最好增加输出口：zero，方便 branch 指令相等不相等的判断。overflow，方便大小判断。

![计组](./imgs/2023-04-03-09-06-15.png)

---

controller 的作用：选择数据通路

![计组](./imgs/2023-04-03-09-11-35.png)

### 4.3 单周期 datapath

1. critical path：延时最大的路径，参见书 P469 ex 4.7
1. 完整 ALU：书 P344 fig 4.21

### 4.4 单周期 Control Unit

1. ALUop：控制 ALU 的初步信号，书 P342 fig 4.18

### 中断和异常 Interrupt & Exception

#### 定义

- Interruption 一般指外部设备通过 I/O 打断当前程序的运行
- Exception 一般指 CPU 内部发生错误打断当前程序的运行

#### 异常处理流程

1. 保存 CPU 现场：
    1. 保存当前 PC (mEPC 寄存器)
    1. 保存发生异常的原因 (mCAUSE 寄存器)
    1. 其他信息，一般不用 (比如：Exception code field: 2 for undefined opcode, 12 for hardware malfunction, ...) 
1. 执行异常处理程序 (handler)
1. 如果能够恢复运行则返回原 PC 继续执行 (mRET 指令退出，读取 mEPC 中保存的 PC)，否则退出运行并报告错误（使用 mEPC, mCAUSE, etc）

#### RISC-V 的特权结构

![CO](./imgs/2023-05-23-20-19-13.png)

- reserved 可以是 hyper-mode，给虚拟机使用
- 每个特权级别有自己的 ISA，只提供给某特权模式使用

#### 特权寄存器 CSR

- CSR：Control Stauts Register
- 总共 4096 个

中断相关的 CSR：

![CO](./imgs/2023-05-23-20-10-10.png)

#### 特权指令 CSR instruction

CSR instruction：只能在 machine mode 下运行

指令格式：

![CO](./imgs/2023-05-23-20-25-37.png)

常用指令：

![CO](./imgs/2023-05-23-20-48-12.png)

1. CSRRW(read & write): `rd = csr, csr = rs1`
1. CSRRS(read & set): `rd = csr, csr |= rs1`
1. CSRRC(read & clear): `rd = csr, csr &= ~rs1`
1. CSRRWI, CSRRSI, CSRRCI: 使用立即数

![CO](./imgs/2023-05-23-20-53-27.png)

1. wfi = wait for interrupt

#### 重要特权寄存器——mstatus(0x300)

![CO](./imgs/2023-05-23-20-27-44.png)

1. MIE, SIE, UIE: 中断使能(interrupt enable)，分别控制 machine mode, supervisor mode, user mode
    - 例如：在进入中断之后，同级或者低级的中断不能打断当前中断处理程序，但是高级的可以
1. MPIE, SPIE, UPIE：存储先前的中断使能，用于中断嵌套中保存程序运行状态
1. MPP：执行中断之前处在什么运行状态

![CO](./imgs/2023-05-23-20-34-23.png)

#### 重要特权寄存器——mie & mip(0x304/0x344)

![CO](./imgs/2023-05-23-20-34-45.png)

- 使能不同类型的中断：外部中断、软件中断、时钟中断

#### 重要特权寄存器——mtvec(0x305)

![CO](./imgs/2023-05-23-20-36-00.png)

- 存储中断向量的基地址 + mode
- 两种中断模式：
    1. direct
    1. vectored: 中断向量中，每种中断只存一句指令，可以跳到真正的 handler

#### 重要特权寄存器——mcause

![CO](./imgs/2023-05-23-20-41-49.png)

- 最高位 INT 表示是中断还是异常
- exception code 和 mtvec 一起用于计算 handler 地址

一些常见的异常原因：

![CO](./imgs/2023-05-23-20-43-23.png)

#### 如何处理异常

1. 增加检测逻辑
1. 增加控制信号（修改 CSR）
1. 增加写入 CSR 的数据通路
1. 判断使能信号，跳转到异常处理程序
1. 返回中断的位置继续执行

![CO](./imgs/2023-05-23-20-58-41.png)

![CO](./imgs/2023-05-23-21-09-02.png)

![CO](./imgs/2023-05-23-21-09-22.png)


## chapter 4-2 流水线 CPU

### 4.5 Pipeline intro

单周期 CPU 有什么缺点？

1. 时钟周期长
1. 吞吐量（throughput, 单位时间执行的指令数量）小
1. 资源（内存、寄存器）利用率低

流水线加速比的计算？理想状态下（各个阶段延迟相同etc），指令个数足够多，加速比等于分的阶段个数

单周期 CPU 分阶段：
- 从左往右的（黑色箭头）可以分阶段在流水线中执行，从右往左（蓝色箭头）可能使流水线出错（数据冒险, hazard）
- **五个阶段**：
    1. IF：取指令
    1. ID：指令解码 & 读寄存器
    1. EX：计算结果 / 计算跳转
    1. MEM：读写数据内存
    1. WB：写回寄存器

![计组](./imgs/2023-04-26-11-01-36.png)

流水线时序图（Multi-cycle pipeline diagram）：蓝色表示使用，右边的蓝色表示读，左边的蓝色表示写，蓝色的长条表示流水线寄存器

![计组](./imgs/2023-04-26-11-03-07.png)

引入流水线寄存器：
- 寄存器的作用：保存每个阶段的状态，在下一个时钟周期送给下一个阶段处理
- 更正：注意 rd 的 datapath 需要修改，需要跟着其他数据一起经过多个阶段，保证在写回阶段的 rd 是同一条指令的 rd（蓝色线）

![计组](./imgs/2023-04-26-11-20-20.png)

流水线性能影响因素：

![计组](./imgs/2023-04-26-11-10-40.png)

pipeline datapath:
- 控制信号也需要存入流水线寄存器，跟着其他信号一起经过多个阶段
- 蓝色线表示控制信号

![计组](./imgs/2023-04-26-11-36-58.png)

小总结：流水线 datapath 和单周期 datapath 的主要区别
- 流水线寄存器
- 控制信号的数据通路
- rd 的数据通路

数据冒险(hazard)概述:
1. structure hazard: 同时多次访问同一个组件
    - 同时读写寄存器或者内存：double bound，上升沿写，下降沿读
    - 同时多个指令需要读内存：指令内存和数据内存分开存放，增加读写带宽
1. data hazard: 违反数据依赖性，先改再读变成先读再改了
    - ![计组](./imgs/2023-04-26-12-01-31.png)
    - 蓝线表示读数据对写数据的依赖
    - 红线是一种解决方法：在 datapath 中增加连线提前把数据送到下一条指令
    - 三种解决方案：stall, double bump, forwarding
1. control hazard: 分支或者跳转指令导致下一条指令的地址是不确定的

### stall

1. 什么时候 stall（stall detection）：
    - 后面的指令负责检测冒险
    - 冒险判断条件 ![CO](./imgs/2023-06-06-12-46-48.png)
        1. control hazard：EX 阶段结束之后跳转指令的 next PC 才计算出来，在此之前不执行其他命令
        1. data hazard：WB 阶段才会写入寄存器，但 ID 阶段就已经读寄存器，EX 阶段就已经用到寄存器的值了。在写之前不读寄存器
1. 如何 stall：使用 interlock，相当于插入空指令
    - 添加 stall control logic 模块，用于检测冒险 ![CO](./imgs/2023-06-06-12-42-44.png)
    - 如何插入空指令：设置写信号，不写入 PC 和寄存器，相当于暂停执行了一条指令 ![CO](./imgs/2023-06-06-14-19-04.png)

---

stall 的性能计算

![CO](./imgs/2023-06-06-13-00-33.png)

理想状态下，不存在 stall， CPI(clock cycly per instruction) 是 1。但是 stall 会增加流水线的 CPI

![CO](./imgs/2023-06-06-13-01-28.png)

### structure hazard 资源竞争

1. 访问内存产生的资源竞争
    - 解决方法一：将指令内存和数据内存分开
    - 解决方法二：同一块内存开更多的读写端口
1. 访问寄存器
    - 解决方法一：multiple access
    - 解决方法二：double bump，读写时序分离，上升沿写，下降沿读
1. 访问计算单元（例如浮点数运算单元）：阶段划分的不好(not fully pipelined)会导致资源竞争
    - 解决方法一：fully pipeline
    - 解决方法二：用成本换效率，多加几个浮点数运算单元 ![CO](./imgs/2023-06-06-13-14-32.png)

---

性能计算：structual hazard 会降低 CPU 效率

![CO](./imgs/2023-06-06-13-24-04.png)

这里的内存没有分成指令内存 & 数据内存，也没有增加端口。因为每个时钟周期都一定有一条指令正在 IF 阶段，所以需要读内存的指令就一定会造成 structual hazard，增加一个时钟周期的 stall。

---

structual hazard 对性能影响的例子：

![CO](./imgs/2023-06-06-13-29-12.png)

![CO](./imgs/2023-06-06-13-29-42.png)

### data hazard 数据冒险

#### stall

用一个例子理解一下数据冒险：

![CO](./imgs/2023-06-06-13-34-05.png)

ID 最早也只能跟 WB 在同一个时钟周期里

#### forwarding

##### 什么是 forwarding

不等前一条指令写入寄存器，而是在计算好之后 / 从内存读出来之后就直接前递给 ALU 使用。

第一种：运算指令的 forwarding

![CO](./imgs/2023-06-06-13-36-22.png)

第二种：load 指令的 forwarding
- 可能要插入一个空指令(stall)

---

图解有 forwarding 的流水线中，寄存器的数据传递：
1. 蓝色线表示数据依赖
1. 红色线表示 forwarding

![CO](./imgs/2023-06-06-13-40-41.png)

##### 怎么做 forwarding

1. 什么时候 forwarding (detection)
    - 每个时钟周期需要把 rd 跟其他数据一起传到下一个流水线寄存器里
    - forwarding 判断条件：前两句话的 rd 等于当前的 rs1 或者 rs2，并且 **RegWrite 为高电平** ![CO](./imgs/2023-06-06-13-48-24.png)
    - 详细版判断条件 ![CO](./imgs/2023-06-06-13-58-01.png)
1. 如何 forwarding
    - 增加 forwarding 检测模块 ![CO](./imgs/2023-06-06-13-51-51.png)
        1. 检测模块输入：ID/EX 的 rs1 和 rs2，EX/MEM 和 MEM/WB 的 rd
        1. 检测模块的输出：ALU 输入信号的控制信号
    - 增加 ALU 输入选择 ![CO](./imgs/2023-06-06-13-54-08.png)
        1. 00 表示正常输入
        1. 10 表示从第 i-1 条指令的 ALU 结果中输入（i 是当前指令）
        1. 01 表示从第 i-2 条指令的内存读取结果中输入

---

实现思路：**枚举任意两种指令的排列组合**，看看他们之间会不会产生 data hazard。如果会产生的话，加入 forwarding 数据通路解决 hazard。

##### Double Data Hazard

例如：

![CO](./imgs/2023-06-06-14-01-38.png)

解决办法：如果 EX hazard 和 MEM hazard 同时发生，且发生 hazard 的寄存器相同，选择从 EX/MEM 输入。

![CO](./imgs/2023-06-06-14-02-11.png)

##### Load-use Data Hazard

什么是 Load-use Data Hazard

![CO](./imgs/2023-06-06-13-36-41.png)

Load-use Data Hazard 有哪几种情况？
- 如果 i-1 条指令产生了 Load-use Data Hazard，则需要 stall 一个时钟周期
- 如果 i-2 条指令产生了 Load-use Data Hazard，只需要 forwarding

![CO](./imgs/2023-06-06-14-17-21.png)

load stall 的判断条件：

![CO](./imgs/2023-06-06-14-13-13.png)

---

load stall 对性能产生的影响：

![CO](./imgs/2023-06-06-14-21-21.png)

---

编译器优化减少 load stall：

![CO](./imgs/2023-06-06-14-24-16.png)

##### 加上 forwarding 和 stall 的 datapath

![CO](./imgs/2023-06-06-14-19-49.png)

forwarding detection 模块输入信号：

1. ID_EX 的 Rs1_addr 和 Rs2_addr
1. EX_MEM 的 RegWrite 和 Rd_addr
1. MEM_WB 的 RegWrite 和 Rd_addr

forwarding detection 模块输出信号：

1. forwardA
1. forwardB

ALU Source 新增两个 mux，分别增加两个输入（总共 2 个 mux 2 * 2 个新输入）：

1. EX_MEM 的 Rd_data
1. MEM_WB 的 Rd_data

hazard detection 模块输入：

1. IF_ID 的 Rs1_addr 和 Rs2_addr
1. ID_EX 的 MemRead 和 Rd_addr

hazard detection 模块输出：

1. PC_Write
1. IF_ID_Write
1. NOP_ID_EX

然后新增一个 mux 用于清空 ID_EX（前面的控制模块别忘了画了）

##### 例题

```asm
    add R4, R5, R2
    lw R15, 0(R4)
    sw R15, 4(R2)
```

以上代码如何进行 forwarding 和 stall？

![CO](./imgs/2023-06-06-14-28-54.png)

### control hazard 控制冒险

#### 用 stall 解决控制冒险

需要 stall 三个时钟周期。因为在 MEM 阶段才把 next PC 算好写入 PC 中，再下一个阶段才能被后一条指令的 IF 阶段读取。

![CO](./imgs/2023-06-06-14-50-03.png)

#### 用 prediction 解决控制冒险

对 stall 做简单改进 - predict not taken

![CO](./imgs/2023-06-06-14-51-46.png)

如果 branch 指令计算完之后发现预测错误，实际上要跳转，就把预测错的计算结果 flush 掉

#### reduce branch delay

修改 datapath，在 ID 阶段就把 next PC 算好

![CO](./imgs/2023-06-06-14-57-45.png)

这样预测错误只损失了一个时钟周期（看如下的时序图）

![CO](./imgs/2023-06-06-15-05-23.png)

#### flush

IF 寄存器新增 flush 信号。如果 branch 预测错误，就把上一条读出来的指令变成 nop 指令

![CO](./imgs/2023-06-06-15-09-40.png)

![CO](./imgs/2023-06-06-15-10-40.png)

#### reduce branch delay 导致的 data hazard

ld 指令和 beq 指令之前至少要隔 2 条指令，R-type 指令和 beq 指令之间至少要隔 1 条指令。

![CO](./imgs/2023-06-06-15-11-39.png)

reduce branch delay 虽然减少了预测错误带来的 stall，但是却增加了 data hazard 带来的 stall。

#### Dynamic Branch Prediction - 1 bit predictor

使用 PC 低地址作为索引

会导致的问题：如果两条指令 PC 低地址相同，会被当做同一条指令进行预测。

![CO](./imgs/2023-06-06-15-16-17.png)

---

效率降低的情况：inner loop，每次进内层循环都必须连错两次

![CO](./imgs/2023-06-06-15-18-13.png)

#### Dynamic Branch Prediction - 2 bit predictor

增加 predictor 状态个数为 4 个，有限状态机如下：

![CO](./imgs/2023-06-06-15-19-43.png)

相当于一个计数器，每次预测错误就 +1，预测正确就 -1，当计数器值大于等于 10 才预测跳转。

---

如何 predict taken？

新增一个 branch target buffer，存跳转的 PC 地址。那么下一条指令就不用等 branch 指令的 ID 执行完才能 IF，而是可以直接取指令。

![CO](./imgs/2023-06-06-15-37-35.png)

### pipeline CPU 中的 Exception

datapath 需要修改：
1. flush 信号
    - 整个 datapath 中有 3 个 flush 信号
        1. IF.flush
        1. ID.flush
        1. EX.flush
    - 发生异常的指令之前的指令继续执行，之后的指令全 flush 掉。（因此只有前 3 个流水线寄存器需要 flush 信号）
1. PC 新增输入来源
    - 如果发生中断，next PC 就是中断处理程序的 PC

![CO](./imgs/2023-06-06-15-41-40.png)

---

举个例子：

![CO](./imgs/2023-06-06-15-55-32.png)

![CO](./imgs/2023-06-06-15-55-46.png)

![CO](./imgs/2023-06-06-15-56-02.png)

---

与单周期 CPU Exception 的区别：
1. 因为同一时刻有多条指令在执行，所以可能同时产生 **multiple exception**
1. 发生 exception 的时候，PC 并不是产生 exception 的指令的 PC。如果能确定具体是哪条指令产生 exception，就叫 **precise exception**。一般来说精确中断比较困难，**inprecise exception** 也够用了 ![CO](./imgs/2023-06-06-15-57-32.png)

## chapter 5 存储结构 Memory Hierarchy

### Memory Technology

常见存储介质：
1. SRAM：触发器
1. DRAM：电容。需要刷新
    - DDR：上升沿和下降沿都可以读写，所以 double data rate
    - QDR：增加输入输出端口，quad data rate
1. Flash：nonvolatile。
    - 损耗均衡：优先把写的地址映射到被写次数少的内存上
    - ![CO](./imgs/2023-06-06-16-16-47.png)
1. disk
    - cylinder & track 磁道 & sector 扇区
    - 寻址操作：寻道 -> 旋转 -> 读写
    - 磁盘读写时间计算： ![CO](./imgs/2023-06-06-16-19-52.png)

---

读写时间 & 成本：

![CO](./imgs/2023-06-06-16-03-14.png)

### Memory Hierarchy

#### Locality

建立存储结构的理论基础：

1. temporal locality: If an item is referenced, it will tend to be referenced again soon.
1. spatial locality: If an item is referenced, items whose addresses are close by will tend to be referenced soon.

---

访存相关概念：

1. block: minimum unit of data (block) for transfers 
1. hit: data requested is in the upper level
    - 参数：hit time - The time to access the upper level of the memory hierarchy, which includes the time needed to determine whether the access is a hit or a miss.
    - 参数：hit rate
1. miss: data requested is not in the upper level
    - 参数：miss penalty - The time to replace a block in the upper level with the corresponding block from the lower level, plus the time to deliver this block to the processor.
    - 参数：miss rate

#### Memory Hierarchy

![CO](./imgs/2023-06-06-16-42-47.png)

其他技术：
1. cache：解决速度问题
1. virtual memory：解决容量问题

### The basics of Cache

#### direct mapped cache

lower memory 中每个块只能放在 cache 中的一个确定的块中。比如说 lower memory 中的地址截取低 n 位作为 cache 中的地址。

![CO](./imgs/2023-06-06-16-47-59.png)

- 优点：寻址简单
- 缺点：miss 的概率非常大

---

寻址模式：
1. byte offset: 块内偏移量，即字节数据与块首地址的偏移量
    - 如果 byte offset 有 n 位，说明块内字节数为 $2^n$
1. index: cache 地址
    - 如果 index 有 n 位，说明 cache 存储空间大小（不包含索引数据）为 $2^n$ 个 block
1. tag: tag + index 是内存中的地址
    - tag 存在 cache 中，用于判断 miss 还是 hit
    - 如果 tag + index 有 n 位，说明 memory 大小为 $2^n$ 个 block

![CO](./imgs/2023-06-06-16-54-30.png)

---

举个例子理解一下 cache 怎么寻址，以及 cache 中除了存数据之外还存了什么

![CO](./imgs/2023-06-06-17-00-38.png)

![CO](./imgs/2023-06-06-17-00-53.png)

---

cache 大小计算例题：

一个 block 需要的 bit 数 = data bit + tag bit + valid bit

![CO](./imgs/2023-06-06-17-04-14.png)

---

计算内存地址对应的 cache 地址例题：

![CO](./imgs/2023-06-13-19-39-47.png)

#### miss & hit

##### miss 情况 & 策略

miss 的分类：
1. compulsory miss: 启动时数据不在 cache 中 -> 减少关联度
1. capacity miss: cache 大小不够 -> 增大 cache 大小
1. conflict miss: 组容量不够 -> 增大关联度

读数据的两种情况：
1. 读指令：发生 miss 时 PC 已经累加，需要先把 PC 减掉再重新取指
1. 读数据

写数据 hit 的两种策略：
1. write-through：cache 和 memory consistent
1. write-back：只有需要被替换的 dirty 块才会被写回内存

写数据 miss 的两种策略：
1. write-allocate：替换到 cache 中再修改
1. no write allocate(write around)：不写到 cache 中，直接在内存中更改，保证 consistency

write buffer：优化写操作，排队等待写到内存中，减少 CPU 的 stall。

##### miss penalty

read & write miss penalty 的计算：因策略而异。直接看例题：

![CO](./imgs/2023-06-13-20-12-15.png)

可以看出不同 write miss 策略导致的 penalty 的差异。

---

early restart：读到想要的数据就重启 CPU，剩下的数据传输和 CPU 并行。一般用在取指令的时候。

##### miss rate

![CO](./imgs/2023-06-13-20-16-18.png)

1. 横坐标：块大小
1. 纵坐标：miss rate
1. 不同线：cache 大小

块大小变大 miss rate 减少，是因为利用了局部性。块大小过大 miss rate 又增加，因为块数量过少。

#### cache 和 CPU 之间的数据传输方式

基本流程：
1. CPU 给 memory 发送地址
1. access initialize：地址译码以及寻址等操作（耗时长）
1. memory 通过 bus 将数据传回 CPU

三种传输模式：

![CO](./imgs/2023-06-13-20-34-28.png)

![CO](./imgs/2023-06-13-20-34-51.png)

![CO](./imgs/2023-06-13-20-35-38.png)

### Measuring and improving cache performance

主要关注的是两点：miss rate 和 miss penalty

#### 检测 cache 性能

计算公式：
1. read 的等待时间
1. write 的等待时间
1. 将 read write 放在一起考虑

![CO](./imgs/2023-06-13-20-42-57.png)

![CO](./imgs/2023-06-13-20-46-04.png)

---

例题：计算 cache miss 对 CPU 效率的影响

![CO](./imgs/2023-06-13-20-59-47.png)

在上题的基础上，如果
1. CPI 减小了
1. clock cycle time 减小了

CPU time 会相应减小，但是 cache miss 对性能产生的影响就更大了

![CO](./imgs/2023-06-13-21-03-23.png)

![CO](./imgs/2023-06-13-21-03-43.png)

##### 提升 cache 性能

###### 第一种策略 - 降低 miss rate：set-associative cache 组相连 cache

每个内存块对应 cache 中的一个组，可以被读到组中的任意一个 block。

![CO](./imgs/2023-06-13-20-48-51.png)

- 通过改变块映射关系减少 miss rate
- direct mapping 是组相连的一种（每个组只有一个 block）
- 组大小（关联度，associativity）是一个超参数，人为设置以得到最优效率。
    - 增加组大小会减小 miss rate，但是每次对 miss or hit 的判断需要花费更多的时间

---

例题：

![CO](./imgs/2023-06-13-21-09-00.png)

![CO](./imgs/2023-06-13-21-09-16.png)

##### 第一种策略 - 降低 miss rate：替换策略

例如 LRU

##### 第二种策略 - 降低 miss penalty：multi-level cache

- 一级 cache 负责减少判断 hit 的时间，快速响应 CPU
    - 一般使用 direct mapping
- 二级 cache 复负责减少 miss rate，减少访存时间
    - 一般使用组相连

计算：

![CO](./imgs/2023-06-13-21-16-12.png)

![CO](./imgs/2023-06-13-21-16-48.png)


##### 软件层面：利用 cache 和存储的局部性

例如：
1. 基数排序 & 快排的比较：基数排序的局部性较差，在数据规模较大时 cache 利用率低
1. 矩阵乘法的分块技术：增加 cache 的利用率

### Virtual Memory

将硬盘中的一部分当做主存(memory)使用。

作用：
1. 拓展主存空间
1. 允许更多程序共享内存

---

基本概念：
1. page：虚拟内存的一个内存大小单位
    - 一般都比较大，因为硬盘的访问时间大于传输时间，所以最好尽量多的数据一起传输
1. page fault：缺页，即虚拟内存中的 "miss"。数据不在内存中，从硬盘取数据到内存中
    - 使用 write back 策略（只有 page 需要替换的时候才会写回），因为硬盘读写太慢了
    - 使用全相连，最大程度上减少 page fault
    - 使用 LRU 替换策略

---

address translation：
1. 虚拟地址
1. 物理地址
1. 硬盘地址

虚拟地址分配给程序用于寻址。虚拟地址映射到物理地址上或者硬盘地址上。每个虚拟地址只会映射到一个物理地址或者硬盘地址，但是同一个物理地址可以被多个虚拟地址映射（共享内存）。

![CO](./imgs/2023-06-13-21-37-39.png)

---

page table：存储虚拟地址对应的物理地址，存放在内存中

页表大小 = 虚页号的个数 = 虚拟地址总个数 / page 大小。页表的大小单位是 GB，还是相当大的。

page table register：存储内存中页表的起始地址

![CO](./imgs/2023-06-13-21-35-11.png)

---

优化页表的速度：TLB(translation lookaside buffer)块表

在 cache 中存一部分最常用的页表项

---

一种可能得访问路径：
1. TLB miss -> 访问 page table
1. page fault -> 中断，控制权交给 OS， 访问硬盘

![CO](./imgs/2023-06-13-22-11-35.png)

枚举访问路径的分支：
1. 如果 TLB hit 了，page table 一定 hit
1. 如果 cache hit 了，page table 一定 hit（说明数据存在内存中）

![CO](./imgs/2023-06-13-22-14-22.png)

---

一种包含 TLB 的存储结构，接下来开始看图说话：
1. 首先，从上到下依次是，虚拟地址，TLB，物理地址，cache（tag 和 data 分开存放）
1. TLB 组织结构：全相连
1. cache 大小：cache 有 256 个 block，每个 block 16 个 word，每个 word 4 byte
1. cache 组织结构：direct mapping

![CO](./imgs/2023-06-13-22-04-57.png)

### 总结 memory hierachy

![CO](./imgs/2023-06-13-22-20-38.png)

访存的整个过程大概来说就是，虚拟地址怎么查 TLB 和 page table 转换成物理地址，如果发生 miss 和 page fault 怎么办。然后知道物理地址之后，怎么判断 cache miss 还是 hit。这些过程中要分类讨论 TLB 和 cache 的组织形式，比如 direct mapping 和 set associative；以及要讨论替换策略，比如 write back 和 write through，write allocate 和 not allocate。

---

用有限状态机控制读写：

![CO](./imgs/2023-06-13-22-47-43.png)

### 虚拟机 virtual machine

没讲，不管。

## Vivado

### 概念

#### Testbench 是什么？怎么写？

[Testbench 是什么？怎么写？](https://vlab.ustc.edu.cn/guide/doc_testbench.html#2-1-testbench%E7%9A%84%E5%BB%B6%E8%BF%9F%E5%BB%BA%E6%A8%A1)

#### IP 包含源文件和不包含源文件的区别？

- 功能上：
    - 包含源文件方便修改（**可以把整个工程目录搬到别的工程里，既可以调用也可以随时修改**）
    - 不包含源文件保护知识产权
- 生成过程：
    - 包含源文件的 IP 直接依据当前项目文件生成
    - 不包含源文件的 IP 则是先导出 edf 和仅包含端口信息的 v 文件，再重新导入到项目中生成 IP（**注意：如果导入到同一个项目中，因为文件名相同，会覆盖之前写的源文件，所以最好新建项目或者修改源文件名字**）。
- 调用方法：
    - 有源无源都一样，只要把 IP 核文件夹的目录加入到 project 的 IP repository 中就行。
- 调用原理：
    - 有源文件：其调用原理是利用xgui下的tcl脚本根据xml特征描述从源文件处重新复制生成工程所需文件
    - 无源文件：其调用原理是利用xgui下的tcl脚本根据xml特征描述从.edf文件处重新复制生成工程所需文件


#### .edf 网表文件是什么？有什么作用？

[.edf 网表文件是什么？有什么作用？](https://zhuanlan.zhihu.com/p/137433454)

#### 什么是 IP core？

IP核文件夹包含 xgui 和 component 以及其对应的源文件（有源文件则为 v，无源文件则为 v 和 edf）

### 操作

#### 使用 VSCode 作为编辑器

[使用 VSCode 作为编辑器](https://zhuanlan.zhihu.com/p/378739805)

```c
F:\programfiles2022\Microsoft VS Code\Code.exe -g [file name]:[line number]
```


#### 新建工程

- Speed: -2L
- Family: Kintex7
- Package: FFG676
- 最终：XC7K160TFFG-2L

#### 导出 edf 和 v 文件

- tcl console 命令：注意文件名要和原源文件不同 `write_verilog -mode synth_stub F:/programfiles2022/Vivado/IP/<project_name>/<project_name>_ns.v` `write_edif F:/programfiles2022/Vivado/IP/<project_name>/<project_name>_ns.edf`
- 若含Xilinx IP则需通过如下命令生成edf文件：`write_edif -security_mode all E:/FPGA/ip/MUX2T1_5.edf`
- 需要打开 Synthesized Design 之后才能执行上述命令

#### 生成自定义 IP

含源文件：Lab0 PPT 79

不含源文件：Lab0 PPT 89

#### 调用自定义 IP

~~xml 文件描述包含源文件的目录位置，若复制源文件时更改了路径位置，则需在xml描述对应位置进行更新，以免出现调用时无法找到源文件的错误。~~ 不会出现上述问题

Lab0 PPT 118

---

包含源文件的 IP：

1. **把 IP 工程放到统一的文件夹下**，使用时只需要把所有 IP 所在的文件夹加入到 IP repository。在加入 IP 目录时可以看到检测到了哪些 IP
1. 在 IP catalog 中双击用 IP 生成一个 module。**注意 module 的名字和 IP 的名字不能一样。**
1. 然后就可以在 verilog 文件里把 module 例化了，显示在 Design Sources 里的名字就是模块名.**展开 xci 后点击 v 或者 veo 文件可以看到例化的模板，copy 出来改改端口就可以用**
    ```verilog
    MUX2T1_5_0 MUX2T1_5_0(
        .I0(I0),
        .I1(I1),
        .s(s1),
        .o(o_0)
    );
    ```
---

不包含源文件：

1. 直接 add or create design sources，把 edf 和 v 文件包含到工程里
1. 参考 v 文件里的输出例化模块。如果调用成功 v 和 edf 会作为子文件出现在调用他们的源文件下面


#### 修改自定义 IP

在修改某些 IP 时，采用右键 IP，选择 Edit in IP Packager 进入自动生成的子工程中修改，修改完成后 Repackage IP，然后回到父工程中 Upgrade IP 即可。可以避免自认为 IP 更新了，实际上工程并没识别到

#### 把原理图翻译成 verilog 文件

1. 输入输出照抄
2. module 实例化（命名，但先不连线）
3. 给每个输出引脚定义一根线，命名为“实例名_引脚名”
4. 遍历每个输入引脚，填入要连的线名称

tips: 使用 VScode 的分屏，把输入输出和 wire 的定义放在一边，在另一边连线，对大工程来说会方便一点。

#### RAM & ROM

Lab0 PPT P131

##### 初始化文件 .coe 怎么导入

- add or create design sources
- 选择 all files，发现 coe 文件出现

##### RAM 怎么调用

```verilog
RAM U3 (
  .clka(clk_m), 	        // input clka
  .wea(data_ram_we),        // input [0 : 0] wea
  .addra(ram_addr),         // input [9 : 0] addra
  .dina(ram_data_in),       // input [31:0] dina
  .douta(ram_data_out)      // output [31:0] douta
);

```

##### RAM 设置 tips

![CO](./imgs/2023-05-16-15-47-28.png)

关闭输出寄存器，仿真时 RAM 在上升沿输出；打开输出寄存器，仿真时 RAM 在下降沿输出。

---

RAM

#### 上板

lab0 PPT 52


#### 封装 clk 和 rst 接口的问题

- clk 报错
- rst 自动反相

参见 Lab01-1 PPT P22-27

#### RISC-V 在线指令翻译器使用方法

lab2 PPT 81

#### Vivado 自动例化脚本

[自动例化脚本使用教程](https://blog.csdn.net/telantan/article/details/114178283)

##### vivado 开机自动运行脚本

[参考教程](https://blog.csdn.net/yundanfengqing_nuc/article/details/107866015)

初始化脚本的路径换成这个：`F:\programfiles2022\Vivado\Vivado\2020.2\scripts`

#### 实验平台的使用

`SW[0]` 控制显示图形还是文字，`SW[1]` 没用

```verilog
SW[0]=0: 显示图形
SW[0]=1: 显示文字
```

`SW[7:5]` 决定了数码管显示什么内容

```verilog
SW[7:5]=显示通道选择
SW[7:5]=000；输出 总线的 Peripheral_in，源头是Cpu_data2bus
SW[7:5]=001；输出 CPU 指令地址 PC_out[31:2]，高 2 位为 0
SW[7:5]=010；输出 指令存储器(ROM)数据输出，PC 的指令输入 Inst_in[31:0]
SW[7:5]=011；输出 计数器输出 Counter_out[31:0]
SW[7:5]=100；输出 PC 输出的地址，即数据存储器(RAM)的地址输入 addr_out[31:0]；同时也是 ALU 的计算结果 alu_res
SW[7:5]=101；输出 CPU 的数据输出 Data_out，即 BUS 的输入 Cpu_data2bus
SW[7:5]=110；输出 CPU 数据输入 Cpu_data4bus，源头是数据存储器数据输出 ram_data_out[31:0] 
SW[7:5]=111；输出 CPU 指令地址 PC_out[31:0]
```

`{SW[8], SW[2]}` 决定了 CPU 的运行速度

```verilog
{SW[8], SW[2]}=CPU单步时钟选择
{SW[8], SW[2]}=00: CPU全速时钟 100MHZ
{SW[8], SW[2]}=01: CPU自动单步时钟(2*24分频)
{SW[8], SW[2]}=1X: CPU手动单步时钟(按键BTN_OK[0])
```

`SW[10]` 用于单步调试
- `SW[10]` 上升沿执行下一条指令
- 使用按键阵列中第一列的按键也能达到同样的效果，但 `SW[10]` 更稳定。

`BTNRST` 重启 CPU

#### vh 文件的使用

[参考博客](https://blog.csdn.net/persistlzy/article/details/106816699#:~:text=1%E3%80%81%E5%88%9B%E5%BB%BA%E5%A4%B4%E6%96%87%E4%BB%B6%EF%BC%8C%E9%80%89%E6%8B%A9verilog%20header%EF%BC%8C%E6%98%AF.vh%E6%96%87%E4%BB%B6%202%E3%80%81%E5%B0%86%E5%A4%B4%E6%96%87%E4%BB%B6%E8%AE%BE%E7%BD%AE%E4%B8%BAGlobal%20Include%EF%BC%8C%E8%BF%99%E6%A0%B7%E5%B0%B1%E4%B8%8D%E7%94%A8%E5%9C%A8%E6%AF%8F%E4%B8%AA%E8%B0%83%E7%94%A8%E7%9A%84%E6%96%87%E4%BB%B6%E9%87%8C%E9%9D%A2%E6%B7%BB%E5%8A%A0,%60include%20%22My_def.vh%22%E6%96%87%E4%BB%B6%E4%BA%86%203%E3%80%81%E5%B0%86%E5%A4%B4%E6%96%87%E4%BB%B6%E6%B7%BB%E5%8A%A0%E9%A2%84%E5%AE%9A%E4%B9%89%EF%BC%8C%E5%A6%82%60define%20SC_ref%20570)

引用头文件 & 使用宏（注意需要加 `）：

```verilog
`include "Lab4_header.vh"

`IMM_SEL_I
```


#### iverilog + GTKWave 进行波形仿真

[参考博客](https://zhuanlan.zhihu.com/p/95081329)

[同时显示多个波形](https://zhuanlan.zhihu.com/p/601002611)

```shell
# 显示波形文件
gtkwave wave.vcd
```

### Verilog

#### assign

- 方向性：等号右边输入(driver, source)，左边输出(sink)
- 持续性：表示持续存在的(continuously)连接关系，而不是一个即刻的赋值行为
- 无序性：语句顺序与结果无关
- 唯一性：一个 wire 只能被一个 driver 驱动，即一个 wire 只能出现在 assign 等式左边一次
- 是 wire 之间的连接关系，本身不是一条 wire

e.g. `assign out = in;`

#### wire

- 声明必须在第一次使用之前
- `input wire in` 简写成 `input in`，本质是一根连接 module 内外的 wire

#### vector

- 声明：`type [upper:lower] vector_name;`, e.g. `wire [31:0] my_vec`
    - negative ranges are allowed, e.g. `input wire [3:-2] z;`
    - 反向 vector, e.g. `wire [0:7] b;`, b[0] is the most-significant bit
    - 禁用未定义网络：在文件最前面写 `default_nettype none
- part-select: `assign out = my_vec[7:0];`
- concatenation
    - 可以组合输出端口，e.g. `assign {out[7:0], out[15:8]} = in;`
    - 可以组合输入端口，e.g. `assign out[15:0] = {in[7:0], in[15:8]};`
    - 必须保证宽度已知，e.g. `{3'b111, 3'b000}` 可以，`{111, 000}` 不行
    - 重复 n 次：`{num{vector}}`, e.g. `{3'd5, {2{3'd6}}}`

p.s. Bitwise vs. Logical Operators 在 operand 是 vector 时行为不同：位运算对于每一位分别运算，返回和运算数同样长度的结果；逻辑运算则把两边当成布尔值，返回 1 位的结果

p.s. unpacked array: 

- 用于定义内存块
- `reg [7:0] mem [255:0];` are 256 unpacked elements, each of which is a 8-bit packed vector of reg. 
- 只能单个使用 `mem[0]`，不能连续使用 `mem[31:0]`
- [参考](https://hdlbits.01xz.net/wiki/Vector1)

#### module

定义一个 module

```verilog
module mod_a ( input in1, input in2, output out );
    // Module body
endmodule
```

调用 (实例化，instantiate) 一个 module
- by position `mod_a instance1 ( wa, wb, wc );` 顺序和定义的时候一样
- by name `mod_a instance2 ( .out(wc), .in1(wa), .in2(wb) );`

p.s. pin 指 1 位的输出端口


#### procedure

procedure 包括：

- always
- initial
- task
- function

procedure 内部的语法有：

- if-else
- case

#### combinational always

`always @(*)` 和 assign 的异同

- 语法不同：always 块内部不能有 assign，但可以使用 if-else, case 等更复杂的语法
- 操作的变量类型不同：assign 左边必须是 net type (e.g. wire)，always 内部的 procedural assignment 左边必须是  variable type (e.g. reg)
- 逻辑相同：Both will recompute the output whenever any of the inputs (right side) changes value.

p.s. `always@()` 括号里叫 sensitivity list，表示检测到其中输入的变化就重新执行块内的代码

p.s. wire 和 reg 的硬件实现相同，只是用于两种不同情景的不同语法。如果 reg 在 `always@(*)`块内的所有分支都出现，那么他会被用多选器来实现；如果没有都出现，则认为在某些条件下需要保留原始值，会生成触发器。

![Alt text](./imgs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-03-15%20235916.png)

e.g.

```verilog
always @(*)
    case(sel)
        2'h0: q = d;
        2'h1: q = o1;
        2'h2: q = o2;
        2'h3: q = o3;
    endcase
```

#### clocked always

p.s. 在 procedure 中 `=` 和 `<=` 的区别：In a combinational always block, use blocking assignments(=). In a clocked always block, use non-blocking assignments(<=).

e.g. `always @(posedge clk) out_always_ff <= a ^ b;`

#### if-else 语句

e.g.

```verilog
always @(*)
    if (sel_b1 & sel_b2) out_always = b;
    else out_always = a;
```

p.s. 如果要在 if-else 中对某个 reg 进行赋值，最好在所有分支中都对其进行赋值。否则会生成一个触发器，在没有赋值的分支保留值，不再是组合逻辑。

#### case 语句


e.g.

```verilog
always @(*) begin     // This is a combinational circuit
    case (in)
      1'b1: begin 
               out = 1'b1;  // begin-end if >1 statement
            end
      1'b0: out = 1'b0;
      default: out = 1'bx;
    endcase
end
```

- 只执行一个分支，不需要 break
- 重复的分支语法正确，但只有第一个分支被使用

p.s. casez: z 可以为任意值

```verilog
always @(*) begin
    casez (in[3:0])
        4'bzzz1: ...
        4'bzz10: ...
        4'bz100: ...
        4'b1000: ...
        default: ...
    endcase
end
```

(casex 同理，可以用 `?` 代替 `z`)


## 复习整理

### ch4-1 单周期

考点：
1. 控制信号 & datapath 数据流动
    - 给一个指令，写出所有控制信号的值，数据在 datapath 中怎么流动
    - 如果要加一个新指令，要加什么模块
1. 记忆指令类型
    - 总共有哪些类型？R, I, S, B, U, J
    - I-type 又分为哪些不同功能？计算、load、jalr、特权指令
    - 分别用到几个寄存器？3, 2, 2, 2, 1, 1
    - 计算公式是？

注意：
1. JAL 和 JALR 的运算一般不经过 ALU，而是单独使用计算模块，方便后续流水线 reduce branch penalty
1. JALR 是 I-type，PC+4 写回 rd

### ch4-2 流水线

#### 考点

1. 流水线的 5 个阶段
    - 哪 5 个阶段？IF, ID, EX, MEM, WB
1. 数据竞争
    - 哪些指令会产生数据竞争？
    - 数据竞争在哪里检测？ID 阶段
    - 数据竞争如何检测？从 IF_ID, ID_EX, EX_MEM 获取数据
    - 数据竞争控制信号有哪些？PCWrite & IF_IDWrite
    - 给一串指令判断哪里有 hazard，不处理 hazard 最终的计算结果（**画时序图**），用 stall 处理 hazard 在哪里加 nop（**让前一条指令的 WB 和后一条指令的 ID 在同一个周期进行**）
1. forwarding
    - 在哪个阶段 forwarding？EX 阶段
    - 哪种数据冲突仅用 forwarding 无法解决？用到 load 的冲突，可能需要加入一个 stall
    - EX hazard & MEM hazard 区别？和前一条指令冲突还是和前前一条指令冲突
    - forwardA & forwardB 信号？为 2 表示 EX hazard，为 1 表示 MEM hazard，为 0 表示没有 hazard
        - 题型：给一串代码，画时序图 + 写出每个周期的 forwarding 信号
        - 题型：看图或者画图 ![CO](./imgs/2023-06-06-14-19-49.png)

注意：
1. load 用到了全部 5 个阶段
1. SD 指令的 forwarding：写入内存的数据在 EX 阶段就需要准备好，因为 forwarding 仅在 EX 阶段前做

#### 错题整理

1. 

![CO](./imgs/2023-06-14-08-47-56.png)

![CO](./imgs/2023-06-14-08-48-18.png)

合并 EX 和 MEM 阶段的效果：
- 不影响时钟周期，因为瓶颈在 ID 阶段
- stall 减少，处理数据竞争最多只需要一个 nop
- 但是指令表达能力减弱，需要更多指令才能达到目标


[TODO] full forwarding 是什么？

### ch5 存储

[TODO] 第五章习题

把存储结构以及本章的一些名词之间的关系理一下