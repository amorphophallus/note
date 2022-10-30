# React

[TOC]



## 复健引导



1. 如何创建一个 react 文件？
2. 如何渲染？
    1. `reactDOM.render(element, document.getElementById('root'))`
    2. 只能更换，不能修改 & 只修改要修改的部分：渲染一个计时器
3. 函数组件是什么？怎么传参？怎么渲染？
    1. 开头大写默认是 react 组件
    2. 函数只能返回一个元素（多个要用 div 套起来）
    3. `<div></div>` 和 `<App />` 有什么区别？
    4. props 不能被修改
4. class 组件怎么写？怎么渲染？
    1. class 中 props 和 state 怎么用？有什么区别？state 怎么修改 (`setState`)？
    2. `componentDidMount` 和 `componentWillUnmount` 函数的作用
5. 事件处理是什么东西？react 怎么写事件处理？有哪些可以用的事件
6. 条件渲染
    1. 条件渲染 + state 能达到什么效果？
    2. {} + && / 三目运算符怎么替换条件渲染？
7. 列表(不是 HTML list)是什么？
    1. key 是什么？在什么地方加？
8. hook
    1. useState
    2. useEffect
9.  路由：看着标题都知道那是些什么东西吗？





## 开始



新建 react：

```
yarn create react-app $app-name$
cd $app-name$
yarn start
```

安装新的包：

```javascript
yarn add $package-name$
```



### 常见 import 文件



```js
```





### tips

1. [create-react-app app安装报错的解决办法](https://blog.csdn.net/chenkeyu1997/article/details/100556513)
2. 整个 react 文件的本体是 `index.js` 



## 函数组件



### 举个例子



```jsx
function Welcome(props) {
  return <h1>Hello, {props.name}</h1>;
}

const element = <Welcome name="Sara" />; // 参数都用 “” 传入，在创建 element 的时候调用函数
ReactDOM.render(
  element,
  document.getElementById('root')
);
```



### 传参

#### tips

1. 只能用字符串作为参数，所以常用一些字符串和数字的转换函数

```js
parseInt(string s, [int radix]) // 可以指定基数

```

2. 传参的方式
  - props
  - context
  - redux

### 跨文件



在函数组件的 js 文件：

```javascript
import React, { useEffect, useState } from "react"; // 导入必要的东西

export default function Timer(){
    // 前缀表示这个函数组件会被导出
    // 函数名首字母大写
    return <div>
        // 只能发返回一个组件
    <div>
}
```

在需要引用这个函数组件的 js 文件：

```javascript
import Timer from "./timer" // 导入同目录的 timer.js 或者 timer.jsx

React.render(<Timer />, document.getElementById("root")) // 组件引用的方法， <$name$ />
```

每个 js 文件中只允许有一个 default export



**tips:** 传递参数的时候，注意只能从父节点向子节点传，所以如果有一个组件需要用另一个组件的参数，那么只能作为它的子组件存在。



### 组合组件



```jsx
function Avatar(props) { // 显示头像
  return (
    <img className="Avatar"
      src={props.user.avatarUrl}
      alt={props.user.name}
    />
  );
}

function UserInfo(props) { // 显示头像和信息
  return (
    <div className="UserInfo">
      <Avatar user={props.user} /> // 使用 Avatar 组件
      <div className="UserInfo-name">
        {props.user.name}
      </div>
    </div>
  );
}

function Comment(props) { // 显示头像、信息、评论
  return (
    <div className="Comment">
      <UserInfo user={props.author} /> // 使用 UserInfo 组件
      <div className="Comment-text">
        {props.text}
      </div>
      <div className="Comment-date">
        {formatDate(props.date)}
      </div>
    </div>
  );
}
```



### tips

1. React 组件首字母大写
2. props 是只读的
3. key 是保留字



## class 组件



### 举个例子

构造 class 和使用 state

```jsx
class Clock extends React.Component { // 继承 React.Component
  constructor(props) { // 构造函数，给 state 一个初始值
    super(props); // super 意为继承，在这个构造函数里其实可以不写
    this.state = {date: new Date()};
  }

    
  componentDidMount() { // 组件渲染到 DOM 之后运行
    this.timerID = setInterval(
      () => this.tick(),
      1000
    );
  }

  componentWillUnmount() { // 被移除出 DOM 之后运行
    clearInterval(this.timerID);
  }

  tick() {
    this.setState({
      date: new Date()
    });
  }  
  
  render() { // 定义 render 函数, 没有参数，用 this.props 代替参数 props
    return (
      <div>
        <h1>Hello, world!</h1>
        <h2>It is {this.props.date.toLocaleTimeString()}.</h2>
      </div>
    );
  }
}

reactDOM.render( // 渲染方法和函数组件一样
	<Clock />,
    document.getElementById('root'),
); // Clock 被传给 render 之后函数调用的顺序: constructor -> render -> componentDidMount
```



### 事件处理

可用事件参考：[合成事件 – React (reactjs.org)](https://zh-hans.reactjs.org/docs/events.html##clipboard-events)



```jsx
class Toggle extends React.Component { // 渲染一个让用户切换开关状态的按钮
  constructor(props) {
    super(props);
    this.state = {isToggleOn: true};

    // 为了在回调中使用 `this`，这个绑定是必不可少的
    this.handleClick = this.handleClick.bind(this);
  }

  handleClick() { // 如果不 bind 那么在调用 handleClick 时的 this 就是调用时的环境而不是 Toggle
    this.setState(state => ({
      isToggleOn: !state.isToggleOn
    }));
  }

  render() {
    return (
      <button onClick={this.handleClick}>
        {this.state.isToggleOn ? 'ON' : 'OFF'}
      </button>
    );
  }
}

ReactDOM.render(
  <Toggle />,
  document.getElementById('root')
);
```



传参



```jsx
<button onClick={(e) => this.deleteRow(id, e)}>Delete Row</button>
```





### 关于 bind 的说明



**普通函数中this的指向，是this执行时的上下文**
**箭头函数中this的指向，是this定义时的上下文**



```js
var name = 'lili',age = 15;
var obj={
    name : 'Bob',
    objage : this.age,
    fun : function(){
        console.log(this.name+''+this.age);
    }
};
console.log(obj.objage); // objage = this.age 其中 this 是全局
obj.fun(); // this.name + this.age 其中 this 是 obj
```



### 关于 super 的说明



super(props) -> 给当前 class 新增一个 this.props ，继承父类型中的 props

super() -> 继承父类型（中的函数等等）



### tips



1. state 和 props 的区别是一个可以修改一个不能修改
2. state 更新之后不用重新 render，内容会直接修改
3. setState 会合并参数和原有的 state
4. state 的更新可能是异步的（可能多个 setState 同时进行）：所以如果要在 setState 中使用 state 作为参数，最好用 `setState(function(state, ...){return ...})`
5. state 信息只能向下传递，不能被外部调用



## 条件渲染



### 举个例子



```jsx
class LoginControl extends React.Component { // 渲染一个点击可以切换状态的按钮
  constructor(props) {
    super(props);
    this.handleLoginClick = this.handleLoginClick.bind(this);
    this.handleLogoutClick = this.handleLogoutClick.bind(this);
    this.state = {isLoggedIn: false};
  }

  handleLoginClick() {
    this.setState({isLoggedIn: true});
  }

  handleLogoutClick() {
    this.setState({isLoggedIn: false});
  }

  render() { // 在修改 state 之后会重新执行 if/else 语句
    const isLoggedIn = this.state.isLoggedIn;
    let button;
    if (isLoggedIn) {
      button = <LogoutButton onClick={this.handleLogoutClick} />;
    } else {
      button = <LoginButton onClick={this.handleLoginClick} />;
    }

    return (
      <div>
        <Greeting isLoggedIn={isLoggedIn} />
        {button}
      </div>
    );
  }
}

ReactDOM.render(
  <LoginControl />,
  document.getElementById('root')
);
```



### {} 内表达式的写法



```jsx
// {} + 三目运算符
<div>
  The user is <b>{isLoggedIn ? 'currently' : 'not'}</b> logged in.
</div>

// {} + && 同理
```



注意 react 组件的传参都是用字符串传的



## 列表渲染



### 举个例子 



```js
function ListItem(props) {
  // 正确！这里不需要指定 key：
  return <li>{props.value}</li>;
}

function NumberList(props) { // 作用是生成一个列表
  const numbers = props.numbers;
  const listItems = numbers.map((number) =>
    // 正确！key 应该在数组的上下文中被指定
    <ListItem key={number.toString()} value={number} />

  );
  return (
    <ul>
      {listItems}
    </ul>
  );
}

const numbers = [1, 2, 3, 4, 5];
ReactDOM.render(
  <NumberList numbers={numbers} />,
  document.getElementById('root')
);
```



### tips



1. key 是必需的，且在同一层级下最好 unique
2. 元素的 key 只有放在就近的数组上下文中才有意义。
3. {} + 箭头函数 + map 可以直接嵌套在 jsx 里面


## hook

和 class 中的 state 几乎功能一样，但是用在函数组件中



### state hook



```js
 import React, { useState } from 'react'; // 需要 import useState 函数

function Example() {
  // 声明一个叫 "count" 的 state 变量，useState 函数的参数是 state 的初始值
  const [count, setCount] = useState(0); // 这里的语法是“解构函数”，useState 返回的是一个数组，而这个语句把 foo[0] 和 foo[1] 重命名了
  const [fruit, setFruit] = useState('banana'); // 可以在一个函数里声明多个不同的 state

  return (
    <div>
      <p>You clicked {count} times</p> // 直接用变量名读取 state
      <button onClick={() => setCount(count + 1)}> // 相当于 class 中的 this.setState()
        Click me
      </button>
    </div>
  );
}

// 如果 state 是一个对象，只想修改对象里的一个参数
const [obj,setobj]=useState({a:'hh',b:'uu',c:'yy',d:'uu',e:'ee'}]
// 可以这样,后面设置的yyy会覆盖前面的yy
// 注意，如果对象中的属性有function，则不会被...识别
setobj({
...obj,
c:'yyy'
}
```



1. state 变量在函数调用结束之后仍会保留，作用和 class 中的 this.state 一样
2. 



### effect hook

可以把 `useEffect` Hook 看做 `componentDidMount`，`componentDidUpdate` 和 `componentWillUnmount` 这三个函数的组合。

"effect" 意为渲染后的副作用

```js
import React, { useState, useEffect } from 'react';

function Example() {
  const [count, setCount] = useState(0);

  useEffect(() => {
    document.title = `You clicked ${count} times`; // 函数主体 = componentDidMount 和 componentDidUpdate
    return function cleanup() { // 返回一个函数 = componentWillUnmount
      ChatAPI.unsubscribeFromFriendStatus(props.friend.id, handleStatusChange);
    };
  });

  return (
    <div>
      <p>You clicked {count} times</p>
      <button onClick={() => setCount(count + 1)}>
        Click me
      </button>
    </div>
  );
}
```



1. 可以使用多个 effect hook，所以可以按照用途拆分
2. useEffect 的第二个参数是一个数组， `useEffect(() => {...}, [props.friend.id])` 表示只有在后面这个数组中有元素更新的时候才会调用 useEffect，要保证所有可能被更改的信息全部包含在后面的数组里
3. 



### 自定义 hook

用于避免重复逻辑，简化代码



```js
import { useState, useEffect } from 'react';

function useFriendStatus(friendID) { // 像普通函数一样可以传入任意参数，可以返回值
  const [isOnline, setIsOnline] = useState(null);

  useEffect(() => {
    function handleStatusChange(status) {
      setIsOnline(status.isOnline);
    }

    ChatAPI.subscribeToFriendStatus(friendID, handleStatusChange);
    return () => {
      ChatAPI.unsubscribeFromFriendStatus(friendID, handleStatusChange);
    };
  });

  return isOnline;
}

function FriendStatus(props) { // 第一次调用
  const isOnline = useFriendStatus(props.friend.id);

  if (isOnline === null) {
    return 'Loading...';
  }
  return isOnline ? 'Online' : 'Offline';
}

function FriendListItem(props) { // 第二次调用
  const isOnline = useFriendStatus(props.friend.id);

  return (
    <li style={{ color: isOnline ? 'green' : 'black' }}>
      {props.friend.name}
    </li>
  );
}
```

1. 函数名必须以 use 开头



### tips

1. react 通过调用顺序来判断每个 hook 对应的是哪个 state 和 effect，所以只能在 react 函数的顶层调用 hook



## 路由



### 开始

下载 react-router-dom

```js
yarn add react-router-dom
```



### BrowserRouter , Routes & Route

1. 写在 render 函数里面
2. BrowserRouter 和 Routes 套在最外面
3. 每个网页写一个 Router，会分别渲染
4. path 是对应的 url   
    1. "/" 是根 url
    2. "*" 是所有都不匹配的时候跳转的链接
5. element 是跳转 path 之后显示的内容



```js
import ReactDOM from "react-dom/client";
import {
  BrowserRouter,
  Routes,
  Route,
} from "react-router-dom";
import App from "./App";
import Expenses from "./routes/expenses";
import Invoices from "./routes/invoices";

const root = ReactDOM.createRoot(
  document.getElementById("root")
);
root.render(
  <BrowserRouter> // 可以直接用一个 <Router> 代替外面的两层
    <Routes>
      <Route path="/" element={<App />} />
      <Route path="expenses" element={<Expenses />} />
      <Route path="invoices" element={<Invoices />} />
    </Routes>
  </BrowserRouter>
);
```



### Route 之间的嵌套(Nested)

操作：

1. 在作为父节点的函数组件里面加入一个 Outlet
2. 在 render 函数里把 Router 写成嵌套的模式

效果：

1. url 会嵌套(/invoices/1099)
2. 跳转子节点的时候父节点的内容也会显示



```js
  <BrowserRouter>
    <Routes>
      <Route path="/" element={<App />}> // 父节点
        <Route path="expenses" element={<Expenses />} />
        <Route path="invoices" element={<Invoices />} />
        <Route
          path="*"
          element={
            <main style={{ padding: "1rem" }}>
              <p>There's nothing here!</p>
            </main>
         }
       />
      </Route> // 父节点结束
    </Routes>
```





### Link

1. 写在函数组件里面，生成一个跳转链接
2. to 里面是跳转链接
3. 尖括号之间的是显示的内容



```js
// App.js
import { Outlet, Link } from "react-router-dom";

export default function App() {
  return (
    <div>
      <h1>Bookkeeper</h1>
      <nav
        style={{
          borderBottom: "solid 1px",
          paddingBottom: "1rem",
        }}
      >
        <Link to="/invoices">Invoices</Link> |{" "}
        <Link to="/expenses">Expenses</Link>
      </nav>
      <Outlet /> // 如果这是一个父节点，需要加上 Outlet
    </div>
  );
}
```



### useParams

在 render 中这么写，表示所有形如 /invoices/xxx 的网页的 xxx 都会被当做参数，可以被 xxx 渲染的函数组件调用

```js
<Route path="invoices" element={<Invoices />}>
  <Route path=":invoiceId" element={<Invoice />} />
</Route>
```

在函数组件里这么写，: 之后的是参数名字

```js
import { useParams } from "react-router-dom";
import { getInvoice } from "../data";

export default function Invoice() {
  let params = useParams();
  let invoice = getInvoice(parseInt(params.invoiceID, 10));
    // params.invoiceID 是字符串，用 parseInt 变成数字，getInvoice 是在 data 中搜索对应的记录的函数
  return (
    <main style={{ padding: "1rem" }}>
      <h2>Total Due: {invoice.amount}</h2>
      <p>
        {invoice.name}: {invoice.number}
      </p>
      <p>Due Date: {invoice.due}</p>
    </main>
  );
}
```



### index route

相当于在父 route 中再加点东西，这些东西在进入他的子 route 时消失

```js
		<Route path="invoices" element={<Invoices />} >
          <Route
            index
            element={
              <main style={{ padding: "1rem" }}>
                <p>Select an invoice</p>
              </main>
            }
          />
          <Route path=":invoiceID" element={<Invoice/>}/>
        </Route>
```



### useSearchParams & useLocation

用法和 state 类似

```js
let [searchParams, setSearchParams] = useSearchParams();
setSearchParams({ filter });
let filter = searchParams.get("filter");
```

但是 searchParams 的值会在 url 中显示出来，例如 `http://localhost:3000/invoices/1995?filter=s`

(useLocation 还不会)


## Context

### 功能

Context 设计目的是为了共享那些对于一个组件树而言是“全局”的数据。使用 context 的通用的场景包括管理当前的 locale，theme，或者一些缓存数据

1. 组件间多级传参不用每级都写参数
2. 没有直系关系（父子孙...）的组件之间传递数据

### 工作原理

1. 使用一个 Provider 并设定 value 来将当前的 Context 传递给以下的组件树
2. Consumer 会往上找到最近的 Provider，然后使用它的值；如果没有对应的 Provider，value 取 defaultValue。
3. 当 Provider 的 value 值发生变化时，它内部的所有 Consumer 都会重新渲染

### 使用

useContext 的作用和 Consumer 一样

```js
// 创建 Context
const MyContext = React.createContext(defaultValue);

// Provider
<Context.Provider value={/*set context value here*/}>
    {/* components that need this context */}
</Context.Provider>

// Consumer
<MyContext.Consumer>
    {value => /* 基于 context 值进行渲染*/}
</MyContext.Consumer>

// useContext
const {n,setN} = useContext(Context_name);
return(
    <div>
      n:{n}
      <button onClick={()=>{setN(n+1)}}>+1</button>
    </div>
  )
```


### 常用技巧

1. 修改 Context ：在 Context 中包含一个修改函数（推荐直接使用 useState）。在 Consumer 处修改数据，React 会从 state 所在组件开始更新整个组件树
2. 

## 其他



### 用数组生成 ReactDom 元素



React.createElement

[(34条消息) React.createElement的理解使用_小白变怪兽的博客-CSDN博客_react.createelement](https://blog.csdn.net/u013558749/article/details/80268449)


### 重新渲染机理 + React.memo

> 1. [详细说明](https://juejin.cn/post/7129670327725981732)
> 2. [介绍一些 re-render 相关的现象](https://www.developerway.com/posts/react-elements-children-parents)

组件自身重新渲染有四个原因：

1. 状态更改 (state)
2. 父级重新渲染
3. 上下文更改 (context)
4. hooks更改

plus. 想要当且仅当组件的 props 发生变化时会发生重新渲染：在组件外套一层 `React.memo()`

> memo 可以翻译为“记忆化组件”。在计算机领域，记忆化是一种主要用来提升计算机程序速度的优化技术方案。它将开销较大的函数调用的返回结果存储起来，当同样的输入再次发生时，则返回缓存好的数据，以此提升运算效率。

### children 传参

> [详细说明](https://www.jianshu.com/p/d1975493b5ea)


使用举例：

```js
const MovingComponent = ({ children }) => {
  const [state, setState] = useState({ x: 100, y: 100 });

  return (
    <div onMouseMove={(e) => setState({ x: e.clientX - 20, y: e.clientY - 20 })} style={{ left: state.x, top: state.y }}>
      {children}
    </div>
  );
};

const SomeOutsideComponent = () => {
  return (
    <MovingComponent>
      <ChildComponent />
    </MovingComponent>
  );
};
```
注意事项：
1. children 仅作为函数组件的 props 存在，而不算是子组件，在函数重新渲染时 **不会** 被重新渲染
2. `{children}` 作为参数的写法相当于以 `props` 为参数并 `let children = props.children`。带大括号是指传递一个参数，参数类型为对象，里面有一个属性children, 不带大括号就是传递多个参数，这里的大括号不是块级作用域，就是单纯的表示一个对象。
3. 可以传入函数作为 children，如下例

```js
const MovingComponent = ({ children }) => {
  const [state, setState] = useState({ x: 100, y: 100 });

  return (
    <div onMouseMove={(e) => setState({ x: e.clientX - 20, y: e.clientY - 20 })} style={{ left: state.x, top: state.y }}>
      // children as render function with some data
      // data doesn't depend on the changed state!
      {children({ data: 'something' })}
    </div>
  );
};

const SomeOutsideComponent = () => {
  return (
    <MovingComponent>
      // ChildComponent re-renders when state in MovingComponent changes!
      // even if it doesn't use the data that is passed from it
      {() => <ChildComponent />}
    </MovingComponent>
  )
}
```

---


内置函数：

1. `React.Children.map`: 类似 JS 数组的 map 方法
    - e.g. 
      ```js
      React.Children.map(children, (child, i) => {
        // Ignore the first child
        if (i < 1) return
        return child
      })
      ```
2. `React.Children.forEach`: 类似 JS 数组的 forEach 方法
3. `React.Children.count`: 返回 children 个数
4. `React.Children.toArray`
5. `React.Children.only` 如果有多个 children 则会报错
    - e.g. `React.Children.only(props.children)()`

---

（批量）修改 children 属性：

使用 `React.cloneElement` 方法

```js
React.Children.map(this.props.children, child => {
    return React.cloneElement(child, {
      name: this.props.name
    })
  })
```


### 大括号和解构语法

> [参考第一个回答](https://segmentfault.com/q/1010000017062649)

```js
function({x,y,z}){
}

// 相当于

function(obj){
  var  x=obj.x, y=obj.y, z=obj.z
}
```