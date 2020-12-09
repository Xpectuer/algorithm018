学习笔记

## 位运算

位运算对于非计算机科学专业的选手需要一个思考的过程

然而对于计算机科学的选手来说，从简单的位运算到复杂的复合位运算

仍然是一个过程

这里就实用主义的角度出发，总结一下做到的题目用到的**复合位运算**

### 2的幂

``n&(n-1)`` 这个操作可以将一个二进制数 $n$ 最右边的1归零

```python
>>> x=0b100101010100
>>> bin(x&(x-1))
'0b100101010000'
```

在二进制数中，任何2的幂都是

- 首位数字为1，其余为0

因此，我们只需要打掉一次末尾的1，如果结果不是0，则**一定不是2的幂**

```cpp
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n>0&&(n&(n-1))==0;
    }
};
```

###  位1的个数

位1的个数实际上就是[汉明重量](https://zh.wikipedia.org/wiki/%E6%B1%89%E6%98%8E%E9%87%8D%E9%87%8F)

它在通信、密码学、计算机科学等领域都有相当重要的地位

本题与上题实际上可以用同一招解决

看代码

- 递归

```cpp
class Solution {
public:
    int hammingWeight(uint32_t n) {
        return n ? 1 + hammingWeight(n & (n - 1)) : 0;
    }
};
```

- 迭代

```cpp
class Solution {
public:
    int hammingWeight(uint32_t n) {
      int count =0;
        while(n) {
          count++;
          n = n&(n-1);
      }
        return count;
    }
};
```

  ​	``uint32_t`` 表示C语言中的32位整型

只要每次循环判断整数是否为0，

我们就不必遍历全部32位就可以得出结论

### 颠倒二进制位

``n&1``：取得二进制数 $n$ 的最后一位

具体的思路，即 **将最后一位放到第一位**

以此类推

我们开辟一个新的二进制数``res=0``

每次左移一位``res`` 放入此时``n``的最后一位

``n`` 右移一位

看代码：

```cpp
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t  res=0;
        for(int i=0; i<32; i++) {
                res = (res<<1) + (n&1);
                n = n >> 1;
        }
        return res;
    }
};
```

### （经典）N皇后II

回溯算法已经做过，这里不在赘述

我们用位运算来加速这个过程

苍白的文字和苍白的代码无法讲清楚，我就结合代码与注释讲解，

**前提是读者已经理解了回溯方法**

```python
class Solution:
    def totalNQueens(self, n: int) -> int:
        if n < 1: return []
        self.count = 0
        self.DFS(n,0,0,0,0)
        return self.count
    def DFS(self, n, row, cols, pie, na):
        # recursion terminator
        if row >= n:
            self.count +=1
            return
         '''
        假设当前 n = 4,
        1层：
        row, col , pie, na = 0,0,0,0
        bits = 0b1111
        while循环：(判断bits是否全为0）
            p = 1 , 最低1位在第1位
            bits = bits & (bit -1)
            bits = 0b1110, 在最低位试探一个皇后
        ----drill down----
        2层：
        row = 1, col = 0b0001, pie = 0b0010, na = 0b0000
        bits = (~(0011)) & (1111)  # num&mask
             = 1100
        得到此时的可用位置
        while循环：
            p=0100
            bit = 1000 # 打掉p位的Q
        ----drill down----
        以此类推
        ...
        
        '''
        bits = (~(cols | pie | na)) & ((1 << n)-1 ) # 得到本层的空位
    while bits:
        p = bits & -bits # 取得最低位的1的位置
        bits = bits & (bit - 1) # 在最低的1位放上皇后，即p位
        # 下探一层，往可行的位置放上皇后
        self.DFS(n, row + 1, cols | p, (pie | p) << 1, (na | p)>>1)
```

如果你想要学习验证位运算的结果

推荐打开你的shell

然后python开一个CLI **交互命令行**

把位运算全部打一遍