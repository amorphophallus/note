[TOC]

目前服务器用的是 Debian Linux

# 常用指令

```shell
passwd # 改密码
netstat -nultp # 查看端口占用情况
```

# 进程

[Linux 下后台运行程序，查看和关闭后台运行程序](https://blog.csdn.net/u013846293/article/details/74003051)

```shell
jobs -l # 查看（当前终端的）所有进程
kill xxxx # 结束编号为 xxxx 的进程
nohup <shell command> & # 后台运行，忽略输入输出
ps -aux # 查看所有进程
ps -aux | grep "command" # 在所有进程中搜索
```

# apt-get

```shell
apt-get update // 更新可以抓的包
apt-get install vim // 下载应用
```

# 添加可执行程序到环境变量

## 创建软链接

`ln -s <源程序绝对路径> <链接绝对路径>`

## 修改环境变量

1. 修改 `/etc/profile`

2. 增加一句 `export PATH=$PATH:/sbin:/usr/X11R6/bin`

3. `source /etc/profile`

# Putty 与外界的复制粘贴

1. 从 Putty 复制：鼠标选中的内容会放到剪贴板里
2. 复制到 Putty 里：shift+insert

# shell 脚本

[(7条消息) shell脚本语言(超全超详细)_看见代码就想敲的博客-CSDN博客_shell脚本](https://blog.csdn.net/weixin_43288201/article/details/105643692)