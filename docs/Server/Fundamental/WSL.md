[TOC]

# 安装和配置

1. 不在默认安装路径的安装：[手动安装wsl2-ubuntu20(指定安装位置)--小亮yuu - 小亮yuu - 博客园 (cnblogs.com)](https://www.cnblogs.com/xiaoliangyuu/p/15506352.html)
2. 安装 vim 和配置：
   - `~/.vimrc` 中编辑配置文件，退出编辑后自动生效
   - 在 `~/.vim/colors` 目录下放主题文件： [vim中添加molokai.vim 配色安装 - KoMiles - 博客园 (cnblogs.com)](https://www.cnblogs.com/wangkongming/p/4702559.html)
   - `\r command not found`：把 DOS 格式改成 unix 格式[Linux 错误： $'\r': command not found_在风中的意志的博客-CSDN博客](https://blog.csdn.net/u010416101/article/details/80135293)
3. 安装 git：
   - `ssh-ke` 之后在 github 上放一份公钥即可用 `git clone` 等命令
4. sudo 免密码：[wsl sudo 免密码 - 代码先锋网 (codeleading.com)](https://www.codeleading.com/article/12044675148/#:~:text=wsl sudo 免密码 1、新建 sudoer 配置文件,sudo vim %2Fetc%2Fsudoers.d%2F <用户名> 2、在上面的文件里添加 sudo 免密配置)
5. 安装 ssh：`apt search <指令名>` 可以看指令在哪个包里，然后就可以用 ssh 登录服务器和传文件啦
   - windows 下 ssh 权限问题：[解决windows10中ssh（OpenSSH_for_Windows）远程登录时报Permissions for "xxx" are too open错误](https://blog.csdn.net/xiaohaolaoda/article/details/105434315)
6. 服务器免密登录：[ssh免密码登录配置方法，（图示加命令）_universe_hao的博客-CSDN博客_ssh免密](https://blog.csdn.net/universe_hao/article/details/52296811)
   - 设置别名快捷登录：[SSH config使用教程和总结 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/35922004)

# 补充芝士

1. mnt 文件夹：把 windows 的所有盘挂载在 mnt 文件夹下，可以方便操作 windows 下的文件。

# Debian 修改环境变量

## 临时修改

命令行`export PATH=$PATH:/usr/bin`

## 当前用户

`sudo vim ~/.bashrc`：

```
PATH=$PATH:/usr/bin

export PATH
```

`source ~/.bashrc`

## 所有用户

`sudo vim /etc/profile`：

```
PATH=$PATH:/usr/bin

export PATH
```

`source /etc/profile`

## tips

1. `PATH` 等号前后不能有空格