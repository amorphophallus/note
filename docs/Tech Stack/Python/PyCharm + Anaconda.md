# PyCharm + Anaconda 搭建 Python 开发环境

> 参考资料：
    1. [安装总教程](https://zhuanlan.zhihu.com/p/140485845)
    2. [查询可安装环境：anaconda 官网](https://anaconda.org/)
    3. [Anaconda 的使用](https://zhuanlan.zhihu.com/p/348120084)
    4. [附加材料：pycharm + jupyter](https://blog.csdn.net/u011262253/article/details/105155581)

[TOC]


## anaconda 的使用

1. 下载：[tuna](https://mirrors.tuna.tsinghua.edu.cn/anaconda/archive/)
2. 添加 conda 源：
    - 打开 anaconda prompt
    - ```shell
        conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
        conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/ 
        conda config --set show_channel_urls yes
        ```
    - `conda info` 查看当前 channel
3. 添加环境变量：把 *安装路径* 和 *Scripts* 路径都放到环境变量里，然后重启
    - 在 powershell 中使用 conda：`conda init powershell`
3. 新建环境 `conda create -n 环境名 [python=3.9]`
    - 查看所有环境 `conda info --envs`
    - 删除环境 `conda remove -n 环境名 --all`
4. 启用环境 `conda activate + 环境名` -> 终端前面有 `(环境名)` 提示
    - 退出当前环境 `conda deactivate 环境名`
5. 在环境中安装包 `conda install 包名称`
    - 安装指定版本的包 `conda install <package>=<version>`，例如 `conda install pytorch=` 
    - 查看环境中所有包 `conda list`
    - 查看环境中的指定包 `conda list <包名称>`，例如 `conda list torch`
    - 搜索可以下载的包和版本 `conda search <包名称>`
    - 可以在 conda 环境中使用 pip `pip install pytorch`
6. 在环境中运行程序 `python main.py`
7. 清理空间 [详见这篇博客](https://stackoverflow.com/questions/56266229/is-it-safe-to-manually-delete-all-files-in-pkgs-folder-in-anaconda-python)，`conda clean --all` 简单粗暴，目前没有遇到问题

[更新 conda](https://zhuanlan.zhihu.com/p/121601968)
[conda 创建新环境](https://zhuanlan.zhihu.com/p/94744929)
[pip 换源](https://blog.csdn.net/skyyzq/article/details/113417832)！！！

## Pycharm 中使用 Anaconda

1. 设置 Project
    - Add Interpreter
    - Conda environment
    - Interpreter: < New Virtualenv >
    - *Location* 是环境的存储地址
    - 点击 + 号添加包
    - 或者打开 Terminal，进入环境之后 install 新包
2. 新建 Project
    - new environment using *Conda*
    - 其他同上

## 常见问题

### 0

很多问题是因为 anaconda 没有更新到最新版本，所以尽量保持 anaconda 在最新的版本。

### 1

问题：

```python
CondaValueError: Malformed version string '~': invalid character(s).
```

解决办法：

```python
# 加上 -c defaults --override-channels 参数，例如
conda install -n base -c defaults --override-channels pip
```

### 2

问题：

官网显示 download success 页面但是下载没有开始。

解决方法：

IDM 抽风了，关闭 IDM 的浏览器插件。

### 3

问题：

```python
UnsatisfiableError: The following specifications were found
to be incompatible with the existing python installation in your environment:

Specifications:

  - torchvision -> python[version='>=3.7,<3.8.0a0|>=3.8,<3.9.0a0|>=3.9,<3.10.0a0']

Your python: python=3.10
```

解决办法：

环境 python 版本太高，换个低版本重新创建环境，比如 `python=3.8` 可以安装

### 4

问题：在使用 conda 环境运行 python 程序时报错

```python
ImportError: DLL load failed while importing _multiarray_umath: 找不到指定的模块。
```

解决办法：没有把 conda 加入到 Path 环境变量里。注意卸载 anaconda 之后环境变量会随之清除。

### 5

问题：

```python
AttributeError: module 'distutils' has no attribute 'version'
```

解决方法： tensorboard 和 pytorch 版本不匹配，降低 tensorboard 的版本。在下载 tensorboard 的时候就直接不要最新版本就好了。

```python
conda uninstall setuptools
conda install setuptools==59.5.0
```