



学习笔记



# Trie字典树（前缀树）

字典树是一类特别的树结构

他的每个节点存取一个结构``dict``

``dict``结构的每个元素指向下一个字符

这样的结构把**搜索单词前缀问题**的复杂度优化到了$O(logn)$

### Trie模板 leetcode 208.

```cpp
class Trie {

    struct TrieNode {
        map<char, TrieNode*> child_table;
        int end;
        TrieNode():end(0) {}
    };
public:
    /** Initialize your data structure here. */
    Trie() {
        // private
        root = new TrieNode();
    }
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* curr = root;
        for(int i = 0;i < word.size(); i++) {
            if(curr->child_table.count(word[i]) == 0)
                curr->child_table[word[i]] = new TrieNode();
            
            curr = curr -> child_table[word[i]];
        }
        curr->end = 1;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        return find(word, 1);
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        return find(prefix, 0);
    }
private:
    /* int exact_match: 
        param 0: prefix match the word
        param 1: need the word exactly match the branch
    */
    TrieNode* root;

    bool find(string s , int exact_match) {
        TrieNode* curr = root;
        for(int i =0;i<s.size(); i++) {
            if(!curr->child_table.count(s[i])) 
                return false;
            else
                curr = curr->child_table[s[i]];
        }
        if(exact_match)
            return (curr->end)?true:false;
        else
            return true;
    }
    
    
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
```

## 例题 leetcode212. 单词搜索II

前置题目 [79. 单词搜索](https://leetcode-cn.com/problems/word-search/)

这道题的基本思路，就是如同，岛屿数量一样，DFS向不同方向遍历匹配单词

然而这道题的测试用例比较变态，如果不剪枝，容易TLE。

那么剪枝的手段，就是利用 **Trie**（这一点Hint里也有提示）

#### 思路

我们先按照``words``建立字典树， 

再对``board``进行dfs，每一个字符去匹配当前的字典树子节点

注意标记走过的路径

#### 代码

```cpp
class TrieNode{
public:
    string word = "";
    vector<TrieNode*> nodes;
    TrieNode():nodes(26, 0){}
};

class Solution {
    int rows, cols;
    vector<string> res;
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        rows = board.size();
        cols = rows ? board[0].size():0;
        if(rows==0 || cols==0) return res;

        //建立字典树的模板
        TrieNode* root = new TrieNode();
        for(string word:words){
            TrieNode *cur = root;
            for(int i=0; i<word.size(); ++i){
                int idx = word[i]-'a';
                if(cur->nodes[idx]==0) cur->nodes[idx] = new TrieNode();
                cur = cur->nodes[idx];
            }
            cur->word = word;
        }

        //DFS模板
        for(int i=0; i<rows; ++i){
            for(int j=0; j<cols; ++j){
                dfs(board, root, i, j);
            }
        }
        // O(knlogn)
        return res;
    }

    void dfs(vector<vector<char>>& board, TrieNode* root, int x, int y){
        char c = board[x][y];
        //递归边界
        // 走过的路 或者 字典不匹配
        if(c=='.' || root->nodes[c-'a']==0) return;
        // 到达相应子节点
        root = root->nodes[c-'a'];
        // 如果是已经遍历过的 单词
        if(root->word!="") {
            res.push_back(root->word);
            root->word = "";
        }
      
        // 标记走过的路  
        board[x][y] = '.';
        if(x>0) dfs(board, root, x-1, y);
        if(y>0) dfs(board, root, x, y-1);
        if(x+1<rows) dfs(board, root, x+1, y);
        if(y+1<cols) dfs(board, root, x, y+1);
        board[x][y] = c;
    }  
};
```

#### 复杂度分析

一开始还在纠结字典树的剪枝是否能够降低时间复杂度（就如同记忆化搜索那样）

然而看了官方题解，其实只要分析了最差情况，诸如``a...aaa``

那么时间复杂度仍然是$O(M\times N\times 4 \times 3^{L-1})$

M与N分别是board的行数与列数

4是第一步**最多**有四种情况

3是第二三四步最多有三种情况（前一步被标记走过）

***



## 并查集（Disjoint Set 分立集合 Union Find）

并查集的概念比较跳跃，应当**独立记忆**

### 效用

并查集解决了独立集合之间的查找与合并问题

比如：

1. 朋友圈问题
2. 岛屿个数问题
3. 编译器变量多个引用问题

实现一个Union Find需要以下的API

```java
interface UF {
    /* 将 p 和 q 连接 */
    public void union(int p, int q);
    /* 判断 p 和 q 是否连通 */
    public boolean connected(int p, int q);
    /* 返回图中有多少个连通分量 */
    public int count();
}
```

### 初始化

```cpp
// iterative
for(int i: parent)
	parent[i] = i
```

此时每个元素都是集合的**领头元素**，即每个元素独立成一个集合，连通矩阵如下：
$$
\begin{bmatrix}
 1 & 0 &0 \\
 0 & 1 &0 \\
 0 &  0&1
\end{bmatrix}
$$

### 查找领头元素（Find）

为了更好的合并，我们需要找到每个分立集合的**领头元素**

我们分别用递归和迭代的方式实现

- 迭代

  ```cpp
  int find(vector<int> p, int i) {
    int root = i;
    while(p[root] != root) {
      root = p[root];
    }
    // root found
    // route compression
    while(p[i]!=i) {
      int x=i;i=p[i];p[x]=root;
    }
  }
  ```

  

- 递归

  ```cpp
  // NO route compression
  int find(vector<int> p, int i) {
    return i==p[i]?i:find(p[i]);
  }
  ```

  

### 合并（Union）

<img src="/Users/alex/Library/Application Support/typora-user-images/截屏2020-12-04 上午11.16.14.png" alt="截屏2020-12-04 上午11.16.14" style="zoom:50%;" />

- 找到各个集合的**领头元素**
- 合并两个领头元素

```cpp
// 还可以优化
void union(vector<int> &p, int i, int j) {
  int rootI = find(p, i);
  int rootJ = find(p, j);
  if(rootI==rootJ) return;
  // p[rootJ] = rootI; // 等效
  p[rootI] = rootJ;
  count--;
}
```

#### 问题&优化

既然是合并集合树，那么必定会出现如：

1. **退化为链表**

2. 左右子树不平衡

这种降低**查询效率**与**路径压缩效率**的问题

- 优化：保持的UF的平衡性
  - 尽量不让小树的头作为领头元素

那么如何判断树的大小呢？

我们维护一个与``p[n] //parent``同样大小的``size[n]`` 数组

``size`` 内的元素维护每个元素的子节点个数

看代码:

```cpp
class UF {
private: 
    int count;
    vector<int> parent;
    // 新增一个数组记录树的“重量”
		vector<int> size;
public:
  	UF(int n) {
        this.count = n;
        parent = vector<int>(n);
        // 最初每棵树只有一个节点
        // 重量应该初始化 1
        size = vector<int>(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i；
        }
    }
  	void union(vector<int> &p, int i, int j) {
      int rootI = find(i);
      int rootJ = find(j);
      if(size[rootI] > size[rootJ]) {
        p[rootJ] = rootI;
        size[rootI] += size[rootQ];
      } else {
        p[rootI] = rootJ;
        size[rootJ] += size[rootI];
      }
      count--;
    }
  	
  
    /* 其他函数 */
}
```

### 例题

#### leetcode547. Friend Circle

这道题类似于岛屿数量，可以用DFS做

但是这里用并查集可以减少运算的复杂度

```cpp
class Solution {
private: 
    vector<int> parent;
    vector<int> size;
    int count;
    int find(int p) {
        return p==parent[p]?p:find(parent[p]);
    }
    
    void _union(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP==rootQ) return;
        //opt
        if(size[rootP] > size[rootQ]) {
            parent[rootQ] = rootP;
            size[rootP] += size[rootQ];
        } else {
            parent[rootP] = rootQ;
            size[rootQ] += size[rootP];
        }
        //cout<<this->count<<endl;
        this->count--;
    }
    
public:
    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        if(n==0) return 0;
        
        
        /*INITIALIZATION*/
        this->count = n;
        parent = vector<int>(n);
        for(int i=0;i<n;i++) parent[i] = i;
        size = vector<int>(n, 1);
        /*INITIALIZATION*/
        
        for(int i=0;i < n; i++) {
            for(int j=i+1;j < n; j++) {
                if(M[i][j]==1){
                    //cout<<count<<endl;
                    _union(i, j);
                }
                    
            }
        }
        return count;
    }

    
};

```

## 高级搜索

#### 初级搜索（不带任何优化）

- 重复不必要计算
- 没有智慧（启发函数）

### DFS模板

```python
def dfs(node, visited):
  if node in visited:
    return
  visited.add(node)
  
  # process the current node
  for next_node in node.connected():
    if next_node not in visited:
	    dfs(next_node, visited)
```

### BFS模板

```python
def bfs(node, visited):
  visited = set()
  queue = []
  queue.append([start])
  
  while queue:
    node = queue.pop()
    visited.add(node)
    
    # some process on node
    connected_nodes = connected_nodes(node)
    queue.push(connected_nodes)
    
    # other processing work
    # ...
```



### 回溯剪枝

#### 爬楼梯

```cpp
class Solution {
private: 
    
public:
    int climbStairs(int n) {
        if(n<=2) return n;
        vector<int> memo(n+1, 0);
        //  n > 2
        return climbStairs(n, memo);
    }
    int climbStairs(int n,vector<int> &memo) {
        if(n<=2) {
            memo[n] = n;
            return n;
        }
      // 这边利用缓存剪枝
        if(memo[n]==0) {
            memo[n] = climbStairs(n-1, memo) + climbStairs(n-2, memo);
        }
        return memo[n];
    }
};
```

#### 零钱兑换

```cpp
// !!!TLE!!! MEMORIZED SEARCH
class Solution {
    vector<int> memo;
public:
    int coinChange(vector<int> coins, int amount) {
        if(coins.size() == 0){
            return -1;
        }
        memo = vector<int>(amount);

        return findWay(coins,amount);
    }
    // memo[n] 表示钱币n可以被换取的最少的硬币数，不能换取就为-1
    // findWay函数的目的是为了找到 amount数量的零钱可以兑换的最少硬币数量，返回其值int
    int findWay(vector<int> coins,int amount){
        if(amount < 0){
            return -1;
        }
        if(amount == 0){
            return 0;
        }
        // 记忆化的处理，memo[n]用赋予了值，就不用继续下面的循环
        // 直接的返回memo[n] 的最优值
        if(memo[amount-1] != 0) {
            return memo[amount-1];
        }
        int min = INT_MAX;
        for(int coin:coins){
            int res = findWay(coins, amount-coin);
            if(res >= 0 && res < min){
                min = res + 1; // 加1，是为了加上得到res结果的那个步骤中，兑换的一个硬币
            }
        }
        memo[amount-1] = (min == INT_MAX ? -1 : min);
        return memo[amount-1];
    }
};

```





### A*启发式搜索

#### 例题

#### leetcode1091. shortest-path-in-binary-matrix

BFS（TLE）

```cpp
// TLE
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        // bfs
        if(grid.size()==0 || grid[0][0] || grid[grid.size()-1][grid.size()-1]) return -1;
        if(grid.size()<=2) return grid.size();
        
        deque<tuple<int, int, int> > q;
        q.push_back({0,0,1});
        vector<pair<int, int> > mov = {{0,1},{1,0},{1,1},{-1,-1},{-1,0},{0,-1},{1,-1},{-1,1}};
        int count=0;
        int n = grid.size();
        
        while(!q.empty()) {
                
            auto co = q.front();
            // reach the objective 
            // first reach must be the closest
            q.pop_front();
            // 8 direction trials
            for(auto p: mov) {
                int new_x = get<0>(co) + p.first;
                int new_y = get<1>(co) + p.second;
                if(new_x >= n || new_y >= n || new_x < 0 || new_y < 0 || grid[new_x][new_y] != 0)  continue;
                
                if(new_x==n-1&&new_y==n-1)  return get<2>(co) + 1;    
                q.push_back({new_x, new_y, get<2>(co)+1});
                // visited
                grid[get<0>(co)][get<1>(co)]== 1;    
            }
            
        }
        return -1;
        
        
    }
};
```



A*：

```cpp
// passed
int n;
int m;

// 记录（x，y）位置处最小距离是多少
struct pos {
    pos (int x, int y, int dis) : x(x), y(y), dis(dis){}
    int x;
    int y;
    int dis;
};

// 关键：由于对角线移动 比 水平、垂直移动的距离更远而花费一样，所以以如下方法排序优先级；
// 例如：（0,0） -> （2,5）的最优预期花费就是max(2 - 0, 5 - 0)
bool operator< (const pos A, const pos B) {
    return max(n - 1 - A.x, m - 1 - A.y) + A.dis - (max(n - 1 - B.x, m - 1 - B.y) + B.dis) >= 0;
}

class Solution {
public:

    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        if (grid.empty()) {
            return -1;
        }
        n = grid.size();
        m = grid[0].size();
        if (grid[0][0] == 1 || grid[n - 1][m - 1] == 1) {
            return -1;
        }
        if (n == 1 && m == 1) {
            return 1;
        }
        priority_queue<pos> q;
        pos start(0, 0, 1);
        q.push(start);
        // 拥塞路径加入closeList
        vector<bool> closeList(n * m, false);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) {
                    closeList[i * m + j] = true;
                }
            }
        }
        // 不需要记录父节点，故openList只保存最小花费
        vector<int> openList(n * m, 0);
        openList[0] = 1;
        // 八个移动方向
        vector<vector<int>> mov {{1, 1}, {1, 0}, {0, 1}, {-1, 1}, {1, -1}, {-1, 0}, {0, -1}, {-1, -1}};
        while (!q.empty()) {
            pos cur = q.top();
            q.pop();
            int curIdx = cur.x * m + cur.y;
            closeList[curIdx] = true;
            for (int k = 0; k < 8; ++k) {
                int xx = cur.x + mov[k][0];
                int yy = cur.y + mov[k][1];
                int nextIdx = xx * m + yy;
                if (0 <= xx && xx < n && 0 <= yy && yy < m && !closeList[nextIdx]) {
                    if (xx == n - 1 && yy == m - 1) {
                        return openList[curIdx] + 1;
                    }
                    // 没有到走过改点或者当前的路线更优
                    if (openList[nextIdx] == 0 || openList[nextIdx] > openList[curIdx] + 1) {
                        openList[nextIdx] = openList[curIdx] + 1;
                        pos next(xx, yy, openList[curIdx] + 1);
                        q.push(next);
                    }
                }
            }
        }
        return -1;
    }
};
```

#### 八联通图坐标cheatsheet

```python
(i -1, j-1),(i-1,j),(i-1,j+1),(i,j-1),(i,j+1),(i+1,j-1),(i+1,j),(i+1,j+1)
```

### 双向BFS搜索模板

```python
def bi_bfs():
  q1 = set(start)
  q2 = set(end)
  q = set()
  while len(q1) and len(q2):
    // ...
    if len(q1) > len(q2):
    		q1, q2 = q2, q1
    q.clear()
    for node in q1:
      # hit
			if node in q1 and node in q2:
        	return
      # process logic
	    for connected_node in get_connected_node(node):
     			q.add(connected_node)
      # process
     # swap
     q, q1 = q1, q
```

#### 例题

##### Word Ladder

```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        
        if(wordList.size()==0) return 0;

        unordered_set<string> dict(wordList.begin(), wordList.end());
        // not exist in dict
        if(!dict.count(endWord)) return 0;
        // bidirectional BFS
        unordered_set<string> q1{beginWord};
        unordered_set<string> q2{endWord};
        int count = 0;
        int l = beginWord.length();
        while(!q1.empty()&&!q2.empty()) {
            count++;
            // swapping ensure always try the shorter one
            if(q1.size() > q2.size()) swap(q1, q2);

            unordered_set<string> q;
            for(string w: q1) {
                for(int i = 0; i < l; i++) {
                    char ch = w[i];
                    for(int j = 'a'; j <= 'z'; j++) {
                        w[i] = j;
                        //meet
                        if(q2.count(w)) return count + 1;
                        // not exist in dict
                        if(!dict.count(w)) continue;
                        dict.erase(w);
                        q.insert(w);
                    }
                    // change the word
                    w[i] = ch;
                }
            }
            // q , q1
            swap(q, q1);
        }
        return 0;

    }
};
```



## AVL树与红黑树

复习：

1. 树的遍历

```python
def preorder(root):
  # process
  preorder(root.left)
  preorder(root.right)
  
def inorder(root):
  inorder(root.left)
  # process
  inorder(root.right)
  
def postorder(root):
  postorder(root.left)
  postorder(root.right)
  # process
```

2. BST二叉搜索树

   ```
   1. 左子树小于根节点
   2. 右子树大于根节点
   3. 中序遍历 可以得到一个 升序序列
   ```
   
3. BST 存在的问题

   理想情况下，我们的二叉搜索树呈现一个**完全二叉树**

   这样可以保持高度最低，也就是查询效率最高

   然而现实与理想往往相悖，在没有处理的情况下，BST很容易变成**不平衡，甚至退化为链表**

   因此，我们需要引入一个平衡方法

   通常的平衡实现有（这里列出面试中较为重要的实现）：

   1. [2-3Tree](https://en.wikipedia.org/wiki/2%E2%80%933_tree)

   2. [AVL Tree](https://en.wikipedia.org/wiki/AVL_tree)

   3. [Red-black Tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree)
   4. [B Tree](https://en.wikipedia.org/wiki/B-tree#:~:text=O(log%20n)-,O(log%20n),with%20more%20than%20two%20children.)
   5. [Splay Tree](https://en.wikipedia.org/wiki/Splay_tree)
   6. [Treap](https://en.wikipedia.org/wiki/Treap)



### AVL树

1. 发明者的姓：G.M.**A**delson-**V**elsky 和 Evgenii **L**andis

2. **要求相邻子树的高度差为1**

3. 在看AVL树之前，引入一个重要的操作：**旋转**

   看代码

   ```python
   right_rotate(node):
     x = node.left
   	x_r = x.right
     x.right = node
     node.left = x_r
     
   left_rotate(node):
     y = node.right
     y_l = y.left
     y.left = node
     node.right = y_l
   ```

   - AVL树**每个节点**需要保存``{-1, 0, 1}``这样的平衡因子，如果**值绝对值大于1**，则要作**平衡调整**
     - 这一点使得AVL树相当吃内存
   - 平衡调整（先找到最高的、因子不平衡节点）
     - RR
       - 左旋
     - LL
       - 右旋
     - LR
       - 左旋变成RR
       - 右旋平衡
     - RL
       - 右旋变成LL
       - 左旋平衡
     - 这一点导致AVL树调整的次数相对较多，降低了其运行效率

   传统功夫讲求一个点到为止👋，能讲清楚各个调整情况即可

    

### Red-Black Tree

不严格要求相邻子树高度差为1

用一个bit就可以存取节点状态（R/B -> 0/1）

1. 每个节点到达**不同叶子结点**经过的**黑色节点个数**相同
2. 相邻子树高度差不超过2倍
3. 红节点不能与黑节点相连