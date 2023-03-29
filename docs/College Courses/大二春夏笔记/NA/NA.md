# 数值分析

[TOC]

## intro

课程内容：

- 了解近似技术
- 未来研究方向：工业软件
- 黄劲 hj@cad.zju.edu.cn

参考资料：

- [去年的智云](https://classroom.zju.edu.cn/coursedetail?course_id=37986&tenant_code=112)：可以参考小测 & Pre
- [ecnu NA 课程主页](https://math.ecnu.edu.cn/~jypan/Teaching/NA/index.html)
- NA 常见问题的程序实现
    - BLAS
        - netlib reference：慢但是可作为精确解对照
    - LAPACK
    - Linpack
    - atlas
    - arpack
    - minpack

## 数学基础

### Roundoff Errors 近似和误差

1. 近似方法
    - chopping
    - rounding
    - e.g. four-digit rounding arithmetic: 每次计算（加减乘除、三角函数etc）都用 rounding 保留到 4 位有效数字
2. 误差
    - absolute error
    - relative error：有效数字实际上是在说明相对误差

e.g. ==课上举的例子==

e.g. 一元二次方程求根

- 分母有理化
- 上溢出 & 下溢出

### Algorithms & Convergence 收敛速度

1. 数列的 Convergence Rate
2. 函数的 Convergence Rate
    - 用 big O notation 表示
    - 求极限的方法：洛必达

## 一元方程求解

### The Bisection Method 二分法

e.g. 加速点积的计算

$x_0\times x_1+y_0\times y_1$

mmx 指令集（同时计算四个浮点数）：用于多媒体的计算

### Fixed-point Iteration 不动点迭代

1. 条件