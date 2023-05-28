# 数值分析

[TOC]

## intro

课程内容：

- 了解近似技术
- 未来研究方向：工业软件
- 黄劲 hj@cad.zju.edu.cn

参考资料：

- [去年的智云](https://classroom.zju.edu.cn/coursedetail?course_id=37986&tenant_code=112)：可以参考小测 & Pre
- [本学期的智云](https://classroom.zju.edu.cn/coursedetail?course_id=50694)
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


[实对称矩阵 -> 正定](https://zhuanlan.zhihu.com/p/69351875)


## 迭代法解线性方程组

### 向量的范数 & 矩阵的范数



### 特征根 & 特征向量 & 谱半径

1. 特征值的求法：
    1. 特征值之和等于矩阵的对角线元素之和（迹），特征值之积等于矩阵的行列式
    1. 矩阵乘一个常数，所有特征值都乘这个常数
    1. 矩阵加一个单位矩阵，所有特征值都加一个单位矩阵

### 迭代法递推公式通式 & 收敛性判断定理

$$x^{(k)}=Tx^{(k-1)}+b$$

收敛的充要条件：$\rho(T)<1$。*任何迭代法判断收敛性都化成这个形式再判断*

![NA](./imgs/2023-04-12-15-42-37.png)

### 四种迭代法的比较

Jacobi

Gauss-Seidel

Relaxation Method

Iterative Refinement

## ch8 Approxiamation Theory

### discrete least squares approximation 离散最小二乘法

`n << m`: 采样点远大于多项式阶数。若 `n > m` 可以用插值使得采样点误差为 0

$P(\textbf{a}, x)=a_0+a_1 x+a_2x^2+\ldots+a_n x^n$ 是一个多项式，系数为 $\textbf{a}=(a_0, a_1, \ldots, a_n)^T$ 在最小二乘法中需要求一个向量 $\textbf{a}$ 使得 $P(\textbf{a}, x)$ 逼近目标函数 $f(x)$

如何衡量近似函数和目标函数的接近程度呢？定义 $$E_2(\textbf{a})=\sum_{i=1}^m (P(\textbf{a}, x_i)-y_i)^2$$

如果用所有采样点的数据组成 m 维向量

$$
\left\{\begin{matrix}
  X=\begin{pmatrix}
  1 & x_1 & \ldots & x_1^n\\
  1 & x_2 & \ldots & x_2^n\\
  \vdots& \vdots & \ddots & \vdots\\
  1& x_m &\ldots & x_m^n
\end{pmatrix}_{m\times n} \\
  X\textbf{a}=(P(\textbf{a}, x_1), P(\textbf{a}, x_2), \ldots, P(\textbf{a}, x_m))^T \\
  \textbf{y}=(y_1, y_2, \ldots, y_m)^T
\end{matrix}\right. 
$$

然后把 error 看成差向量的范数，有

$$
\begin{align*}
E_2(\textbf{a}) &= ||X\textbf{a}-\textbf{y}||_2^2\\
&=(X\textbf{a}-\textbf{y})^T(X\textbf{a}-\textbf{y})\\
&=\textbf{a}^TX^TX\textbf{a}-2\textbf{a}^TX^T\textbf{y}+\textbf{y}^T\textbf{y}
\end{align*}
$$

推导中可以合并两个交叉项，因为其结果是一个 $1\times 1$ 的矩阵，相当于一个标量，而他们的标量数值显然是相等的。即 $(X\textbf{a})^T\textbf{y}=\textbf{y}^T(X\textbf{a})$

因为最小二乘法的要求是最小化 error，所以其必要条件是 $\textbf{a}$ 是 $E_2(\textbf{a})$ 的极值点。所以我们对 $E_2(\textbf{a})$ 求导

$$\frac{\partial E_2(\textbf{a})}{\partial\textbf{a}}=2X^TX\textbf{a}-2X^T\textbf{y}=0$$

$$X^TX\textbf{a}=X^T\textbf{y}$$

可以令 $A=X^TX$，之后的正交向量部分就是构造具有特殊性质的矩阵 $A$

Linearization: 把非线性的多项式通过换元等操作变成多项式，比如 $y=ae^\frac{b}{x}$ 可以变成多项式

### 正交向量 & 连续最小二乘法

线性空间：所有不超过 n 阶的多项式组成的线性空间 $\Pi_n$

线性无关的定义：（几何直观：向量不平行）[线性无关](https://zhuanlan.zhihu.com/p/411455683)

多项式空间内积的定义：
- 内积可以有很多种，这里使用带 weight 的版本
- 定义离散的内积：取 m 个采样点（常数），把对应采样点的函数值乘起来

![NA](./imgs/2023-04-26-14-27-05.png)

使用内积得到正交的条件：（几何直观：向量垂直）两个多项式内积为 0

将 $\Pi_n$ 的一组正交基 $\phi_0(x),\phi_1(x),\ldots,\phi_n(x)$ 代入 $X$，得到的 $X$ 长这样：

$$
X=\begin{pmatrix}
  \phi_0(x_1) & \phi_1(x_1) & \ldots & \phi_n(x_1)\\
  \phi_0(x_2) & \phi_1(x_2) & \ldots & \phi_n(x_2)\\
  \vdots& \vdots & \ddots & \vdots\\
  \phi_0(x_m)& \phi_1(x_m) &\ldots & \phi_n(x_m)
\end{pmatrix}
$$

因为 $\phi_0(x),\phi_1(x),\ldots,\phi_n(x)$ 是一组正交基，根据内积的性质，$A=X^TX$ 除了对角线之外全都为 0，即 $A$ 是一个对角阵，求解 $A\textbf{a}=X^T\textbf{y}$ 就方便多了。

使用施密特正交化求一组正交基，可以得到条件数更小的 $A$。 

![NA](./imgs/2023-04-26-14-53-57.png)

### 切比雪夫多项式

![NA](./imgs/2023-05-09-14-47-43.png)

#### 应用：幂级数降阶

![NA](./imgs/2023-05-09-15-05-27.png)

### ch4 积分方法

[数值积分方法](https://zhuanlan.zhihu.com/p/166272592)



## Project 记录

### Proj 3 求解周期性三对角阵方程组

[参考博客](https://blog.csdn.net/qq_32096491/article/details/78213914)

原方程

$$
\left[
\begin{matrix}
 2      & 0.5     &0  & \cdots &0&0.5      \\
 0.5      & 2     &0.5& \cdots & 0&0      \\
 0      & 0.5     &2 & \cdots & 0&0      \\
 \vdots & \vdots & \ddots & \vdots \\
 0      &0    &0& \cdots & 2&0.5      \\
0.5    & 0     &0 & \cdots &0.5&2      \\
\end{matrix}
\right]
\left[
\begin{matrix}
x_0\\
x_1\\
x_2\\
\vdots\\
x_{n-2}\\
x_{n-1}\\
\end{matrix}
\right]=\left[
\begin{matrix}
p_0\\
p_1\\
p_2\\
\vdots\\
p_{n-2}\\
p_{n-1}\\
\end{matrix}
\right]
$$

将最后一个变量先作为参数 $k$，得到三对角矩阵

$$
\left[
\begin{matrix}
 2      & 0.5     &0  & \cdots &0&0      \\
 0.5      & 2     &0.5& \cdots & 0&0      \\
 0      & 0.5     &2 & \cdots & 0&0      \\
 \vdots & \vdots & \ddots & \vdots \\
 0      &0    &0& \cdots & 2&0.5      \\
0    & 0     &0 & \cdots &0.5&2      \\
\end{matrix}
\right]
\left[
\begin{matrix}
x_0\\
x_1\\
x_2\\
\vdots\\
x_{n-3}\\
x_{n-2}\\
\end{matrix}
\right]=\left[
\begin{matrix}
p_0-0.5k\\
p_1\\
p_2\\
\vdots\\
p_{n-3}\\
p_{n-2}-0.5k\\
\end{matrix}
\right]
$$

用 Crout's Method 对三对角矩阵进行 LU 分解之后

$$
L=\begin{pmatrix}
l_0  &  &  &  & \\
0.5  & l_1 &  &  & \\
  & 0.5 & l_2 &  & \\
  &  & \ddots & \ddots & \\
  &  &  & 0.5 & l_{n-2}
\end{pmatrix}
$$

$$
U=\begin{pmatrix}
1 & u_0 &  &  & \\
  & 1 & u_1 &  & \\
  &  & 1 & \ddots & \\
  &  &  & \ddots & u_{n-2}\\
  &  &  &  & 1
\end{pmatrix}
$$

其中 $l_i = 2-\frac{0.25}{l_{i-1}}$ 通过递推求得，$u_i=\frac{0.5}{l_i}$

解方程后得到的 $\vec{x}(k)$ 是 $k$ 的一次式，所以 **解方程的时候不仅要存常数，还要存 $k$ 的系数**。

然后利用刚刚舍弃掉的那个方程求出 $k$，代回到 $\vec{x}(k)$ 中得到最终的答案。

$$
\begin{align*}
&\left\{\begin{matrix} 
  x_0  =  a_0k+b_0\\  
  x_{n-2}  = a_1k+b_1 \\
  0.5x_0+0.5x_{n-2}+2x_{n-1}  = p_{n-1}
\end{matrix}\right. \\
\Longrightarrow & k=\frac{2p_{n-1}-b_0-b_1}{a_0+a_1+4}
\end{align*}
$$

检验：使用 numpy 进行矩阵乘法和解线性方程组

```python
import numpy as np

# 新建矩阵
x = np.array([2, 0, 0, 0.5, 1.875, 0, 0, 0.5, 1.867]).reshape(3, 3)
b = np.array([1, 2, 3]).reshape(1, 3)

# 矩阵乘法
np.matmul(x, y)

# 解线性方程组
np.linalg.solve(x, b)
```

### Proj 4 实现 Jacobi 方法和 Gauss-Seidel 方法

- [向量范数的理解](https://blog.csdn.net/lz867422770/article/details/80013600)
- [矩阵的特征分解](https://zhuanlan.zhihu.com/p/314464267)
- [矩阵特征分解的条件](https://blog.csdn.net/u012845311/article/details/76461424)
- 矩阵的奇异值分解：看《统计学习方法》, [奇异值分解](https://zhuanlan.zhihu.com/p/29846048)

### Proj 5 LU 分解 + inverse power method 求解特征值和特征向量

条件：给出特征值的估计值 q，给出特征向量的初始值 $\hat{x}^{(0)}$

引理：如果 x 是 A 的关于 $\lambda$ 的特征向量，那么 x 也是 $A^{-1}$ 的关于 $\frac{1}{\lambda}$ 的特征向量

先判断给定的 q 是不是 A 的特征值，即 $\det(A-qI)=0$ 是否成立。我的做法是做初等行变换计算行列式。(tips: 可以提前做判断，也可以在后面迭代解方程的时候，如果方程没有解说明 q 就是特征值)

初始化：对 $\hat{x}^{(0)}$ 进行 normalization (**注意 normalization 是把最长的维度变成 1，需要考虑符号；而不是把最长的维度长度变成 1，否则最后无法收敛**)

$$
\left\{\begin{matrix} 
  A-qI=A' \\
  x^{(0)} = \frac{\hat{x}^{(0)}}{\hat{x}^{(0)}_p}, where \; |\hat{x}_p^{(0)}| = ||\hat{x}^{(0)}||_{\infty}
\end{matrix}\right.
$$

然后每次的迭代过程就是解方程

$$
\left\{\begin{matrix} 
  (A-qI)\hat{x}^{(k+1)}=x^{(k)} \\  
  x^{(k+1)} = \frac{\hat{x}^{(k+1)}}{\hat{x}^{(k+1)}_p}, where \; |\hat{x}_p^{(k+1)}| = ||\hat{x}^{(k+1)}||_{\infty} \\
  \lambda^{(k)}= \frac{1}{\hat{x}^{(k+1)}_p}+q
\end{matrix}\right.
$$

解方程还是用 ~~高斯消元~~ LU 分解。

直到前后两次迭代的特征值的差小于给定值或者前后两次迭代的特征向量差的范数小于给定值（题目采用前者，书上采用后者），或者迭代次数超过上限，退出迭代，

参考：
- LU 分解：书 P393
- Inverse Power Method：书 P569

---

优化：LU 分解

前提条件：不用行变换就可以完成高斯消元（**注意：本题为了强制使用 LU 分解，只要方程组的系数矩阵不能 LU 分解都当做方程组无解，即当做系数矩阵行列式为 0**）

如果可以 LU 分解的话，对 (A-qI) 进行 LU 分解

$$
\left\{\begin{matrix} 
  l_{i,i}=1 \\
  u_{i,i}=a_{i,i}-\sum_{j=0}^{i-1}l_{i,j}u_{j,i} \\
  l_{j,i}=\frac{1}{u_{i,i}}(a_{j,i}-\sum_{k=0}^{i-1}l_{j,k}u_{k,i}), j>i \\
  u_{i,j}=a_{i,j}-\sum_{k=0}^{i-1}l_{i,k}u_{k,j}, j>i 
\end{matrix}\right. 
$$

整个 LU 分解可以看成是一个 $n\times n$ 元线性方程组求解。过程是从左上角往右下角做，先对 $a_{i,i}$ 列一个方程，假设 $l_{i,i}=1$ 算出 $u_{i,i}$，对角算出来之后对 $a_{i,j}$ 和 $a_{j,i}$ 列方程，可以得到 $u{i,j}$ 和 $l_{j,i}$。

使用 LU 分解可以加速迭代过程中解方程的步骤。

---

拓展：行列式的求法

1. 初等行列变换变成上三角或者下三角，对角线乘积就是行列式
1. 代数余子式，递归求（空间消耗比较大）
1. 枚举全排列，$\sum(-1)^{\tau(j_1,j_2,...,j_n)}a_{1,j_1}a_{2,j_2},...a_{n,j_n}$

这个 Proj 选择用初等行变换实现是因为之后还要用到高斯消元，部分代码可以重用，比较省力。


### 可复用模块

#### 行变换法求矩阵行列式

```c
double MyDet(int n, double a[][MAX_SIZE], double TOL){
    double A[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < n; ++ i)
        for (int j = 0; j < n; ++ j)
            A[i][j] = a[i][j];
    for (int i = 0; i < n; ++ i){
        int max_i = i;
        for (int j = i+1; j < n; ++ j)
            if (fabs(A[j][j]) > fabs(A[max_i][max_i]))
                max_i = j;
        if (max_i != i)
            for (int j = 0; j < n; ++ j){
                MySwap(&A[i][j], &A[max_i][j]);
            }
        if (fabs(A[i][i]) < TOL) return 0;
        for (int j = i+1; j < n; ++ j){
            double frac = A[j][i] / A[i][i];
            for (int k = i; k < n; ++ k)
                A[j][k] -= frac * A[i][k];
        }
    }
    double ret = 1;
    for (int i = 0; i < n; ++ i) ret *= A[i][i];
    return ret;
}
```

#### 高斯消元 + scaled partial pivoting

1. 重复计算了每行的最大值，所以复杂度会比较高。需要降低复杂度的时候可以稍作修改。
1. 会修改 A 和 b 数组中的值，需要提前进行备份。

```c
void MyGaussian(int n, double A[][MAX_SIZE], double b[], double x[]){

    for (int i = 0; i < n; ++ i){
        int max_i;
        double max_value = 0;
        for (int j = i; j < n; ++ j){
            double max_a = 0;
            for (int k = i; k < n; ++ k)
                max_a = MyMax(max_a, fabs(A[j][k]));
            max_a = fabs(A[j][i] / max_a);
            if (max_a > max_value){
                max_value = max_a;
                max_i = j;
            }
        }
        if (max_i != i){
            for (int j = 0; j < n; ++ j)
                MySwap(&A[i][j], &A[max_i][j]);
            MySwap(&b[i], &b[max_i]);
        }
        for (int j = i+1; j < n; ++ j){
            double frac = A[j][i] / A[i][i];
            for (int k = i; k < n; ++ k)
                A[j][k] -= frac * A[i][k];
            b[j] -= frac * b[i];
        }
    }

    for (int i = n-1; i >= 0; -- i){
        x[i] = b[i];
        for (int j = i+1; j < n; ++ j)
            x[i] -= x[j] * A[i][j];
        x[i] /= A[i][i];
    }
}
```

#### LU 分解

1. 不会对原数组进行修改，不用提前备份。
1. 能够进行 LU 分解返回 0，不能分解返回 1

```c
int MyLUFactorization(int n, double A[][MAX_SIZE], double L[][MAX_SIZE], double U[][MAX_SIZE], double TOL){
    for (int i = 0; i < n; ++ i){
        // L[i][i]
        L[i][i] = 1;

        // U[i][i]
        U[i][i] = A[i][i];
        for (int j = 0; j < i; ++ j)
            U[i][i] -= L[i][j] * U[j][i];
        if (fabs(U[i][i]) < TOL) return 1;
        
        // L[j][i]
        for (int j = i+1; j < n; ++ j){
            L[j][i] = A[j][i];
            for (int k = 0; k < i; ++ k)
                L[j][i] -= L[j][k] * U[k][i];
            L[j][i] /= U[i][i];
        }

        // U[i][j]
        for (int j = i+1; j < n; ++ j){
            U[i][j] = A[i][j];
            for (int k = 0; k < i; ++ k)
                U[i][j] -= L[i][k] * U[k][j];
        }
    }
    return 0;
}
```

```c
void MyLUSolveLinearSys(int n, double L[][MAX_SIZE], double U[][MAX_SIZE], double x[], double b[]){
    double y[MAX_SIZE];

    // Ly=b
    for (int i = 0; i < n; ++ i){
        y[i] = b[i];
        for (int j = 0; j < i; ++ j)
            y[i] -= L[i][j] * y[j];
        y[i] /= L[i][i];
    }

    // Ux=y
    for (int i = n-1; i >= 0; -- i){
        x[i] = y[i];
        for (int j = i+1; j < n; ++ j)
            x[i] -= U[i][j] * x[j];
        x[i] /= U[i][i];
    }
}
```

#### 调试函数：输出矩阵、输出向量

```c
void MyPrintMat(int n, double A[][MAX_SIZE]){
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < n; ++ j)
            printf("%7.3lf", A[i][j]);
        printf("\n");
    }
    printf("----------------\n");
}
```

```c
void MyPrintVec(int n, double x[]){
    for (int i = 0; i < n; ++ i)
        printf("%7.3lf", x[i]);
    printf("\n==================\n");
}
```

#### 常用函数：Swap

```c
void MySwap(double *x, double *y){
    double temp = *x;
    *x = *y;
    *y = temp;
}
```