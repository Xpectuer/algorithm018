学习笔记

## 暴力搜索



### 广度优先搜索

- 寻找当前节点的所有邻接节点，遍历
- 往往维护队列以实现，对**队列头部**进行取邻等操作
- 图遍历时，注意记录走过的节点避免重复

#### 模板代码

```python
# Python
def BFS(graph, start, end):
    visited = set()
	queue = [] 
	queue.append([start]) 
	while queue: 
		node = queue.pop() 
		visited.add(node)
		process(node) 
		nodes = generate_related_nodes(node) 
		queue.push(nodes)
	# other processing work 
	...
```



### 深度优先搜索

- 递归地寻找当前节点的子节点
- 实现时，可以用递归（系统栈）实现；也可以用手动维护栈实现（迭代） 

#### 代码模板

```cpp
//C/C++
//递归写法：
map<int, int> visited;

void dfs(Node* root) {
  // terminator
  if (!root) return ;

  if (visited.count(root->val)) {
    // already visited
    return ;
  }

  visited[root->val] = 1;

  // process current node here. 
  // ...
  for (int i = 0; i < root->children.size(); ++i) {
    dfs(root->children[i]);
  }
  return ;
}
```

```cpp
//C/C++
//非递归写法：
void dfs(Node* root) {
  map<int, int> visited;
  if(!root) return ;

  stack<Node*> stackNode;
  stackNode.push(root);

  while (!stackNode.empty()) {
    Node* node = stackNode.top();
    stackNode.pop();
    if (visited.count(node->val)) continue;
    visited[node->val] = 1;


    for (int i = node->children.size() - 1; i >= 0; --i) {
        stackNode.push(node->children[i]);
    }
  }

  return ;
}

```



## 非暴力搜索

### 贪心算法

贪心在每一步选择中选出局部最好的结果，并希望获得全局最优解。

然而事实往往**事与愿违**，每次选择最优结果**不一定是**最优的结果。



#### 适用场景

问题能够分解为子问题解决，子问题的最优解**能够**递推到最终问题的最优解，这种子问题最优解称为**最优子结构**。

贪心算法与动态规划的区别：对每个子问题，贪心算法都**必须作出选择**且**不能回退**。而动态规划则会保存以前的运算结果，并根据以前的结果对当前进行选择，且可以**回退**。



#### 例题



322. Money Change



### 动态规划

动态规划之于贪心算法的不同是：对每个字问题的解决方案都做出选择，并且能够回退。

动态规划回保存之前的运算结果，根据以前的运算结果，与当前结果比较得出最优解，并且可以有回退功能。（其实是一种特殊的回溯算法）



### 二分查找

1. 有序序列
2. 存在上下界
3. 随机访问特性

#### 代码模板

```python
left, right = 0, len(array) - 1
while left <= right:
  mid = (left+right)/2
  if array[mid] == target:
    #find the target
    break or return result
  elif array[mid] < target:
    left = mid + 1
  else: 
    right = mid - 1
```

#### 四步做题法

1. 读题
2. 罗列解法
3. 代码
4. 测试样例（思考极端边界情况）



#### 例题

##### 搜索旋转排序数组

1. 暴力还原

我们用$O(n)$ 的复杂度进行peak的搜索，还原为有序，然后二分查找

2.  二分查找还原

用$O(logn)$的复杂度搜索peak（二分查找），然后还原为有序，再进行二分查找

```cpp
class Solution {
public:
  //主函数
    int search(vector<int>& nums, int target) {

        if(nums.size() == 0) return -1;
        
        int peak  = peakIndexInMountainArray(nums);
        
        if(nums[peak] < target) {
           return bs(nums, 0, peak, target);
        }
       
        return bs(nums, peak+1, nums.size(), target);
        
        

    }
  // 这边偷懒一下 用一下 leetcode 852.的代码
    int peakIndexInMountainArray(vector<int>& nums) {
        // bs 
         if(nums.size()==1) return nums[0];
        long long l= 0,  r = nums.size() -1;

       
        while(l<=r) {
            int mid = (l + r )/2;

            if(nums[mid] < nums[mid +1]) l = mid +1;
            else if(nums[mid] < nums[mid - 1]) r = mid - 1;
            else return mid;
        }
        return -1; 
    }
    int bs(vector<int> &nums, int low, int high, int target) {
        
        while(low <= high) {
            
            int mid = (low + high ) >> 1;

            if(nums[mid] < target) low = mid+1;
            else if(nums[mid] > target) high = mid -1 ; 
            else {
                if(mid==0|| nums[mid-1] != target) return mid;
                high = mid - 1;
            }
            
        }

        return -1 ;
    }
};
```



3. 正解：改造的二分查找

由于题目给出的输入是**局部单调**的，在**某两段**存在一定的单调性。

> 二分查找的条件：
>
> 1. 单调（非严格满足）
> 2. 边界（满足）
> 3. 随机访问（满足）

例如：

```pseudocode
nums = [4,5,6,7,0,1,2] , target = 0
```

在**原味二分查找**中，**收敛条件**是**大于或者小于** mid 值

因此，这里我们需要思考的是，```target``` 将会在**哪一段单调部分**，然后**把所有区间罗列出来**

我们依然取 

```pseudocode
mid = left + (right - left) / 2
```

然后，我们比较三个变量

``` pseudocode
nums[0]  	nums[mid] 	 target
```

 接下来，就罗列一下所有情况：（下面的```i```可以看作 high 位）

1. ```nums[0] <= nums[mid] ```，说明```0 - mid```有序。

   1. ```nums[0] <= target < nums[mid] ``` ，我们只要在 0 - mid 范围内查找，那也就是按照**原味二分查找**进行收敛。

2. ```nums[0] > nums[i]```，说明```0 - mid```存在peak。

   1. ```nums[0] > nums[i] >= target```，此时```target```在peak 后方，我们**向后收敛**。

   2. ```target >= nums[0] > nums[i]```，此时**向前收敛**。
   
   3. ```nums[0] > target >= nums[i]``` ，此时**向后收敛**。
   
   ![](/Users/alex/Desktop/2020Courses/algoTraining/algorithm018/week04/搜索旋转排序数组 2.png)

> 这里peak这个变量我们就不考虑了

如此，我们就不难写出代码：（虽说“不难”，其实磨了好久的细节，感觉离散数学还给老师了）

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.size()==0) return -1;

        int l = 0, h = nums.size() - 1;
        // 按照两种情况二分
        while(l < h) {
            int mid = l + ((h-l) >> 1);

            if(nums[mid] == target) return mid;
           // 0 - mid 有序 
            if( nums[l] <= nums[mid]) {
                // target 在这个范围内
                if( target >= nums[l] && target < nums[mid] ) h = mid - 1; 
                else  l = mid + 1;
            }
  
           // 0 - mid 存在peak
           // nums[l] > nums[mid]
            else {
              // target 在后半段有序序列
                if(target > nums[mid] && target <= nums[h] ) l = mid + 1;
                else  h = mid - 1;
            }

        }
        return nums[l] == target ? l : -1;
    }
  
};
```



最后顺便给一种[简洁版解法](https://leetcode-cn.com/problems/search-in-rotated-sorted-array/solution/ji-jian-solution-by-lukelee/)，要理解的这个解法的话，要点在于自己画一张**真值表**

```cpp
/*
作者：LukeLee
链接：https://leetcode-cn.com/problems/search-in-rotated-sorted-array/solution/ji-jian-solution-by-lukelee/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size() - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if ((nums[0] > target) ^ (nums[0] > nums[mid]) ^ (target > nums[mid]))
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo == hi && nums[lo] == target ? lo : -1;
    }
};

```

![真值表证明](/Users/alex/Desktop/2020Courses/algoTraining/algorithm018/week04/搜索旋转排序数组 3.png)

我们结合真值表，结合前面的解法，不难证明这种方案的**正确性**。（但是能想出来是真的大神）

### [153. 寻找旋转排序数组中的最小值](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/)

点出这道题的原因在于，这道题的某篇题解对于二分查找的条件做了相对详细的分析，帮助解题者更好地理解二分查找代码中的各种细节。



