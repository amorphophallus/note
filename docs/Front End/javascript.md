# javascript

[TOC]

## JavaScript 语言

### 数组操作备忘单

- 添加/删除元素：
  - `push(...items)` —— 向尾端添加元素，
  - `pop()` —— 从尾端提取一个元素，
  - `shift()` —— 从首端提取一个元素，
  - `unshift(...items)` —— 向首端添加元素，
  - `splice(pos, deleteCount, ...items)` —— 从 `pos` 开始删除 `deleteCount` 个元素，并插入 `items`。
  - `slice(start, end)` —— 创建一个新数组，将从索引 `start` 到索引 `end`（但不包括 `end`）的元素复制进去。
  - `concat(...items)` —— 返回一个新数组：复制当前数组的所有元素，并向其中添加 `items`。如果 `items` 中的任意一项是一个数组，那么就取其元素。
- 搜索元素：
  - `indexOf/lastIndexOf(item, pos)` —— 从索引 `pos` 开始搜索 `item`，搜索到则返回该项的索引，否则返回 `-1`。
  - `includes(value)` —— 如果数组有 `value`，则返回 `true`，否则返回 `false`。
  - `find/filter(func)` —— 通过 `func` 过滤元素，返回使 `func` 返回 `true` 的第一个值/所有值。
  - `findIndex` 和 `find` 类似，但返回索引而不是值。
- 遍历元素：
  - `forEach(func)` —— 对每个元素都调用 `func`，不返回任何内容。里面放一个函数，默认第一个参数是当前元素 item， 第二个参数是 index，第三个参数是数组 array（参数名字可以不是这个）
    - e.g. 列表渲染： `appendChild` + `forEach`
  - `for (let item of arr){...}` 遍历每一个元素
  - `for(let key in node){...}` 是遍历对象的每一个属性（数组里不常用）
- 转换数组：
  - `map(func)` —— 根据对每个元素调用 `func` 的结果创建一个新数组。**参数：(item, index, array) 按顺序****
  - `sort(func)` —— 对数组进行原位（in-place）排序，然后返回它。
  - `reverse()` —— 原位（in-place）反转数组，然后返回它。
  - `split/join` —— 将字符串转换为数组并返回。
  - `reduce/reduceRight(func, initial)` —— 通过对每个元素调用 `func` 计算数组上的单个值，并在调用之间传递中间结果。
- 其他：
  - `Array.isArray(arr)` 检查 `arr` 是否是一个数组。
- 注意事项：
  1. js 的数组赋值不是真正的赋值，而是取别名。修改别名的数组之后原数组也会修改。

### 数据类型

1. Date 类型：不能直接输出，但有方法 time.toString()




### 对象

对象属性的获取方式：

1. 点符号：`user.isAdmin`
2. 方括号：
    - `user["isAdmin"]` , `user["is admin"]` (多词键值)
    - `let key = "is admin"; user[key] = true;` 在方括号内使用字符串变量

对象键值和属性的操作方式：

1. 计算属性：用变量生成键值
    - e.g.
        ```js
        let fruit = prompt("Which fruit to buy?", "apple");
        let bag = {
          [fruit + 'Computers']: 5 // bag.appleComputers = 5
        };
        ```
2. 属性值缩写：用于属性名跟变量名一样的场景
    - e.g. 
        ```js
        function makeUser(name, age) {
          return {
            name,       // 与 name: name 相同
            age: 30,    // 可以混用
            // ...
          };
        }
3. 判断属性是否存在：`"key" in object`
4. 遍历一个对象的所有键: `for (let key in object) {}`
    - 遍历顺序：整数属性（一个可以在不做任何更改的情况下与一个整数进行相互转换的字符串，例如 `49` 是整数属性名，但 `+49` 不是）会被进行排序，其他属性则按照创建的顺序显示

---




### 异步 (to be completed)

注意事项：

1. JS 的异步代码默认是在同步代码执行完成之后运行的（非抢占式）






### 杂项

#### package.json 的作用

package.json 中保存着一些项目的配置信息，其中依赖的模块在 "dependencies" 和 "devDependencies" 中记录。前者存放的是使用时依赖的模块，后者放的是开发时依赖的模块。

使用 `npm install` 可以在一个有 package.json 的文件夹中下载所有依赖。

使用 `npm init` 可以自动生成一个 package.json 文件。

`npm -S` 会把安装的模块写入 dependencies 中，`npm -D` 会把安装的模块写入 devDependencies 中。

#### import 和 require

语法:

1. import Heap from 'heap-js';
2. const Heap = require('heap-js');

无法 import 某个模块？在想要调用的模块内部的 `package.json` 中添加一行 `"type": "module"` ,或者在 html 文件导入 js 的语句加一句 type="module" 效果相同。原因是 ：import 是 ES6 标准中的模块化解决方案，不加上默认的是 type="commonjs" 用的应该是 ES5 标准 。

而 require 是 node 中遵循 CommonJS 规范的模块化解决方案。如果不写 type："module" 则可以用 require 语句代替，但是浏览器和 node.js 一般是不支持 require 语法的，百度 "require is not defined" 可以找到答案。

btw 在浏览器中和在 node.js 中想要应用同一个模块需要的语法是不一样的，以前居然完全没在意。大概意思如下：

![image.png](https://s2.loli.net/2022/01/22/uyCB9XPF3R2U4lE.png)

比如说 alert 在 node.js 中就不支持。


#### 函数的块状定义和语句定义

```javascript
function func(args) { /* body */ } // 块状定义
var func = function [can have a name but no meaning](args) { /* body */ } // 语句定义
promise.then(function (args) { /* body */ }) //语句定义的应用
```

#### 在 VScode 中使用浏览器环境调试

直接在 vscode 中按 F5 即可调试，会报错并显示行数，比直接在浏览器中打开好多了。

#### 正则表达式 (to be completed)

[MDN](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Guide/Regular_Expressions##%E4%BD%BF%E7%94%A8%E6%8B%AC%E5%8F%B7%E7%9A%84%E5%AD%90%E5%AD%97%E7%AC%A6%E4%B8%B2%E5%8C%B9%E9%85%8D)

举两个例子，看了就懂：

```
alert('(${x}, ${y})')
```

其中 `${}` 里面可以放任何表达式，输出的时候会转换为其值输出。


## 浏览器：文档、事件、接口

### DOM 树操作

[dom 树操作（详细）](https://blog.csdn.net/w390058785/article/details/80534328)

[DOM 树操作（表格）](https://www.w3school.com.cn/js/js_htmldom_document.asp)

#### 查找

1. `let element = document.getElementById(...)` 或者 `ByClassName/ByTagName` 获取元素，`byTagName` 中的 tagname 是 `input/p/a/span` 这种，获取的是一个 node
2. 1. `element.children` 返回一个数组，包含子节点中所有元素
   2. `element.childNodes` 返回一个数组，包含子节点中所有内容，包括直接写在里面的（这个时常容易出问题，还是用 children 好）
3. （to be continued）

#### 修改

1. `let element = document.createElement('div')` 创建新元素
2. `element.style.width = "50%"` 修改元素样式，或者`height/position/display/etc`
3. `element.className = "..."` 修改 class 属性 `innerHTML` 修改开始标签和结束标签之间的内容
4. `element.appendChild(newElement)` 在一个元素的所有儿子末尾插入新儿子
5. `element.replaceChild(new_child, element.childNodes[i]);` 替换某一个儿子元素

### 事件

#### 事件列表

- 鼠标事件：
  1. click —— 当鼠标点击一个元素时（触摸屏设备会在点击时生成）。
  1. contextmenu —— 当鼠标右键点击一个元素时。
  1. mouseover / mouseout —— 当鼠标指针移入/离开一个元素时。
  1. mousedown / mouseup —— 当在元素上按下/释放鼠标按钮时。
  1. mousemove —— 当鼠标移动时。
- 键盘事件：
  1. keydown 和 keyup —— 当按下和松开一个按键时。
- 表单（form）元素事件：
  1. submit —— 当访问者提交了一个 `<form>` 时。
  1. focus —— 当访问者聚焦于一个元素时，例如聚焦于一个 `<input>`。
- Document 事件：
  1. DOMContentLoaded —— 当 HTML 的加载和处理均完成，DOM 被完全构建完成时。
- CSS 事件：
  1. transitionend —— 当一个 CSS 动画完成时。

#### 事件处理 (handler)

1. HTML: 处理程序可以设置在 HTML 中名为 `on<event>` 的特性（attribute）中
    - e.g.
        ```js
        <script>
          function countRabbits() {
            for(let i=1; i<=3; i++) {
              alert("Rabbit number " + i);
            }
          }
        </script>

        <input type="button" onclick="countRabbits()" value="Count rabbits!">
        ```
    - 当浏览器读取 HTML 特性（attribute）时，浏览器将会使用特性中的内容创建一个处理程序，所以需要在函数后加括号
        ```js
        button.onclick = function() {
          countRabbits(); // <-- 特性（attribute）中的内容变到了这里
        };
        ```
    - HTML attribute 是大小写 **不** 敏感的
2. DOM: 我们可以使用 DOM 属性（property）`on<event>` 来分配处理程序
    - e.g.
        ```js
        <input id="elem" type="button" value="Click me">
        <script>
          elem.onclick = function() {
            alert('Thank you');
          };
        </script>
        ```
    - 要移除一个处理程序 —— 赋值 `elem.onclick = null`
    - DOM 属性是大小写敏感的
3. addEventListener: 多次调用 addEventListener 允许添加 **多个** 处理程序
    - e.g.
        ```js
        element.addEventListener(event, handler[, options]); // 通用形式
        elem.addEventListener("click", handler1); // Thanks!
        elem.addEventListener("click", handler2); // Thanks again!
        ```
    - options:
        1. once：如果为 true，那么会在被触发后自动删除监听器。
        1. capture: 事件处理的阶段
4. handleEvent：将一个对象分配为事件处理程序，当事件发生时，就会调用该对象的 `handleEvent` 方法。这种特性允许用类来定义 handler 的模板
    - e.g.
        ```js
        class Menu {
          handleEvent(event) {
            // mousedown -> onMousedown
            let method = 'on' + event.type[0].toUpperCase() + event.type.slice(1);
            this[method](event);
          }

          onMousedown() {
            elem.innerHTML = "Mouse button pressed";
          }

          onMouseup() {
            elem.innerHTML += "...and released.";
          }
        }
        let menu = new Menu();
        elem.addEventListener('mousedown', menu);
        elem.addEventListener('mouseup', menu);
        ```

### 表单和控件处理




## 网络请求和数据存储 (to be completed)

### fetch



### cookie


