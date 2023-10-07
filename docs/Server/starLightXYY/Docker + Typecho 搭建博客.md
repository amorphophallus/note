# Docker + Typecho + Caddy 搭建博客

[TOC]

## docker + typecho

用 `docker-compose` 自动下载镜像和生成容器

### 创建网络

```shell
$ docker network create blog
## blog 用于连接 typecho 的容器和 mariadb
$ docker network create db_admin
## db_admin 用于连接 phpmyadmin 和 mariadb，可以通过前者在网页上管理数据库
```

### mariaDB

docker-compose.yml

```yaml
version: "3"

services:
  mariadb:
    image: mariadb:latest
    container_name: mariadb
    networks:
      - blog
      - db_admin
    # Do not need password if there's alreasy 
    # environment:
    #   - MARIADB_ROOT_PASSWORD=NhwaJU8tW7UZ5u
    volumes:
      - ./data:/var/lib/mysql
    restart: unless-stopped

networks:
  blog:
    external: true
  db_admin:
    external: true
```

挂载最好在同一个目录下面，方便搬运, 记得用 **相对路径**

### phpMyAdmin

docker-compose.yml

```yaml
version: "3"

services:
  phpmyadmin:
    image: phpmyadmin/phpmyadmin:latest
    container_name: phpmyadmin
    environment:
      - PMA_HOST=mariadb
    networks:
      - db_admin
    ports:
      - "5210:80"
    restart: unless-stopped

networks:
  db_admin:
    external: true
```

设置：
1. 登录 phpMyAdmin `vpshost:5210`
2. 新增用户账户 `typecho`
3. 登录博客页面，进行初始化设置
    - 数据库地址：`mariadb` (和 typecho 在同一网络内，用容器名标识地址)
    - 数据库用户名和密码用刚刚创建的

### typecho

1. 在 dockerhub 上找镜像[joyqi/typecho - Docker Image | Docker Hub](https://hub.docker.com/r/joyqi/typecho)
2. 把文档里的 `docker run` 翻译成 `docker compose` 文件
   - `docker run --name typecho-server -e TYPECHO_SITE_URL=https://your-domain.com -d joyqi/typecho:nightly-php7.4-apache`

docker-compose.yml

```yaml
version: "3"

services:
  typecho:
    image: joyqi/typecho:nightly-php7.4-apache
    container_name: typecho
    networks:
      - blog
    ports:
      - "5120:80" ## 服务器的 5120 提供给容器的 80 端口
    restart: unless-stopped
    volumes:
      - ./data:/app

networks:
  blog:
    external: true
```

然后就可以用端口 5120 访问 typecho 主页，注册账号。可以用 5210 端口访问 phpmyadmin 管理数据库。



## caddy 反向代理

### 参考文档

1. 官方文档：[Welcome — Caddy Documentation (caddyserver.com)](https://caddyserver.com/docs/)
2. 中文文档：[Caddy中文文档 - Caddy中文文档 (dengxiaolong.com)](https://dengxiaolong.com/caddy/zh/)
3. 简略版：[更好用的 Web 服务器：Caddy - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/144208057)

### 操作步骤

1. `vim /etc/caddy/CaddyFile`

2. ```yaml
    starlightxyy.cn {
        reverse_proxy localhost:5120
    }
   
    www.starlightxyy.cn { ## www 是算作一个子域名的，也需要做反向代理
        reverse_proxy localhost:5120
    }
   
    overleaf.starlightxyy.cn {
        reverse_proxy localhost:5000
    }
   ```

3. `caddy reload`

### 常见问题

1. 样式表加载失败：静态资源引用问题，在博客管理界面修改**站点地址**为 `https://starlightxyy.cn`
2. 申请子域名：在阿里云后台>域名管理，添加记录（[阿里云网站运维检测平台](https://zijian.aliyun.com/)可以检测是否申请成功）
1. [docker exec 失败](https://blog.csdn.net/leiwuhen92/article/details/127772413)

## 网站备案

[腾讯云域名备案全过程](https://www.cnblogs.com/yyzwz/p/13393223.html#:~:text=%E5%A6%82%E4%BD%95%E5%A4%87%E6%A1%88%EF%BC%88%E4%BB%A5%E8%85%BE%E8%AE%AF%E4%BA%91%E4%B8%BA%E4%BE%8B%EF%BC%89%EF%BC%9F%201%201.%E6%B3%A8%E5%86%8C%E8%85%BE%E8%AE%AF%E4%BA%91%E8%B4%A6%E5%8F%B7%EF%BC%8C%E5%AE%8C%E6%88%90%E5%AE%9E%E5%90%8D%E8%AE%A4%E8%AF%81%20%E6%88%91%E5%A4%87%E6%A1%88%E6%97%B6%E6%89%80%E7%94%A8%E7%9A%84%E6%97%B6%E9%97%B4%EF%BC%8C%E7%BB%99%E5%A4%A7%E5%AE%B6%E4%B8%80%E4%B8%AA%E5%8F%82%E8%80%83%EF%BC%8C%E4%B8%8B%E5%90%8C%EF%BC%88%E6%B3%A8%E5%86%8C3%E5%88%86%E9%92%9F%EF%BC%8C%E5%AE%9E%E5%90%8D%E8%AE%A4%E8%AF%81%E4%B8%AA%E4%BA%BA1~2%E5%A4%A9%EF%BC%8C%E4%BC%81%E4%B8%9A2~3%E5%A4%A9%EF%BC%89%20%E8%85%BE%E8%AE%AF%E4%BA%91%E5%AE%98%E7%BD%91%EF%BC%9A%20https%3A%2F%2Fcloud.tencent.com%2F%20%EF%BC%8C%E6%B3%A8%E5%86%8C%E4%B8%80%E4%B8%AA%E8%87%AA%E5%B7%B1%E7%9A%84%E8%B4%A6%E5%8F%B7%EF%BC%8C%E5%B9%B6%E4%B8%94%E5%AE%8C%E6%88%90%E5%AE%9E%E5%90%8D%E8%AE%A4%E8%AF%81%E3%80%82%20%EF%BC%88%E4%B8%80%E8%88%AC%E5%BB%BA%E8%AE%AE%E9%82%AE%E7%AE%B1%E6%B3%A8%E5%86%8C%EF%BC%8C%E6%96%B9%E4%BE%BF%E7%99%BB%E5%85%A5%EF%BC%89,%E4%B8%8A%E6%9C%89%E5%8D%83%E7%99%BE%E4%B8%87%E5%8F%B0%E4%B8%BB%E6%9C%BA%EF%BC%8C%E4%B8%BA%E4%BA%86%E5%8C%BA%E5%88%86%E8%BF%99%E4%BA%9B%E4%B8%BB%E6%9C%BA%EF%BC%8C%E6%AF%8F%E4%B8%80%E5%8F%B0%E4%B8%BB%E6%9C%BA%E9%83%BD%E8%A2%AB%E5%88%86%E9%85%8D%E4%B8%80%E4%B8%AA%E7%9A%84%20IP%20%E5%9C%B0%E5%9D%80%E3%80%82%20...%204%204.%E7%94%B3%E8%AF%B7%E5%A4%87%E6%A1%88%20%E6%88%91%E5%A4%87%E6%A1%88%E6%97%B6%E6%89%80%E7%94%A8%E7%9A%84%E6%97%B6%E9%97%B4%EF%BC%8C%E7%BB%99%E5%A4%A7%E5%AE%B6%E4%B8%80%E4%B8%AA%E5%8F%82%E8%80%83%20)，可以参考

一些注意事项：

1. 域名和服务器一定要买同一家的。阿里云的备案需要“ICP 备案服务码”，如果服务器不在阿里云，这个服务码还得多花 100 块钱买，纯纯的坑人。腾讯云虽然可以接入备案，但是肯定不如域名和服务器都买腾讯云的方便。

## 博客搬运

### csdn




## 主题

选用 [Amaze](https://github.com/spiritree/typecho-theme-amaze)

### 安装

1. `docker exec -it typecho bash`
2. `cd /app/usr/themes`
3. `apt-get update && apt-get install wget && apt-get install unzip`
4. `wget https://github.com/spiritree/typecho-theme-amaze/archive/refs/heads/master.zip`
5. `unzip master.zip`
6. `mv typecho-theme-amaze-master/ amaze/`
7. 在博客后台(`/admin`)启用主题

[E: Unable to locate package vim 问题解决](https://blog.csdn.net/xiaozhangdetuzi/article/details/118112231)

tips: 在安装包之前先 update 以下，否则可能找不到包

### 自定义

#### 添加备案号

在容器中修改 `/app/usr/themes/amaze/footer.php`，或者在容器外的 docker-compose 同文件夹下修改 `./data/usr/themes/amaze/footer.php`：

```php
 <img style="padding-top:2px;height:1.2rem;width:1.2rem" src="<?php $this->options->themeUrl('/img/gh.png')?>"><a href="https://beian.miit.gov.cn"target="_blank">浙ICP备2022026654号</a>
```

typecho 的 php 文件是网页模板，会交给目标网页去渲染，所以需要用 php 找到静态资源的位置，而不是直接使用相对地址。

## 插件


## 补充芝士

1. 静态博客和动态博客：[从零开始折腾博客(0)：静态？动态？ - idealclover](https://idealclover.top/archives/237/)
2. yml 文件的编写：[YAML 入门教程 | 菜鸟教程 (runoob.com)](https://www.runoob.com/w3cnote/yaml-intro.html)