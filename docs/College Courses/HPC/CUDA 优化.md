# CUDA 优化


## 利用 SM / warp 优化



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



## 优化访存



### preFetch 异步预取



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

        

### 利用 shared-memory




### 减少 bank conflict

32 个内存一个 bank

=== "先 block 后 thread"

    ```cpp
    for (int n = blockIdx.x; n < batch_size; n += grid_size)
        for (int x = blockIdx.y; x < size; x += grid_size)
            for (int y = threadIdx.x; y < size; y += block_size)
                for (int co = threadIdx.y; co < out_channel; co += block_size)
                    access a[n][x][y][co];
    ```
=== "打乱顺序"

    ```cpp

    for (int n = blockIdx.x; n < batch_size; n += grid_size)
        for (int x = threadIdx.y; x < size; x += block_size)
            for (int y = threadIdx.x; y < size; y += block_size)
                for (int co = blockIdx.y; co < out_channel; co += grid_size)
                    access a[n][x][y][co];
    ```

### 利用 register

### 利用访存的局部性

时间上的局部性，空间上的局部性

`global memory` 连续访问：同一个 **warp** 内访问的内存连续


### 利用 CUDA Streams 优化



```cpp
cudaStream_t stream;
cudaStreamCreate(&stream); // 指针
someKernel<<<number_of_blocks, threads_per_block, 0, stream>>>(); // 核函数的四个参数
cudaStreamDestroy(stream); // 值
```



（注意默认流会阻止其他流的进程）



## 利用 tensor core 优化

