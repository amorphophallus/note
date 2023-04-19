# C 盘清理

[TOC]

## 常规手段

[知乎-清理C盘](https://zhuanlan.zhihu.com/p/427183314)

设置 qq 微信的用户文件存储位置

## 软链接

[VSCode 用户文件夹 .vscode 迁移](https://blog.csdn.net/weixin_53510183/article/details/126906182#:~:text=%E5%BD%93%E6%88%91%E4%BB%AC%E8%A7%A3%E5%8E%8B%E5%AE%8C%E6%AF%95%E5%90%8E%3A%201%20%E5%9C%A8%E5%BD%93%E5%89%8D%20VSCode%20%E7%9B%AE%E5%BD%95%E4%B8%8B%E6%96%B0%E5%BB%BA%E4%B8%80%E4%B8%AA%20data%20%E6%96%87%E4%BB%B6%E5%A4%B9%202,C%3A%5CUsers%5CAppData%5CRoaming%5CCode%20%E6%96%87%E4%BB%B6%E5%A4%B9%E5%86%85%E7%9A%84%E6%89%80%E6%9C%89%E6%96%87%E4%BB%B6%E5%85%A8%E9%80%89%E5%A4%8D%E5%88%B6%E5%88%B0%20user-data%20%E7%9B%AE%E5%BD%95%E5%86%85%EF%BC%8C%E5%86%8D%E6%AC%A1%E6%89%93%E5%BC%80%20Code.exe%20%E7%A8%8B%E5%BA%8F%EF%BC%8C%E5%B0%B1%E5%8F%AF%E4%BB%A5%E5%8F%91%E7%8E%B0%E6%A0%B9%E4%BB%A5%E5%89%8D%E7%9A%84%20VSCode%20%E4%B8%80%E6%A8%A1%E4%B8%80%E6%A0%B7%E7%9A%84%E9%85%8D%E7%BD%AE%E4%BB%A5%E5%8F%8A%E6%89%A9%E5%B1%95)：看最后一个方法，就是建立软连接

[windows mklink 介绍](https://blog.csdn.net/carpediem_sisy/article/details/122928011)：mklink 的第一个参数路径是虚拟的，需要保证不存在这个文件目录；第二个参数路径的文件夹需要自己创建，否则会报错找不到文件位置之类的。

目前已经创建的软链接如下：

```shell
mklink /D "C:\Users\allen\AppData\Local\Programs\camscanner-toc" "F:\programfiles2022\camscanner-toc"
mklink /D "C:\Users\allen\.android" "E:\programfiles\Android\.android"
mklink /D "C:\Users\allen\.vscode" "F:\programfiles2022\VSCode_UserFiles\.vscode"
mklink /D "C:\Users\allen\.gradle" "F:\programfiles2022\.gradle"
```

C 盘下的 program files 和 program files(x86) 无法重命名和移动，就没有办法方便地创建软链接了，里面还有一些应用程序可以考虑重装或者迁移。

## 查看磁盘空间占用情况

使用 spacesniffer