# C# Basic

[TOC]

> 参考资料：
> 1. [菜鸟教程](https://www.runoob.com/csharp/csharp-tutorial.html)
> 
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

1. `new Task` 不会直接开始运行直到 `t.Start()`
2. `Task.Run()` 会直接开始异步运行

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

### 异常处理——堆栈跟踪

显示报错的具体位置

```CS
try
{
    errorMethod();
}
catch (System.Exception e)
{
    Console.Write("Method exception:" + e.Message + "\n\n" + e.StackTrace);
}
```

### base

base 关键字用于从派生类中访问基类的成员：

- 调用基类上已被其他方法重写的方法。

- 指定创建派生类实例时应调用的基类构造函数。

仅允许基类访问在构造函数、实例方法或实例属性访问器中进行。

```cs
// This constructor will call BaseClass.BaseClass(int i) 用基类的构造函数构造
public DerivedClass(int i) : base(i)
{
}
```

### is

判断类型


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

~~问题：JS function 并不能完全转化为 C# delegate 类，在转化过程中报错的语句翻译不过来。所以不能将可能报错的 JS function 作为参数传到 C# 函数里进行执行，必须在 JS 转 C# 之前在 JS 代码中就把错误处理给做好。~~

目前的问题：

stackTrace

```CS
MethodA exception:Expected string but got Undefined
在 Jint.JsValueExtensions.ThrowWrongTypeException(JsValue value, String expectedType)
在 Jint.Runtime.JavaScriptException.JavaScriptErrorWrapperException.SetCallstack(Engine engine, Location location, Boolean overwriteExisting)
在 Jint.Runtime.JavaScriptException.SetJavaScriptCallstack(Engine engine, Location& location, Boolean overwriteExisting)
在 Jint.Runtime.ExceptionHelper.ThrowJavaScriptException(Engine engine, JsValue value, Completion& result)
在 Jint.Native.Function.ScriptFunctionInstance.Call(JsValue thisArgument, JsValue[] arguments)
在 Jint.Runtime.Interpreter.Expressions.JintCallExpression.EvaluateInternal(EvaluationContext context)
在 Jint.Runtime.Interpreter.Expressions.JintExpression.GetValue(EvaluationContext context)
在 Jint.Runtime.Interpreter.Statements.JintVariableDeclaration.ExecuteInternal(EvaluationContext context)
在 Jint.Runtime.Interpreter.JintStatementList.Execute(EvaluationContext context)
在 Jint.Runtime.Interpreter.Statements.JintBlockStatement.ExecuteBlock(EvaluationContext context)
在 Jint.Runtime.Interpreter.Statements.JintBlockStatement.ExecuteInternal(EvaluationContext context)
在 Jint.Runtime.Interpreter.Statements.JintTryStatement.ExecuteInternal(EvaluationContext context)
在 Jint.Runtime.Interpreter.JintStatementList.Execute(EvaluationContext context)
在 Jint.Engine.ScriptEvaluation(ScriptRecord scriptRecord)
在 Jint.Engine.<>c__DisplayClass70_0.<Execute>b__0()
在 Jint.Engine.ExecuteWithConstraints[T](Boolean strict, Func`1 callback)
在 Jint.Engine.Execute(Script script)
在 Jint.Engine.Execute(String code, String source, ParserOptions parserOptions)
在 Jint.Engine.Execute(String code, String source)
在 ConsoleApp4.Promise.<>c__DisplayClass3_0.<Then>b__0(Task`1 rep) 位置 D:\Projects\csrepo\ConsoleApp4\Program.cs:行 号 51default!!!!
```

1. `JavaScriptErrorWrapperException` 类从 `JintException` 继承而来，`JintException` 是从 `Exception` 继承而来。在其中的 `SetCallstack` 方法中，`Error` 有 `CommonProperties.Stack` 这个属性，但是不是 `String` 而是 `undefined`，所以在 `AsString` 的时候报错 `Expected string but got Undefined`.
    ```cs
    internal void SetCallstack(Engine engine, Location location, bool overwriteExisting)
    {
        _location = location;

        var errObj = Error.IsObject() ? Error.AsObject() : null;
        if (errObj is null)
        {
            _callStack = engine.CallStack.BuildCallStackString(location);
            return;
        }

        // Does the Error object already have a stack property?
        if (errObj.HasProperty(CommonProperties.Stack) && !overwriteExisting)
        {
            _callStack = errObj.Get(CommonProperties.Stack).AsString();
        }
        else
        {
            _callStack = engine.CallStack.BuildCallStackString(location);
            errObj.FastSetProperty(CommonProperties.Stack._value, new PropertyDescriptor(_callStack, false, false, false));
        }
    }
    ```

2. 调用 `SetCallstack` 的是 `ExceptionHelper.ThrowJavaScriptException` 方法中的一句 `throw new JavaScriptException(value).SetJavaScriptCallstack(engine, result.Location);`。问题在新建 `JavaScriptException` 实例的时候的 `value`。
    ```cs
    public static void ThrowJavaScriptException(Engine engine, JsValue value, in Completion result)
    {
        throw new JavaScriptException(value).SetJavaScriptCallstack(engine, result.Location);
    }
    ```

3. `CommonProperties` 是定义在 `CommonProperties.cs` 中的类，`CommonProperties.Stack` 就是一个 `"stack"` 字符串

4. `JavaScriptException` 的构造函数是调用基类中的构造函数
    ```cs
    public JavaScriptException(JsValue error)
        : base(GetMessage(error), new JavaScriptErrorWrapperException(error, GetMessage(error)))
    {
        _jsErrorException = (JavaScriptErrorWrapperException) InnerException!;
    }
    ```

5. 最终问题是出在函数换了一个 engine 运行之后堆栈信息丢失，导致无法抛出错误。解决办法是把 engine 当成变量传到 engine 里面。

在 js 中封装 C# 中的 Promise 类：

```js
// 在 JS 中进行 try catch
class PromType{
    constructor(prom = Async(), ancestor = undefined){
        this.promData = prom;
        this.ancestor = (typeof ancestor) == (typeof undefined) ? prom : ancestor;
        this.then = function(func){
            return new PromType(eng, this.promData.Then((data) =>{
                try{
                    log('in JS then!!!!' + data);
                    let ret = func(data);
                    log(RetValue(ret, 0).ret + '@@@@@');
                    return RetValue(ret, 0);
                }catch(err){
                    log('!!!!!');
                    return RetValue(err.message, 1);
                }
            }), this.ancestor);
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
            }), this.ancestor);
        };
        this.run = function(){
            this.ancestor.Run();
        };
    }
}

// 仅仅在 JS 中进行一个封装
class PromType{
    constructor(prom = Async(), ancestor = undefined){
        this.promData = prom;
        this.ancestor = (typeof ancestor) == (typeof undefined) ? prom : ancestor;
        this.then = function(func){
            return new PromType(this.promData.Then(eng, func), this.ancestor);
        };
        this.catch = function(func){
            return new PromType(this.promData.Catch(eng, func), this.ancestor);
        };
        this.run = function(){
            this.ancestor.Run();
        };
    }
}
```

在 C# 中封装 try catch 语句

```js
// 第一种
retValue = (() => {
    let ret;
    try{
        log('in JS!!!');
        ret = func(data);
        log('func over!!!');
        return RetValue(ret, 0);
    }catch(err){
        log ('func error!!!');
        return RetValue(err.message, 1);
    }})();

// 第二种
retValue = RetValue('default', 0);
try{
    log('in JS!!!');
    let ret = func(data);
    log('func over!!!');
    retValue = RetValue(ret, 0);
}catch(err){
    log ('func error!!!');
    retValue = RetValue(err.message, 1);
};
```

测试 js 代码：

```js
// 第一版
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

// 第二版
(() =>{
    // Async().Then(()=>{log(1); return 3;}).Then((res) => {log(2); log(res); log(res+1); return res+2;}).Then((res)=>{log (res); try{throw new Error('Test Error!!!');}catch(err){log(err.message + ' 1st time'); throw new Error(err.message)}; log(res+1); return res+2;}).Catch((err)=>{log('Catch Error: '+err)}).Then((res)=>{log(res)})
    // var prom = Async()
    // prom.Then(eng, ()=>{log(1); return 3;}).Then(eng, (res) => {log(2); log(res); log(res+1); return res+2;}).Then(eng, (res)=>{log (res); try{throw new Error('Test Error!!!');}catch(err){log(err.message + ' 1st time'); throw new Error(err.message)}; log(res+1); return res+2;}).Catch((err)=>{log('Catch Error: '+err)}).Then(eng, (res)=>{log(res)})
    // prom.Run();
    new PromType().then(()=>{log(1); return 2;}).then((res) => {log(res); return res+1;}).then((res)=>{log (res); try{throw new Error('Test Error!!!');}catch(err){log(err.message + ' 1st time'); throw new Error(err.message)}; log(res+1); return res+2;}).catch((err)=>{log('Catch Error: '+err)}).then((res)=>{log(res)}).run();
})();

// 最终版
new PromType().then(()=>{
    log(1);
    return 2;
}).then((res) => {
    log(res);
    return res+1;
}).then((res)=>{
    log(res);
    try{
        throw new Error('Test Error!!!');
    }catch(err){
        log(err.message + ' 1st time');
        throw new Error(err.message);
    }
    log(res+1);
    return res+2;
}).catch((err)=>{
    log('Catch Error: '+ err);
    return 'error caught!';
}).then((res)=>{
    log(res)
}).run();
```

学到的东西：

1. JS 类（如果要用链式调用必须要递归的返回）
2. JS error 有作用域，比如说语法错误的域比 try catch 广不能被捕捉到。可以深入探究一下。



### 4

目前的问题是：

1. Jint engine 退出运行之后， engine 中的全局变量会丢失
    - 尝试1：首先检查一下 eng 作为参数传递的时候是否是
    - 尝试2：修改 Jint 原码，把 Engine 里最后结束的时候清空 Agent 的操作给去掉，或许可以把 engine 里的变量保存下来


然后需要写一些类似 React hook 风格的异步函数

需求：

1. usePromise() 新建一个 Task，返回值是 RetValue
2. useCatch() 新建一个抓取错误的 Task，
3. useIf() 在两个 Task 中选择一个执行
4. useRef() 在 C# 中定义一个新的全局变量
5. 还要能够判断异步是否已经运行结束了
6. 最好能够输出报错的位置

RetValue：（小改）

如果函数正确结束，返回值 0 & 返回值
如果函数抛出错误，返回 1 & Error（类型是 JSValue，把整个 error 丢）

可能存在的问题：

1. 传入 eng 内部的 eng，stackTrace 是否是正确的 stackTrace（即 eng 作为 eng 内部的变量时，两者是不是同一个东西）