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

我的 `mkdocs.yml` 文档

```yaml
## Project Information
site_name: XYY's Notebook                           ## 显示在左上角和标签页上的站点名字
site_url: https://note.starlightxyy.cn              ## 点击站点名字跳转到的网址
repo_url: https://github.com/amorphophallus/note    ## 右上角 icon 的跳转地址
repo_name: note-github                              ## 右上角 icon 的备注文字
edit_uri: edit/main/docs                            ## 文章目录左侧的编辑按钮的跳转地址
site_description: Note about everything.
theme:
    name: material
    features:
        - navigation.tabs                           ## 启用顶端导航
        - navigation.sections                       ## 展开侧边导航
        - navigation.indexes                        ## 启用章节概览 index.md
        - navigation.top                            ## 启用回到顶部按钮

## Documentation Layout
nav:
    - 'About': 'index.md'
    - 'Server':
        - 'Fundamental':
            - 'Linux Command': 'Server/Fundamental/Linux Command.md'
            - 'vim': 'Server/Fundamental/vim.md'
            - 'git':
                - '常见操作': 'Server/Fundamental/git/常见操作.md'
                - '常见问题': 'Server/Fundamental/git/常见问题.md'
            - 'WSL': 'Server/Fundamental/WSL.md'
            - 'Docker': 'Server/Fundamental/Docker.md'
            - 'Caddy': 'Server/Fundamental/Caddy.md'
        - 'StarLightXYY':
            - 'Server/starLightXYY/index.md'                                                    ## 章节概览使用方式:index.md
            - 'Docker + Typecho 搭建博客': 'Server/starLightXYY/Docker + Typecho 搭建博客.md'
            - '服务器部署 overleaf': 'Server/starLightXYY/服务器部署 overleaf.md'
            - 'mkdocs 部署笔记文档': 'Server/starLightXYY/mkdocs 部署笔记文档.md'
    - 'Front End':
        - 'html': 'Front End/html.md'
        - 'javascript': 'Front End/javascript.md'
        - 'css': 'Front End/css.md'
        - 'react': 'Front End/react.md'
        - 'antd': 'Front End/antd.md'
    - 'Programming Tools':
        - 'LaTeX': 'Programming Tools/LATEX/LATEX.md'
        - 'Python':
            - 'Python': 'Programming Tools/Python/python.md'
            - 'Numpy': 'Programming Tools/Python/Numpy.md'
    - 'Projects':
        - 'box-2021 项目总结': 'Projects/box-2021 项目总结.md'
        - 'rop-neo-front':
            - '内训笔记': 'Projects/rop-neo-front/内训笔记.md'
            - '项目笔记': 'Projects/rop-neo-front/项目笔记.md'
        - 'android':
            - '笔记': 'Projects/android/笔记.md'
    - 'College Courses':
        - 'Tools':
            - 'word学习笔记': 'College Courses/Tools/word学习笔记.md'
            - '论文相关': 'College Courses/Tools/论文相关.md'
        - '网安导':
            - '笔记': 'College Courses/网安导/笔记.md'
            - '实验报告': 'College Courses/网安导/README.md'
    - 'Others':
        - '经验':
            - '本科毕业出路经验分享': 'Others/经验/本科毕业出路经验分享.md'
            - '寒假社会实践经验总结': 'Others/经验/寒假社会实践经验总结.md'
            - '职规学长学姐经验分享': 'Others/经验/职规学长学姐经验分享.md'
            - '竺院学长经验分享-兴趣': 'Others/经验/竺院学长经验分享-兴趣.md'
        - '兴趣':
            - 'AE学习': 'Others/兴趣/AE学习.md'
            - 'pr小技巧': 'Others/兴趣/pr小技巧.md'
            - '篮球运球': 'Others/兴趣/篮球运球.md'
            - '素描课程笔记（知识点篇）': 'Others/兴趣/素描课程笔记（知识点篇）.md'
            - '素描课程笔记（练习篇）': 'Others/兴趣/素描课程笔记（练习篇）.md'
        - 'Something to read': 'Others/something to read.md'

```

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
2. [code blocks](https://squidfunk.github.io/mkdocs-material/reference/code-blocks/)
3. 

### 附加代码

懒得搞了，先酱紫吧...

## 常见问题

### 403

静态网页文件访问需要 root 权限。把文件 mv 到其他位置即可。
