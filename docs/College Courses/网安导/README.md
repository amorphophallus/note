[toc]

# 代码文档



## 功能和原理说明



本 project 实现了基于 socket 的两方通信和基于 SHA-256 的隐私求交协议。



## 文件结构



```json
│ README.md // 代码文档
│  
├─client // 客户端文件
│      answer.json // 求交结果实例文件
│      B_m.json // 客户端初始数据实例文件
│      client.py // 客户端程序
│      
└─server // 服务器端文件
        answer.json // 求交结果实例文件
        A_m.json // 服务器端初始数据实例文件
        server.py // 服务器端程序
```





# 使用说明

假设有两个人 A, B 需要使用该程序进行隐私求交。两人分别使用服务器端程序 `server.py` 和客户端程序 `client.py` 实现通信和求交。

1. **环境依赖**：A 和 B 需要先分别在服务器和本地安装 `python3`

2. A 登录服务器，将数据写入 `A_m.json` 文件，数据格式如下

    ```json
    {
        "count":6,
        "maindata": [
                "胡英俊",
                "张小丽",
                "牛爷爷"
        ]
    }
    ```

    其中 count 是集合中的总元素数， maindata 中存储集合中所有元素

3. A 修改 `serber.py` 中的服务器 IP 为当前使用的服务器 IP，在服务器上运行 `server.py`，并将服务器 IP 和端口告诉 B

4. B 在本地将数据写入 `B_m.json` ，数据格式同上

5. B 修改 `client.py` 中的服务器 IP 和端口，并在本地运行 `client.py` 

6. `client.py` 运行结束时，交集已经分别存储在服务器端和本地的 `answer.json` 中了



# 测试结果



1. `A_m.json`

```json
{
    "count":8,
    "maindata": [
        	"张三",
            "李四",
            "王五",
            "胡图图",
            "胡英俊",
            "张小丽",
            "赛文奥特曼",
            "牛爷爷"
    ]
}
```

2. `B_m.json`

```json
{
    "count":6,
    "maindata": [
        	"张五",
            "李四",
            "王三",
            "胡英俊",
            "张小丽",
            "牛爷爷"
    ]
}
```

3. 运行过程

![image-20220605224710620.png](https://s2.loli.net/2022/06/05/DvgdeRQN8CV1IGP.png)

4. `answer.json`（服务器上和本地一样）

```json
{
    "count": 4,
    "maindata": [
        "李四", 
        "胡英俊", 
        "张小丽", 
        "牛爷爷"
    ]
}
```

