# Content Tabs

## 参考

[官方文档](https://squidfunk.github.io/mkdocs-material/reference/content-tabs/)

## 基本语法

注意 tab 里的内容一定艺要有缩进

```cpp
=== "c++"

    ```cpp
    for (int n = blockIdx.x; n < batch_size; n += grid_size)
        for (int x = blockIdx.y; x < size; x += grid_size)
            for (int y = threadIdx.x; y < size; y += block_size)
                for (int co = threadIdx.y; co < out_channel; co += block_size)
                    access a[n][x][y][co];
    ```
=== "markdown"

    A *sample* **Markdown** text.


```

=== "c++"

    ```cpp
    for (int n = blockIdx.x; n < batch_size; n += grid_size)
        for (int x = blockIdx.y; x < size; x += grid_size)
            for (int y = threadIdx.x; y < size; y += block_size)
                for (int co = threadIdx.y; co < out_channel; co += block_size)
                    access a[n][x][y][co];
    ```
=== "markdown"

    A *sample* **Markdown** text.