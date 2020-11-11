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