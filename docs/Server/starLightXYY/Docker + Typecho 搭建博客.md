[TOC]

# docker + typecho

用 `docker-compose` 自动下载镜像和生成容器

## 创建网络

```shell
$ docker network create blog
# blog 用于连接 typecho 的容器和 mariadb
$ docker network creeate db_admin
# db_admin 用于连接 phpmyadmin 和 mariadb，可以通过前者在网页上管理数据库
```

## mariaDB

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
    environment:
      - MARIADB_ROOT_PASSWORD=NhwaJU8tW7UZ5u
    volumes:
      - /data/mysql:/var/lib/mysql
    restart: unless-stopped

networks:
  blog:
    external: true
  db_admin:
    external: true
```

## phpMyAdmin

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

## typecho

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
      - "5120:80" # 服务器的 5120 提供给容器的 80 端口
    restart: unless-stopped

networks:
  blog:
    external: true
```

然后就可以用端口 5120 访问 typecho 主页，注册账号。可以用 5210 端口访问 phpmyadmin 管理数据库。

# caddy 反向代理

## 参考文档

1. 官方文档：[Welcome — Caddy Documentation (caddyserver.com)](https://caddyserver.com/docs/)
2. 中文文档：[Caddy中文文档 - Caddy中文文档 (dengxiaolong.com)](https://dengxiaolong.com/caddy/zh/)
3. 简略版：[更好用的 Web 服务器：Caddy - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/144208057)

## 操作步骤

1. `vim /etc/caddy/CaddyFile`

2. ```yaml
    starlightxyy.cn {
        reverse_proxy localhost:5120
    }
   
    www.starlightxyy.cn { # www 是算作一个子域名的，也需要做反向代理
        reverse_proxy localhost:5120
    }
   
    overleaf.starlightxyy.cn {
        reverse_proxy localhost:5000
    }
   ```

3. `caddy reload`

## 常见问题

1. 样式表加载失败：静态资源引用问题，在博客管理界面修改**站点地址**为 `https://starlightxyy.cn`
2. 申请子域名：在阿里云后台>域名管理，添加记录（[阿里云网站运维检测平台](https://zijian.aliyun.com/)可以检测是否申请成功）

# 主题和插件

# 补充芝士

1. 静态博客和动态博客：[从零开始折腾博客(0)：静态？动态？ - idealclover](https://idealclover.top/archives/237/)
2. yml 文件的编写：[YAML 入门教程 | 菜鸟教程 (runoob.com)](https://www.runoob.com/w3cnote/yaml-intro.html)