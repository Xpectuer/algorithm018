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

