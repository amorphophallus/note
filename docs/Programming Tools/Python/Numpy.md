# Numpy

[TOC]

## 前言

### 参考文档

1. [Numpy 入门教程](https://betterprogramming.pub/numpy-illustrated-the-visual-guide-to-numpy-3b1d4976de1d)
2. [Numpy 菜鸟教程](https://www.runoob.com/numpy)
3. [Numpy 进阶文档](https://www.labri.fr/perso/nrougier/from-python-to-numpy/)

### 约定

在以下文档中，
- `np` 代指 `numpy`
- `a, b, c, ...` 是 `ndarray`

## 基础操作

## 数据类型

1. `a.dtype` 查看数据类型
2. `a = b.astype('int32')` 修改数据类型 

### 创建数组

1. `np.arange()` 不包含 stop
2. `np.linspace()` 等差数列
3. `np.logspace()` 等比数列

### 矩阵的自我重复

在 `axis` 那一维上重复 `n` 次，形状从 `(a, b, c)` 变成 `(a, b*n, c)`

```python
a = np.arange(8).reshape(2, 2, 2)
b = np.repeat(a, 2, axis = 1)
print(a)
print(a.shape)
print(b)
print(b.shape)

>>>
# a
[[[0 1]
  [2 3]]

 [[4 5]
  [6 7]]]
(2, 2, 2)
# b
[[[0 1]
  [0 1]
  [2 3]
  [2 3]]

 [[4 5]
  [4 5]
  [6 7]
  [6 7]]]
(2, 4, 2)

```

## 索引

### 数组索引

```python
a = np.array([[1,2,3], [4,5,6],[7,8,9]])
b = np.array([0, 1, 2])
c = np.array([0, 1, 2])
print(a[b, c])

>>> [1, 5, 9] # == [a[0, 0], a[1, 1], a[2, 2]]
```

### 切片

可以降维或者不降

`:` 代表某一维全部取，`...` 表示前面的所有维都全部取，例如 `a[:, :, :, :-1]` 等价于 `a[..., :-1]`

```python
a = np.array([[1,2,3,4],[5,6,7,8],[9,10,11,12]]).reshape(2, 2, 3)
print(a)
print (a[...,1])

>>> 
[[[ 1  2  3]
  [ 4  5  6]]

 [[ 7  8  9]
  [10 11 12]]]  # a
[[ 2  5]
 [ 8 11]]       # a[..., 1]
```

### 布尔索引

To be continued.

## 矩阵操作

### reshape

`a.reshape(H, W, C, -1)`

-1 表示让程序自己算最后一维


### 两种拼接

#### concatenate

`np.concatenate((a, b), axis=0)` 不会增加数组维度

`concatenate` 更方便理解

```python
# 第一个数组：
[[1 2]
 [3 4]]


# 第二个数组：
[[5 6]
 [7 8]]


# 沿 axis = 0 连接两个数组：
[[1 2]
 [3 4]
 [5 6]
 [7 8]]


# 沿 axis = 1 连接两个数组：
[[1 2 5 6]
 [3 4 7 8]]
```

#### stack

`np.stack((a, b), axis=0)` 会增加数组维度

```python
# 第一个数组：(2, 2)
[[1 2]
 [3 4]]


# 第二个数组：(2, 2)
[[5 6]
 [7 8]]


# 沿轴 0 堆叠两个数组：(2, 2, 2)
[[[1 2]
  [3 4]]

 [[5 6]
  [7 8]]]


# 沿轴 1 堆叠两个数组：(2, 2, 2)
[[[1 2]
  [5 6]]

 [[3 4]
  [7 8]]]

# 沿轴 2 堆叠两个数组：(2, 2, 2)
[[[1 5]
  [2 6]]

 [[3 7]
  [4 8]]]
```

### 去除循环

1. 函数
    - `np.floor/ceil/round(a)`
    - `np.sin/cos/arctan(a)`
2. 运算
    - `a+1` 给所有元素 +1
    - `np.all/any/none(a)` 对 bool 矩阵做布尔运算


###


## 运算

###  矩阵乘法（高维）

相当于先切片，对于对应的矩阵分别做乘法，最后再 stack 起来。

例如 `a[N1, N2, N3, H, W]` 和 `b[N1, N2, N3, W, C]` 相乘，相当于 `N1 * N2 * N3` 个矩阵相乘，得到结果 `res[N1, N2, N3, H, C]`

```python
a = np.arange(8).reshape(2,2,2) 
b = np.arange(4).reshape(2,2) 
print(a)
print(b)
print (np.matmul(a,b))

>>>
# a
[[[0 1]
  [2 3]]

 [[4 5]
  [6 7]]]
# b
[[0 1]
 [2 3]]
# np.matmul(a, b)
[[[ 2  3]
  [ 6 11]]

 [[10 19]
  [14 27]]]
```



## Log

*2022.7.26upd* 你啥时候开始写 lab2 呀...