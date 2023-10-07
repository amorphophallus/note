# python 项目记录

[TOC]

## WebGLM

### 相关资源

1. [开源仓库](https://github.com/THUDM/WebGLM#prepare-serpapi-key)：包含环境配置和是使用教程

### 过程记录

1. 搜索语句：`how to treat scale problem in kiwifruits using inputs permitted by organic`
1. `AttributeError: module 'torch' has no attribute 'concat'`：错误原因是 pytorch 版本太低，把 concat 换成 cat 就能解决问题，~~或者买块好点的显卡~~
1. `index out of range`，提示修改 `modeling_webglm.py` 中第 49 行的函数参数 `max_length`，我把 1024 改成了 2048，但并没有解决问题

### 结论

可能得错误原因：
1. cpu 运行：
    - [pytorch index out of range](https://blog.csdn.net/qq_32743513/article/details/109959952)
    - [stack overflow 回答](https://stackoverflow.com/questions/62081155/pytorch-indexerror-index-out-of-range-in-self-how-to-solve)，看起来应该是代码本身的问题，在 embedding 层数据超出范围，可以尝试提一下 issue。不过纯 cpu 运行的问题已经有人在 [issue](https://github.com/THUDM/WebGLM/issues/46) 里提过了，感觉有显卡还是用显卡吧。
2. gpu 运行：
    - [cublas_status_not_supported](https://github.com/pytorch/pytorch/issues/94294)，看起来解决办法就是用更好的显卡，更新的 cuda，和配套更新的 pytorch。在我的本机上 2B 的 model 都放不到显卡上，后面估计不用想了。