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
               
### 例题
#### 20.有效的括号

> 检测一段字串序列中的有效括号

##### 栈方法（C++）

1. 创建一个栈结构，

   1. 若是左括号，则入栈
   2. 若是右括号，则检测栈顶是否是相应左括号

2. 细节：

   1. 检测输入长度，若是0，直接返回true;若长度为奇数，返回false

      ```cpp
       if(!s.length()) return true;
       if(s.length%2=1) return false;
      ```
   ```
   
   ```
   
2. 建立散列表（方便检测）
   
      ```cpp
        unordered_map<char, char> pairs = {
                  {']','['},
                  {'}','{'},
                  {')','('}    
              };
	```
	
	3. 检测是否是右括号
	
	   ```cpp
	    if(pairs.count(c))
	   ```
	   
	4. 别忘了检测完出栈哦
	   
	5. 最后检验栈是否为空
	
	   ```cpp
	   return stk.empty();
	   ```
##### 源码（[map方法](https://leetcode-cn.com/problems/valid-parentheses/solution/you-xiao-de-gua-hao-by-leetcode-solution/)）

```cpp
class Solution {
public:
    bool isValid(string s) {

        if(!s.length()) {
            return true;
        }
        
        unordered_map<char, char> pairs = {
            {']','['},
            {'}','{'},
            {')','('}
            
        };

        stack<char> stk;


        for(char c: s) {
            
            if(pairs.count(c)) {
                
                if(stk.empty() || stk.top()!=pairs[c]) {
                    return false;
                }
                stk.pop();

            }
            else {
                stk.push(c);
            }
        }
        return stk.empty();

    }
};
```

##### 源码（[switch方法](https://leetcode.com/problems/valid-parentheses/discuss/9252/2ms-C%2B%2B-sloution)）

```cpp
    class Solution {
    public:
        bool isValid(string s) {

            if(s.empty()) return true;
            if(s.size()%2==1) return false;
            
            stack<char> paren;
            for (char& c : s) {
                switch (c) {
                    case '(': 
                    case '{': 
                    case '[': paren.push(c); break;
                    case ')': if (paren.empty() || paren.top()!='(') return false; else paren.pop(); break;
                    case '}': if (paren.empty() || paren.top()!='{') return false; else paren.pop(); break;
                    case ']': if (paren.empty() || paren.top()!='[') return false; else paren.pop(); break;
                    default: ; // pass
                }
            }
            return paren.empty() ;
        }
    };
```




#### 155.最小栈

> 设计一个可以在 $O(1)$ 时间复杂度内找到栈内**最小元素**的栈结构

##### 双栈方法

- 再开一个栈，名为最小栈，与数据栈并行操作，不同：

1. push时，最小栈只压入当前最小元素
2. 两栈一起pop。
3. getMin直接去最小栈查询。

- 细节

  - 官方题解很憨，最小栈不管什么情况都压入，这样会多出很多重复最小元素，**浪费空间**

    ```cpp
    min_stack.push(min(min_stack.top(), x));
    ```

    

  - 想**节省空间**，在push时做一个判断，利用getMin方法与待入元素做比较，节省**最小栈**的空间

    ```cpp
     void push(int x) {
            data_stack.push(x);
            if(min_stack.empty() || x<=getMin())
                 min_stack.push(x); 
        }
    ```

    

  - 最小栈pop时判断，不pop

    ```cpp
    void pop() {
            if(data_stack.top()==getMin())
                min_stack.pop();
            data_stack.pop();
        }
    ```

##### 双栈法源码

```cpp
class MinStack {
public:
    /** initialize your data structure here. */

    // Two Stacks Method 
    stack<int> data_stack;
    stack<int> min_stack;

    MinStack() {
        min_stack.push(INT_MAX);
    }
    
    void push(int x) {
        data_stack.push(x);
        if(min_stack.empty() || x<=getMin())
             min_stack.push(x); 
    }
    
    void pop() {
        
        if(data_stack.top()==getMin())
            min_stack.pop();
        data_stack.pop();
    }
    
    int top() {
        return data_stack.top();
    }
    
    int getMin() {
        return min_stack.top();
    }
};
```

##### Pair 法

本方法只用**一个栈**，但是**扩大**存入的元素大小

int ----> { int, min_int }

每个元素的**second值**记录当前最小值

题解来源：[fuxuemingzhu](https://leetcode-cn.com/problems/min-stack/solution/zui-yi-dong-yi-ge-zhan-tong-shi-bao-cun-dang-qian-/)

```cpp
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
    }
    
    void push(int x) {
        if (st.size() == 0) {
            st.push({x, x});
        } else {
            st.push({x, min(x, st.top().second)});
        }
    }
    
    void pop() {
        st.pop();
    }
    
    int top() {
        return st.top().first;
    }
    
    int getMin() {
        return st.top().second;
    }
private:
    stack<pair<int, int>> st;
};
```



#### 622.设计循环队列  &  641. 设计双向循环队列

> **循环队列**，故名思义，就是**头尾相接**的数组/链表等**基础数据结构** 为基础实现的队列结构



##### 链表方法

不如数组的下标可以利用**复杂的数关系**那样的 tricky

链表法在实现时，是比较容易思考的，因为链表的基本操作完全是是线性的

以下是我个人思考链表题时的过程：(分函数考虑)

```flow
st=>start: 开始
generic=>operation: 考虑一般情况
boundary=>operation: 考虑边界情况
pianting=>operation: 画图
pa=>operation: 再画图
code=>operation: 写代码
st->generic->pianting->boundary(right)->pa(right)->code(right)->generic
```

##### 细节：

 1. 注意边界的检查，即插入第一个元素时，控制首尾指针的行为

 2. 插入顺序：

    ```cpp
    newnode ->next = temp;
    rear -> next = head;           
    ```
##### 源码：

```cpp
struct LinkedNode {
    int val;
    LinkedNode *next;

    LinkedNode(int val){
        val = val;
        next = nullptr;
    }
};

class MyCircularQueue {

    // This implementation is based on Linked List
private:
    int size,capacity;
    ListNode* head,*rear;
    
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        // the head as a dummy node
        size = 0;
        head =nullptr;
        
        rear = nullptr;
        
        capacity = k; 
    }
    
    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if(!isFull()) {

                ListNode* newnode =new ListNode(value), 
                *temp = head;

            		if(isEmpty()) {
                    rear = newnode;
                }

                head = newnode;
                newnode ->next = temp;
                rear -> next = head;
                
                size++;

                return true;
        }
        
        return false;

    }
    
    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if(!isEmpty()) {
            ListNode* temp = head;
          
           while(temp->next !=rear) {
               temp= temp->next;
           }

            //kill
            temp ->next = head;
            rear = temp;

            size--;
            return true;

        }
        return  false;
        
    }
    
    /** Get the front item from the queue. */
    int Front() {
       return isEmpty()? -1 : this->rear->val;
    }
    
    /** Get the last item from the queue. */
    int Rear() {
        return isEmpty()? -1 : this->head->val;
    }
    
    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        return size == 0;
    }
    
    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        return size == capacity;
    }
};


```



#### 用链表设计Deque



- 第一次想着：是不是把上面那道题的代码copy过来就行了，然而我过于天真，有以下几点问题：

  - 插入第一个元素：要使得**头尾指针同时指向**一个元素。

   ```cpp
  if(isEmpty()) {
    	head = newnode;
      rear = newnode;            
  }
   ```

  - 删除第一个元素：要恢复头尾指针到空指针：

  ```cpp
   if(rear == head) {
      rear = nullptr;
      head = nullptr;
      size--;
      return true;
     }
  ```

  - 临时指针到判空（前后插入都要，这里只给出前插入）

  ```cpp
  bool insertFront(int value) {
  	if(!isFull()) {
  
                  LinkedNode* newnode = new LinkedNode(value),
                  *temp = head;
  
                  if(isEmpty()) {
                      head = newnode;
                      rear = newnode;
                  }
  
  
                  head = newnode;
     							// 必须判空，不然前插入后插入会使得循环链表断开
                  if(temp) newnode ->next = temp;
                  rear -> next = head;
                  
                  size++;
  
                  return true;
          }
  }
  ```

  

##### 源码

```cpp
struct LinkedNode {
    int val;
    LinkedNode *next;
   

    LinkedNode(int val){
        this->val = val;
        next = nullptr;
       
    }
};

class MyCircularDeque {
private:
    LinkedNode* head,*rear;
    int size,capacity;

public:
    /** Initialize your data structure here. Set the size of the deque to be k. */

    MyCircularDeque(int k) {
       
        head = nullptr;
        rear = nullptr;
        size = 0;
        capacity = k;
    }
    
    /** Adds an item at the front of Deque. Return true if the operation is successful. */
    bool insertFront(int value) {
        
        if(!isFull()) {

                LinkedNode* newnode = new LinkedNode(value),
                *temp = head;

                if(isEmpty()) {
                    head = newnode;
                    rear = newnode;
                }


                head = newnode;
          			// 必须判空，不然前插入后插入会使得循环链表断开
                if(temp) newnode ->next = temp;
                rear -> next = head;
                
                size++;

                return true;
        }
        
        return false;
    }
    
    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value) {
              if(!isFull()) {
                
                LinkedNode* newnode =new LinkedNode(value),
                *temp = rear;

                if(isEmpty()) {
                    head = newnode;
                    rear = newnode;
                    
                }

                rear = newnode;
                // 必须判空，不然前插入后插入会使得循环链表断开
                if(temp) temp->next = rear;
                rear->next = head ;
                

                size++;
                return true;

        }
        
        return false;
    }
    
    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
    bool deleteFront() {
             if(!isEmpty()) {
                 
                 if(rear == head) {
                    rear = nullptr;
                    head = nullptr;
                     size--;
                     return true;
                 }
                 
                 head = head -> next;
                 rear -> next = head;
                 size--;
                 return true;
                
        }
        return  false;
    }
    
    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast() {

           if(!isEmpty()) {
               
            LinkedNode* temp = head;
           // maintain_rear(rear);
               if(rear == head) {
                  rear = nullptr;
                  head = nullptr;
                   size--;
                   return true;
               }
               
           while(temp->next != rear) {
               temp = temp->next;
           }

            //kill
            temp ->next = head;
            rear = temp;

            size--;
            return true;

        }
        return  false;
        
    }
    
    /** Get the front item from the deque. */
    int getFront() {
        return isEmpty()?-1:head->val;
    }
    
    /** Get the last item from the deque. */
    int getRear() {
        return isEmpty()?-1:rear->val;
    }
    
    /** Checks whether the circular deque is empty or not. */
    bool isEmpty() {
        return  size == 0;
    }
    
    /** Checks whether the circular deque is full or not. */
    bool isFull() {
        return  size == capacity ;

    }

};
```

#### 数组方法（只给出单向循环队列）

##### 图解（TODO）



##### 源码

```cpp
class MyCircularQueue {

    /*
        This is the implementation based on array

    */
private:
    int size,head, rear;
    int * queue;
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    
    MyCircularQueue(int k) :size(k+1),head(0),rear(0){
        // ***********detail***********
        queue = new  int[k+1];
    }
    
    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if(!isFull()){
            queue[rear]=value;
            rear = (rear+1) % size;
            return true;
        }
        return false;
    }
    
    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if(!isEmpty()) {
            head  = (head + 1) % size;
            return true;
        }
        
        return false;
    }
    
    /** Get the front item from the queue. */
    int Front() {
        return isEmpty()?-1:queue[head];
    }
    
    /** Get the last item from the queue. */
    int Rear() {

        // ***********detail***********
        return isEmpty()?-1:queue[(rear-1+size)%size];
    }
    
    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        return rear == head;
    }
    
    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        // ***********detail***********
        return (rear+1)%size==head;
    }
};
```



## 参考

1. [Leetcode 官方题解](https://leetcode-cn.com/problems/valid-parentheses/solution/you-xiao-de-gua-hao-by-leetcode-solution/)
2. [外国老哥的神奇题解](https://leetcode.com/problems/valid-parentheses/discuss/9252/2ms-C%2B%2B-sloution)
3. [单栈法题解](https://leetcode-cn.com/problems/min-stack/solution/zui-yi-dong-yi-ge-zhan-tong-shi-bao-cun-dang-qian-/)





