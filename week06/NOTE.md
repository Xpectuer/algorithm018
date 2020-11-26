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



#### 例题（必会）

1143.  **Longest Common Subsequence** (LCS)

##### Brute Force

我们暴力穷举两字符串的子序列，看是否相互匹配的。

时间复杂度：$O(2^n)$

#### 动态规划DP

我们定义``dp(s1, i, s2, j) -> int``是为计算``s1[i...]``和``s2[j...]`` 的最长公共子序列长度

我们最后需要``dp(s1, 0, s2, 0) -> int``的**输出**作为答案

###### Base Case

那么当``i==len(s1)``或者``j==len(s2)``时，本质上两个指针有一个到达了尾部，公共子序列长度一定为 0。

```cpp
if(i==text1.length() || j==text2.length()) return 0;
```

###### Conditions

1. 如果``s1[i]==s2[j]`` 那么这个字符就**一定在LCS**中，

```cpp
// 当字符相等，则一定在LCS中
if(s1[i]==s2[j]) {
		return 1 + dp(text1,i+1,text2,j+1);
}else {
		// ... 
}
```

2. 如果``s1[i] != s2[j]`` 至少有一个字符不在LCS中
   1. ``s1[i]``不在LCS中
   2. ``s2[j]``不在LCS中
   3. 均不在LCS中

```cpp
// 当字符相等，则一定在LCS中
if(s1[i]==s2[j]) {
		return 1 + dp(text1,i+1,text2,j+1);
}else {
//  1. s1[i]不在LCS中
//  2. s2[j]不在LCS中
//  3. 均不在LCS中
  	// 我们穷举三种情况，并取得其中最大的结果
		return max(
    	 dp(text1,i,text2,j+1),
      dp(text1,i+1,text2,j)
      //dp(text1,i+1,text2,j+1) 一定较小，我们可以忽略
    );
}
```

我们还可以优化的原因：

情况三下计算``s1[i+1...]``与``s2[j+1...]``的LCS长度，

它一定是小于等于情况一、情况二

因此可以忽略不计

###### Memory

为代码添加缓存，降低代码复杂度

```cpp
// cpp超时
class Solution {
private:
    vector<vector<int> > memo;
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length(), n = text2.length();
        // -1 代表还未计算
        memo.resize(m+1);
        for(auto &it : memo) it.resize(n+1);
        for(auto &it:memo) fill(it.begin(),it.end(),-1);

        return dp(text1,0,text2,0);
    }
    int dp(string text1,int i ,string text2, int j) {
        // base case
        if(i==text1.length() || j==text2.length())
            return 0;

        // 取缓存
        if(memo[i][j]!=-1) return memo[i][j];
        // 当字符相等，则一定在LCS中
        if(text1[i]==text2[j]) {
            memo[i][j] = 1 + dp(text1,i+1,text2,j+1);
        } else {
            //  1. s1[i]不在LCS中
            //  2. s2[j]不在LCS中
            //  3. 均不在LCS中
  	        // 我们穷举三种情况，并取得其中最大的结果
		return memo[i][j] = max(
    	    dp(text1,i,text2,j+1),
            dp(text1,i+1,text2,j)
        );
        }

        return memo[i][j];
    }
};
```



###### DP Equation

$$
dp[i][j]= \begin{cases}
		1 + dp[i-1][j-1]\\
		max(dp[i-1][j],\ dp[i][j-1])
\end{cases}
$$





#### 自底向上

```cpp
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        const int m = text1.length(),n = text2.length();
        int dp[m+1][n+1];
        for(int i=0;i<m+1;i++){
            for(int j=0;j<n+1;j++){
                dp[i][j] = 0;
            }
        }
        // 我们定义 s1[0...i-1]与s2[0...j-1] 的lcs长度为dp[i][j]
        // 目标是求 dp[m][n]
        // base case: dp[0][j] = dp[i][0] = 0
        for(int i = 1; i<=m; i++) {
            for(int j = 1; j<=n; j++) {
                if(text1[i-1]==text2[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
                else{
                    // s1[i-1] 和 s2[j-1] 至少有一个不在lcs中
                    dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }
        return dp[m][n];

    }
};
```



