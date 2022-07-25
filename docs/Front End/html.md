[TOC]

# 所有元素参考

[HTML 标签参考手册 (w3school.com.cn)](https://www.w3school.com.cn/tags/index.asp)



# table

[综述](https://www.runoob.com/html/html-tables.html)

[比较全的样例](https://c.runoob.com/codedemo/3187/)



# form

点击submit之后上传整个表单

action



# input

[input 的所有 type 属性](https://www.w3school.com.cn/tags/att_input_type.asp)

[input 的其他可用属性](https://www.w3school.com.cn/tags/tag_input.asp)

name：只有设置了 name 属性的表单元素才能在提交表单时传递它们的值。

value：显示在元件上的东西（button 或者 text 之类）

placeholder：文本框内没有文字的时候用灰色字体显示

event：input / change / beforeinput [HTMLElement: input event - Web APIs | MDN (mozilla.org)](https://developer.mozilla.org/en-US/docs/Web/API/HTMLElement/input_event)

### radio

单选

不同的radio设置了同一个name才能算在同一个单选题中。

[radio对象自带的属性和方法](https://www.w3school.com.cn/jsref/dom_obj_radio.asp)

### textarea 和 file

[将 file 中的文字取出放在 textarea中](https://blog.csdn.net/zxl_1996/article/details/105781714)



### button 的一般形式

```html
<input type="button" value="Click me" onclick="msg()" />
<button></button>
```

用 js 来修改 button 的 onclick 属性

```javascript
document.getElementById('but').addEventListener('click', () => {
	/*content*/
})
```

注意要先在 html 中定义这个元素然后再修改他的属性。一般来说都把这个 js 文件放在 body 的最后。

# label



[label 配合可点击的控件使用](https://www.w3school.com.cn/tags/tag_label.asp)

label："for" 属性可把 label 绑定到另外一个元素。请把 "for" 属性的值设置为相关元素的 **id** 属性的值。

`<label for="male">Male</label>`



# canvas

### 如何用 canvas 做 background

position 设成 absolute

然后 z-index 设置成最小，相当于置于底层。



### 一些注意事项

1. 尽量不要贴着边画，不然会看起来边上的线细一点（实际上是超出画布了）