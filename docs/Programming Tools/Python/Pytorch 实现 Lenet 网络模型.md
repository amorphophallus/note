# Pytorch LeNet-5

> 参考资料：
    1. [总教程](https://blog.csdn.net/Serins/article/details/121477739)
    2. [知乎专栏一：神经网络结构入门](https://zhuanlan.zhihu.com/p/65472471)
    3. [知乎专栏二：反向传播入门](https://zhuanlan.zhihu.com/p/66534632)
    4. [知乎专栏三：numpy 手写 2 曾神经网络](https://zhuanlan.zhihu.com/p/67682601)
    5. [softmax 函数反向传播的计算](https://zhuanlan.zhihu.com/p/37740860)
    6. [全连接层的作用](https://blog.csdn.net/weixin_45829462/article/details/106548749)
    7. [全连接层的正向传播和反向传播](https://blog.csdn.net/l691899397/article/details/52267166)
    8. [官方教程：60分钟快速入门 pytorch](https://zhuanlan.zhihu.com/p/66543791)
    9. [nn.module 官方文档](https://pytorch.org/docs/stable/generated/torch.nn.Module.html)
    10. [torch.Tensor 官方文档]()

## 数据准备


0. MNIST 数据格式：
    - 输出 DataLoader 查看数据集尺寸
        ```python
        for data in train_loader:
            imgs, targets = data
            print(imgs.shape)
            print(targets)
        ```
    - `img.shape=torch.Size([512, 1, 28, 28])`，表示每张图像是单通道， 28 * 28 像素，512 张图像为一个批(batch)
    - [dataloader 参考](https://blog.csdn.net/weixin_43981621/article/details/119685671)
1. 准备数据集： `torchvision.datasets.MNIST`，[参数](https://pytorch.org/vision/0.8/datasets.html#mnist)
    - root: 在 MNIST中是 processed/training.pt 和 processed/test.pt 的主目录
    - train: True 代表训练集，False 代表测试集
    - transform 和 target_transform: 分别是对图像和 label 的转换操作
    - download: 若为 True 则下载数据集并放到 root 所指定的目录中，否则直接尝试从 root 目录中读取
2. 加载数据集： `DataLoader`，[参数](https://pytorch.org/docs/stable/data.html?highlight=dataloader#torch.utils.data.DataLoader)
    1. epoch：训练次数
    2. iteration：一次训练中的迭代次数
    3. batchszie：批大小，一次取多少数据进行学习
    4. 迭代次数（iteration）=样本总数 / 批尺寸（batchszie）
    5. dataset (Dataset) – 决定数据从哪读取或者从何读取；
    6. batch_size (python:int, optional) – 批尺寸(每次训练样本个数,默认为１）
    7. shuffle (bool, optional) –每一个 epoch是否为乱序 (default: False)；
    8. num_workers (python:int, optional) – 是否多进程读取数据（默认为0，只用主进程);
    9. drop_last (bool, optional) – 当样本数不能被batchsize整除时，最后一批数据是否舍弃（default: False)
    10. pin_memory（bool, optional) - 如果为True会将数据放置到GPU上去（默认为false）
3. 图像增强： `transform`
    - Normalize() 函数的作用是将数据转换为标准正太分布，使模型更容易收敛，[Normalize 参数的计算方法](https://blog.csdn.net/peacefairy/article/details/108020179)


## 网络编写

### 基础知识 - 网络结构

![](img/%E5%8F%8C%E5%B1%82%E7%A5%9E%E7%BB%8F%E7%BD%91%E7%BB%9C%E7%BB%93%E6%9E%84.jpg)

1. 卷积层：矩阵乘加运算
    - 应用中的结果：输出层中值最大的就是神经网络判断的分类
    - $y = Wx+b$，W 代表 weight，权重参数，b 代表 bias，偏置参数
2. 激活层：非线性函数，使多层神经网络有意义
    - 阶跃函数 / sigmoid / ReLU（0或自身）
3. Softmax：输出转化为概率的形式，$S_i=\frac{e^{a_i}}{\sum_j e^{a_j}}$
4. Cross Entropy Loss（交叉熵损失）：衡量输出的好坏，$L=-logS_{ans}$
    - 正确答案的概率越接近 1，交叉熵损失就越接近 0
5. 池化层(pooling)：减小计算量，过滤噪声和畸变
    - 取最大值、平均值
6. 全连接层：把张量拍平成一维向量，然后做向量的矩阵乘法 `y(1*out_size) = x(1*in_size) * W(in_size*out_size)`
    - [全连接层的作用](https://blog.csdn.net/weixin_45829462/article/details/106548749)
    - [全连接层的正向传播和反向传播](https://blog.csdn.net/l691899397/article/details/52267166)

### 基础知识 - 反向传播

[softmax 函数反向传播的计算看这篇](https://zhuanlan.zhihu.com/p/37740860)

![](img/Softmax-with-loss%E5%8F%8D%E5%90%91%E4%BC%A0%E6%92%AD.jpg)

1. 反向传播的含义：如果交叉熵损失有 $dL$ 的变化，求出每个节点的变化是多少倍的 $dL$，本质上是求导（链式求导法则）
2. 常用节点的导数：
    1. 加法节点：
    2. 乘法节点：
    3. Cross Entropy Loss 节点：（其中 $t_i$ 为 1 表示这个分类是正确答案，0 则不是）
        $$\frac{\partial L}{\partial y_i} = -\frac{t_i}{y_i}$$
    4. SoftMax 节点：
        $$\frac{\partial y_i}{\partial x_j} = \begin{cases} y_i-y_i^2  &,i=j \\ 0-y_iy_j &, i\not= j\end{cases}$$
    5. SoftMax-with-Loss：即 3 和 4 的复合函数，用链式求导法则，（且 $\sum_j t_j=1$）
        $$\frac{\partial L}{\partial x_i} = \sum_j \frac{\partial L}{\partial y_j} \frac{\partial y_j}{\partial x_i} = y_i-t_i$$
3. 参数更新方法
    1. 正则化惩罚项：防止 $dW$ 修改的过于集中
        $$dW=dW+reg*W$$
    2. 学习度：防止步子太大，记作 $\epsilon$ `epsilpon`

[练习：手写一个二层神经网络](https://zhuanlan.zhihu.com/p/67682601)

### 基础知识 - 正向传播

1. 卷积层
    - [nn.Conv2d()](https://blog.csdn.net/qq_42079689/article/details/102642610)
    - 输入：4 维张量 BCHW
    - 参数：in_channels, out_channels, kernel_size
    - 举例：输入 1 * 28 * 28 (CHW)，核 6 * 5 * 5，输出 6 * 24 * 24
2. 激活层：`F.relu()`
3. 池化层：`F.max_pool2d()`
4. 全连接层
    - [nn.Linear()](https://www.cnblogs.com/douzujun/p/13366939.html)
    - 输入：2 维向量 [batch_size, size]
    - 参数：in_features, out_features
5. softmax-with-loss
    - [F.log_softmax()](https://pytorch.org/docs/stable/generated/torch.nn.functional.log_softmax.html)
    - 参数：input, dim

### 定义网络

![](img/lenet-5%E7%BB%93%E6%9E%84.png)

1. 卷积层：`(1 @ 28 * 28) * (6 @ 5 * 5) = (6 @ 24 * 24)`
    - 激活层：relu
2. 池化层：2*2 矩阵取最大值，`(6 @ 24 * 24) -> (6 @ 12 * 12)`
3. 卷积层：`(6 @ 12 * 12) * (16 @ 5 * 5) = (16 @ 8 * 8)`
    - 激活层：relu
4. 池化层：2*2 矩阵取最大值，`(16 @ 8 * 8) -> (16 @ 4 * 4)`
    - 拍平：`(16 @ 4 * 4) -> (256)`
5. 全连接：`(256) -> (120)`
    - 激活层：relu
6. 全连接：`(120) -> (84)`
    - 激活层：relu
7. 全连接（输出层）：`(84) -> (10)`
8. softmax-with-loss：输出 `(batch_size * 10)`，小于 0，数值越大概率越高

### 训练和测试

流程在上面都学过了，主要是代码

```python
# 实例化网络和优化器
model = Net()
optimizer = optim.Adam(model.parameters())
writer = SummaryWriter('./log/train')

for epoch in range(0, EPOCH):
    # 进入训练模式
    model.train()
    min_loss = 1
    for batch_idx, (data, target) in enumerate(train_loader):
        data, target = data.to(DEVICE), target.to(DEVICE)
        # 正向传播
        output = model(data)
        # 计算损失函数
        loss = F.nll_loss(output, target)
        min_loss = min(min_loss, loss.item())
        # 反向传播
        optimizer.zero_grad() # 清空梯度缓存
        loss.backward() # 反向传播
        optimizer.step() # 更新权重
        # 输出训练进度，总共 118 个 batch
        if (batch_idx+1)%30 == 0 or batch_idx == 117:
            print('Train Epoch: {} [{}/{} ({:.0f}%)]\tLoss: {:.6f}'.format(
                epoch, batch_idx * len(data), len(train_loader.dataset),
                100. * batch_idx / len(train_loader), loss.item()))

    # 进入测试模式
    model.eval()
    test_loss = 0
    correct = 0
    with torch.no_grad():
        for data, target in test_loader:
            data, target = data.to(DEVICE), target.to(DEVICE)
            # 正向传播
            output = model(data)
            # 计算损失和正确率
            test_loss += F.nll_loss(output, target, reduction='sum').item() # 将一批的损失相加
            pred = output.max(1, keepdim=True)[1] # 找到概率最大的下标
            correct += pred.eq(target.view_as(pred)).sum().item() # 检查是否判断正确
    test_loss /= len(test_loader.dataset)
    print('\nTest set: Average loss: {:.4f}, Accuracy: {}/{} ({:.0f}%)\n'.format(
        test_loss, correct, len(test_loader.dataset),
        100. * correct / len(test_loader.dataset)))
    # loss 存入 tensorboard
    writer.add_scalar('loss', test_loss, epoch)
    # 正确率存入 tensorboard
    writer.add_scalar('accuracy', 100. * correct / len(test_loader.dataset), epoch)
```

### 保存训练模型

[参考](https://blog.csdn.net/comli_cn/article/details/107516740)

```python
# 保存
torch.save(model.state_dict(), './LeNet-5.pt')
# 读取
new_model = LeNet()
new_model.load_state_dict(torch.load('./LeNet-5.pt'))
```

## TensorBoard 可视化

### 基本使用

[基本使用](https://zhuanlan.zhihu.com/p/103630393)

1. 安装 `conda install tensorboard`
2. 使用 
    ```python
    from torch.utils.tensorboard import SummaryWriter   
    writer = SummaryWriter('./path/to/log')
    writer.add_scalar(tag, y axis, x axis)
    add_image(self, tag, img_tensor, global_step=None, walltime=None, dataformats=‘CHW’)

    ```
    - 变量归类 `loss/loss1`
    - log 文件夹可以再建子文件夹避免冲突
3. 可视化: `tensorboard --logdir=./path/to/the/folder --port xxxx`

> add_image(self, tag, img_tensor, global_step=None, walltime=None, dataformats=‘CHW’):绘制图片，可用于检查模型的输入，监测 feature map 的变化，或是观察 weight。
tag：就是保存图的名称
img_tensor:图片的类型要是torch.Tensor, numpy.array, or string这三种
global_step：第几张图片
dataformats=‘CHW’，默认CHW，tensor是CHW，numpy是HWC

### 例子：可视化 LeNet-5 的中间层

1. `print('1st mat: {}'.format(x.type))` 发现 x 的类型是 `torch.FloatTensor`
2. `print('1st mat: {}'.format(x.shape))` 发现 x 的形状是 `torch.Size([1, 6, 24, 24])`
3. 查阅 [torch.tensor 官方文档](https://pytorch.org/docs/stable/tensors.html)，发现有一些可用的方法，或者参考 [中文文档](http://www.codebaoku.com/it-python/it-python-262352.html#:~:text=Tensor%20%E5%8F%AF%E4%BB%A5%E4%BD%BF%E7%94%A8%20torch.tensor%20%28%29%20%E8%BD%AC%E6%8D%A2%20Python%20%E7%9A%84%20list,requires_grad%20%E5%B1%9E%E6%80%A7%EF%BC%8C%E5%8F%AF%E7%94%A8%20requires_grad_%20%28%29%20%E6%88%96%E8%80%85%20detach%20%28%29%20%E6%9D%A5%E9%81%BF%E5%85%8D%E6%8B%B7%E8%B4%9D%E3%80%82)
    ```python
    def add_img_set(fea, tag):
        for i in range(fea.shape[1]):
            writer.add_image(tag + f'/{i}', fea[0][i].detach().cpu().unsqueeze(dim=0), 0)
    ```
