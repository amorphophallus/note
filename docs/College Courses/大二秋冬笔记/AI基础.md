# AI 基础

## 工具介绍

### 智海 Mo 平台

1. [Mo 平台](mo.zju.edu.cn)
2. Jupyter Notebook
    - 作业主文档：`main.ipynb` 
    - 提交作业：选择代码块组成 `main.py` 并进行用例测试，提交 **只有一次机会**
    - 资源：2核4G cpu + 4G内存，TF 2.x / torch 1.4.0（ **注意兼容问题** ）
    - 使用 GPU： 新建 `xxx.py`，header 选择新建任务，选择 GPU 机器， **注意结果存放在 `/result` 文件夹下**

### 人工智能框架：PaddlePaddle & MindSpore

1. 人工智能 > 机器学习 > 深度学习
2. 机器学习的本质：参数估计
    - 模型假设
    - 评价函数
    - 优化算法
3. PaddlePaddle：百度，2016开源（多端多平台分布式部署？）
4. MindSpore：华为（全栈全场景？）

## 作业讲解

### 斑马问题 - python 逻辑编程

逻辑编程库： kanren