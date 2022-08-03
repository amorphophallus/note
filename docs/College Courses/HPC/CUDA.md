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



## 分析性能



1. `nsys profile --stats=true -o multi-thread-vector-add ./multi-thread-vector-add`：`./可执行文件名`
2. 用 `Nsight System` 打开 `.qdrep` 文件，查看报告
3. 调参（执行配置）：记录核函数执行时间



## 性能优化



### 利用 SM / warp 优化



1. 线程块可以放到 SM 中运行，所以如果 `gridDim` 是 `SM` 数量的整数倍，性能会有所提升
2. SM 会把线程块内的线程分成 32 个一组，称为 `warp` ，所以如果 `blockDim` 是 32 的整数倍，性能会有所提升

3. 查询设备信息（[CUDA Runtime API :: CUDA Toolkit Documentation (nvidia.com)](https://docs.nvidia.com/cuda/cuda-runtime-api/structcudaDeviceProp.html)）

```cpp
// GPU 设备编号
int deviceId;
cudaGetDevice(&deviceId);

// cudaDeviceProp 内含有很多设备信息，可以在手册里查看
cudaDeviceProp props;
cudaGetDeviceProperties(&props, deviceId);

// 几个重要信息
int computeCapabilityMajor = props.major; // major compute capability
int computeCapabilityMinor = props.minor; // minor compute capability
int multiProcessorCount = props.multiProcessorCount; // SM 数量
cudaDeviceGetAttribute(&numberOfSMs, cudaDevAttrMultiProcessorCount, deviceId); // SM 数量的另一种求法
int warpSize = props.warpSize; // warp 大小
```



（数据>网格导致核函数内部有循环并不会降低运行效率，反而线程块数量太大会降低效率）



### 优化访存



#### preFetch 异步预取



1. `cudaMallocManaged` 的内存分配模式：

    - 统一内存（UM，unified memory）
    - 未驻留内存 -> 分页错误 -> 内存读写（`HtoD / DtoH`）

2. 优化方法：

    - 只在 GPU 或者 CPU 上操作数据

    - 在申请内存后操作前，或者在 CPU 操作后 GPU 操作前，或者在 GPU 操作后 COU 操作前，在以上三种场景使用预取，效率会高于遇到分页错误之后再进行内存读写

    - ```cpp
        cudaMemPrefetchAsync(pointerToSomeUMData, size, deviceId);
        cudaMemPrefetchAsync(pointerToSomeUMData, size, cudaCpuDeviceId);
        
        // examples
        float *c;
        cudaMallocManaged(&c, N * sizeof(float));
        cudaMemPrefetchAsync(c, N * sizeof(float), deviceId); // cudaGetDevice
        cudaMemPrefetchAsync(c, N * sizeof(float), cudaCpuDeviceId); // cudaCpuDeviceId 是环境变量
        ```

        

#### 利用 shared-memory



1. `stream`
2. `shared memory`
    - 交换数据？
    - `bank conflict`：一个数组，32 个数一个 **bank**
3. `register`
4. `global memory` 连续访问：同一个 **warp** 内访问的内存连续



### 利用 CUDA Streams 优化



```cpp
cudaStream_t stream;
cudaStreamCreate(&stream); // 指针
someKernel<<<number_of_blocks, threads_per_block, 0, stream>>>(); // 核函数的四个参数
cudaStreamDestroy(stream); // 值
```



（注意默认流会阻止其他流的进程）



### 利用 tensor core 优化



## 常见错误



1. 并行写入
    - 产生原因：在GPU中，线程在并行时，每个**线程（Thread）**都会有一组专供自己的用的寄存器。对同一个显存变量进行“读-计算-写”的操作时，虽然期望读到的数据是经过另一个线程操作的，但实际读的操作可能是同时进行的，没有先后。
    - 方法一：逻辑上避免
    - 方法二：原子操作（[CUDA 手册](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#arithmetic-functions)）
2. 优化方法论：最首要的任务是找到**性能瓶颈**
    - 有两层循环的，就不要先想着优化一层循环

