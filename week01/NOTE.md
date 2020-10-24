# 学习笔记

## Abstract

![abs](/Users/alex/Desktop/2020Courses/algoTraining/algorithm018/week01/数据结构与算法.png)

## 数组，顺序结构，双指针



## 感悟

1. 关于双指针、三指针：
   1. 双指针的方法，最好是用在有序序列的基础上，这样才有判断指针移动的合理标准。
   2. 双指针三指针遇到相同的值可以跳过加速。
   3. 三指针请注意边界问题，以及跳过时的判断，使得代码更安全。





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



## 栈、队列、双端队列、优先队列

### Java源码

#### Stack

继承自：Vector\<E\>

APIs：

1. push() - 增加一个元素，调用父类方法:

   ```java
   addElement(item);//线程安全的
   ```

   并返回增加的元素

   

2. pop() - 弹出一个元素

   注意：这个方法加了```synchronized```	关键词，这样多个线程调用此方法时加锁，后来的线程必须等先来的线程调用完才能执行，这样防止可能产生的元素顺序问题。

3. peek() - 查看栈顶元素

   注意：这个方法同样加了```synchronized```关键词，防止**脏读问题**的出现。

4. search() -搜索栈内元素

   返回：最高的给定元素的下标

   同样是线程安全的。

5. empty() - 判断是否为空



#### Queue 

> 基本上是一种接口，定义了Queue需要具备的几种**抽象方法**。

在Queue的源码中，定义了几种效果相同，名称不同的抽象方法。



1. add() 与 offer() : 
   1. 都是使一个元素**从末尾**进队
   2. add()在进队失败后（如因，超出内存限制），抛出 *IllegalStateException* ，而offer return false
2. remove()与poll()：
   1. 都是**从队列头部**移除并返回元素。
   2. 前者在队列空时，抛 *NoSuchElementException* ，后者则是return null
3. element() 与 peek()：前者在无法找到元素时：
   1. 查看队列头部元素
   2. 前者在队列空时，抛 *NoSuchElementException* ，后者则是return null

#### Priority Queue

1. Basis

   1. Object[] queue - 可见，Priority Queue的底层基于一个数组实现。

   2. Constructor 重载参数

      1. initialCapacity ，指定初始容量，默认初始容量为11.
      2. comparator，比较接口的引用，规定**优先队列** 的**排序方式**。
      3. Collection <? extends E> c ,**深拷贝**一个SortedSet或者PriorityQueue。

   3. 重要的成员变量/常量

      1. MAX_ARRAY_SIZE=Integer.MAX_VALUE - 8:	对应JVM给予的内存上限，超出这个值，认为是**溢出Overflow** 会抛出OutOfMemoryError
      2. DEFAULT_INITIAL_CAPACITY = 11  指定默认的队列容量。
      3. size，当前队列中元素的数量。

   4. 重要的方法

      1. add(E e) - 插入一个指定的元素到这个优先队列中。(这是一个**冗余**的方法，目的是实现Collection接口，这是一种**面向接口**的编程).接下来讲实现

         1. offer(E e)  add(E e)的**实际实现**

            1. 实现了动态扩容，详见 grow()

            2. siftUp(int k,E x) 将元素插入后排到**指定位置**，根据Comparator的规则排序。

               1. 在siftUpComparable()中，存在一个>>>符号，这指的是**无符号右移**
               2. 这个方法用的是堆的插入方式，因此时间复杂度是$O(logn)$。这里实现的是大顶堆。
                  1. 先把待插入的元素加到堆底
                  2. 逐次与父元素比较key大小，把较大的父元素拿到下层，待插入元素逐级向上，直到没有比待插入元素更大的父元素。
                  3. 注意：这里仅仅移动了待插入元素，只是实现了堆化操作的一半（heapify）       

            3. siftDown(int x, E e) - 把指定元素滤到堆底或小于等于它 的子节点

               

            4. grow()

               - 根据原队列大小扩容

               1. 如果小于64，cap*2+2

               2. 大于64，cap*1.5

               3. 如果超出MAX_ARRAY_SIZE的限制，则深拷贝一个新的**Integer.MAX_VALUE** 大小的数组

                  > 当Integer.MAX_VALUE再加后，将会变为一个负数（我们可以通过这个特性判断overflow）。（原理见**计算机组成原理**）

            5. peek() 查看栈顶元素

               

