---
tags:
    - todo
---

# SSH

[TOC]

> todo:
    1. 补充完善指令细节和功能选项，能够复制就用

## 生成新的密钥 & 实现 SSH 无密码登录

[参考博客](https://blog.csdn.net/liu_qingbo/article/details/78383892)

1. `ssh-keygen`，记得指定密钥名称，别覆盖了别的。然后最好在想要的 `.ssh` 文件夹里执行这条命令，否则存放密钥的位置会比较迷
1. `ssh-copy-id -i ./id_rsa_2023_9_5.pub allen@116.62.135.219` 把公钥传送到远程主机上
1. `ssh allen@116.62.135.219 -i ./id_rsa_2023_9_5` 尝试连接远程主机
    - 如果提示有什么文件权限不对，如果是在 windows powershell 中登录，[使用这个方法](https://zhuanlan.zhihu.com/p/364189095)
    - 如果是在 WSL 中登录，直接 `chmod 600 [file_name]` 就可以
    - 注意 WSL 没法修改挂载的 windows 目录中的权限，需要在 windows 中手动设置
1. 配置本地 ssh 配置文件，参考下面的例子
1. 现在就可以直接用 `ssh aliyun` 来连接远程服务器啦

## 不同环境下 ssh 配置问题(git bash, powershell, wsl)

1. git bash
    - ssh: `C:\Users\allen\git\.ssh`
        - 配置文件 `C:\Users\allen\git\.ssh\config`
            1. 一种是直接用域名作为 Host 的名字
                ```c
                Host git.zju.edu.cn
                    User git
                    HostName git.zju.edu.cn
                    IdentityFile ~/.ssh/zjugit_rsa
                ```
                - 注意 `Host` 必须和 `HostName` 同名，否则只能用 `ssh Host` 的形式访问，不能用 `ssh User@HostName` 的形式访问
                - 注意 `config` 中的相对路径是相对 `git bash` 的当前位置，而不是 `config` 所在位置。所以最好设置成绝对路径。
            1. 一种是使用代称
                ```c
                Host aliyun
                HostName 116.62.135.219
                User allen
                Port 22
                IdentityFile C:\Users\allen\.ssh\id_rsa_2023_9_5
                ```
        - 公私钥对应：注意 `IdentityFile` 指明的私钥和放在 remote 端的公钥要对应
            - 注意私钥不能有过多的权限：`chmod 700 zjugit_rsa`
    - git：不用单独配置，只要 `ssh git@git.zju.edu.cn` 能连上，就能用 `git`
1. windows powershell
    - ssh: `C:\Users\allen\.ssh`，同上设置
1. WSL
    - ssh: `~/.ssh`，同上设置

## 传输相关

[菜鸟教程](https://www.runoob.com/linux/linux-comm-scp.html)

```shell
scp sourcefile username@host:destfolder
-r # 递归复制整个文件夹
```

注意 scp 复制和写入都需要权限，如果遇到 `permission denied` 可以登录远程服务器的 `root` 用户来执行 scp

注意 scp 不能使用 `./`，此时可以用 `$PWD` 替代
