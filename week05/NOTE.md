学习笔记



## 【刷题笔记】46.全排列优质解法

思路：回溯



## 基本盘：

我们每次递归，记录已访问的元素。

从剩下的元素中取，取完回溯。

状态树是每层决定放入一个元素。



## 新思路

今天复习的时候，看到外国老哥相当精妙的理解。

就来做一个~~汉化~~

主要思路有点像**插入排序**

每次的决定从决定放入哪个元素到决定下一个元素放在哪个位置。

具体来讲，

比如我的输入是```[1, 2, 3]``` ，

- 先拿一个```[1]``` ，剩下```[2, 3]```
- 按照顺序，我们拿```[2]```, 我们尝试将```[2]```放到```[1]``` **之前或之后**，出现两种情况
  - ``[1, 2]``
  - ``[2, 1]``
- 我们尝试放``[3]``，那么就有 $2\times 3 = 6$ 种情况，因为```[3]``` 的位置有三种放法，又有两种排列（``[1, 2]``和 ``[2, 1]``）
  - 放0位
    - ``[3, 1, 2]``
    - ``[3, 2, 1]``
  - 放1位
    - ``[1, 3, 2]``
    - ``[2, 1, 3]``
  - 放2位
    - ``[1, 2, 3]``
    - ``[2, 1, 3]``
- 如此，就得到了全排列

## 实现

如此找位置插入，我们不难对基本的回溯代码做出改造：



```cpp
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>>res;
        vector<int>vec;
        DFS(nums, 0, vec, res);
        return res;
    }
    
    void DFS(vector<int>& nums, int pos, vector<int>& vec, vector<vector<int>>& res){
        if(pos == nums.size()){
            res.push_back(vec);
            return;
        }
      	// 遍历vec寻找位置
        for(int i = 0; i <= vec.size(); i++){
            vec.insert(vec.begin() + i, nums[pos]);
          // drill down，找下一个数
            DFS(nums, pos + 1, vec, res);
            vec.erase(vec.begin() + i);
        }
        return;
    }
};
```



因为是找位置，我们需不需要过多的容器来储存中间结果

这样就会使得我们的代码更加简洁。



基于这个想法，利用```swap```交换元素，达到一样的目的

```cpp
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>>res;
        DFS(res, nums, 0);
        return res;        
    }
    
    void DFS(vector<vector<int>>& res, vector<int>& nums, int pos){
        if(pos == nums.size() - 1){
            res.push_back(nums);
            return;
        }
        for(int i = pos; i < nums.size(); i++){
            swap(nums[pos], nums[i]);
            DFS(res, nums, pos + 1);
            swap(nums[pos], nums[i]);
        }
    }
};
```

1, 2

1, 2, 3

2, 1, 3

3, 2, 1

2, 1











