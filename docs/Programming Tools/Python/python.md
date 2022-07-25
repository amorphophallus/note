# Python 学习笔记

[TOC]

[Python 基础教程 | 菜鸟教程 (runoob.com)](https://www.runoob.com/python/python-tutorial.html)

[Python教程 - 廖雪峰的官方网站 (liaoxuefeng.com)](https://www.liaoxuefeng.com/wiki/1016959663602400)





## 输出中文



```python
f=open('test1.txt','a+',encoding="utf-8")  ## open file -> encoding
json.dumps({'text':"你好"},ensure_ascii=False,indent=2) ## json -> ensure_ascii
## -*- coding: UTF-8 -*-
print( "你好，世界" ) ## print -> 
```



## socket



### send的参数



必须是 bytes 类型，涉及到 string 和 bytes 的转换

```python
sk.send(bytes(string, encoding='utf-8'))
ret_string = str(sk.recv(6666), 'utf-8')
```





## 文件 I/O



```python
```





## JSON



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



## tips



1. range(a, b) 生成的是左闭右开区间 [a, b-1]
2. True 和 False 关键字是开头大写的