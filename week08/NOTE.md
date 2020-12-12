学习笔记

## 位运算

理解位运算对于非计算机科学专业的选手需要一个思考的过程

然而对于计算机科学的选手来说，从理解简单的位运算到复杂的复合位运算

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



## Bloom Filter 布隆过滤器

**哈希表**可以依照KV存取一个**对象**

1. 布隆过滤器的效用，只是检测**某元素是否存在**

2. 布隆过滤器具有极高的**查询效率**与**空间效率**

3. 布隆过滤器的缺点：存在一定的误判别率

> 不存在（0）布隆过滤器的元素一定不存在，存在的（1）不一定存在

### 工作过程

1. 插入元素
   1. 对要插入的元素做多次hash（原元素），hash函数的输出值为**布隆数组下标**
   2. 我们 将相应下标的布隆数组元素置为**1**
2. 查询元素
   1. 对要查询的元素多次hash，看每一位的下标是否为1
      1. 出现0，一定不存在这个元素
      2. 全1，可能存在这个元素（通过hash设计降低误判率）

​	<img src="/Users/alex/Library/Application Support/typora-user-images/截屏2020-12-11 下午12.21.03.png" alt="截屏2020-12-11 下午12.21.03" style="zoom:50%;" />

### 应用

布隆过滤器高效且存在误判的特性，使得其能够很好地作为**系统外部的缓存**来使用

这样可以做到fail fast，快速判断不存在，就不需要进入db低效查询了



## LRU缓存（Least Recent Used最近最少使用）

- 大小，替换策略
- HashTable + DoubleLinkedList
- O(1) 查询
- O(1) 修改更新





### 排序算法

#### 插入排序

```cpp
void insert(int* arr, int n){
    //无序部分向有序部分插入
    // i 指向有序
    for(int  i= 1;i<n;i++){
        int temp = arr[i];
        int j=i;
        while (j > 0 && temp < arr[j-1]){
            arr[j]=arr[j-1];
            j--;
        }
        arr[j]=temp;
    }
}
```

#### 选择排序

```cpp
void select(int* arr,int n) {
    int j = 0, i=0;
    int min_index = 0;
    for(i=0;i<n;i++) {
        min_index = i;
        for(j=i;j<n;j++) {
            if(arr[j]<arr[min_index]) min_index = j;
        }
        // swap
        int temp = arr[i];arr[i] = arr[min_index];arr[min_index] =temp;
    }
}
```

### 冒泡排序

```cpp
void bubble(int *arr, int n) {
    for(int i=0;i<n;i++) {
        for(int j=0;j<n-1;j++) {
            if(arr[j]>arr[j+1]){
                int temp = arr[j+1];arr[j+1] = arr[j];arr[j] =temp;
            }
        }
    }
}
```

###  快速排序

```cpp
int partition(vector<int> &arr, int begin, int end) {
    // find the pivot
    // it is better to use random algo to select a pivot
    // pivot: position of pivot , counter: num of element smaller than element pivot
    
    //int pivot = rand() % (end - begin+1) + begin;  //随机选择pivot ！！！有问题回来优化
    int pivot = end;
    int counter = begin;
    
    for(int i=begin;i<=end;i++) {
        if(arr[i] < arr[pivot]) {
            swap(arr[i],arr[counter]);
            counter++;
        }
       
    }
    swap(arr[pivot],arr[counter]);
    // ...
    return counter;
}

void quickSort(vector<int> &arr,int begin,int end) {
    if(begin>=end) return;
    int pivot = partition(arr,begin,end);
    quickSort(arr,begin,pivot-1);
    quickSort(arr,pivot+1,end);
}
```

### 归并排序

```cpp

void merge(vector<int> &arr,int l,int mid,int r) {
    vector<int> tmp(r-l+1);
    int i = l, j = mid+1, k=0;
    // cmp & merge
    while(i<=mid&&j<=r) tmp[k++]=arr[i]<=arr[j]?arr[i++]:arr[j++];
    // pour
    while(i<=mid) tmp[k++] = arr[i++];
    while(j<=r) tmp[k++] = arr[j++];
    // copy ***critical***
    for(int p = 0;p < tmp.size();p++) {
        arr[l+p] = tmp[p];
    }
    
}

void merge_sort(vector<int> &arr, int l, int r) {
   
    if(l>=r) return;
    int mid = l + ((r-l)>>1);
    
    merge_sort(arr, l, mid);
    merge_sort(arr, mid+1, r);
    merge(arr,l,mid,r);
    
}
```

