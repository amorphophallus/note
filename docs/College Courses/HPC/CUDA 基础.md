# CUDA C/C++

[TOC]

## 基础知识



### hardware



1. SISD
2. SIMD（体系结构类别）
3. SIMT：可实现分支结构，SIMD 不行
4. SM：streaming mutiprocessor 流多处理器



### software



1. thread（thread per block 上限 1024，32 的倍数最理想）
2. thread block
3. grid
4. kernel：核函数
5. warp：32 个 thread





## 运行 CUDA C 程序



[Programming Guide :: CUDA Toolkit Documentation (nvidia.com)](https://docs.nvidia.com/cuda/cuda-c-programming-guide/)



1. 保存为 `.cu` 文件
2. `__global__ void`：可全局调用函数
3. `GPUfunc<<<n, m>>>(args)`：调用函数的执行配置，n thread block, m thread per thread block，`args` 中传参
4. `cudaDeviceSynchronize`：让 CPU 程序等待 GPU 程序运行完毕后退出
5. `nvcc -o multi-thread-vector-add 01-vector-add/01-vector-add.cu -run`：命令行编译+运行



（GPU 和 CPU 代码的运行是异步(async)的）

**注意嵌套的并行一般是不被允许的**



## 参数



1. `gridDim.x`：一个网格有多少个块
2. `blockDim.x`：一个块有多少个线程
3. `blockIdx.x`：块下标(index from 0)
4. `threadIdx.x`：线程下标(index from 0)



（线程之间、块之间不保证运行顺序）



## 分配内存



1. `cudaMallocManaged(&a, size)`：`&a` 是**指针的地址**，在 `a` 所指的位置分配 `size` 的内存。（CPU 和 GPU 均可访问）
    - 在 CPU 和 GPU 上都分配地址
    - `firstTouch` 机制：反复在 CPU 和 GPU 上修改数据，会需要反复在 CPU 和 GPU 之间交换数据
    - `cudaMemPrefetchAsync`：
2. `cudaMalloc(&a, size)`：（只能被 GPU 访问）
3. `cudaFree(a)`：释放 `a` 所指位置的内存。
4. `cudaMallocHost(&a, size); cudaFreeHost(a);` 分配在 CPU 的内存，但允许与 GPU 之间异步拷贝
    - `cudaMemcpy(目标, 源, size, 参数);`：参数是 `cudaMemcpyHostToDevice / cudaMemcpyDeviceToHost`
    - `cudaMemcpyAsync`：可加入第五个参数，使 `memcpy` 运行在非默认流上





## 数据大小和 grid 大小不匹配



1. 数据 < 网格：（判断）优先满足 `threads_per_block` 是 32 的倍数
2. 网格 < 数据：（循环）



## 错误检查



```cpp
inline cudaError_t checkCuda(cudaError_t result)
{
  if (result != cudaSuccess) {
    fprintf(stderr, "CUDA Runtime Error: %s\n", cudaGetErrorString(result));
    // assert(result == cudaSuccess);
  }
  return result;
}

int main()
{
  checkCuda( cudaGetLastError() ); // syncError
  checkCuda( cudaDeviceSynchronize() ); // asyncError
}
/*
cudaError_t
cudaGetLastError()
cudaGetErrorString()
*/
```

### CUDA-GDB




## 分析性能



1. `nsys profile --stats=true -o multi-thread-vector-add ./multi-thread-vector-add`：`./可执行文件名`
2. 用 `Nsight System` 打开 `.qdrep` 文件，查看报告
3. 调参（执行配置）：记录核函数执行时间



## 常见错误

### 原子操作

1. 并行写入
    - 产生原因：在GPU中，线程在并行时，每个**线程（Thread）**都会有一组专供自己的用的寄存器。对同一个显存变量进行“读-计算-写”的操作时，虽然期望读到的数据是经过另一个线程操作的，但实际读的操作可能是同时进行的，没有先后。
    - 方法一：逻辑上避免
    - 方法二：原子操作（[CUDA 手册](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#arithmetic-functions)）


### Segmentation Fault

可能是因为内存只能被 cpu 或者 gpu 访问，可以改用 `cudaMallocManaged`

### invalid configuration argument

报错： `CUDA Runtime Error: invalid configuration argument`

一般是因为 grid 或者 block 过大

### 优化方法论


优化方法论：最首要的任务是找到 **性能瓶颈**
    - 有两层循环的，就不要先想着优化一层循环

