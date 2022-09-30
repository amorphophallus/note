# C++ 使用技巧

## 将函数作为参数传入

[参考博客](https://blog.csdn.net/zj1131190425/article/details/88528948)

声明和实现：

```cpp
pid timer(int (*func)(int, int, int[N][N]), int n, int m, int mat[N][N], int k);

pid timer(int (*func)(int, int, int[N][N]), int n, int m, int mat[N][N], int k){
    for (int i = 0; i < k; ++ i)
        ret = func(n, m, mat);
}
```

调用：

```cpp
ret_N3 = timer(brute_force_N6, n, m, mat, k3);
```