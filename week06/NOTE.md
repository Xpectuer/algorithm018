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



### 思想武器

1. 打破思维惯性，形成及其思维
2. 理解复杂逻辑的关键
3. 职业进阶的要点



### 5 EZ Steps to DP

1. Define a subproblem
2. Guess part of solution
3. relate subproblem solutions
4. Recurse & Memorize
5. ~~Solve Original problem~~

(自顶向下，自底向上都要练一下)

状态压缩

#### 例题（必会）

##### 1143.**Longest Common Subsequence** (LCS) 二维DP

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



##### 198. 打家劫舍 （一维DP）



这是力扣一维dp的经典题目。

我们知道，dp的核心就是找到dp方程，代码也就呼之欲出了。

由于题目的制约因素是：

> **如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警**。

也就是不能同时入侵相邻的房间。



回到抢房子，先不思考限制条件，

我们最直观的思维：

我们要么抢这间房``num[i]``，要么不抢。



设``dp[i]``存放打劫到第`i`间房的最好结果

再想不能对相邻的房子下手

我们的是要得到``dp[i]``最好的结果，

那么我们只要知道``dp[i-1]``最好的结果，并决定在第``i``间房**下不下手**

1. 下手，则``dp[i-1]``不下手，说明我们在``i-2``下手，结果就是``dp[i-2] + num[i]``

2. 不下手，则``dp[i-1]``下手，结果就是``dp[i-1]``

   我们直接选择``dp[i]``更大的决定：

   ```pseudocode
   dp[i] = max(dp[i-2]+num[i],dp[i-1])
   ```

   也就不难写出代码（这里用go实现）

   ```go
   func rob(nums []int) int {
       if nums==nil || len(nums)==0 {
           return 0
       }
       if len(nums)==1 {
           return nums[0]
       }
     // 空间复杂度压缩到O(1)
       first := nums[0]
       second := max(nums[0], nums[1])
   
       for i:=2;i<len(nums);i++ {
           first, second = second, max(first + nums[i], second)
       }
       return second
   }
   // go没有 max(int,int) int 的库函数，我们手动实现一个
   func max(a int , b int) int {
       if a>b {
           return a
       }
       return b
   }
   ```

   

##### 213. 打家劫舍II

Leetcode198.的简单变体

这道题把数组设作旋转数组，使得最后一间与第一间房不能同时抢

这个思路我由于缺乏处理旋转排序数组的经验，一开始未曾想到

看了题解确实精妙，便作记录



方法便是我们取``num[1:]``和``num[:-1]``依葫芦画瓢两段分别DP，取其中最大的即可

```go
func rob(nums []int) int {

     if nums==nil || len(nums)==0 {
        return 0
    }
    if len(nums)==1 {
        return nums[0]
    }

    return max(dp(nums[1:]), dp(nums[:len(nums)-1]));
}
func dp(nums []int) int {
    if nums==nil || len(nums)==0 {
        return 0
    }
    if len(nums)==1 {
        return nums[0]
    }

    first := nums[0]
    second := max(nums[0], nums[1])
		// 空间复杂度压缩到O(1)
    for i:=2;i<len(nums);i++ {
        first, second = second, max(first + nums[i], second)
    }
    return second
}
// go没有 max(int,int) int 的库函数，我们手动实现一个
func max(a int , b int) int {
    if a>b {
        return a
    }
    return b
}
```



##### 122.买卖股票的最佳时机 I





>  声明：本博客性质为**学习笔记**，
>
> 请争议原创的耗子尾汁
>
> 本篇致谢[labuladong](https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/1.5-qi-ta-jing-dian-wen-ti/tuan-mie-gu-piao-wen-ti)





这道题明明是简单题还讲？

不就是动态规划吗？简单的。

如果有人如此说，你可以这么回他：

> 这是白纸和笔，你可以帮我手撕一下这道题吗？

那么这个时候会有两种情况：

1. 他撕不出来，你劝他好生刷题
2. 他撕出来了，那是他真的nb



聊题！聊题！

###### 看状态

就如我上面👆的碎碎念所述，问出问题，出现了**两种情况**

也就是**一个状态两种选择**

但是这道题目有点特殊

涉及到**三种状态**

首先，在**购买股票**时，只有三种**选择**

1. 买入
2. 卖出
3. 不动

值得注意的是，就本题而言，实际上只有**两种状态**

1. 持仓
2. 不持仓

因为你**不可能先卖再买**股票，也不能**光买不卖**，以此类推



其次，操作股票有**天数**

最后，存在**剩余交易次数**

我们可以用一个**三元组**唯一确定某天的状态

```
dp[i][k][0/1] // 天数，剩余交易次数，持仓/不持仓
```



我们最终要求的是	

```
dp[n-1][k][0]
```

也就是第n-1天，剩余交易次数k的情况下，**最大交易获利**

这里（0）的意思就是**不持仓**，显然，如果**此时还持仓（1）必亏**（因为最后一天就没有交易机会了）



###### 状态转移

用一张图来阐明状态转移过程：

![img](https://gblobscdn.gitbook.com/assets%2F-LrtQOWSnDdXhp3kYN4k%2Fsync%2F298b4971971d6e850923f64ab74792b86aa5c668.png?alt=media)

图源：[labuladong的算法小抄](https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/1.5-qi-ta-jing-dian-wen-ti/tuan-mie-gu-piao-wen-ti)

我们从**股票的持有是否**入手，尝试写一下dp方程

先枚举讨论所有情况：

1. 今天不持仓：
   1. 昨天也不持仓，不操作
   2. 昨天持仓，今天卖出
2. 今天持仓：
   1. 昨天也持仓
   2. 昨天不持仓，今天买入



根据这些情况，写出dp方程：


$$
\begin{cases}
	dp[i][k][0] = max(dp[i-1][k][0],dp[i-1][k][1] + price[i])\\
	\\
	dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k][0] - price[i])
\end{cases}
$$


###### Base case

$$
\begin{cases}
	dp[-1][k][0] = 0\\
	
\\
	dp[-1][k][1] = -\infty 
\end{cases}
$$

我们在还未开始交易时，不持仓的收益为0

并且我们不可能持仓，设此时收益为**负无穷**



###### coding

写出dp方程，我们还怕写不出代码？

不过，实际上需要注意的是**base case 的处理**

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //dp
        int n = prices.size();
        if(n==0) return 0;
        int dp[n][2];

        // base cases
        dp[0][0] = 0;
      	// 随便找比-price[0]小的负数即可，只要第一重循环max()
      	// dp[1][0]返回0 dp[1][1]返回 -price[0]
        dp[0][1] = -prices[0];
        
        // dp方程，从1开始
        for(int i=1;i < n;i++) {
            dp[i][0] = max(dp[i-1][0],dp[i-1][1]+prices[i]);
          	// 因为k=1，因此相当于i-1天不持仓: dp[i-1][0]=0,所以
            // dp[i][1] = max(dp[i-1][1],dp[i-1][0]-prices[i]);
          	// 化简为：
          	dp[i][1] = max(dp[i-1][1],-prices[i]);
        }

        return dp[n-1][0];
    }
};
```

与前面的dp题一样，我们可以**状态压缩**

因为实际上只需要两个变量在存储状态即可

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //dp
        int n = prices.size();

        // base cases
        int dp_i_0 = 0;
        int dp_i_1 = INT_MIN;//随便找个负数即可
        
        //dp方程
        for(int i=0;i < n;i++) {
            // ....状态压缩
            dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);
            dp_i_1 = max(dp_i_1, -prices[i]);
        }

        return dp_i_0;
    }
};
```





##### 买卖股票的最佳时机II

 这道题与上一题的区别，即

你可以进行多次交易（多次买入，多次卖出）



那么就是根据上一题的dp方程：
$$
\begin{cases}
	dp[i][k][0] = max(dp[i-1][k][0],dp[i-1][k][1] + price[i])\\
	\\
	dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k][0] - price[i])
\end{cases}
$$
因为没有限制k的次数

dp方程中可以忽略 $k$

轻松写出代码：

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //dp
        int n = prices.size();

        // base cases
        int dp_i_0 = 0;
        int dp_i_1 = INT_MIN;//随便找个负数即可
        
        //dp方程
        for(int i=0;i < n;i++) {
            // ....状态压缩
            int temp = dp_i_0;
            dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);
            dp_i_1 = max(dp_i_1, dp_i_0-prices[i]);
        }
        return dp_i_0;
    }
};
```

##### 买卖股票的最佳时机含冷冻期

这道题的需求就是：

卖出后，不能在第二天买入股票

我们对dp方程稍作改动：
$$
\begin{cases}
	dp[i][k][0] = max(dp[i-1][k][0],dp[i-1][k][1] + price[i])\\
	\\
	dp[i][k][1] = max(dp[i-1][k][1], dp[i-2][k][0] - price[i])
\end{cases}
$$
即当持仓时，只能是

1.  前一天也持仓
2. 前两天买入

因此只要对上面的代码稍作修改：

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //dp
        int n = prices.size();

        // base cases
        int dp_i_0 = 0;
        int dp_i_1 = INT_MIN;//随便找个负数即可
        int dp_pre_0 = 0; // 保存dp[i-2][0]
        //dp方程
        for(int i=0;i < n;i++) {
            // ....状态压缩
            int temp = dp_i_0;
            dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);
            dp_i_1 = max(dp_i_1, dp_i_0-prices[i]);
           	dp_pre_0 = temp;
        }
        return dp_i_0;
    }
};
```

##### [714. Best Time to Buy and Sell Stock with Transaction Fee](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/)

###### dp equation

$$
\begin{cases}
	dp[i][k][0] = max(dp[i-1][k][0],dp[i-1][k][1] + price[i])\\
	\\
	dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k][0] - price[i]- fee)
\end{cases}
$$

唯一要注意的点就是