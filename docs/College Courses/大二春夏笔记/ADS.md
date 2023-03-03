# 高级数据结构

[TOC]

## intro

1. 评分标准
    - Homework（作业） 10%
    - Discussion（讨论） 10%  
    - Research Project（大程） 30%
    - Mid Exam（期中）10%
    - Final Exam（期末） 40%
    - 期中的 10 分 = max(期中考卷面分, 期末考卷面分)
    - 平时分不能超过 60 分
2. project
    - Done in groups of 3
    - choose 2 out of 8 topics
    - Reports (14 points and 10 points, respectively)
    - In-class presentation (10~15 minutes, 6 points)
    - If there are many volunteers, at most 3 groups will be chosen to give presentations
    - For those groups not to give presentations, each will gain bonus points = report points / 10
3. Lab report
    - 模块：可以用 FDS 的模板，开头加一块 summary
    - 内容：图表(e.g. table of running time)需要注记和解读，伪代码需要自然语言解释
    - 报告：重点在于 project 中的发现，激情！

## AVL & Splay & Amortized Analysis

1. AVL tree
    - 性质：递归地定义
    - 高度：O(logn)，用斐波那契数列证明（令深度为 h 的 AVL）
    - 每个节点记录：子树深度，balance value(左子树深度 - 右子树深度)
    - insertion & rebalance
        - zig-zig: single-rotation，两个点旋转
        - zig-zag: double-rotation，三个点旋转
        - 证明：最多需要旋转一次。因为对 u 旋转之后 u 的深度和插入之前一样，再往上不需要修改子树深度和 balance value。
    - deletion：也是旋转
        - 证明：最多需要旋转 O(logn) 次。即构造一个路径上每个节点都需要旋转的例子。 **快来把这个写了**
2. Splay tree
    - 操作：把插入、查找的节点(x)都旋转到根
        - x 的父亲是根：single-rotation
        - x 有父亲(p)和祖父(g)
            - zig-zig：2 * single-rotation（先对 p 和 g 做单旋，再对 x 和 p 做单旋）
            - zig-zag：double-rotation
    - 复杂度证明
3. Amortized Analysis(均摊分析)
    - aggregate analysis(聚类分析)
        - multi-pop：一个栈，三个操作 push, pop, multi-pop（弹出 k 个元素）。multi-pop 的复杂度为 O(1)。
    - accounting method(记账方法)
    - potential method(势能分析)