---
tags:
    - todo
---

# SSH

[TOC]

> todo:
    1. 补充完善指令细节和功能选项，能够复制就用

## 秘钥相关

```shell
ssh-keygen
ssh-copy-id
```

## 连接相关

```shell
ssh
```

~/.ssh/ssh_config:

```shell
Host cluster
        HostName 123.cn
        User hy-summer
        Port 14514
        IdentityFile ~/.ssh/id_rsa_windows
```

## 传输相关

[菜鸟教程](https://www.runoob.com/linux/linux-comm-scp.html)

```shell
scp sourcefile username@host:destfolder
-r # 递归复制整个文件夹
```

注意 scp 复制和写入都需要权限，如果遇到 `permission denied` 可以登录远程服务器的 `root` 用户来执行 scp

注意 scp 不能使用 `./`，此时可以用 `$PWD` 替代