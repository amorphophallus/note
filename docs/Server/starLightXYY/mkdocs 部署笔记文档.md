# Docker + Mkdocs + Github 部署文档网页

[TOC]

## 前置芝士

官方文档：[Getting started - Material for MkDocs (squidfunk.github.io)](https://squidfunk.github.io/mkdocs-material/getting-started/)

### 静态网页

1. 所有网页内容都提前渲染好（比如都放在 `path/to/mkdocs/site` 里面）

2. 没有后端

3. 用 web server 部署，需要一个 `index.html` 作为开始页面

### 一些指令

#### `docker run --rm -v -p -it`

#### `${PWD}`

打印当前路径

### caddyfile

1. `encode zstd gzip` 表示打开 gzip 和 Zstandard 压缩功能，这样网站在传输网页时降低流量

2. `file_server` 指令表示生成静态网页，加上 `browse` 则不需要 index 文件自动生成目录

3. `root` 是指定网站的根目录

## 安装

### 基本安装

1. 下载 mkdocs（自动下载依赖）：`pip install mkdocs-material`

2. 创建新项目：`mkdocs new .`

3. 修改 `./mkdocs.yml`：
   
   ```yaml
   site_name: XYY's Notebook
   theme:
     name: material
   ```

4. 预览页面效果：`mkdocs serve -a localhost:<port>`
   
   - 只能在*本地*预览，可以使用 `curl localhost:<port>` 命令来检查是否成功

5. 修改文档之后重新生成页面：`mkdocs build`
   
   - 静态页面的位置：`./site`

6. 修改 `/etc/caddy/Caddyfile` ，加入

```json
note.starlightxyy.cn {
    file_server
    root * /root/apps/mkdocs/site
}
```

7. 重启 caddy 服务：`caddy reload`

### Docker 安装

*Docker 部署的好处是修改文档之后不用 build 直接就可以生效，稍微方便一点。*

1. DockerFile：在原始镜像的基础上安装需要的插件
   
   ```dockerfile
   FROM squidfunk/mkdocs-material
   RUN pip install mkdocs-minify-plugin && pip install mkdocs-redirects
   ```

2. docker-compose.yml
   
   ```yaml
   version: "3"
   
   services:
       mkdocs:
           build: .
           image: squidfunk/mkdocs-material:with-plugins
           container_name: mkdocs
           ports:
               - "5234:8000"
           volumes:
               - /root/dockers/mkdocs/docs:/docs
           command: ["serve", "-a", "0.0.0.0:8000"]
           restart: unless-stopped
   ```

3. 在挂载的目录（`/root/dockers/mkdocs/docs`）下运行 `mkdocs new .` 生成初始文档

4. `docker-compose up -d`

5. 修改 `/etc/caddy/Caddyfile` ，加入
   
   ```
   note.starlightxyy.cn {
       reverse_proxy localhost:5234
   }
   ```

6. `caddy reload`

7. 检查：
   
   - `docker ps -a` 查看运行情况（反复 restart 说明命令写错了）
   
   - `curl localhost:5234 -v`
   
   - `curl https://note.starlightxyy.cn -v`

### 关联 GitHub 仓库

1. 新建仓库

2. 清空挂载目录

3. 克隆到挂载目录：`git clone git@github.com:amorphophallus/note.git ./docs`

4. 重新 `mkdocs new .`

5. `git push origin main` 

然后就可以多端共享文件啦！

### 自动同步 github 仓库

1. 在本地仓库外面新建 `pull.sh`
   
   ```shell
   ##!/bin/bash
   while true
   do
       git -C ./docs/ pull origin main
       sleep 1m
   done
   ```

2. 设置权限 `chmod -R 777 pull.sh`

3. 后台运行 `nohup ./pull.sh &`

4. 结束进程：
   
   - `ps -aux | grep "pull.sh"`
   
   - `kill PID`

然后就可以每隔一段时间同步一下上传的文件了！

## 编辑

官方配置指南：[Configuration - MkDocs](https://www.mkdocs.org/user-guide/configuration/)

调试：可以在本地装一个 `mkdocs-material`，使用 `mkdocs serve`

### navigation config

[Setting up navigation - Material for MkDocs ](https://squidfunk.github.io/mkdocs-material/setup/setting-up-navigation/)，主要是关于顶端导航、侧边栏和文章目录的设置

## 更新

### 更新 mkdocs

1. 更新 python：`apt-get update && apt-get upgrade`

2. 更新 mkdocs：`pip install --upgrade mkdocs-material`

3. 查看版本：`pip show mkdocs-material` 

### 安装插件

1. 修改 DockerFile

2. `docker-compose up -d --build` ：重新构建镜像和容器

3. 修改 `mkdocs.yml` 增加 `extensions`


## 自定义

### 插件

1. [task list](https://squidfunk.github.io/mkdocs-material/setup/extensions/python-markdown-extensions/#tasklist)
2. [code blocks](https://squidfunk.github.io/mkdocs-material/reference/code-blocks/)：代码块可以添加
    - 标题
    - 行号
    - 高亮
    - 高亮某几行
    - 脚注（可展开收起）
    - 高亮行内代码
3. [dark mode](https://squidfunk.github.io/mkdocs-material/setup/changing-the-colors/)
4. [content tab](https://squidfunk.github.io/mkdocs-material/reference/content-tabs/)：去官方文档查看语法
5. [roam-links](https://github.com/Jackiexiao/mkdocs-roamlinks-plugin)：支持链接语法

### 附加代码

懒得搞了，先酱紫吧...

## 常见问题

### 403

静态网页文件访问需要 root 权限。把文件 mv 到其他位置即可。
