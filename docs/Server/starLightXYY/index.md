# StarLightXYY 建站笔记

[TOC]

## TODO

- [x] 买域名
- [ ] 学习部分
  - [x] docker compose
  - [x] docker network：network 如何把容器连接在一起
  - [x] web server 的工作原理（nginx，caddy）
    - [ ] 静态资源引用
    - [ ] 端口映射
    - [x] 反向代理
    - [ ] CORS（跨域资源共享）
  - [x] YAML：[YAML 入门教程 | 菜鸟教程 (runoob.com)](https://www.runoob.com/w3cnote/yaml-intro.html)
  - [ ] python flask：web app 框架
  - [ ] [跟着 MDN 学后端](https://developer.mozilla.org/en-US/docs/Learn/Server-side)
  - [ ] 传输文件(FTP,SFTP)：超算课程的 Linux 基本操作那节课
- [ ] typecho 
  - [ ] php 语言
    - [ ] `.php` 文件及其作用
  - [ ] 数据库
    - [ ] database 的数据管理模式
    - [ ] 怎么用 phpMyAdmin 或者命令行管理数据库（建立表格，建立连接？）
    - [ ] 博客怎么引用数据库里的信息
    - [ ] 写一个多层分类插件
  - [ ] 主题
  - [ ] 插件
  - [ ] 管理文章的方式：一个类似文件夹管理系统的 + tag
- [x] caddy：反向代理，用域名访问博客，子域名访问 overleaf（[Caddyfile Tutorial](https://caddyserver.com/docs/caddyfile-tutorial)）
- [x] [docsify](https://docsify.js.org/##/)：做一个文档网页，用于存放曾经做过的笔记（改用 mkdocs）
- [ ] markmap：部署一个可以在线编辑，把文件保存在数据库里的 mindmap web app
- [ ] 又拍云 CDN，海外加速
  - [ ] 学学 CDN 是什么东西
- [ ] 腾讯云买服务器
- [ ] 搭建私人邮件服务器
  - [ ] 学习 RSS
  - [ ] 腾讯企业邮箱：实现订阅功能
- [x] 嵌入 overleaf
  - [ ] overleaf 实现用户注册登录功能：[实践自部署Overleaf | Sparktour's](https://sparktour.me/2021/04/02/self-host-overleaf/##完整宏包支持（完整版TexLive）)**（有空做）**
- [ ] 搞个在线文档阅读器（可以上传文档 + 保存到服务器）

## Done

1. 安装 docker（[Debian Docker 安装 | 菜鸟教程 (runoob.com)](https://www.runoob.com/docker/debian-docker-install.html)）
2. 部署 overleaf
3. 部署 typecho
4. whoami + 反向代理
5. 部署 mkdocs

## TimeLine

1. 2021.8.25 在 bandwagon 租赁服务器一台
2. 2022.6.5 为了做网安导大作业—— socket 通信 + 隐私求交，时隔一年终于再次登录了服务器
3. 2022.7.2 在 skyWT 同学的帮助下，星光闪耀的小越越（starlightxyy.cn）正式上线，网站部署的第一个服务是 sharelatex
4. 2022.7.24 note.starlightxyy.cn 上线

## Record

在对 docker 一无所知的情况下，首先选择在网站上部署 overleaf 是一个明智的决定，跟着文档走难度较低，可以当做 docker 学习的第一个 lab。

## Learning

### DNS

DNS（Domain Name System，域名系统），因特网上作为域名和IP地址互相映射的一个分布式数据库

数据库结构：树形结构

域名解析过程：

1，在浏览器中输入[http://pool.btc.com](https://link.zhihu.com/?target=http%3A//pool.btc.com)域名，操作系统会先检查自己本地的hosts文件是否有这个网址映射关系，如果有，就先调用这个IP地址映射，完成域名解析。

2，如果hosts里没有这个域名的映射，则查找**本地DNS解析器缓存**，是否有这个网址映射关系，如果有，直接返回，完成域名解析。

3，如果hosts与本地DNS解析器缓存都没有相应的网址映射关系，首先会找TCP/ip参数中设置的首选DNS服务器，在此我们叫它**本地DNS服务器**，此服务器收到查询时，如果要查询的域名，包含在本地配置区域资源中，则返回解析结果给客户机，完成域名解析，此解析具有权威性。

4，如果要查询的域名，不在本地DNS服务器区域解析，但该服务器已缓存了此网址映射关系，则调用这个IP地址映射，完成域名解析，此解析不具有权威性。

5，如果本地DNS服务器本地区域文件与缓存解析都失效，则根据本地DNS服务器的设置（是否设置转发器）进行查询，如果未用转发模式，本地DNS就把请求发至13台根DNS，根DNS服务器收到请求后会判断这个域名(.com)是谁来授权管理，并会返回一个负责该顶级域名服务器的一个IP。本地DNS服务器收到IP信息后，将会联系负责.com域的这台服务器。这台负责.com域的服务器收到请求后，如果自己无法解析，它就会找一个管理.com域的下一级DNS服务器地址([http://BTC.com](https://link.zhihu.com/?target=http%3A//BTC.com))给本地DNS服务器。当本地DNS服务器收到这个地址后，就会找[http://pool.btc.com](https://link.zhihu.com/?target=http%3A//pool.btc.com)域服务器，重复上面的动作，进行查询，直至找到[http://pool.btc.com](https://link.zhihu.com/?target=http%3A//pool.btc.com)主机。

6，如果用的是转发模式，此DNS服务器就会把请求转发至上一级DNS服务器，由上一级服务器进行解析，上一级服务器如果不能解析，或找根DNS或把转请求转至上上级，以此循环。不管是本地DNS服务器用是是转发，还是根提示，最后都是把结果返回给本地DNS服务器，由此DNS服务器再返回给客户机。

公共 DNS 服务器：[什么是DNS？ - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/186028919##:~:text=DNS概括. DNS（Domain Name System，域名系统），因特网上作为域名和IP地址互相映射的一个分布式数据库，能够使用户更方便的访问互联网，而不用去记住能够被机器直接读取的IP数串。. 通过主机名，最终得到该主机对应的IP地址的过程叫做域名解析（或主机名解析）。. DNS协议运行在UDP协议之上，使用端口号53。.,DNS的分布数据库是以域名为索引的，每个域名实际上就是一棵很大的逆向树中路径，这棵逆向树称为域名空间（domain name space），如下图所示树的最大深度不得超过127层，树中每个节点都有一个可以长达63个字符的文本标号。. DNS的作用. DNS系统的作用. 正向解析：根据主机名称（域名）查找对应的IP地址. 反向解析：根据IP地址查找对应的主机域名.)

### UDP

UDP（UserDatagramProtocol）是一个简单的面向消息的传输层协议

### BTC

比特币，[BTC.com 矿池，更好的比特币矿池](https://pool.btc.com/)

### web server

某段程序监听了当前机器的 xxxx 端口，一旦外部访问当前机器的 xxxx 端口，这段程序就会返回一些内容。

#### 反向代理

1. 用户通过域名发出访问Web服务器的请求，该域名被DNS服务器解析为反向代理服务器的IP地址；
2. 反向代理服务器接受用户的请求；
3. 反向代理服务器在本地缓存中查找请求的内容，找到后直接把内容发送给用户；
4. 如果本地缓存里没有用户所请求的信息内容，反向代理服务器会代替用户向源服务器请求同样的信息内容，并把信息内容发给用户，如果信息内容是缓存的还会把它保存到缓存中。

#### 负载均衡

[什么是负载均衡？ - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/32841479)

1. 一个（或者多个）负载均衡服务器，多个 web 服务器——所有的后端服务器会保证提供相同的内容，以便用户无论哪个服务器响应，都能收到一致的内容。
2. 负载均衡器一般根据两个因素来决定要将请求转发到哪个服务器。首先，确保所选择的服务器能够对请求做出响应，然后根据预先配置的规则从健康服务器池（healthy pool）中进行选择。运行状态检查服务会定期尝试使用转发规则定义的协议和端口去连接后端服务器，如果，服务器无法通过健康检查，就会从池中剔除。
3. 负载均衡算法

#### cookie, token & session

- session：客户端和服务端都存有 session，缺点是负载均衡的每个服务器都要存一样的一组 session
- cookie：[深入理解Cookie - 简书 (jianshu.com)](https://www.jianshu.com/p/6fc9cea6daa2)
- token：好像和 cookie 作用类似但是格式不一样
- 发展历史：[彻底理解cookie，session，token - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/63061864)

#### F12 查看请求报文

1. F12
2. 网络
3. Fetch -> 可以看到 request header, response header
4. 一般来说看不懂，可以找不同发现错误

### emoji

[Complete list of github markdown emoji markup](https://gist.github.com/rxaviers/7360908)

[Emoji picture download](https://www.emojiall.com/zh-hans)

### GNU、MingW、CMAKE

[捋一捋gcc/g++/MingW/MSVC与make/CMake的关系 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/448884264)

### 软链接和硬链接

[5分钟让你明白“软链接”和“硬链接”的区别 - 简书 (jianshu.com)](https://www.jianshu.com/p/dde6a01c4094)

- 硬链接： `inode` 都指向同一个文件在硬盘中的区块
- 软链接： 保存了其代表的文件的绝对路径，是另外一种文件，在硬盘上有独立的区块，访问时替换自身路径。

### 操作系统原理——文件管理系统

（待学习）
