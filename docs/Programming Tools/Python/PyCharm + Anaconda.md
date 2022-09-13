# PyCharm + Anaconda 搭建 Python 开发环境

> 参考资料：
    1. [安装总教程](https://zhuanlan.zhihu.com/p/140485845)
    2. [查询可安装环境：anaconda 官网](https://anaconda.org/)
    3. [Anaconda 的使用](https://zhuanlan.zhihu.com/p/348120084)
    4. [附加材料：pycharm + jupyter](https://blog.csdn.net/u011262253/article/details/105155581)


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
3. 新建环境 `conda create -n 环境名`
    - 查看所有环境 `conda info --envs`
    - 删除环境 `conda remove -n 环境名 --all`
4. 启用环境 `activate + 环境名` -> 终端前面有 `(环境名)` 提示
    - 退出当前环境 `deactivate 环境名`
5. 在环境中安装包 `conda install 包名称`
    - 查看环境中所有包 `conda list`
6. 在环境中运行程序 `python main.py`

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

