# Linux 指令

[TOC]

目前服务器用的是 Debian Linux

## 用户相关指令

```shell
passwd ## 改密码
useradd # 新增用户，记得修改密码
su <userid> # 切换用户
```

## 文件相关指令

[菜鸟教程 chmod](https://www.runoob.com/linux/linux-comm-chmod.html)，chmod 后面三个 0 到 7 之间的整数（3
 bit 二进制数），分别表示 owner / group / other users 的 read / write / execute 权限。

```shell
chmod 777 filename # 修改文件权限
```

## 进程查看

[Linux 下后台运行程序，查看和关闭后台运行程序](https://blog.csdn.net/u013846293/article/details/74003051)

```shell
jobs -l ## 查看（当前终端的）所有进程
kill xxxx ## 结束编号为 xxxx 的进程
nohup <shell command> & ## 后台运行，忽略输入输出
ps -aux ## 查看所有进程
ps -aux | grep "command" ## 在所有进程中搜索
```

## apt-get

```shell
apt-get update // 更新可以抓的包
apt-get install vim // 下载应用
```

---

update 命令只会获得系统上所有包的最新信息，并不会下载或者安装任何一个包。而是 apt upgrade 命令来把这些包下载和升级到最新版本。

## mv

[菜鸟教程](https://www.runoob.com/linux/linux-comm-mv.html)

1. 重命名

```shell
mv aaa bbb
```

2. 搬运文件

```shell
mv source_file(文件) dest_directory(目录)
mv source_directory(目录) dest_directory(目录)
mv -i # 在覆盖之前询问，否则会直接覆盖
```

注意检查隐藏文件是否 mv 成功

## 添加可执行程序到环境变量

### 创建软链接

`ln -s <源程序绝对路径> <链接绝对路径>`

### 修改环境变量

1. 修改 `/etc/profile`

2. 增加一句 `export PATH=$PATH:/sbin:/usr/X11R6/bin`

3. `source /etc/profile`

## Putty 与外界的复制粘贴

1. 从 Putty 复制：鼠标选中的内容会放到剪贴板里
2. 复制到 Putty 里：shift+insert

## shell 脚本

[(7条消息) shell脚本语言(超全超详细)_看见代码就想敲的博客-CSDN博客_shell脚本](https://blog.csdn.net/weixin_43288201/article/details/105643692)

## 查看系统软硬件信息

1. cpu 使用率

```shell
top # 类似于 ctrl+alt+delete
dstat --top-cpu # 实时更新占用率最高的程序
```

2. 查看网络配置

```cpp
netstat -nultp ## 查看端口占用情况
```