学习笔记



### 递归

递归就像是盗梦空间的层层梦境，每次都会把主角团队（**参数**）带入下一层梦境，下一层梦境的又是新的与上层不相关的世界（**函数栈调用**）。

如何设计递归代码？

1. 找到问题中重复的任务
2. 数学归纳思想
   1. 初始条件，比如n=1时的任务
   2. 思考n =k时的情形
   3. 思考n = k+1的情形
3. 不要人肉递归！不要人肉递归！不要人肉递归！

#### 树

树的节点错综复杂，而且一般的题目无法回溯，所以**递归写法**比较契合树的特性（可回溯，重复工作）。

### 例题



### leetcode226. Reverse Binary Tree

后序遍历，没什么好说的

```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return root;
        dfs(root);
        return root;
    }
    void dfs(TreeNode* root) {
        if(!root) return;
        
        dfs(root->left);    
       
        dfs(root->right);
         // operation
        TreeNode* tmp = root ->left;
        root->left = root ->right;
        root->right = tmp;
    }
};
```

### leetcode98. Validate BST

中序遍历，根据BST特性，遍历的**前一个节点一定小于后一个节点**

坑：用例有INT_MIN 会导致 pre初始化INT_MIN通不过，故使用LONG_MIN

```cpp
class Solution {
private:
    long pre = LONG_MIN;
public:
    bool isValidBST(TreeNode* root) {
        if(!root) return true;
        if(!isValidBST(root->left)) return false;
        if(root->val <= pre) return false;
        pre = root ->val;
        return isValidBST(root->right);
    }
};
```

### leetcode 297. Serialize and Deserialize Binary Tree

递归部分的代码无特殊性，主要是掌握C++语言sstream的应用，来绕过全局变量的限制

```cpp
class Codec {
private:
    void serialize(TreeNode* root, ostringstream &os) {
        if(!root) {
            os << "# ";
            return;
        }
        os << root->val << " ";
        serialize(root->left, os);
        serialize(root->right, os);
        
    }
    TreeNode* deserialize(istringstream &in) {
        string val;
        in >> val;
        if(val == "#") return nullptr;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = deserialize(in);
        root->right = deserialize(in);
        return root;
    }
        
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream os;
        serialize(root,os);
        return os.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream  in(data);
        return deserialize(in);
    }

};
```



## 分治算法 Divide And Conquer

分治算法，是递归的特殊形式

在递归将问题分成子问题后后的还需要进行分治处理

最经典的例子就是 **归并排序**

### 分治代码模板

```cpp
// C/C++
int divide_conquer(Problem *problem, int params) {
  // recursion terminator
  if (problem == nullptr) {
    process_result
    return return_result;
  } 

  // process current problem
  subproblems = split_problem(problem, data)
  subresult1 = divide_conquer(subproblem[0], p1)
  subresult2 = divide_conquer(subproblem[1], p1)
  subresult3 = divide_conquer(subproblem[2], p1)
  ...

  // merge
  result = process_result(subresult1, subresult2, subresult3)
  // revert the current level status
 
  return 0;
}
```



### 例题

### leetcode Pow(x, n)

1. 暴力 x\*x\*x... 迭代n次
2. 分治求N/2次 x*x，N/4次 x\*x\*x\*x , ...
3. 注意正负号、奇数N

```cpp
class Solution {
public:
    double fastPow(double x, long long N) {
        if(N ==0) {
            return 1.0;
        }
        double y = fastPow(x,N/2);
        return N%2==1?y*y*x:y*y;
    }

    double myPow(double x, int n) {
        long long N = n;
        return N>=0? fastPow(x,N):(1.0 /fastPow(x,-N));
        }
    };
```



## 回溯算法

回溯的本质就是暴力遍历，暴力地遍历**整棵决策树**，它可以达到$O(m^n)$的糟糕表现

但是其中有**剪枝**的操作

剪枝，也就是遇到合适的情况，直接**返回到**父节点（上一个决策位）

以八皇后的问题为例，不合适的情况，就是在当前皇后的路径上存在其他皇后。

这可能在我们遍历到最后一行之前就会被触发，这就是**剪枝**，剪去决策树的**子树**。

### 例题

####   [leetcode 22. Generate Parentheses](https://leetcode-cn.com/problems/generate-parentheses/)

我们可以迭代我们的方法。

1. 生成所有括号的组合
2. 剪去不合适的决策
   1. 我们创建 left 与 right 的来计算当前 左括号与右括号
   2. 左括号不能大于右括号的数量
   3. 左右括号皆不能大于输入参数N（N对括号）

```cpp
class Solution {
private:
    vector<string> rs;
public:
    vector<string> generateParenthesis(int n) {
        if(n==0) return {};

        _generate(0, 0, n, "");
        return rs;
    }

    void _generate(int left, int right, int n, string brace) {
        if(left==n && right==n) {
            rs.push_back(brace);
            return;
        }

        if(left < n) _generate(left+1, right,n, brace+"(");
        if(left > right) _generate(left,right+1,n,brace+")");
    }
};
```



#### [leetcode78. Subsets](https://leetcode-cn.com/problems/subsets/)

子集问题，最简单的解决方案即暴力DFS，然而这样的效率相当低下

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        if(nums.size()==0) return {};
        vector<int> list;
        vector<vector<int>> ans;
        dfs(0, nums, list, ans,nums.size());
        return ans;
    }
    void dfs(int i,const vector<int> nums,vector<int> list, vector<vector<int>> &ans, int n) {
        if(i==n) {
            ans.push_back(list);
            return;
        }
        
        // do not select
        dfs(i+1, nums, list, ans, n);
        // select
        list.push_back(nums[i]);
        dfs(i+1, nums, list, ans, n);
       

    }
};
```

​	以下是迭代递归的方法，剪去了**部分子树**

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> subs;
        vector<int> sub;
        subsets(nums, 0, sub, subs);
        return subs;
    }
private:
    void subsets(vector<int>& nums, int i, vector<int>& sub, vector<vector<int>>& subs) {
        subs.push_back(sub);
        for (int j = i; j < nums.size(); j++) {
            sub.push_back(nums[j]);
            subsets(nums, j + 1, sub, subs);
            sub.pop_back();
        }
    }
};
```

当然也有**迭代**的写法，逐步扩大集的大小，直到全部枚举完毕

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> subs = {{}};
        for (int num : nums) {
            int n = subs.size();
            for (int i = 0; i < n; i++) {
                subs.push_back(subs[i]); 
                subs.back().push_back(num);
            }
        }
        return subs;
    }
}; 

//Using [1, 2, 3] as an example, the iterative process is like:

//Initially, one empty subset [[]]
//Adding 1 to []: [[], [1]];
//Adding 2 to [] and [1]: [[], [1], [2], [1, 2]];
//Adding 3 to [], [1], [2] and [1, 2]: [[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]].
```

**位运算**，当前无法理解，贴着备用

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size(), p = 1 << n;
        vector<vector<int>> subs(p);
        for (int i = 0; i < p; i++) {
            for (int j = 0; j < n; j++) {
                if ((i >> j) & 1) {
                    subs[i].push_back(nums[j]);
                }
            }
        }
        return subs;
    }
};
```

