1. shape correspondence
2. curve-skeleton
3. although there is no rigorous definition on what a good correspondence is, it is rather easy to identify very poor correspondences.
    This motivated us to design a statistical method.
4. 剪枝不需要太精确（不需要精确的调参和阈值），允许好的匹配被剪掉，也允许坏的匹配不被剪掉。搜索算法的核心是设计剪枝策略。
5. 算法的目标是： find a 1-1 semantic correspondence in feature nodes
6. 概念：feature node
    - terminal nodes
    - junction nodes（在原图形中的）连接节点
7. 第一层：只考虑 junction feature pair （对本题来说并没有用）
8. pruning test
    1. T1: individual feature: 定义 centricity
    2. T2: pair feature：定义 geo 函数和 rad 函数，并和之前选择的每个配对进行计算
    3. T3: 3+ nodes feature：分别找到点集中最近的点，如果这两个点不匹配则剪枝
    4. T4: 3+ nodes feature：为了解决原图对称、旋转、姿势不同的问题
        - 首先进行 pose-normalization(least-square multidimensional scaling)：~~好像是把每个点变成一个数（1-dimensional）~~
        - 然后定义 Apq 为 non-translational transformation，是 {(p'k-3)-(p'k), ..., (p'k-1)-(p'k)} 到 {q...} 的线性变换
        - Rpq 是 rotational component，由 **polar decomposition** 得到（如果是 -1 则要乘上 -1）
        - RDpq = ||Apq - Rpq||f，f 是 **范数（Frobenius norm）**
        - 用同样的方法计算 RDqp，取 RDΩ = max(pq, qp)，剪枝掉 RDΩ > eRD 的部分
    - pose normalization before search
    - eC = 0.5, eRD = 1.0
    - 子树深度 > 4 才能作为 elector，因为 T4 需要至少 4 个节点才能剪枝