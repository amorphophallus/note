---
tags:
  - todo
---

# markdown 转 pdf

[TOC]

> todo：
    1. 优化 `head.tex`
    2. 简化命令放到环境变量里（一键编译）
参考：
[知乎专栏-包含编译选项](https://zhuanlan.zhihu.com/p/444440478#:~:text=Pandoc%20%E5%B0%86%20Markdown%20%E6%96%87%E6%A1%A3%E8%BD%AC%E4%B8%BA%20PDF%20%E6%96%87%E4%BB%B6%EF%BC%8C%E5%AE%9E%E9%99%85%E4%B8%8A%E5%8C%85%E5%90%AB%E4%B8%A4%E4%B8%AA%E6%AD%A5%E9%AA%A4%EF%BC%9A%20%E7%AC%AC%E4%B8%80%E6%AD%A5%EF%BC%9A%E5%B0%86%20Markdown,pdflatex%E3%80%81xelatex%20%E6%88%96%E8%80%85%E5%85%B6%E4%BB%96%20Tex%20%E5%91%BD%E4%BB%A4%EF%BC%8C%E5%B0%86%20LaTex%20%E6%BA%90%E6%96%87%E4%BB%B6%E6%B8%B2%E6%9F%93%E4%B8%BA%20PDF%20%E6%96%87%E4%BB%B6%E3%80%82)

## 本地方法

1. 下载 [pandoc](https://www.pandoc.org/installing.html)
    - `pandoc -v` 检查是否安装成功
2. 下载 LaTex
    - `xelatex -v & latex -v` 检查是否安装成功
3. 编译 `pandoc --pdf-engine=xelatex -V CJKmainfont="Microsoft YaHei" --toc -N -H F:\'Program Files'\texlive\head.tex xxx.md -o xxx.pdf`

**注意**：文件名，包括引用的图片文件名都不能是中文

### 补充芝士

*Pandoc*：A universal markup converter

> 还没看的其他方法：
[图灵社区](https://www.ituring.com.cn/article/828)
[曲线救国——mkdocs插件下载pdf](https://www.zhihu.com/question/20849824/answer/565654864)

### 编译选项

```shell
--pdf-engine=xelatex -V CJKmainfont="Microsoft YaHei" # 编译中文以及中文字体
-V geometry:"top=2cm, bottom=1.5cm, left=2cm, right=2cm" # 调整页边距
--toc # 添加目录
-N # 给 section 添加编号
-H head.tex # 使用头文件
```

head.tex 样例

```tex
%% 设置页边距
\usepackage[top=2cm, bottom=2cm, left=1.5cm, right=1.5cm]{geometry}

%% 针对中文自动换行
\XeTeXlinebreaklocale "zh"

%% 设置行间距 1.5 倍
\linespread{1.5}\selectfont

%% 设置首行缩进
\usepackage{indentfirst}
\setlength{\parindent}{2em}

%% 段落之间的距离
\setlength{\parskip}{3pt}   

%% 字与字之间加入0pt至1pt的间距，确保左右对齐
\XeTeXlinebreakskip = 0pt plus 1pt

%% 设置页眉页脚
\usepackage{fancyhdr}
\pagestyle{fancy}
\lhead{} 
\chead{}
\rhead{}
\lfoot{}
\cfoot{}
\rfoot{\thepage}
\renewcommand{\headrulewidth}{0.4pt}  %% 页眉分割线宽
\renewcommand{\footrulewidth}{0.4pt}  %% 页脚分割线宽

%% 设置表头背景色
\usepackage{colortbl}
\definecolor{tableheadcolor}{RGB}{225,225,225}

%% 设置 shade 背景色（代码背景颜色）
\usepackage{color,framed}
\definecolor{shadecolor}{RGB}{235,235,235}

%% 设置 block quote 的样式
%% 由于还不知道怎么统一设置 quote 的背景色，先引用 shade 背景色
%% 用左右边距区分 quote
\usepackage{quoting}
\newenvironment{shadedquotation}
 {\begin{shaded*}
  \quoting[leftmargin=1em, rightmargin=1em, vskip=0pt, font=itshape]
 }
 {\endquoting
 \end{shaded*}
 }

% quote 应用 shadedquotation 环境
\def\quote{\shadedquotation}
\def\endquote{\endshadedquotation}

%% 设置代码块样式
\usepackage{listings}
\usepackage{xcolor}
\lstset{
    basicstyle=\small\ttfamily,                          % 使用等宽字体    
    numbers=left,                                        % 在左侧显示行号
    numberstyle=\scriptsize\color{gray},                 % 设定行号格式
    numbersep=1em,                                        % 行号和代码的距离
    frame=none,                                          % 不显示背景边框
    backgroundcolor=\color[RGB]{245,245,244},            % 设定背景颜色
    breaklines=true,                                     % 代码超出宽度换行
    showstringspaces=false,                % 不显示字符串中的空格（下划线显示）
    tabsize=4                                            % tab 大小
}
```


## 其他方法

*在线转换*：需要把图片上传到图床

1. [哈希文档](https://www.hashspace.cn/markdown/)
2. [markdowntopdf](https://www.markdowntopdf.com/)