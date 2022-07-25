[TOC]



[CSS 课件](https://scratched-antimatter-2e3.notion.site/CSS-e18457e1c3364fb79cfdbb90fa0c224d)

有用 ： [flex 布局的基本概念 - CSS（层叠样式表）](https://developer.mozilla.org/zh-CN/docs/Web/CSS/CSS_Flexible_Box_Layout/Basic_Concepts_of_Flexbox##元素间的对齐和空间分配)



## 开始



```js
import './styles/style.css' // 记得引入
```





## 基础

############ 对象

```
h1
a:link
.manythings  (class=manythings)
##onething    (id=onething)
*
.box p
.box p:first-child
h1, h2, .intro
```

注意 id 不能只有数字（太伞兵了）

```css
// 包含关系
h1 p{
    
}

// 并列关系
h1 + p{
    
}
```



############ padding, border & margin

![](https://img-blog.csdn.net/20180726145644500?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MDkyNjYyOQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

有些 margin 的默认值可能不是 0，有的白边去不掉可以尝试手动设置 margin。



############ 字体

`font` 简写

`font-size` 字体大小

`font-family` 字体

`font-weight` 字体粗细

[font - CSS（层叠样式表） | MDN (mozilla.org)](https://developer.mozilla.org/zh-CN/docs/Web/CSS/font)



## 盒子大小



`1vw` 是页面宽度的 1% ， `1vh` 是页面高度的 1%。

`1em` 一个字体大小



## 排版



############ justify-content

`justyfy-content` 主轴上的排列 `space-around/space-between`（但配合 wrap 食用的时候效果并不好）

不如用 `center` 加上 `margin=xxx%` 效果好

############ 其他

`align-items` 交叉轴上的排列

`overflow/overflow-x/overflow-y` 溢出设置，需要配合 `max-width/max-height` 食用

[overflow](https://developer.mozilla.org/zh-CN/docs/Web/CSS/overflow)





############ 伸缩





## flexbox

[MDN_flexbox](https://developer.mozilla.org/zh-CN/docs/Web/CSS/CSS_Flexible_Box_Layout/Basic_Concepts_of_Flexbox##%E6%9B%B4%E6%94%B9flex%E6%96%B9%E5%90%91_flex-direction)



## position



- `static`

    该关键字指定元素使用正常的布局行为，即元素在文档常规流中当前的布局位置。此时 `top`, `right`, `bottom`, `left` 和 `z-index `属性无效。

- `relative`

    该关键字下，元素先放置在未添加定位时的位置，再在不改变页面布局的前提下调整元素位置（因此会在此元素未添加定位时所在位置留下空白）。position:relative 对 table-*-group, table-row, table-column, table-cell, table-caption 元素无效。

- `absolute`

    元素会被移出正常文档流，并不为元素预留空间，通过指定元素相对于最近的非 static 定位祖先元素的偏移，来确定元素位置。绝对定位的元素可以设置外边距（margins），且不会与其他边距合并。

    *absolute 相对于 flexbox 内部元素定位的时候会有点迷，所以最好不要和 space-around 之类的属性一起用*

- `fixed`

    元素会被移出正常文档流，并不为元素预留空间，而是通过指定元素相对于屏幕视口（viewport）的位置来指定元素位置。元素的位置在屏幕滚动时不会改变。打印时，元素会出现在的每页的固定位置。`fixed` 属性会创建新的层叠上下文。当元素祖先的 `transform`, `perspective` 或 `filter` 属性非 `none` 时，容器由视口改为该祖先。

- `sticky`

    元素根据正常文档流进行定位，然后相对它的*最近滚动祖先（nearest scrolling ancestor）*和 [containing block](https://developer.mozilla.org/en-US/docs/Web/CSS/Containing_block) (最近块级祖先 nearest block-level ancestor)，包括table-related元素，基于`top`, `right`, `bottom`, 和 `left`的值进行偏移。偏移值不会影响任何其他元素的位置。

    该值总是创建一个新的[层叠上下文（stacking context](https://developer.mozilla.org/en/docs/Web/CSS/CSS_Positioning/Understanding_z_index/The_stacking_context)）。注意，一个sticky元素会“固定”在离它最近的一个拥有“滚动机制”的祖先上（当该祖先的`overflow` 是 `hidden`, `scroll`, `auto`, 或 `overlay`时），即便这个祖先不是最近的真实可滚动祖先。这有效地抑制了任何“sticky”行为（详情见[Github issue on W3C CSSWG](https://github.com/w3c/csswg-drafts/issues/865)）。



[详细介绍](https://developer.mozilla.org/zh-CN/docs/Web/CSS/position)



## border



border-style

| `none`   | 和关键字 `hidden` 类似，不显示边框。在这种情况下，如果没有设定背景图片，[`border-width`](https://developer.mozilla.org/zh-CN/docs/Web/CSS/border-width) 计算后的值将是 `0`，即使先前已经指定过它的值。在单元格边框重叠情况下，`none` 值优先级最低，意味着如果存在其他的重叠边框，则会显示为那个边框。 |
| -------- | ------------------------------------------------------------ |
| `hidden` | 和关键字 `none` 类似，不显示边框。在这种情况下，如果没有设定背景图片，[`border-width`](https://developer.mozilla.org/zh-CN/docs/Web/CSS/border-width) 计算后的值将是 `0`，即使先前已经指定过它的值。在单元格边框重叠情况下，`hidden` 值优先级最高，意味着如果存在其他的重叠边框，边框不会显示。 |
| `dotted` | 显示为一系列圆点。标准中没有定义两点之间的间隔大小，视不同实现而定。圆点半径是 [`border-width`](https://developer.mozilla.org/zh-CN/docs/Web/CSS/border-width) 计算值的一半。 |
| `dashed` | 显示为一系列短的方形虚线。标准中没有定义线段的长度和大小，视不同实现而定。 |
| `solid`  | 显示为一条实线。                                             |
| `double` | 显示为一条双实线，宽度是 [`border-width`](https://developer.mozilla.org/zh-CN/docs/Web/CSS/border-width) 。 |
| `groove` | 显示为有雕刻效果的边框，样式与 `ridge` 相反。                |
| `ridge`  | 显示为有浮雕效果的边框，样式与 `groove` 相反。               |
| `inset`  | 显示为有陷入效果的边框，样式与 `outset` 相反。当它指定到 [`border-collapse`](https://developer.mozilla.org/zh-CN/docs/Web/CSS/border-collapse) 为 `collapsed` 的单元格时，会显示为 `groove` 的样式。 |
| `outset` | 显示为有突出效果的边框，样式与 `inset` 相反。当它指定到 [`border-collapse`](https://developer.mozilla.org/zh-CN/docs/Web/CSS/border-collapse) 为 `collapsed` 的单元格时，会显示为 `ridge` 的样式。 |

