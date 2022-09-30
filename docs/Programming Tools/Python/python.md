# Python 学习笔记

[TOC]

[Python 基础教程 | 菜鸟教程 (runoob.com)](https://www.runoob.com/python/python-tutorial.html)

[Python教程 - 廖雪峰的官方网站 (liaoxuefeng.com)](https://www.liaoxuefeng.com/wiki/1016959663602400)


## 基础

### 简介

1. 解释语言
2. 交互式语言
    - 命令行
    - Jupyter Notebook

### 数据类型

1. 数据类型
    - `type(a)` 查看数据类型
    - `int(a); str(b)` 转换数据类型
    - 定义变量不用声明数据类型
3. 运算符
    - `//` 整除
    - `**` 取幂

### 字符串

1. **单引号和双引号均可**， **单引号包双引号不会打断字符串**
2. 运算符
    - `s1+s2` 连接
    - `s * int` 重复
3. 常见函数
    - `s.split()` 按照空格，tab，换行等划分，返回字符串数组
    - `s.replace(s1, s2)` 
    - `s.upper(); s.lower()`
    - `len(s)`

### 索引和分片

1. 名词解释：索引是取出单个元素，分片是取出多个元素
2. 索引
    - `a[0]` 从 0 开始正向索引
    - `a[-1]` 负数代表从后往前数
3. 分片：`var[start_index: stop_index: step]`
    - 默认分别为：开头，结尾，1

### 列表

0. **同一个数组可以存不同类型的数据**
1. 运算符
    - 加法
    - 乘法
2. 函数
    - `len(arr)`
    - `arr.append()`
    - `arr.extend()` 对 self 进行操作
    - `arr.reverse()` 等效于 `arr[::-1]`
    - 删除：
        - `del arr[index]`
        - `arr.pop(index)`
        - `arr.remove(obj)`
    - 搜索：
        - `obj in arr`
        - `arr.index(obj)`
        - `arr.count(obj)`
    - 排序：
        - `arr.sort(reverse = True/False)`
        - `b = sorted(arr)`

### 字典

1. 定义：
    - `dic={}`
    - `dic = dict()`
2. 函数：
    - 查询：
        - `dic.get(key, default=None)`
        - `dic.keys()`
        - `dic.values()`
        - `dic.items()`

### 元组

Tuple

1. 特性
    - 定义之后无法更改（功能类似 const array）
    - 用小括号定义：`a=(); b=(1,); c=(1,2,3)`
2. 函数
    - `b = list(tuple)`

### 集合

1. 定义
    - 方法一：大括号 `set = {1, 2, 3}`
    - 方法二：列表初始化 `set = set([1, 2, 3]);`

### 代码块

用缩进识别代码块

1. 判断语句
    ```python
    if x > 0:
        print(1)
    elif x < 0:
        print(2)
    else:
        print(3)
    ```
2. 循环语句
    ```python
    # while 循环
    l = [1, 2, 3, 4]
    while l: # 列表非空为 True
        del l[0]
    # for 循环
    for i in range(100):
        print(i)
    for item in _list:
        print(item)
        if (item == "114514"):
            break
    else:
        
    ```
    - 可以使用 continue 和 break
    - 循环的 else

## 其他问题

### 输出中文



```python
f=open('test1.txt','a+',encoding="utf-8")  ## open file -> encoding
json.dumps({'text':"你好"},ensure_ascii=False,indent=2) ## json -> ensure_ascii
## -*- coding: UTF-8 -*-
print( "你好，世界" ) ## print -> 
```



### socket



#### send的参数



必须是 bytes 类型，涉及到 string 和 bytes 的转换

```python
sk.send(bytes(string, encoding='utf-8'))
ret_string = str(sk.recv(6666), 'utf-8')
```





### 文件 I/O



```python
```





### JSON



```python
import json

json_data = json.load(json_file) // 没有s是在JSON和文件之间转换
json.dump(json_data, file)
json_data = json.loads(json_string) // 有s是在JSON和字符串之间转换
string = json.dumps(json_data)

number = json_data['number'] // json 内容直接用方括号调用
string = json.dumps(json_data, ensure_ascii=False) // 用于转换非 ascii 的字符
```



注意：

1. json 的键值要用**字符串**，且只能用**双引号**，格式参考[JSON 数据格式_w3cschool](https://www.w3cschool.cn/json/9l4f1h7u.html)



### tips



1. range(a, b) 生成的是左闭右开区间 [a, b-1]
2. True 和 False 关键字是开头大写的