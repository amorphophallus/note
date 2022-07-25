# Docker 部署 Overleaf

[TOC]

## 整体步骤



参考：部署 overleaf（[Overleaf-在线Latex编辑器部署 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/150827584)）

参考：skyWT（[服务器 Overleaf 部署指南 - SkyWT](https://blog.skywt.cn/posts/self-host-overleaf)）



## 下载 docker 镜像





1. 依赖：curl**（好像很厉害，不知道是个什么东西）**

2. 依赖：pip（[Python pip 安装与使用 | 菜鸟教程 (runoob.com)](https://www.runoob.com/w3cnote/python-pip-install-usage.html)）**（不知道是个什么东西）**

3. 用 docker 下载 sharelatex 镜像：`docker pull sharelatex/sharelatex` 
    - texlive 源：[TeX Live - TeX Users Group (tug.org)](https://tug.org/texlive/)



## 启动容器



1. 使用 `docker-compose.yml` 里的配置生成容器：`docker-compose up -d`
2. `docker exec -it sharelatex bash`：进入 sharelatex 的虚拟服务器的 shell（sharelatex容器本质上是一个Ubuntu）
3. 修改完容器之后（下载完 `texlive` 或者下载完字体包之后）都记得 `docker restart <container_id>`  重启容器，否则不会自动更新



**p.s. **



1. yml 是配置文件，声明了 `image`，`container_name`，`depend_on`，`port` 等内容
2. `tlmgr` 是 `Tex Live Manager` 的简称，是 `sharelatex` 自带的
3. 如果空间够的话还可以为 `sharelatex:with-texlive-full` 创建一个镜像，以后就算 container 没了也可以（[Quick Start Guide · overleaf/overleaf Wiki (github.com)](https://github.com/overleaf/overleaf/wiki/Quick-Start-Guide)）





## 反向代理



### nginx proxy



参考  [nginx-proxy 的 github 仓库](https://github.com/nginx-proxy/nginx-proxy)



但是因为主机环境用的是 caddy，会有端口占用问题，所以改用 caddy



从 curl 的报错里发现问题

```shell
## curl -H "Host: whoami.local" localhost -v
*   Trying ::1:80...
* Connected to localhost (::1) port 80 (##0)
> GET / HTTP/1.1
> Host: whoami.local
> User-Agent: curl/7.74.0
> Accept: */*
>
* Mark bundle as not supporting multiuse
< HTTP/1.1 308 Permanent Redirect
< Connection: close
< Location: https://whoami.local/
< Server: Caddy ## web server 用的是 Caddy
< Date: Sat, 09 Jul 2022 08:20:09 GMT
< Content-Length: 0
<
* Closing connection 0
```





### caddy



1. `/etc/caddy/Caddyfile`

 ```caddy
 overleaf.starlightxyy.cn {
     reverse_proxy localhost:5000
 }
 ```

2. 环境变量 `/etc/profile`

```
export SHARELATEX_SECURE_COOKIE=true
export SHARELATEX_BEHIND_PROXY=true
```







## 常见问题



### 报错："The container name "/mongo" is already in use by Creating redis"



1. `docker ps -a` 查看所有状态的容器（不加`-a`只显示运行的容器）

2. 发现有停止的容器占用了名称，`docker rm <container_id>` 删除容器，再重新生成容器即可



### 修改 admin 邮箱



修改 admin 邮箱：输入命令之后会提示去修改密码页面修改密码 `docker exec sharelatex /bin/bash -c "cd /var/www/sharelatex; grunt user:create-admin --email joe@example.com"`



### 可以编译但是无法渲染 pdf



是 IDM 自动抓取文件的问题 [overleaf报错：PDF Rendering Error Something went wrong while rendering this PDF_Ma lidong的博客-CSDN博客_overleaf pdf渲染错误](https://blog.csdn.net/qq_41684249/article/details/118638988)



### pdfLatex 可以编译但是 XeTeX 不能编译 



有问题去 github 上看 issue，重新下载 `scheme-full` [XeLaTeX unable to compile · Issue ##703 · overleaf/overleaf (github.com)](https://github.com/overleaf/overleaf/issues/703)



### 支持中文字体



1. 参考博客：支持中文字体：[部署sharelatex并配置中文 · 语雀 (yuque.com)](https://www.yuque.com/latex/sharelatex/vdit69)

2. 服务器空间不够了，只能传部分中文字体：[WIndows 中文字体类型对应的文件名称](https://blog.csdn.net/qq_29856789/article/details/80883301)
    - latex 需要的中文字体 ：[LaTeX的学习--字体 - 简书 (jianshu.com)](https://www.jianshu.com/p/9c3845f76668)，具体的看下面
        - 宋体：`\songti`——注意宋体是 `simsun.ttf` 不是 `simsunb.ttf`
        - 楷书：`\kaishu`
        - 黑体：`\heiti`
        - 隶书：`\lishu`
        - 幼圆：`\youyuan`
        - 雅黑：`\yahei`：`msyh.ttc,msyhl.ttc,msyhbd.ttc`
    - 在 `C:/Windows/Fonts` 里搜索字体的中文名（例如“宋体”），把所有搜到的文件都传到服务器

3. 参考博客 [LaTeX 中文字体配置指南 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/538459335)，ctex 的字体设置文件在容器内的 `/usr/local/texlive/2022/texmf-dist/tex/latex/ctex/fontset`

    - ```tex
        \setCJKfamilyfont { zhsong  } { SimSun          }
        \setCJKfamilyfont { zhhei   } { SimHei          }
        \setCJKfamilyfont { zhfs    } { FangSong        }
        \setCJKfamilyfont { zhkai   } { KaiTi           }
        \setCJKfamilyfont { zhyahei } { Microsoft~YaHei } [ BoldFont = *~Bold ]
        \setCJKfamilyfont { zhli    } { LiSu            }
        \setCJKfamilyfont { zhyou   } { YouYuan         }
        ```

    - 可以根据平台+编译器（例如我用的是 windows+XeTex）选择合适的 `.def` 文件查看，找到所有需要的字体





可行的步骤：

1. 下载 microsoft 标准字体
    1. `apt-get update`
    2. `apt install ttf-mscorefonts-installer`，阅读条款选择 yes
    3. `fc-cache -vr`
    4. `fc-list` 查看所有字体
2. 搬运中文字体：
    1. 从本地用 scp 传字体到服务器 `scp ./* root@vps:~/dockers/overleaf/sharelatex_data/tmp/texmf-var/fonts/chinese`
    2. 根据挂载信息`~/dockers/overleaf/sharelatex_data:/var/lib/sharelatex`，把字体搬到`~/dockers/overleaf/sharelatex_data` 目录下
    3. 进入容器 `docker exec -it sharelatex /bin/bash`
    4. 搬运字体，从 `/var/lib/sharelatex` 到 `/usr/share/fonts/`
    5. 再 `fc-cache -vr` 
    6. `fc-list :lang=zh` 查看中文字体
3. 编写 $\LaTeX$ 代码时记得 `\usepackage{ctex}`



### minted 代码高亮



看 sky 的博客，操作完成之后 `docker restart`



### favicon.ico 变成奇怪的图像



因为曾经反向代理到 phpMyAdmin，在浏览器里留下了缓存，所以更新反向代理之后浏览器会直接使用本地的 favicon.ico 而不会去服务器请求。



解决办法是 `ctrl + F5` 刷新浏览器缓存。





### A previous compile is still running. Please wait a minute and try compiling again.



超时错误。可能是项目里有太大的文件。删除 pdf 和 bib 等中间文件，基本就不会有问题了。

