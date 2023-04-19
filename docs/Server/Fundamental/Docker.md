# Docker

[TOC]

## 参考文档

1. 菜鸟教程：[Docker 教程 | 菜鸟教程 (runoob.com)](https://www.runoob.com/docker/docker-tutorial.html)
2. [前言 - Docker — 从入门到实践 (gitbook.io)](https://yeasy.gitbook.io/docker_practice/)
3. Docker Compose 官方文档：[Compose specification | Docker Documentation](https://docs.docker.com/compose/compose-file/)
4. 资源汇总：[Docker 资源汇总 | 菜鸟教程 (runoob.com)](https://www.runoob.com/docker/docker-resources.html)

## 安装

[docker教程](https://blog.csdn.net/pushiqiang/article/details/78682323)

[菜鸟教程](https://www.runoob.com/docker/debian-docker-install.html)


先卸载，再安装

## 基础知识

| 概念                   | 说明                                                                                                                                                                                                                                                                                                  |
|:-------------------- |:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Docker 镜像(Images)    | Docker 镜像是用于创建 Docker 容器的模板，比如 Ubuntu 系统。                                                                                                                                                                                                                                                           |
| Docker 容器(Container) | 容器是独立运行的一个或一组应用，是镜像运行时的实体。                                                                                                                                                                                                                                                                          |
| Docker 客户端(Client)   | Docker 客户端通过命令行或者其他工具使用 Docker SDK (https://docs.docker.com/develop/sdk/) 与 Docker 的守护进程通信。                                                                                                                                                                                                         |
| Docker 主机(Host)      | 一个物理或者虚拟的机器用于执行 Docker 守护进程和容器。                                                                                                                                                                                                                                                                     |
| Docker Registry      | Docker 仓库用来保存镜像，可以理解为代码控制中的代码仓库。Docker Hub([https://hub.docker.com](https://hub.docker.com/)) 提供了庞大的镜像集合供使用。一个 Docker Registry 中可以包含多个仓库（Repository）；每个仓库可以包含多个标签（Tag）；每个标签对应一个镜像。通常，一个仓库会包含同一个软件不同版本的镜像，而标签就常用于对应该软件的各个版本。我们可以通过 **<仓库名>:<标签>** 的格式来指定具体是这个软件哪个版本的镜像。如果不给出标签，将以 **latest** 作为默认标签。 |
| Docker Machine       | Docker Machine是一个简化Docker安装的命令行工具，通过一个简单的命令行即可在相应的平台上安装Docker，比如VirtualBox、 Digital Ocean、Microsoft Azure。                                                                                                                                                                                          |

## 基本操作

### docker run

1. `docker run <image> <command>`
   - e.g. `docker run ubuntu:15.10 /bin/echo "Hello world"`  
2. `docker run -i -t <image> <shell>`
   - `-i`：允许你对容器内的标准输入 (STDIN) 进行交互
   - `-t`：在新容器内指定一个伪终端或终端
   - e.g. `docker run -i -t ubuntu:15.10 /bin/bash`
3. `-d`：后台运行
4. `--name <container name>`：指定容器名字
5. 端口映射：
   - `-p <external port>:<internal port>`
   - `-P`：将容器内部使用的网络端口随机映射到我们使用的主机上
   - 也可以设置绑定的 IP 和使用的协议（tcp/udp）：`-p 127.0.0.1:5000:5000/udp`
6. 其他参数：
   - `-v`：修改挂载点（VOLUME）
   - `--rm`：

### 容器查看

1. `docker ps`：查看运行的容器
   
   - `-a`：查看所有状态的容器
   - `-l`：查询最后一次创建的容器

2. `docker logs <container ID or name>`：查看容器内的标准输出
   
   - e.g. `docker logs 2b1b7a428627`
   
   - e.g. `docker logs amazing_cori`

3. `docker port <container ID or name>`：查看端口映射

4. `docker top <container ID or name>`：查看容器内部运行的进程

### 容器操作

1. `docker stop <container ID or name>`：停止容器
   
   - `kill` 类似

2. `rm`：删除容器
   
   - `docker container prune`：删除所有停止的容器

3. `docker restart <container ID or name>`：重启

4. `docker exec -it <container ID> <shell>`：进入容器
   
   - `docker exec -it 243c32535da7 /bin/bash`

5. 导入导出：
   
   - `docker export <container ID> > <export_image_name>.tar`
   - `docker import <file or URL or -> <REPOSITORY[:TAG]>`

6. [一次重启所有已停止的容器](https://blog.csdn.net/qq_39314099/article/details/105785134#:~:text=%E4%B8%80%E6%AC%A1%E9%87%8D%E5%90%AF%E6%89%80%E6%9C%89%E5%B7%B2%E5%81%9C%E6%AD%A2%E7%9A%84docker%E5%AE%B9%E5%99%A8%201%20%E6%9F%A5%E7%9C%8B%E6%89%80%E6%9C%89%E7%9A%84docker%E5%B7%B2%E5%81%9C%E6%AD%A2%E7%9A%84%E5%AE%B9%E5%99%A8%E7%9A%84%E5%8A%9E%E6%B3%95%EF%BC%9A%20docker%20ps%20-a%20%7C%20grep,%7C%20awk%20%27%20%7Bprint%20%241%7D%27%20%7Cxargs%20docker%20start)
   - 如果遇到 id 重复，直接 `reboot` 重启机器即可或者杀掉所有容器进程即可。

#### e.g. 运行一个 web app

1. `docker run -d -P training/webapp python app.py`
2. `docker ps -a`，在 **PORTS** 栏得到端口映射信息
3. 浏览器访问：`<IP>:<port>`

### 镜像查看

1. `docker images`：列出本地主机上的镜像
   - Repository
   - Tag
2. `docker search <repo name>`
   - official

### 镜像创建

1. `docker commit <container ID> <image name>:<tag>`
   - e.g. `docker commit -m="has update" -a="runoob" e218edb10161 runoob/ubuntu:v2`
   - `-m`：提交的描述信息
   - `-a`：指定镜像作者
2. `docker build -t <image name> <path/to/dockerFile>`
   - e.g. `docker build -t runoob/centos:6.7 .`
   - 利用 **dockerFile** 创建镜像
   - **注意**：上下文路径下不要放无用的文件，因为会一起打包发送给 docker 引擎，如果文件过多会造成过程缓慢。
3. `docker tag <image ID> <image name>:<tag>`

### DockerFile

- FROM

构建镜像基于哪个镜像

- MAINTAINER

镜像维护者姓名或邮箱地址

- RUN

构建镜像时运行的指令：

```dockerfile
## shell 格式
RUN <命令行命令>
RUN ./test.php dev offline
## exec 格式
RUN ["可执行文件", "参数1", "参数2"]
RUN ["./test.php", "dev", "offline"]
## 用 && 连接命令防止层数过多
RUN yum -y install wget \
    && wget -O redis.tar.gz "http://download.redis.io/releases/redis-5.0.3.tar.gz" \
    && tar -xvf redis.tar.gz
```

- CMD

运行容器时执行的shell环境

- VOLUME

指定容器挂载点到宿主机自动生成的目录或其他容器

- USER

为RUN、CMD、和 ENTRYPOINT 执行命令指定运行用户

- WORKDIR

为 RUN、CMD、ENTRYPOINT、COPY 和 ADD 设置工作目录，就是切换目录

- HEALTHCHECH

健康检查

- ARG

构建时指定的一些参数

- EXPOSE

声明容器的服务端口（仅仅是声明）

- ENV

设置容器环境变量

- ADD

拷贝文件或目录到容器中，如果是URL或压缩包便会自动下载或自动解压

- COPY

拷贝文件或目录到容器中，跟ADD类似，但不具备自动下载或解压的功能

- ENTRYPOINT

运行容器时执行的shell命令

## Docker Network

1. 作用：容器互联

2. 查看网络：`docker network ls`

3. 创建网络：`docker network create -d <network type> <network name>`
   
   - e.g. `docker network create -d bridge test-net`
   - network type: bridge / overlay

4. 容器接入网络：`--network <network name>`
   
   - e.g. `docker run -itd --name test1 --network test-net ubuntu /bin/bash`

5. 效果：在同一网络中的容器，以容器名为 hostname，可以相互连接
   
   - e.g. `ping test1`

6. 修改 DNS：`/etc/docker/daemon.json`
   
   - ```json
       {
         "dns" : [
           "8.8.8.8",
           "8.8.4.4"
         ]
       }
     ```
   
   - 重启 docker 生效：`systemctl resrtart docker`
   
   - check：`docker run -it --rm  ubuntu  cat etc/resolv.conf`

## Docker Compose

Compose 是用于定义和运行多容器 Docker 应用程序的工具。

### 安装

`sudo pip install docker-compose` 用 pip 安装

### YAML

参考文章：[YAML 菜鸟](https://www.runoob.com/w3cnote/yaml-intro.html)，[YAML 阮一峰](https://www.ruanyifeng.com/blog/2016/07/yaml.html)

1. 格式：
   - 缩进（空格:heavy_check_mark:，tab:x:），左对齐
   - `:`，`?`，`-`，`&,<<,*` 的作用
2. 数据类型：
   - 对象
   - 数组
   - 纯量

### docker-compose.yml

[docker-compose教程](https://blog.csdn.net/pushiqiang/article/details/78682323)，不会的可以查这个博客

常用配置：

1. `version`：compose 的版本
2. `services`
3. `build`：如果你同时指定image和build，则compose会通过build指定的目录构建容器镜像，而构建的镜像名为image中指定的镜像名和标签。
4. `image`
5. `container_name`
6. `expose`：只将端口暴露给连接的服务，而不暴露给主机
7. `ports`：
8. `links`：自动创建网络连接容器
9. `networks`：可以自行配置的网络
   - [docker-compose的网络networks的使用技巧 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/382779160)
10. `volumes`：挂载`external:internal`
    - 可通过顶级 volumes 设置挂在卷别名
11. `restart`：`"no", always, no-failure, unless-stop`
12. `environment`：环境变量
13. `env_file`
14. `command ["serve", "-a", "localhost:8000"]` ：创建容器时执行的命令

示例文件

```yaml
version: "3"

services:
  typecho:
    image: joyqi/typecho:nightly-php7.4-apache
    container_name: typecho
    networks:
      - blog
    ports:
      - "5120:80"
    restart: unless-stopped

networks:
  blog:
    external: true
```

### 用 docker-compose 创建容器

1. `docker-compose up -d` 后台运行

2. `docker exec -it <container_name> <shell>` 进入容器
   
   - 常用的 shell 有 sh, bash, zsh

## 其他

### docker machine

### docker swarm

## 常见问题

### driver failed programming external connectivity on endpoint quirky_allen

外部端口被占用。