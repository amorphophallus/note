# C# Basic

[TOC]

> 参考资料：
> 1. [菜鸟教程](https://www.runoob.com/csharp/csharp-tutorial.html)
> todo:
> 1. CSharp 语法，和 C 不一样的地方记一下 [菜鸟教程](https://www.runoob.com/csharp/csharp-tutorial.html)
> 2. CSharop Task （继承 Task 创建新类） [Task 详解](https://www.cnblogs.com/zhaoshujie/p/11082753.html)
> 3. .NET 是什么 + 结构 [.NET CLR](https://www.cnblogs.com/yplong/p/3280008.html#:~:text=%E4%BB%8E%E5%9B%BE2%E5%8F%AF%E4%BB%A5%E7%9C%8B%E5%88%B0%EF%BC%8CC%23%E6%89%80%E5%85%B7%E6%9C%89%E7%9A%84%E8%AE%B8%E5%A4%9A%E7%89%B9%E7%82%B9%E9%83%BD%E6%98%AF%E7%94%B1CLR%E6%8F%90%E4%BE%9B%E7%9A%84%EF%BC%8C%E5%A6%82%E7%B1%BB%E5%9E%8B%E5%AE%89%E5%85%A8%20%28Type%20Checker%29%E3%80%81%E5%9E%83%E5%9C%BE%E5%9B%9E%E6%94%B6%EF%BC%88Garbage%20Collector%EF%BC%89%E3%80%81%E5%BC%82%E5%B8%B8%E5%A4%84%E7%90%86,%28Exception%20Manager%29%E3%80%81%E5%90%91%E4%B8%8B%E5%85%BC%E5%AE%B9%20%28COM%20Marshaler%29%E7%AD%89%EF%BC%8C%E5%85%B7%E4%BD%93%E7%9A%84%E8%AF%B4%EF%BC%8C.NET%E4%B8%8A%E7%9A%84CLR%E4%B8%BA%E5%BC%80%E5%8F%91%E8%80%85%E6%8F%90%E4%BE%9B%E5%A6%82%E4%B8%8B%E7%9A%84%E6%9C%8D%E5%8A%A1%EF%BC%9A)
> 4. 异步的执行原理 [知乎](https://zhuanlan.zhihu.com/p/77555719#:~:text=%E4%BA%8B%E4%BB%B6%E5%BE%AA%E7%8E%AF%E6%98%AFJav,%E5%88%97%E4%B8%AD%E7%9A%84%E5%9B%9E%E8%B0%83%E5%87%BD%E6%95%B0%E3%80%82)

## VisualStudio

### NuGet

添加源：

```
nuget.org
https://api.nuget.org/v3/index.json
```

## 类型

### Task

相当于 Promise

```Csharp
// no return value
Task t1 = new Task(action, "alpha");
// with return value
var t = Task<int>.Run(action);
```

### delegate

类似于 C 或 C++ 中函数的指针，是存有对某个方法的引用的一种引用类型变量

Action 和 Func 都是 delegate。

声明一个委托：

```Csharp
delegate <return type> <delegate-name> <parameter list>
```

### Action

相当于函数

不能输出（返回值）

```Csharp
public delegate void Action<in T>(T obj);
```

`Action.Invoke(args)` 相当于 `action(args)`，作用是传参

### Func

相当于函数

1. 输入 & 输出
2. 无输入，仅输出

```csharp
public delegate TResult Func<in T,out TResult>(T arg);
public delegate TResult Func<out TResult>();
```

## Usage

### Exception Handling

`try...catch...finally`

执行逻辑：执行 try 中的命令，一旦发现错误就跳转执行 catch 中的命令，最终结束执行并跳出 try...catch 语句。

**注意：** 函数返回语句不能放在 finally 里，因为不管是否获取到错误 finally 一定会执行，与 catch 错误之后返回是矛盾的。

### JS Error & C# Exception

**注意：** throw new Exception 有 context

## Jint

### Basic

1. 新建引擎
    ```CSharp
    import 
    var engine = new Engine()
    ```
2. CSharp -> JS
    - 变量
    - 函数
    ```CSharp
    // 传入函数 log(object)
    var engine = new Engine()
    .SetValue("log", new Action<object>(Console.WriteLine));
    // 传入变量，执行 evaluate 并返回结果到 C# 程序里
    var square = new Engine()
    .SetValue("x", 3) // define a new variable
    .Evaluate("x * x") // evaluate a statement
    .ToObject(); // converts the value to .NET
    ```
3. JS -> CSharp
    - 方法一：获取函数 reference
    - 方法二：直接执行代码
    ```CSharp
    // 方法一
    // 返回 add 函数（包含 Invoke 子函数）
    var add = new Engine()
    .Execute("function add(a, b) { return a + b; }")
    .GetValue("add");
    // 传入参数并执行
    add.Invoke(1, 2); // -> 3

    // 方法二
    string code = @"
        let pro1 = new Promise((res, rej)=>{
            log(1);
            res(2);
        })
        pro1.then((data)=>{
            log(data);
        })
    "
    eng.Execute(code)
    ```
## 解决的问题

### 1

问题：CSharp 运行 JS 代码可以实现异步，但是不能传参给 Promise.then 。

解决方法：发现问题不是出在 CSharp 运行 JS 的环境上，而是 Promise 忘记 resolve 了。

### 2

问题：CSharp 运行 JS 代码，同步部分结束后环境消失，Promise resolve 完之后不会运行 Promise.then 。

解决办法：环境消失是 Jint 本身特性导致，无法更改。所以放弃使用 Promise，直接使用 CSharp 中的异步。用 Task 构造函数 `AsyncFunc`，传入一个包含需要依次执行的 JS 函数的数组，由 CSharp 来构造 `Task.ContinueWith.ContinueWith...`

### 3

问题：在问题 2 的基础上新增需求

- 要求抓取异步执行过程中可能产生的错误，并在最后实现一个类似 catch 的函数
- 有多个异步的函数需要执行，在所有异步函数运行结束后执行一个函数，即实现一个功能类似于 `Promise.all()` 的函数。
- 需要封装到 JS 内部只需要正常写代码，而能够完成错误获取和处理

问题：JS function 并不能完全转化为 C# delegate 类，在转化过程中报错的语句翻译不过来。所以不能将可能报错的 JS function 作为参数传到 C# 函数里进行执行，必须在 JS 转 C# 之前在 JS 代码中就把错误处理给做好。

```js
class PromType{
    constructor(prom){
        this.promData = prom;
        this.then = function(func){
            return new PromType(this.promData.Then((data) =>{
                try{
                    log('in JS then!!!!' + data);
                    let ret = func(data);
                    log(RetValue(ret, 0).ret + '@@@@@');
                    return RetValue(ret, 0);
                }catch(err){
                    log('!!!!!');
                    return RetValue(err.message, 1);
                }
            }));
        };
        this.catch = function(func){
            return new PromType(this.promData.Catch((data) =>{
                try{
                    log('in JS catch!!!!' + data);
                    let ret = func(data);
                    log(RetValue(ret, 0).ret + '@@@@@');
                    return RetValue(ret, 0);
                }catch(err){
                    log('!!!!!');
                    return RetValue(err.message, 1);
                }
            }));
        };
    }
}
```

```js
(() =>{
    Async().then(()=>{
        log(1);
        return 3;
    }).then(()=>{
        log(1);
        return 3;
    }).then((res) => {
        log(2);
        log(res);
        log(res+1);
        return res+2;
    }).then((res)=>{
        log (res);
        log(abcde);
        return res+1;
    }).catch((err)=>{
        log('Catch Error: '+err);
    }).then((res)=>{
        log(res);
    })
    log('function over')
})();
```

学到的东西：

1. JS 类（如果要用链式调用必须要递归的返回）
2. JS error 有作用域，比如说语法错误的域比 try catch 广不能被捕捉到。可以深入探究一下。