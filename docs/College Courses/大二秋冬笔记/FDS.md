# 数据结构基础

## Project Report 要求

0. 删除个人信息
1. 封面
    - 标题 + 日期 (-1)
2. Chapter 1 Introduction
    - 自己描述题目，不能照搬照抄 (-3)
3. Chapter 2 Algorithm Specification
    - 伪代码 + 自然语言描述
    - 不要直接贴项目代码
4. Chapter 3 Testing Result
    - 每一组测试样例都要写 purpose (-3)
    - 至少一组综合测试样例 (comprehensive test case)，数据规模的上下边界各一组，极限情况 (extreme case) 必须测试到，再加 n 组随机数据 (-4)
    - *搞点图来展示运行时间*
5. Chapter 4 Analysis and Comments
    - 分析复杂度需要写过程 (-4)
        - 例如循环要这么写：*The loop runs for N times and the complexity of each loop body is O(1), so the total time complexity is O(N).*
    - 时间和空间都要写到
6. 代码
    - 一定要多写注释，至少写到代码总长度的 30% 以上 (-50)
7. README
    - 怎么编译？怎么运行？怎么输入？期望的输出？

## 绪论

1. ch1：课程简介
2. ch2：复杂度分析
    - 大 O：上限
    - 大 Ω：下限
    - 大 θ：上限 + 下限
    - 小 o：无穷小量（大 O 的反向操作）
    - if/else：选较大的那个分支算复杂度
    - 主定理