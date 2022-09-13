# Pytorch LeNet

> 参考资料：
    1. [总教程](https://blog.csdn.net/Serins/article/details/121477739)
    2. 

## 数据准备


0. MNIST 数据格式：
    - 每张图像单通道， 28 * 28 像素
1. 准备数据集： `torchvision.datasets.MNIST`，[参数](https://pytorch.org/vision/0.8/datasets.html#mnist)
    - root: 在 MNIST中是 processed/training.pt 和 processed/test.pt 的主目录
    - train: True 代表训练集，False 代表测试集
    - transform 和 target_transform: 分别是对图像和 label 的转换操作
    - download: 若为 True 则下载数据集并放到 root 所指定的目录中，否则直接尝试从 root 目录中读取
2. 加载数据集： `DataLoader`，[参数](https://pytorch.org/docs/stable/data.html?highlight=dataloader#torch.utils.data.DataLoader)
    1. epoch：所有的训练样本输入到模型中称为一个epoch； 
    2. iteration：一批样本输入到模型中，成为一个Iteration;
    3. batchszie：批大小，决定一个epoch有多少个Iteration；
    4. 迭代次数（iteration）=样本总数（epoch）/批尺寸（batchszie）
    5. dataset (Dataset) – 决定数据从哪读取或者从何读取；
    6. batch_size (python:int, optional) – 批尺寸(每次训练样本个数,默认为１）
    7. shuffle (bool, optional) –每一个 epoch是否为乱序 (default: False)；
    8. num_workers (python:int, optional) – 是否多进程读取数据（默认为0，只用主进程);
    9. drop_last (bool, optional) – 当样本数不能被batchsize整除时，最后一批数据是否舍弃（default: False)
    10. pin_memory（bool, optional) - 如果为True会将数据放置到GPU上去（默认为false）
3. 图像增强： `transform`
    - Normalize() 函数的作用是将数据转换为标准正太分布，使模型更容易收敛，[Normalize 参数的计算方法](https://blog.csdn.net/peacefairy/article/details/108020179)


## 网络编写

### 定义网络
