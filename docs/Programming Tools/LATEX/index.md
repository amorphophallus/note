[TOC]

# 语法

1. 优秀的入门文档：[一份其实很短的 LaTeX 入门文档 | 始终 (liam.page)](https://liam.page/2014/09/08/latex-introduction/)
2. 超简单版：[Latex基础语法 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/52347414)
3. overleaf 的 30 min 入门：[Learn LaTeX in 30 minutes - Overleaf, Online LaTeX Editor](https://www.overleaf.com/learn/latex/Learn_LaTeX_in_30_minutes)
4. 参考数学符号：[mohu](http://mohu.org/info/symbols/symbols.htm)
5. 带目录的文档：[中文版Latex常用语法大全教程](https://blog.csdn.net/tianzong2019/article/details/106521432)

## 基本结构

```latex
\documentclass{article}

% 这里是导言区（% 后面是注释）

\begin{document}

This is the main content.

\end{document}
```

## 导言区

### 文档类型

```latex
\documentclass{article}
```

其他文档类型：

1. article

2. report

3. book

4. 

### 标题、作者、日期、摘要、目录

```latex
\title{My First LaTex Document}
\author{StarlightXYY}
\date{\today}


% 在正文中生成标题、作者、日期
\maketitle
% 在正文中编写摘要
\begin{abstract}
LaTex is an elegant typesetting tool.
\end{abstract}
% 在正文中生成目录
\tableofcontents
```

> 1. 注意 `article` 默认不会给标题和目录单独一页，需要用 `\newpage` 来翻页。
> 
> 2. 目录居中 `\begin{center} ... \end{center}`
> 
> 3. 目录起始页码设置
>    
>    ```latex
>    \setcounter{page}{0}
>    \thispagestyle{empty}
>    \newpage
>    %<---从这里开始是正文--->%
>    ```
> 
> 4. 目录数字字体设置
>    
>    ```latex
>    % 前言和摘要可以设置成罗马数字
>    \pagenumbering{Roman}
>    % 正文的页码设置成阿拉伯数字
>    \pagenumbering{arabic}
>    ```

> 目录支持点击跳转的方法：
> 
> ```latex
> 
> ```

### 调用宏包

```latex

```

### 支持中文

```latex
\usepackage{ctex}
```

## 正文区

### 章节、段落

```latex
% in article
\section{}
\subsection{}
\subsubsection{}
\paragraph{}
\subparagraph{}
\subsubparagraph{}
% in report
\chapter{}
% in book
\part{}
```

### 数学公式

### 插入图片

### 插入列表

参考文档：[技术|LaTeX 排版（1）：列表 (linux.cn)](https://linux.cn/article-13112-1.html)

```latex
\begin{itemize} % 无序列表
    \item Fedora
\end{itemize}
\begin{enumerate} % 有序列表
    \item Item
\end{enumerate}
```

### 插入代码

使用宏包 `listlings`

listlings 设置参考文档：[LaTeX listings 宏包使用说明 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/261667944)

```latex
%<--------------------导言区-------------------->%
\usepackage{listings}
\usepackage{xcolor} % 用于自己设置代码高亮
\lstset{
 basicstyle=\small\ttfamily,                          % 使用等宽字体    
 numbers=left,                                        % 在左侧显示行号
 numberstyle=\scriptsize\color{gray},                 % 设定行号格式
 numbersep=1em,                                       % 行号和代码的距离
 frame=none,                                          % 不显示背景边框
 backgroundcolor=\color[RGB]{245,245,244},            % 设定背景颜色
 breaklines=true,                                     % 代码超出宽度换行
 showstringspaces=false,                % 不显示字符串中的空格（下划线显示）
 tabsize=4                                            % tab 大小
}
%<--------------------正文区-------------------->%
\begin{lstlisting}
#include<bits/stdc++.h>
using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
\end{lstlisting}
```

> 其他设置：
> 
> ```latex
> keywordstyle=\color[RGB]{40,40,255},                 % 设定关键字颜色
> commentstyle=\it\color[RGB]{0,96,96},                % 设置代码注释的格式
> identifierstyle=\color{red}                          % 设置标识符格式（括号、标点）
> stringstyle=\rmfamily\slshape\color[RGB]{128,0,0},   % 设置字符串格式
> language=c++,                      % 设置语言(也可以在正文中的[]里说明)
> ```
> 
> 在注释中使用中文和公式：
> 
> ```latex
> extendedchars=true,   % 设置 escape 的代码用 latex 解析显示
> escapechar=\%,        % 设置被 % 包围的代码 escape
> texcl=true,           % 设置注释的代码用 latex 解析显示
> ```

### 插入流程图

参考文档：

1. 比较详细的博客：[LaTeX画流程图 - 梧桐鹿 - 博客园 (cnblogs.com)](https://www.cnblogs.com/deer2021/p/15096624.html)

2. [[LaTeX 绘图] tikz 绘制流程图，概述和两个示例 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/82435856)

基本使用：

1. `\node[形状、位置参数] (代号) {}`
   
   1. 形状：
      
      - default：长方形
      
      - `rounded corners`：常用作开始和结尾
      
      - `diamond`：常用作分支判断
   
   2. 位置：
      
      - `below=of some_name` ：在 some_name 下方默认距离
      
      - `right=30pt of some-name` 在 some_name 右边 30pt 的距离

2. `\graph{}` 可以用链的方式来表示 node 之间的关系
   
   1. `(choice) ->["Yes"left] (end)` 中括号内是连线上的注释，写在线的哪个位置

```latex
%<--------------------导言区-------------------->%
\usepackage{tikz}
\usetikzlibrary{graphs, positioning, quotes, shapes.geometric}
%<--------------------正文区-------------------->%

% 定义属性
\tikzstyle{startstop} = [rectangle,rounded corners, minimum width=3cm,minimum height=1cm,text centered,text width =3cm, draw=black,fill=red!30]
\tikzstyle{io} = [trapezium, trapezium left angle = 70,trapezium right angle=110,minimum width=3cm,minimum height=1cm,text centered,text width =3cm,draw=black,fill=blue!30]
\tikzstyle{process} = [rectangle,minimum width=3cm,minimum height=1cm,text centered,text width =3cm,draw=black,fill=orange!30]
\tikzstyle{decision} = [diamond,aspect = 3,text centered,draw=black,fill=green!30]
\tikzstyle{arrow} = [thick,->,>=stealth]
\tikzstyle{straightline} = [line width = 1pt,-]
\tikzstyle{point}=[coordinate]

% 画图
\begin{tikzpicture}[node distance=2cm]
  \node (start) [startstop] {开始};
  \node (input1) [io,below of=start] {输入聚类的个数 $k$ 和最大迭代次数 $n$ };
  \node (process1) [process,below of=input1] {初始化 $k$ 个聚类中心};
  \node (process2) [process,below of=process1] {分配各数据对象到距离最近的类中};
  \node (decision1) [decision,below of=process2,yshift=-0.5cm] {是否收敛或迭代次数达到 $n$ };
  \node (stop) [startstop,below of=decision1,node distance=3cm] {输出聚类结果};
  \node(point1)[point,left of=input1,node distance=5cm]{};

  \draw [arrow] (start) -- (input1);
  \draw [arrow] (input1) -- (process1);
  \draw [arrow] (process1) -- (process2);
  \draw [arrow] (process2) -- (decision1);
  \draw [arrow] (decision1) -- node[anchor=east] {是} (stop);
  \draw [straightline] (decision1) -|  (point1);
  \draw [arrow] (point1) -- node[anchor=south] {否} (input1);
\end{tikzpicture}

% 画图（用 graph 生成连线）
\begin{tikzpicture}[node distance=10pt]
  % 节点
  \node[draw, rounded corners]                        (start)   {Start};
  \node[draw, below=of start]                         (step 1)  {Step 1};
  \node[draw, below=of step 1]                        (step 2)  {Step 2};
  \node[draw, diamond, aspect=2, below=of step 2]     (choice)  {Choice};
  \node[draw, right=30pt of choice]                   (step x)  {Step X};
  \node[draw, rounded corners, below=20pt of choice]  (end)     {End};

  % 连线
  \graph{
    (start) -> (step 1) -> (step 2) -> (choice) ->["Yes"left] (end);
    (choice) ->["No"] (step x) ->[to path={|- (\tikztotarget)}] (step 2);
  };
\end{tikzpicture}
```

> 在 node 中显示多行文字：**设置文本宽度** + 换行符
> 
> ```latex
> \tikzstyle{multiple_line} = [text width=6cm];
> \node[multiple_line] (start) {Line1 \\ Line2 \\ Line3};
> ```

## 文末区

### 脚注

### 参考文献

### 索引

## 注意事项和常见错误

### 空白区域

### BibTex 报错 "I found no \citation commands---while reading file lab1_report.aux"

在导言区加入 `\usepackage[backend=bibtex]{biblatex}`

### 特殊字符

`\# \$ \% \^{} \& \_ \{ \} \~{}` 需要加反斜杠。

`() [] : '"` 不用加反斜杠。

# 安装

1. [安装LaTex + 测试中文](https://zhuanlan.zhihu.com/p/56982388)
2. LATEX+VScode
   - [安装和配置](https://zhuanlan.zhihu.com/p/38178015)
   - **重点看这篇：**[配置文件解读](https://zhuanlan.zhihu.com/p/166523064)
3. [Overleaf：在线 LATEX编辑器](https://www.overleaf.com/project)

## 报错和解决办法

1. [Recipe terminated with fatal error: spawn xelatex ENOENT](https://blog.csdn.net/mengxt169/article/details/110126235)

## settings

1. 右下角错误弹窗：`latex-workshop.message.error.show`
2. 中文路径： `%DOCFILE%` 和 `%DOC%`
3. 自动编译：`latex-workshop.latex.autoBuild.run`
4. 清理中间文件：`latex-workshop.latex.autoClean.run`
5. 在右键菜单栏中显示正向查找：`latex-workshop.showContextMenu`
6. 反向查找：`latex-workshop.view.pdf.internal.synctex.keybinding`

## 操作

1. 编译：选择编译链->双击->左下角显示 √ 或者 × 
2. 正向搜索：右键菜单 或者 `ctrl+alt+J`
3. 反向搜索：双击 pdf 中的元素，反向定位到 tex 文件中（需要中间文件）