# 数据库系统概念

[TOC]

## reference

1. [mysql 官方中文文档](https://docs.gitcode.net/mysql/guide/)
1. [W3School](https://www.w3schools.cn/mysql/default.html)
1. [教材官网](https://www.db-book.com/)
1. [随机生成数据库数据教程](https://cloud.tencent.com/developer/article/1373196#:~:text=MySQL%20%E4%BB%8E%E9%9B%B6%E5%BC%80%E5%A7%8B%EF%BC%9A08%20%E7%95%AA%E5%A4%96%EF%BC%9A%E9%9A%8F%E6%9C%BA%E7%94%9F%E6%88%90%E6%95%B0%E6%8D%AE%E5%BA%93%E6%95%B0%E6%8D%AE%201,1%E3%80%81%E7%BD%91%E9%A1%B5%E7%89%88%EF%BC%9AGeneratedata%202%202%E3%80%81%E5%AE%A2%E6%88%B7%E7%AB%AF%EF%BC%9Aspawner%203%203.%E4%BB%A3%E7%A0%81%E7%94%9F%E6%88%90%EF%BC%9Apydbgen)
    - [随机数据网站](https://generatedata.com/generator)

## intro

1. 评分标准
    - Exercise（作业） 10%
    - Quiz（测试+讨论） 10%  
    - Lab & Project （实验和大程） 30%   
    - Exam （考试） 50% 
2. 参考
    - ch1 Introduction：纸质书
    - ch2 Relational Model：纸质书
    - ch3 Introduction to SQL：ppt + 笔记


## Course Note

### ch3 Introduction to SQL

1. DDL
    - **Domain Types**: 5 - 6
    - create table: 7 - 10
        - forein key 的完整性条件维护方法：10 [添加外键约束](https://blog.csdn.net/lvtula/article/details/81940429) [查看、删除外键约束](https://www.php.cn/mysql-tutorials-493494.html#:~:text=%E5%9C%A8mysql%E4%B8%AD%EF%BC%8C%E5%8F%AF%E4%BB%A5%E5%88%A9%E7%94%A8ALTER%20TABLE%E8%AF%AD%E5%8F%A5%E9%85%8D%E5%90%88DROP%E5%85%B3%E9%94%AE%E5%AD%97%E6%9D%A5%E5%88%A0%E9%99%A4%E5%A4%96%E9%94%AE%E5%85%B3%E7%B3%BB%EF%BC%88%E7%BA%A6%E6%9D%9F%EF%BC%89%EF%BC%8C%E8%AF%AD%E6%B3%95%E2%80%9CALTER%20TABLE%20%E6%95%B0%E6%8D%AE%E8%A1%A8%E5%90%8D%20DROP,FOREIGN%20KEY%20%E5%A4%96%E9%94%AE%E7%BA%A6%E6%9D%9F%E5%90%8D%3B%E2%80%9D%EF%BC%9B%E2%80%9CALTER%20TABLE%E2%80%9D%E8%AF%AD%E5%8F%A5%E7%94%A8%E4%BA%8E%E4%BF%AE%E6%94%B9%E8%A1%A8%EF%BC%88%E6%94%B9%E5%8F%98%E5%8E%9F%E6%9C%89%E8%A1%A8%E7%9A%84%E7%BB%93%E6%9E%84%EF%BC%89%EF%BC%8C%E8%80%8C%E6%B7%BB%E5%8A%A0%E4%BA%86%E2%80%9CDROP%20FOREIGN%20KEY%E2%80%9D%E8%AF%AD%E5%8F%A5%E5%90%8E%EF%BC%8C%E4%BF%AE%E6%94%B9%E5%8A%9F%E8%83%BD%E5%B0%B1%E9%99%90%E5%88%B6%E5%9C%A8%E5%88%A0%E9%99%A4%E5%A4%96%E9%94%AE%E5%85%B3%E7%B3%BB%EF%BC%88%E7%BA%A6%E6%9D%9F%EF%BC%89%E4%B8%8A%E3%80%82)
    - drop & alter table: 11 [修改表结构](https://www.yisu.com/zixun/620726.html#:~:text=mysql%E4%BF%AE%E6%94%B9%E8%A1%A8%E7%BB%93%E6%9E%84%E7%9A%84%E8%AF%AD%E5%8F%A5%E6%98%AF%E2%80%9CALTER%20TABLE%E2%80%9D%EF%BC%8C%E8%AF%A5%E8%AF%AD%E5%8F%A5%E5%8F%AF%E4%BB%A5%E6%94%B9%E5%8F%98%E5%8E%9F%E6%9C%89%E8%A1%A8%E7%9A%84%E7%BB%93%E6%9E%84%EF%BC%8C%E4%BE%8B%E5%A6%82%E5%A2%9E%E5%8A%A0%E6%88%96%E5%88%A0%E5%87%8F%E5%88%97%E3%80%81%E6%9B%B4%E6%94%B9%E5%8E%9F%E6%9C%89%E5%88%97%E7%B1%BB%E5%9E%8B%E3%80%81%E9%87%8D%E6%96%B0%E5%91%BD%E5%90%8D%E5%88%97%E6%88%96%E8%A1%A8%E7%AD%89%EF%BC%9B%E8%AF%AD%E6%B3%95%E6%A0%BC%E5%BC%8F%E4%B8%BA%E2%80%9CALTER%20TABLE,%3C%E8%A1%A8%E5%90%8D%3E%20%5B%E4%BF%AE%E6%94%B9%E9%80%89%E9%A1%B9%5D%E2%80%9D%E3%80%82%20%E6%9C%AC%E6%95%99%E7%A8%8B%E6%93%8D%E4%BD%9C%E7%8E%AF%E5%A2%83%EF%BC%9Awindows7%E7%B3%BB%E7%BB%9F%E3%80%81mysql8%E7%89%88%E6%9C%AC%E3%80%81Dell%20G3%E7%94%B5%E8%84%91%E3%80%82)
2. DML(query)
    - SQL 和关系代数的联系：12-14
    - select: 16 - 18
    - where: 19 - 20 [关系代数 AND, OR, NOT](https://www.w3schools.cn/mysql/mysql_and_or.html)
        - 字符串操作：28 - 29
        - null value: 36 - 37
    - from: 21 - 25
        - natural **JOIN**: 23 - 26
        - 不能直接用 natural join 的例子：25 - 26
        - 其他：left join, right join, full join, etc.
    - rename(as): 27
    - order by: 30
    - limit: 31
    - 集合操作(union (all), intersect (all), except (all)): 34 - 35
    - 合计函数: 38 - 44
        - group by: 40
        - having: 42
        - null value in aggregate functions: 43
        - 合计函数 + 代数运算：44
    - nested subqueries: 45 - 62
        - set membership(in & not in): 46 - 47
        - set comparisons(some & all): 48 - 52
            - scalar subquery: 52
        - set cardinality(exists & not exists): 53 - 55
        - 检查多重集(unique): 56 - 58
        - 在 from 语句中嵌套: 59 - 60
        - with 嵌套: 61 - 62
3. DML(modification): 63 - 70
    - delete: 64 - 65
        - 时序问题：65
    - insert: 66 - 67
        - 单行插入(value): 66
        - 多行插入(select): 67
    - update(set + where, set + case): 68 - 70

[补充：视图](https://blog.csdn.net/moxigandashu/article/details/63254901)

补充：WorkBench 的使用参考 “实验二举例 MySQL”。

补充：补充阅读 / MySQL JOIN cheat sheet

tips: as 的优先级比 natural join 高，`A natural join B as C` C 指代的是 B 而不是 `A natural B`。

补充：[数据库生成随机数据](https://cloud.tencent.com/developer/article/1373196#:~:text=MySQL%20%E4%BB%8E%E9%9B%B6%E5%BC%80%E5%A7%8B%EF%BC%9A08%20%E7%95%AA%E5%A4%96%EF%BC%9A%E9%9A%8F%E6%9C%BA%E7%94%9F%E6%88%90%E6%95%B0%E6%8D%AE%E5%BA%93%E6%95%B0%E6%8D%AE%201,1%E3%80%81%E7%BD%91%E9%A1%B5%E7%89%88%EF%BC%9AGeneratedata%202%202%E3%80%81%E5%AE%A2%E6%88%B7%E7%AB%AF%EF%BC%9Aspawner%203%203.%E4%BB%A3%E7%A0%81%E7%94%9F%E6%88%90%EF%BC%9Apydbgen)

### ch4 Intermidiate SQL

- Domain Type 拓展
    - 用户自定义类型(类似 typedef): PPT 12
    - blob：PPT 14
- 完整性约束：书 4.4 节
    - foreign key 引用自己的例子：PPT 21
    - 自动生成 unique key values：书 4.5.6
- assertion：单独定义的复杂 check，PPT 24
- view：书 4.2 节
    - MySQL 没有 materialized view，只能用 table + trigger 实现
- index：书 4.6 节
- transaction：书 4.3 节
    - transaction 举例：PPT 36
    - ACID property：PPT 37
- Authorization：书 4.7 节



### ch5 database API

- 缩写汇总：PPT 5
- 注入攻击 [参考文章](https://www.easysoft.com/developer/sql-injection.html)
- [SQLJ 手册](https://docs.oracle.com/en/database/oracle/oracle-database/21/jsqlj/)
- trigger：[MySQL trigger 语法](https://dev.mysql.com/doc/refman/8.0/en/trigger-syntax.html)
- [JDBC 手册](https://docs.oracle.com/javase/tutorial/jdbc/index.html)
- [ODBC 手册](https://docs.oracle.com/cd/E17952_01/connector-odbc-en/index.html)
- [Embedded SQL 手册 1](https://docs.oracle.com/en/database/oracle/oracle-database/21/lnpcc/embedded-SQL.html)
- [Embedded SQL 手册 2](https://docs.oracle.com/cd/A87860_01/doc/appdev.817/a42525/ch04.htm)

创建新用户时的问题：[MySQL Workbench 8.0 点击Server Status面板Could not acquire management access for administration报错问题解决](https://www.cnblogs.com/MarcLiu/p/17180986.html)


### ch6 E-R model

#### 设计 E-R model

![数据库系统概念](./imgs/2023-04-03-10-19-13.png)

- 基本元素
    - 方框：entity，实体
    - 菱形：relation，实体之间的关系
    - 双层菱形：weak relation。比如 `section` 自己无法唯一确定一个实体，是一个 weak entity set，依赖 `course` 存在，称为 identifying entity set。`section` 需要补充 `course` 的主键才能成为一个独立的表格，这种关系用双层菱形表示。
- 联系类型
    - 箭头：表示多对一的关系。比如从 `inst_dept` 指向 `department` 的箭头，表示一个 `instructor` 只能有一个 `department`
    - 双实线：total participant，全参与。比如 `instructor` 和 `inst_dept` 之间的双实线表示每个 `instructor` 一定属于一个 `department`
    - 单实线：participant，既没有一对多又没有要求全参与。比如 `student` 和 `takes` 之间的单实线，表示一个 `student` 可以不 `takes` 任何 `section`，一个 `section` 也可以有多个 `student` 来 `takes`
    - 虚线：表示附加属性。比如上课了就会有成绩，需要 `grade` 来记录
- 减少冗余
    - primary key 相同的所有表都可以合并
        - 被箭头和双实线连接的 relation 不会出现在 DDL 中，因为其属性可以并入双实线连接的 entity 中。
    - weak entity set
        - 比如 section 不用存课程名字、学分等信息，减少冗余。

#### E-R model 补充概念

![数据库系统概念](./imgs/2023-04-03-11-03-45.png)

---

![数据库系统概念](./imgs/2023-04-03-11-07-59.png)

- 多元关系一定可以转化为一些二元关系。比如可以实体化 `proj_guide`，将三元关系转化为 3 个二元关系

---

![数据库系统概念](./imgs/2023-04-03-11-15-38.png)

- multivalued：一个 entity 的同一个 attribute 可以有多个值，比如电话号码
- cmoposite：多个 attribute 的组合，比如 `first name` 和 `last name` 可以是一组 composite attribute，组成 `name`

e.g. 缩进表示符复合属性，大括号表示多值属性，小括号表示派生属性

![数据库系统概念](./imgs/2023-04-03-11-29-40.png)

---

mapping cardinality 映射基数

one to one, one to many, etc. 用连线的类型表示，比如一对一就是两个箭头。

---

![数据库系统概念](./imgs/2023-04-03-11-27-38.png)

#### 将 E-R model 转化为关系数据库的 DDL

- 可以不建表的元素：
    - 弱实体的 identifying relationship
    - 一对多的 relationship

![数据库系统概念](./imgs/2023-04-03-11-46-01.png)

![数据库系统概念](./imgs/2023-04-03-11-46-29.png)

---

- 主键的选择

---

- composite attribute: 
    1. flattened out by creating a separate attribute for each component attribute
    1. 一个表格用于存储 detail，一个用于存储组合后的属性，例如 `time_slot_detail(time_slot_id, day, start_time, end_time)` + `time_slot(time_slot_id)`
- multivalued attribute: 新建一张表格

---

常见错误：一个学生上某门课，一般不可能只有一次作业。可以设计成多值属性，但在转化为关系数据模型时一般会变成 c 图中的样子。

![数据库系统概念](./imgs/2023-04-03-12-09-40.png)

---

设计原则

- attribute 转化为 entity，可以增强 E-R 图的表达能力。例如新建表可以表达 multivalued attribute。
- relationship 转化为 entity，可以增强 E-R 图的表达能力。例如把购买关系实体化为订单，可以和用户、支付方式、商品建立关系。
- 多元联系实体化为 entity，再和原来连接的 entity 之间建立二元联系。

---

Specialization(特化) & Generalization（概化）

![数据库系统概念](./imgs/2023-04-04-21-13-27.png)

- overlapping: 子类可能有重合部分
- disjoint: 子类没有交集
- partial: 展示部分子类，可能存在其他类型
- total: 展示所有子类

实现方法 * 3-：P278 6.8.6.1

#### e.g. 12306 数据库设计

改进方案：

1. “车次” entity 去掉“过站信息”的多值属性，在“过站”关系上加上衍生属性“站点次序”。去除冗余信息。
1. 在“车票”和“用户”之间新增 entity “订单”，可与多张票建立关系，包含订单号、下单时间、价格等信息。
1. 新增 entity “区间”，包含所有的两站之间有铁路相连的站点对。“车次模式”和“区间”之间建立关系，表示一趟车会经过哪些区间。
1. 新增 entity “车次_区间_座位”，即实体化一个三元关系，其中包含属性：
    1. 车次的 format_id 和发车日期
    1. 区间 id
    1. 座位 id
    1. 价格 & 是否被购买
    - 这张表用来存储座位的购买信息，支持查询经过一些区间的车票
1. 新增关系“订单信息”，在“订单”和“车次_区间_座位”之间建立关系。

### ch7 Relational Database Design

1. decomposition
    - lossy: PPT 9
    - lossless
    - dependency preservation: PPT 39, 40
        - 保留的例子 & 不保留的例子: PPT 41
1. functional dependency
    - combined schema 的问题：PPT 5 7
    - 用 functional dependency 证明 lossless decomposition: PPT 11
    - closure F+: PPT 20
    - attribute set closure: PPT 25
        - 自动化计算方法: PPT 25
        - 求 superkey: PPT 27
        - 求 F+: PPT 28
    - dependency 推导
        - armstrong's axioms: PPT 21
        - collarary: PPT 23, 24
    - canonical cover: PPT 29
        - 正式定义: PPT 31
        - 求最简覆盖算法: PPT 31
1. normal forms
    - 1NF
    - 2NF
    - 3NF
        - motivation：BCNF 不一定能满足依赖 dependency preservation，削弱条件
        - 定义：PPT 46
        - 分解成 3NF 的算法：PPT 49
    - BCNF: PPT 35
        - 不是 BCNF 的例子: PPT 34, 35
        - 分解成 BCNF 的算法: PPT 36，37
        - 非 BCNF 的问题：信息冗余、插入异常、更新困难 PPT 5
    - 4NF
        - motivation：BCNF 无法处理多值依赖导致的问题，需要一个更强的条件
        - 多值依赖：PPT 59, 60
        - 多值依赖的性质：PPT 61, 63
            - 函数依赖一定是多值依赖
            - 若存在多值依赖 X->->Y，一定存在 X->->(R-Y)。即多值依赖一定是成对出现的
        - 分解成 4NF 的方法：PPT 65

---

lossless 和 dependency-preserved 的区别：前者是分开的两个 relation natural jion 之后能变成和分开前一样。后者是保证只要检查分开后每张表自己的 functional dependency，就可以保证分开前的所有依赖都满足。

### ch8 面向对象数据库

- 面向对象数据库
    - 关系数据库的局限性：PPT 5，书（多个作者，多个关键词，拥有多个属性的出版社属性）
    - array & set：PPT 9
    - 自定义类型：PPT 10
    - 类型的继承 & 表的继承：PPT 11
    - 引用类型：PPT 12
    - 从面向对象到关系形式的转化：ORM，PPT 13-17
- 半结构数据类型
    - xml
        - 树结构和 XPATH 查询：PPT 29
        - XQUERY： PPT 30
    - json


### ch9 数据存储

1. 物理存储介质
    - 存储级别：![DB](./imgs/2023-05-10-14-41-22.png)
    - 磁盘
        - 相关概念：ppt 6
        - 磁盘性能指标：ppt 10 - 12
        - 磁盘性能优化方案：ppt 13 - 15
    - flash: SSD: ppt 16
    - NVM: ppt 18

1. 数据存储结构

- [数据存储模型：NSM, DSM, PAX](https://www.jianshu.com/p/eb44bd5bc786)
- [cache miss](https://www.cnblogs.com/jokerjason/p/10711022.html)

### ch14 索引 Indexing

1. ordered index: ppt 5，注重概念
1. B+ 树
    - 插入的例子：
    - 删除的例子：
    - 综合的例子：
    - bulk loading: ppt 45, 两种方法，bottom up build 和排序了再插入
    - B+ tree file organization: ppt 41, 注意这里叶子节点存放 record 而不是指向 record 的指针
    - multi-key: ppt 51
1. cache conscious: ppt 54
    - cache miss：CPU 要访问的数据在 cache 中有缓存，就叫 hit，否则叫 miss
1. LSM: log-structured merge tree
    - one kind of "write-optimized tree": ppt 55, 56
    - insert 操作：ppt 57，满的时候合并，合并的时候使用 bottom up build
    - delete 操作：ppt 60, 打 lazy tag，查询的时候忽略，合并的时候删除
    - benefit: ppt 58
1. stepped-merge index: ppt 59
1. Buffer tree: ppt 61，有点 lazy 操作的味道，插入的 record 可能存在非叶子节点里，等满了再往下更新
1. bitmap indices: ppt 62


## 错题摘录

except 注意加括号，否则运算顺序容易出错。

```sql
select A.ID, A.customer_name, A.customer_street, A.customer_city
from customer as A
where not exists ((
	select B.branch_name
    from branch as B
    where B.branch_city = "Brooklyn"
) except (
	select D.branch_name
    from depositor as C natural join account as D
    where A.ID = C.ID
)) ;
```

---

两张表具有同名但含义不同的列时特别注意，不能直接用 natrual join

---


## 实验记录

![数据库系统概念](./imgs/2023-04-02-10-39-55.png)

## cheat sheet

以下都是我完全记不住的东西：

- trigger 的语法
- function 的语法


## OceanBase 讲座

数据库的核心技术：事务！

- 实时系统，调试困难，难以跟踪
- 主备库一致性问题
- 分布式数据库，硬件持久性问题，硬件成本问题

现代数据库：处理突发高并发

机遇：互联网发展红利期，淘宝支付宝的需求

---

问题1：收藏夹（上亿） & 商品（百万）的连接

原地实时更新 -> 批量异步更新

修改量相对于原始数据量来说非常小，用一台机器存修改量，每天两点更新并生成快照

---

问题2：防掉电（主备库至少两份备份） & 可用性（备库掉电或断网不影响使用） tradeoff，并减少应急的情况

[paxos 分布式协议](https://zhuanlan.zhihu.com/p/31780743)：主库只需要备份到其中一个备库，备库合并可做成主库

恢复时间 30s

---

问题3：新旧系统的兼容性，换系统

---

问题4：交易（行存） & 分析（列存）

增量部分，因为频繁写，所以行存

---

根据业务量实时伸缩，减少成本

压缩数据，利用 cpu 性能

---

问题5：数据正确性

[CRC 校验](https://zhuanlan.zhihu.com/p/256487370)

备库数据更行：回放日志

---

[oceanBase 社区](https://open.oceanbase.com/)
- 其他竞争者：google spanner

