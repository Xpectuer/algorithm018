# 学习笔记



## 数组，顺序结构，双指针



## leetcode# 26 删除数组的重复项

### BF解法

1. 建立一个新的数组rs，一个临时变量temp

2. temp存取前一个元素

3. 遍历输入的数组

   1. 每次存取前一个元素到temp变量
   2. 每次检查temp与现在的**当前的数组元素**是否相等
      1. 相等，跳过
      2. 不相等，存入rs数组

4. 返回rs数组的长度

   

### 双指针法

1. 定义两个指针 i，j
2. 遍历输入数组 arr
   1. 如果i与j元素相等，j++
   2. 如果不相等 arr[ i ] = arr[ j ]将j拷贝到i上，这样循环结束后，前i+1个元素即处理后的数组，j++，i++
3. return 一个i+1（处理后数组的长度）



## leetcode# 11 盛水最多的容器

### Brute Force 暴力解法

1. 两重循环遍历所有情况，记录面积最大的情况

## 问题

计算冗余极大，导致**提交超时**



### 双指针法

1. 把指针设置在数组的**两头**
2. 评价标准
   1. 两个指针越远越好
   2. 木桶效应
3. 移动指针的规则
   1. 如果，左指针 > 右指针，右指针左移
   2. 右指针 < 左指针，左指针右移
   3. 这样可以同时保证**评价标准 1与 2**
4. 用一个max的变量存最大面积



# 【leetcode#70】Climb Stairs

## 常规思路
这道题本质上是斐波那契数列，但是传统的递归解法会**超时**。

```cpp
class Solution {
public:
    int climbStairs(int n) {
        if(n==1 || n==2)
            return n;
        
        return climbStairs(n-1)+ climbStairs(n-2);
    }
};
```
（菜鸡落泪,复杂度高达$O(2^n)$
## 通过
随后就去Discussion上看解法，发现通过的大佬**甚至没有用到递归**（因为函数栈即耗时又耗空间）
这是一种类似于动态规划Dynamic Programming的写法，但是其核心思想是：**用空间换时间**。
算法把每次相加的结果放进数组里，以便下次计算取用，而不是用递归的方法（算完就忘）。
时间复杂度则是降到了$O(n)$ 
```cpp
class Solution {
public:
    int climbStairs(int n) {
     // dp
        // space -> time
       int* dp = new int[n + 1];
        if (n == 1) {
            return 1;
        }
        if (n == 2) {
            return 2;
        }
        
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        
        for (int i = 3; i <= n; i++) {
          dp[i] = dp[i-1] + dp[i - 2];
        }
        return dp[n];
       
        
    }

};
```