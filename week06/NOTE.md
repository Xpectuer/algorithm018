学习笔记



# 动态规划

## 动态规划 定义

>  In both contexts it refers to simplifying a complicated problem by breaking it down into simpler sub-problems in a [recursive](https://en.wikipedia.org/wiki/Recursion) manner. While some decision problems cannot be taken apart this way, decisions that span several points in time do often break apart recursively. 

在两种语境（数学，CS）下，动态规划指：

**递归地分解原问题为子问题**，来简化一个复杂问题。

尽管某些决策问题不能如上述的方式分解，跨越多个节点（Node）的决策



## 最优子结构

#### 最优子结构

> if a problem can be solved optimally by breaking it into sub-problems and then recursively finding the optimal solutions to the sub-problems, then it is said to have [optimal substructure](https://en.wikipedia.org/wiki/Optimal_substructure).

如果一个问题可以找到最优解，并且其子问题也可以找到最优解。

则这个问题存在**最优子结构**

比如贪心算法，如果其能够被证明每一步的贪心选择都是最优的话，那么它就存在最优子结构。

### 分治

实际上，动态规划可以看作分治的一种特殊形式，它存在淘汰次优解的情形。



## 关键点

- 动态规划与递归或是分治没有本质上的区别（关键看是否有最优子结构）
- 共性： 重复子问题
- 差异性：最优子结构、中途可以淘汰次优解



1. 最优子结构 ```opt[n] = best_of(opt[n-1], opt[n-2],...)```

2. 储存中间状态：``opt[i]``

3. 递推公式（状态转移方程 或DP方程）

   Fib：``opt[n-1] + opt[n-2]``

   二维路径：``opt[i,j] = opt[i+1][j] + opt[i][j+1]``（且判断是否为空地）