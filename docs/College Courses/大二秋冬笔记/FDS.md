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

## 课程笔记

1. ch1：课程简介
2. ch2：复杂度分析
    - 大 O：上限
    - 大 Ω：下限
    - 大 θ：上限 + 下限
    - 小 o：无穷小量（大 O 的反向操作）
    - if/else：选较大的那个分支算复杂度
    - 主定理
2. ch3：栈和队列
    - 中缀表达式转后缀表达式：
        1. 如果是操作数, 则直接压进输出队列中
        2. 如果是运算符, 分以下情况:
            a. 运算符堆栈为空, 或者运算符栈顶元素为'(', 则直接将运算符压进栈
            b. 运算符如果是')', 则将运算符栈中的元素都压进去输出队列中并将其弹出运算符栈, 直到遇到'('为止
            c. 运算操作符是'+' '-' '*' '/' 之一的时候, 将其与运算符栈顶元素作比较,如果栈顶的优先级较小（ **如果运算符是左结合的则优先级相等也要出栈** ）, 则将运算符压入栈中。否则, 将栈顶元素弹出并压入输出队列中, 然后继续比较栈顶, 直到运算符被压入栈.
    - 中缀表达式转前缀表达式：
        1. 存两个堆栈, 一个存放操作数, 一个存放运算符
        2. 由于要转换为prefix, 运算符在操作数前, 所以扫描从中缀表达式 **从右往左** 扫描.
        3. 如果是操作数, 则直接压进操作数栈中
        4. 如果是运算符, 分以下情况:
            a. 运算符堆栈为空, 或者运算符栈顶元素为')', 则直接将运算符压进栈
            b. 运算符如果是'(', 则将运算符栈中的元素都压进去操作数栈中并将其弹出运算符栈, 直到遇到')'为止
            c. 运算操作符是'+' '-' '*' '/' 之一的时候, 将其与运算符栈顶元素作比较,如果栈顶的优先级较小,（ **如果运算符是右结合的则优先级相等也要出栈** ） 则将运算符压入栈中. 否则, 将栈顶元素弹出并压入操作数栈中, 然后继续比较栈顶, 直到运算符被压入栈。
        5. 扫描完一遍后, 将运算符堆栈剩余的元素都压入操作数栈中。
        6. 将操作数栈从栈顶到栈底输出就是prefix.
3. ch4：树
    - traversal:
        - preorder: 根左右
        - inorder: 左根右
        - postorder: 左右根
    - degree of tree: max degree of node
    - 任意树变成二叉树：倾斜 45 度，兄弟变儿子；i.e.左儿子是第一个儿子，右儿子是兄弟
    - threaded binary tree 线索二叉树：
        - 目的：n 节点二叉树有 n+1 个儿子指针是 NULL，利用这些指针来使遍历更加方便
        - 分类：前序 / 中序 / 后序
        - 构造：NULL 的左儿子换成（前序 / 中序 / 后序）遍历中的前驱节点，右儿子换成后继。
        - 遍历：不再需要回溯，只需要判断自身和左右儿子的顺序即可
4. ch5：二叉搜索树
    - BST: binary search tree
        - delete:
            - 1 degree: 儿子挪上来
            - 2 degree: 用 largest in the left subtree 或者 smallest in the right subtree 来替换当前节点
        - lazy tag: 标记删除但是不实际删除，用于删除操作不多的情况
    - ADT: abstract data type
    - decision tree:
        - internal node & external node(leaf)
    - 特殊的树
        - complete binary tree: 叶子节点深度差最大为 1
        - full binary tree
5. ch6：binary heap
    - property：
        - 每个节点都比儿子大（左右儿子之间没有限制）
        - 一定是 complete binary tree
        - 查找只能 $O(N)$
        - 编号从 $\lfloor \frac{N}{2}\rfloor +1$ 开始就都没有儿子
    - operation
        - 建堆：保证操作每个节点时，他的两个儿子子树都是堆，然后将这个节点往下推。有 $\frac{N}{2}$ 个节点需要往下推至少一次，$\frac{N}{4}$ 个节点往下至少两次，以此类推 $T(N)=\frac{N}{2}+\frac{N}{4}+...=O(N)$
        - push：在最大编号后面插入，依次往上交换
        - pop：左右儿子挑一个大（小）的提上来
    - d-heaps: 
        - 单次操作 $O(d \log_dN)$，d 为 3 时时间复杂度最低
        - 父亲：$father(i)$ 是一个阶梯函数，$father(1) = 0$，每过 d 个数函数值 +1，$father(i) = \lfloor (i+d-2)/d\rfloor$
        - 最大的儿子：把最大的儿子后面的节点全去掉，则树上除了叶子之外全都是满儿子，$$father(son_{max}(i)) = [son_{max}(i)-1]/d = i$$ 所以 $son_{max}(i)=id+1$
        - 最小的儿子： $son_{min}(i) = (i-1)d+2$
7. ch7: disjoint set ( 并查集 )
    - union-by-size: 小树合并做大树的儿子，查询 $O(\log_2 N)$，因为从任意节点每往上爬一层，子树大小至少翻一倍
        - array representation: 非根节点，数组中存父亲编号；根节点，数组中存数组大小的相反数
    - union-by-depth: 浅树合并做深树的儿子，查询 $O(\log_2 N)$，因为一棵深度为 n 的树需要 2 棵深度为 n-1 的树合并得到，所以深度为 n 的树大小至少为 $2^n$，树深度为 $O(\log_2 N)$ 级
    - path compression: 查询和合并的复杂度都是 $O(1)$】
        - 并查集的非递归写法：
            ```c
            SetType  Find ( ElementType  X, DisjointSet  S )
            {
                ElementType  root,  trail,  lead;
                for ( root = X; S[ root ] > 0; root = S[ root ] );
                for ( trail = X; trail != root; trail = lead ) {
                lead = S[ trail ] ;   
                S[ trail ] = root ;   
                }
                return  root ;
            }
            ```
    - relation 的性质：reflexive 自反性，symmetric, transit
8. ch8: graph
    - 定义：![Alt text](./img/ch9-1.png)![Alt text](./img/ch9-2.png)![Alt text](./img/ch9-3.png)
        - 单讲 connected 一般是无向图，有向图要分强联通和弱联通
        - 有向图的 adjacent 有 from 和 to 之分
    - 图的存储方式：adjacent multilist，就是同一条边存两个next，分别是对于出点的 next 和对于入点的 next，方便找入度
    - 拓扑排序相关定义：![Alt text](./img/ch9-4.png)
9. ch10: shortest path
    1. Floyd
        - $O(N^3)$
    2. Dijkstra
        - $O(V^2+E)$
        - 堆优化：$O((V+E)\log V)$，log 后面是 E 还是 V 并不关键因为 E 最多是 V 的平方。
        - 无法处理负边权
    3. Bellman-Ford & SPFA
        - 平均情况下 $O(kE)$, 其中 $k$ 是所有顶点进队的平均次数，一般满足 $k<2$。最坏情况退化为 Bellman-Ford 算法，复杂度 $O(VE)$
        - 用数组 dis 记录每个结点目前的最短路径值，用邻接表来存储图 G。设立一个队列用来保存待优化的结点，优化时每次取出队首结点 u，并且用 u 点当前的最短路径值对 u 点能到达的所有结点 v 进行松弛操作，如果 v 点的最短路径估计值有所调整，且 v 点不在当前的队列中，就将 v 点放入队尾。这样不断从队列中取出结点来进行松弛操作，直至队列空为止。
    4. AOE Activity on edge（有向无环图 DAG）
        - 拓扑排序 -> 最短路 & 最长路
        - critical path: 关键路径，即占据最长时间的路径
10. ch11: 其他图论算法
    1. 最小生成树 (minimum spanning tree)
        0. 性质：边权最小的边一定在最小生成树中（用于证明两个算法的正确性）
        1. Kruskal：
            - 做法：按边权从小到大排序 + 取边做并查集
            - 证明：用性质
        2. Prim：
            - 做法：以某个点为初始点集，每次选点集和外界连边中最小的边，把那个点加入点集
            - 证明：用性质
    2. 最大流 (max flow)
        1. 定义：有源有汇，其他点流入等于流出。 [定义参考博客](https://blog.csdn.net/mystery_guest/article/details/51910913)
        2. 定理：最大流 = 最小割
            1. 平面图网络流：
                - 把源汇连边，找 **对偶图** （面作为点，面之间相邻就连 2 条 **有向边**，正向保留边权，反向设为 0，走一条有向边表示把边左边的点放进 s 的集合中，右边的点放进 t 的集合中）
                - 求最短路（本质上来说对偶图中的环相当于一个割。为了保证源汇在不同的集合中，强制选取了源汇之间连的虚拟边）
        3. 常见增广路算法：
            1. 核心思路： **引入反向边**
                - 反向边小技巧：正向边存在数组的偶数位，反向边存在奇数位，则取反向边只需要 `i^1`
            2. Ford-Fulkerson：找到增广路径就更新
            3. Edmonds-Karp (EK 算法) ：BFS 找边数最少的增广路径更新，$O(NM^2)$
            4. Dinic：在 EK 的基础上，分层 (BFS) + 多路增广(DFS)，复杂度 $O(N^2M)$
                - 当前弧优化：已经增广过的边不再增广，引用写法 `for (int &i = cur[u]; i; i = g.nxt[i])`
11. DFS 的应用：
    1. 欧拉路径（回路）和哈密尔顿路径
        - 欧拉回路 dfs： $O(V+E)$
    2. 无向图的双连通分量(biconnectivity)
        1. 定义：
            - articulation point: 关节点，去掉这个点图变得不连通
            - biconnected graph: 不存在关节点
            - biconnected component: maximal biconnected subgraph
        2. tarjan 算法：
            1. 生成一颗 dfs 树，遍历顺序记为 `dfn[v]`
            2. 除了树边之外仅可能存在一种边：连接 u 和 u 子树中的节点 v 的边。记 `low[v]` 为从 **v 和 v 子树中的节点** 出发走 **1 条** 非树边能够到达的最小 dfn，更准确地说，
            
            $$
            low[u]=\min
            \left\{
            \begin{align*}
            &dfn[u]&\\
            &low[v]&,v\textsf{ is a son of }u\\
            &dfn[w]&,(u,w)\textsf{is a back edge}
            \end{align*}
            \right\}
            $$
            
            当 u 的某个儿子 v `low[v]>=dfn[u]` 时 u 是关节点。
            3. 想要记录每个双联通分量中的点有哪些：将遍历到的点都入栈，在找到关节点的时候不断出栈直到关节点出栈，然后再把关节点入栈。（因为每个关节点可能会被包含在多个点双中）
            4. 注意：对于图的所有不连通的分量都要搜索，注意特判孤立节点的情况
    3. 有向图的强联通分量：
        1. 生成一颗 dfs 树，遍历顺序记为 `dfn[v]`
        2. 除了树边之外可能存在 3 种边：
            1. 前向边：可以忽略
            2. 后向边：可以形成强连通
            3. 横插边：从 dfn 大的子树插到 dfn 小 的子树
        3. `low[u]` 表示从 u 出发可以到达的最小的 dfn，其中 w 必须是还未确定在哪个强连通分量的点（即需要在栈中，用 `inq[w]` 来判断）

        $$
        low[u]=\min
            \left\{
            \begin{align*}
            &dfn[u]&\\
            &low[v]&,v\textsf{ is a son of }u\\
            &low[w]&,(u\to w)\textsf{ is a non-tree-edge and w}\in \textsf{undetermined component}
            \end{align*}
            \right\}
        $$

        4. 当节点 u 满足 `low[u]==dfn[u]` 时说明 u 和他的父亲属于不同的强连通分量，弹栈直到弹出 u
12. 排序：
    1. 插入排序：
        - 插入排序（以及任何交换相邻元素的排序）的交换次数 = 逆序对个数(inversion count)
        - 最大比较和交换次数 $\frac{n(n-1)}{2}$，最小比较和交换次数 $n-1, 0$
        - stable sort
    2. 希尔排序：
        - 取步长，进行分组插入排序，并逐步缩小步长，直到步长为 1，变为插入排序。
        - 步长可以取 `floor(n/2)`，每次除 2。
        - 平均复杂度取决于步长的选取，在随机条件下效果较好，$O(N^{\frac{3}{2}})$ 或者 $O(N^{\frac{5}{4}})$
        - unstable sort
    3. 定义：
        - stable sort: 大小相同的元素不会交换位置
        - unstable sort：会交换位置
    4. 堆排序：
        - $O(N)$ 建堆，每次把堆顶的元素和最后一个元素交换，$O(logN)$ 更新堆。理论总复杂度不到 $O(NlogN)$，但实际效果并不好。


## 错题整理

1. 

期中考

If a stack is used to convert the infix expression a+b*c+(d*e+f)*g into a postfix expression, what will be in the stack (listing from the bottom up) when f is read?

Ans：`+(+`