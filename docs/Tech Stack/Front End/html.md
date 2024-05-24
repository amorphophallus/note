# HTML

[TOC]

## 所有元素参考

[HTML 标签参考手册 (w3school.com.cn)](https://www.w3school.com.cn/tags/index.asp)



## table

[综述](https://www.runoob.com/html/html-tables.html)

[比较全的样例](https://c.runoob.com/codedemo/3187/)



## form & input

一个简单的表单形式如下：

```js
<form name="input" action="html_form_action.php" method="get">
  Username: <input type="text" name="user"><br>
  Password: <input type="password" name="password"><br>
  <input type="radio" name="sex" value="male">男<br>
  <input type="radio" name="sex" value="female">女<br>
  <input type="checkbox" name="vehicle" value="Bike">我喜欢自行车<br>
  <input type="checkbox" name="vehicle" value="Car">我喜欢小汽车<br>
  <input type="file" name="file"/>
  <input type="submit" value="Submit">
</form>
```

---

input 常见类型：

- 输入类型
    1. text: 定义单行的输入字段，用户可在其中输入文本。默认宽度为 20 个字符。
    1. password: 定义密码字段。该字段中的字符被掩码。
    1. radio: 定义单选按钮。
        - 不同的 radio 设置了同一个 name 才能算在同一个单选题中
    1. checkbox: 定义复选框。
        - 不同的 checkbox 设置了同一个 name 才能算在同一个单选题中
    1. file: 定义输入字段和 "浏览"按钮，供文件上传。
    1. hidden: 定义隐藏的输入字段。
- 提交类型
    1. submit: 定义提交按钮。提交按钮会把表单数据发送到服务器。
    1. button: 定义可点击按钮
        - 多数情况下，使用 `onclick` 属性，通过 JavaScript 启动脚本
    1. image: 定义图像形式的提交按钮。
        - 必须有 src 和 alt 属性
    1. reset: 定义重置按钮。重置按钮会清除表单中的所有数据。

input 常见属性：
1. name：只有设置了 name 属性的表单元素才能在提交表单时传递它们的值。
1. value：显示在元件上的东西（button 或者 text 之类）
1. placeholder：文本框内没有文字的时候用灰色字体显示
1. event：input / change / beforeinput [HTMLElement: input event - Web APIs | MDN (mozilla.org)](https://developer.mozilla.org/en-US/docs/Web/API/HTMLElement/input_event)

---

实战：

1. [将 file 中的文字取出放在 textarea中](https://blog.csdn.net/zxl_1996/article/details/105781714)



## label

[label 配合可点击的控件使用](https://www.w3school.com.cn/tags/tag_label.asp)

label："for" 属性可把 label 绑定到另外一个元素。请把 "for" 属性的值设置为相关元素的 **id** 属性的值。

`<label for="male">Male</label>`



## canvas

### 如何用 canvas 做 background

position 设成 absolute

然后 z-index 设置成最小，相当于置于底层。



### 一些注意事项

1. 尽量不要贴着边画，不然会看起来边上的线细一点（实际上是超出画布了）