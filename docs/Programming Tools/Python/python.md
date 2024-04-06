# Python 学习笔记

[TOC]

> [Python 基础教程 | 菜鸟教程 (runoob.com)](https://www.runoob.com/python/python-tutorial.html)
> [Python教程 - 廖雪峰的官方网站 (liaoxuefeng.com)](https://www.liaoxuefeng.com/wiki/1016959663602400)


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
2. 运算符
    - `//` 整除
    - `**` 取幂
3. 数字函数：
    - max & min： **可以有任意多个参数**
    - `sum(lst)`: 列表求和

### 字符串

1. **单引号和双引号均可**， **单引号包双引号不会打断字符串**
2. 运算符
    - `s1+s2` 连接
    - `s * int` 重复
3. 常见函数
    - `s.split()` 按照空格，tab，换行等划分，返回字符串数组
    - `s.join(sequence)` : 以 s 为连接符将序列 sequence 中的元素连接起来，并返回连接后得到的新字符串
    - `s.replace(s1, s2)` : 从头用 s1 匹配 s，一旦匹配则替换，会替换所有的匹配项
    - `s.upper(); s.lower()`: 大小写转换
    - `len(s)`

### 索引和分片

1. 名词解释：索引是取出单个元素，分片是取出多个元素
2. 索引
    - `a[0]` 从 0 开始正向索引
    - `a[-1]`: 索引 -1 表示倒数第 1 个元素
3. 分片：`var[start_index: stop_index: step]`
    - 默认分别为：开头，结尾，1
    - 范围左闭右开，即 `[start_index, stop_index)`
    - 可类比 for 循环，如果 step 是负数，则 start_index 要大于 stop_index

### 列表

0. **同一个数组可以存不同类型的数据**
1. 运算符
    - 定义: [] 或者 list([obj])
        - `list()` 的参数可以是 **空、列表或者元组**，如果是单个元素需要用 [] 包裹起来
    - 加法: 相当于将两个列表按顺序连接
    - 乘法: 列表与整数相乘，相当于将列表重复相加
        - **注意：如果列表内元素的赋值是传地址，则乘法得到的元素也是简单的复制地址**
2. 函数
    - `len(arr)`
    - 添加；
        - `arr.append(obj)`: 单个元素添加到列表最后
            - *元素可以是序列，但不展开*
        - `arr.extend(lst)`: 序列元素依次添加到列表最后
        - `arr.insert(idx, obj)`: 在索引 idx 处插入 ob ，之后的元素依次后移
    - 删除：
        - `del arr[index]`
        - `arr.pop(index)`
        - `arr.remove(obj)`: 将列表中第一个出现的 obj 删除
        - **删除后序列下标仍连续，长度变短**
    - 搜索：
        - `obj in arr` & `obj not in arr`: 返回 True or False
        - `arr.index(obj)`: *如果 obj 不在 arr 中会报错*
        - `arr.count(obj)`
    - 排序：
        - `arr.sort(reverse = True/False)`
        - `b = sorted(arr)`: 不改变原来列表中的值
        - `arr.reverse()`: *改变原列表*
        - `b = arr[::-1]`: *不改变原列表*

### 字典

1. 定义：
    - 是一种由 *键值对* 组成的数据结构
    - `dic = {}`
    - `dic = dict()`
2. 函数：
    - 查询：
        - 索引：`dic[key]`
        - `dic.get(key, default=None)`: 如果没有这个键，返回 default 指定的值（默认是 None)
    - `dic.keys()`: 返回 type 是 `dict_keys` 不能使用索引，但是可以 `extend` 到列表上然后使用索引
    - `dic.values()`
    - `dic.items()`
3. 注意：
    - 字典的键必须是数字、字符串、元组等，不能是列表、字典、集合
    - *字典没有顺序* ：print 一个字典时，Python 并不一定按照插入键值的先后顺序进行显示

### 元组

Tuple

1. 特性
    - 定义之后无法更改（功能类似 const array）
    - 用小括号定义：`a=(); b=(1,); c=(1,2,3)`
2. 函数
    - `b = list(tuple)`: 转化为列表

### 集合

1. 定义
    - 方法一：大括号 `set = {1, 2, 3}`
    - 方法二：列表初始化 `set = set([1, 2, 3])`
    - 定义空集合: `a = set()`
2. 方法：
    - `in & not in`
    - 转化为列表进行操作

### 判断和循环

*用缩进识别代码块*

1. 判断语句
    ```python
    if x > 0:
        print(1)
    elif x < 0:
        print(2)
    else:
        print(3)
    ```
    - 大部分表达式的值都会被当作 True, 但以下表达式值会被当作 False:
        - False
        - None
        - 0
        - 空字符串，空列表，空字典，空集合
2. 循环语句
    - while 循环
    ```python
    l = [1, 2, 3, 4]
    while l: # 列表非空为 True
        del l[0]
    ```
    - for 循环
    ```python
    for i in range(100):
        print(i)
    for item in _list:
        print(item)
        if (item == "114514"):
            break
    else:
        
    ```
    - 可以使用 continue 和 break
    - *循环的 else*
        - 当循环正常结束时，循环条件不满足， else 被执行；当循环被 break 结束时，循环条件仍然满足， else 不执行。

## 进阶

### 推导式

1. 列表推导式
    - 循环生成列表: 
        ```python
        a = [x for x in range(4)]
        ```
    - 循环 + if: 
        ```python
        a = [x for x in range(3,10) if x % 2 == 0]
        ```
    - 多重循环 + 元组: 
        ```python
        a = [(x,y,z) for x in range(1,3) for y in range(1,3) for z in range(1,3)]
        ```
2. 字典推导式
    - `key:value` 表示键值对
        ```python
        values = [10, 21, 4, 7, 12]
        square_dict = {x: x**2 for x in values if x <= 10}
        ```
3. 集合推导式
    ```python
    values = [10, 21, 4, 7, 12]
    square_set = {x**2 for x in values if x <= 10}
    ```

### 函数

1. 定义
    ```python
    def add(x, y):
        """Add two numbers""" # docstring, explaining this funxtion
        a = x + y
        return a
    ```
    - 设定参数默认值
    - 不定长参数
        ```python
        def add(x, *args):
            total = x
            for arg in args:
                total += arg
            return total
        ```
    - 带关键词的不定长参数
        ```python
        def add(x, **kwargs):
            total = x
            for arg, value in kwargs.items():
                print("adding %s=%s"%(arg,value))
                total += value
            return total
        
        add(10, y=11, z=12, w=13)
        ```
        - 传入的数据以字典的形式存储，可以用字典的方法
2. 使用
    - 传入参数的 2 种模式：按照位置传入参数 & 关键词模式
        ```python
        add(2, 3)
        add(y="foo", x="bar")
        ```
    - 多个返回值
        ```python
        def divid(a, b):
            quotient = a // b
            remainder = a % b
            return quotient, remainder

        quotient, remainder = divid(7,4)
        ```
        - 返回值的类型 `type(divid(1, 2))` 是元组，同样的语法可以用于列表
    - 用元组和字典传参
        ```py
        z = (7,4)
        print(divid(*z))

        z = {'a':7,'b':4}
        print(divid(**z))
        ```
        - *注意 * 号的使用*
3. **map 方法**
    - 传入的列表或者元组个数等于函数参数的个数，返回 map object，可转化为 list
    ```py
    list(map(divid,a,b))
    ```
#### Python 内置函数

1. zip: 将可迭代的对象作为参数，将对象中对应的元素打包成一个个元组，然后返回由这些元组组成的列表
    ```py
    a = [1,2,3]
    c = [4,5,6,7,8]
    zip(a,c)
    
    output: [(1, 4), (2, 5), (3, 6)] # 元素个数与最短的列表一致
    ```

2. random: 

```py
import random

print( random.randint(1,10) )        # 产生 1 到 10 的一个整数型随机数  
print( random.random() )             # 产生 0 到 1 之间的随机浮点数
print( random.uniform(1.1,5.4) )     # 产生  1.1 到 5.4 之间的随机浮点数，区间可以不是整数
print( random.choice('tomorrow') )   # 从序列中随机选取一个元素
print( random.randrange(1,100,2) )   # 生成从1到100的间隔为2的随机整数
```

3. print:

[print 格式化输出](https://blog.csdn.net/sinat_28576553/article/details/81154912)：简而言之就是可以长得跟 C 很像，也可以长得跟 C# 很像

```py
print("{} + {} = {}".format(1, 1, 1+1)) # 类似于 printf 的输出方式
```

4. argmin / argmax

返回元素最值的索引

```py
import numpy as np
a = np.array([3, 1, 2, 4, 6, 1])
b = np.argmax(a)
```

5. deepcopy

深拷贝，地址不相同

```py
import copy
a = [1, 2, 3]
d = copy.deepcopy(a) # a和d的地址不相同
```

python 的函数形参是实参的引用，修改函数参数的操作会直接影响在函数外部的参数本身。比如下面 f1 会改变外部的 arr，而 f2 改变了形参引用的地址，arr 不会改变。

```py
def f1(arr):
    arr.append(2)

def f2(arr):
    arr = copy.deepcopy(arr2)

arr = [1, 2, 3]
arr2 = [5, 6, 7]
f1(arr)
f2(arr)
```

#### 传参：传值 vs 引用

1. 自定义类型传参是引用(赋值也是引用)

```py
class node:
    x = 1

def func(node):
    node.x = 123

node = node()
func(node)
print(node.x)
```

输出为 123

### 模块和包

1. 导入
    - 模块
        ```py
        # 语法一
        import ex1
        ex1.add(1, 2)
        # 语法二
        from ex2 import add
        from ex3 import *
        add(2, 3)
        ```
    - 包
        - 结构
            ```sh
            /foo
            ├─__init__.py
            ├─bar.py
            └─baz.py
            ```
        - 导入: foo 文件夹在 PYthon 的搜索路径中
            ```py
            from foo.bar import func
            ```
2. 导入的原理: 执行一遍模块的代码
    - 重新导入
        ```py
        from imp import reload
        reload(ex1)
        ```
        - *直接再次 import 不会执行模块中的代码*
    - *区分运行状态：`__name__`*
        ```py
        if __name__ == '__main__':
        test()
        ```
        - 只有当文件被当作脚本执行的时候， __name__ 的值才会是 `'__main__'`

#### Python 常用包

1. 三维画图：`Axes3D`
2. 表格：`pandas.DataFrame` [有需要照着这个文档写就行了](https://blog.csdn.net/Parzival_/article/details/114240650)

### 异常处理

[Python 标准异常查表](https://www.runoob.com/python/python-exceptions.html)

```py
try:
    <code>
except ValueError as exc:   # 获取异常数据
    <code>
except ZeroDivisionError:   # 处理特定种类的异常
    <code>
except Exception:           # 处理所有其他异常
    <code>
except:                     # 处理不继承 Exception 的异常
    <code>
else:                       # 不出现异常执行
    <code>
finally:                    # 不管是否异常都执行
    <code>
```

注意：

1. 最多只会执行 1 个 `except` 语句，所以可以用 `except: Exception` 接收所有其他异常
2. 如果出现异常并没有被获取，`finally` 会在抛出异常前执行；如果捕获异常，在最后执行

### warning

[warning 种类查表](https://docs.python.org/3/library/warnings.html)

1. 发出 warning
    ```py
    import warnings
    warnings.warn(msg, WarningType = UserWarning)
    ```
2. 忽略 warning
    ```py
    import warnings
    warnings.filterwarnings(action = 'ignore', category = RuntimeWarning)
    ```

### 文件读写

1. 常见用法
    - `f = open(file, [mode])`: 打开文件
        - 'r': 只读
        - 'w': 从头写入（如果文件不存在会被创建；如果文件已经存在， w 模式会覆盖之前写的所有内容）
        - 'a': 追加模式(不会覆盖之前已经写入的内容，而是在之后继续写入)
        - 'w+': 读写模式
    - `text = f.read()`: 读全文
    - `lines = f.readlines()`: 返回一个列表，每个元素代表文件中每一行的内容
    - `for line in f:`: 遍历每一行的内容
    - `f.close()`: 关闭文件
    - 'f.seek(idx)': 移动到文件的第 idx 个字符处，然后可以用 f.read() 读出剩下的内容
2. **with 写法**
    ```py
    with open('newfile.txt','w') as f:
        <code>
    ```
    - 自动 close，更安全
3. 注意事项
    - *读写结束后必须关闭文件* ，否则会出现未完整写入等问题：可以使用 try/except/finally 块来关闭文件

### CSV

1. csv 是什么？
    - Comma-Separated Values，逗号分隔值文件格式
    - excel 可以导出为 csv，也可以打开 csv 文件

意思是 python 有库可以操作 excel 文件。

## 面向对象

[python document class](https://docs.python.org/zh-cn/3/tutorial/classes.html)

1. 方法函数在声明时，有一个显式的参数代表本对象，该参数由调用隐式提供



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


### pytorch & cuda

**注意 python & pytorch & torchvision & cuda 的版本对应关系！！！**

首先讲一下，在某一台不清楚配置的电脑上，怎么确定要安装什么版本的包：

1. 首先，根据显卡型号确定 cuda 的版本，对应关系去 NVIDIA 官网上看。下载好了之后基本就不动了。通过 `nvcc -V` 查看 cuda 版本，这里我的 cuda 版本是 `V10.1`
    - [nvcc -V 和 nvidia-smi cuda 版本不一致](https://blog.csdn.net/sophicchen/article/details/120782209)，和 pytorch 版本对应的是 nvcc -V 看到的 cuda 版本
2. 然后去 [pytorch 官网](https://pytorch.org/get-started/previous-versions/) 找 cuda 版本对应的 pytorch 版本，可以直接 `ctrl+f` 搜索，这里我找到的版本是 `pip install torch==1.7.1+cu101 torchvision==0.8.2+cu101 torchaudio==0.7.2 -f https://download.pytorch.org/whl/torch_stable.html`
3. 在创建环境之前，先去 [torch 官方仓库](https://github.com/pytorch/vision#installation) 里找 torch 和 python 的对应关系，一般 3.9, 3.10 就可以了，保证版本足够高就 ok；但是也不要太高，太高了 pytorch 可能没有适配的版本
4. 如果能够用 pip 下载那么到上一步就结束了。但是在 conda 和 pip 源里都找不到包，所以采用离线下载。
    1. 先查看当前环境适配的版本 `pip debug --verbose`，在 `compatible tags` 中就是所有适配的标签，比如我的环境是 python 3.9 ，适配的版本有
        ```python
        Compatible tags: 33
        cp39-cp39-win_amd64
        cp39-abi3-win_amd64
        cp39-none-win_amd64
        cp38-abi3-win_amd64
        cp37-abi3-win_amd64
        cp36-abi3-win_amd64
        cp35-abi3-win_amd64
        cp34-abi3-win_amd64
        cp33-abi3-win_amd64
        cp32-abi3-win_amd64
        py39-none-win_amd64
        py3-none-win_amd64
        py38-none-win_amd64
        py37-none-win_amd64
        py36-none-win_amd64
        py35-none-win_amd64
        py34-none-win_amd64
        py33-none-win_amd64
        py32-none-win_amd64
        py31-none-win_amd64
        py30-none-win_amd64
        cp39-none-any
        py39-none-any
        py3-none-any
        py38-none-any
        py37-none-any
        py36-none-any
        py35-none-any
        py34-none-any
        py33-none-any
        py32-none-any
        py31-none-any
        py30-none-any
        ```
        实在没有对应的版本，就找个最接近的，然后修改文件名，参考 [这篇博客](https://blog.csdn.net/qq_44832009/article/details/129351554)，但修改文件名后续容易出错。
    2. 然后在 [pytorch 历史版本](https://download.pytorch.org/whl/torch_stable.html) 页面找到想要的版本，下载。我这次下载的是 `cu101/torch-1.7.1%2Bcu101-cp39-cp39-win_amd64.whl`，具体含义为
        - cu102:表示cuda版本为10.2
        - torch-1.7.1:表示torch版本为1.7.1
        - cp38:表示适用python版本为3.8
        - linux:表示适用于linux系统
        - x86_64:表示同时兼容32和64位系统
    3. 然后进入 whl 文件所在目录，`pip install 文件名.whl` 即可安装到对应环境

最终的配置步骤：

1. conda 创建一个 python 版本为 3.9 的环境：`conda create -n CV2023 python==3.9`
1. 在 [pytorch 历史版本](https://download.pytorch.org/whl/torch_stable.html) 网站上下载 `cu101/torch-1.7.1%2Bcu101-cp39-cp39-win_amd64.whl` 文件
1. 进入 whl 文件所在目录，安装到环境中 `pip install torch-1.7.1+cu101-cp39-cp39-win_amd64.whl`
1. 在 [pytorch 历史版本](https://download.pytorch.org/whl/torch_stable.html) 网站上下载 `cu101/torchvision-0.8.2%2Bcu101-cp39-cp39-win_amd64.whl`
1. 进入 whl 文件所在目录，安装到环境中 `pip install torchvision-0.8.2+cu101-cp39-cp39-win_amd64.whll`


其他可能用到的：

- [AssertionError: Torch not compiled with CUDA enabled 报错解决方法](https://blog.csdn.net/m0_74890428/article/details/130184164)：报错原因就是 cuda 和 pytorch 版本不匹配，解决方法就是卸载重装对应版本的 pytorch
- [查看 torch 是否是 gpu 版本](https://blog.csdn.net/weixin_44498476/article/details/125944962)
- [pip 换源](https://blog.csdn.net/skyyzq/article/details/113417832)：`-i https://pypi.tuna.tsinghua.edu.cn/simple`
- 解决 cuda 显存地址不够的问题：RuntimeError: CUDA out of memory. Tried to allocate 20.00 MiB (GPU 0; 2.00 GiB total capacity; 1.23 GiB already allocated; 15.00 MiB free; 1.31 GiB reserved in total by PyTorch) **还没解决**

再举个例子：

- 实验室的 155 服务器。`nvcc -V` 发现 Runtime cuda 版本是 9.1，`nvidia-smi` 发现 Driver cuda 版本是 11.6
- 先看 Runtime CUDA，在官网只找到 9.0 和 9.2 所以选了 9.2，python 选择 3.10。
- 但是 pip 找不到 9.2 那么早的了，还是改成 11.6 了，也可以跑

所以最后的命令是：

- `conda create -n NLP python=3.10`
- `conda activate NLP`
- `pip install torch==1.7.1+cu92 torchvision==0.8.2+cu92 torchaudio==0.7.2 -f https://download.pytorch.org/whl/torch_stable.html`