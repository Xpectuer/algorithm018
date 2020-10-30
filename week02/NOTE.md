学习笔记

## Java HashMap（Implements Map）

### TIPS:

1. Java 的HashMap实现与Hashtable实现几乎相似，除了两点：
   1. HashMap实现是**线程不安全的**，也就是说，任何多线程修改操作都有可能造成脏读。
   2. HashMap **允许存在null值**
2. HashMap **不保证容器内元素的顺序性**，任何插入修改动作，都有可能会破坏元素的顺序。
3. 工程中，当hashmap内的元素需要存放大量元素时，尽量把装载因子（load factor）和容量（capacity）设置得足够大**以降低rehash与扩容的代价。**



### Basics：

1. HashMap的实现，提供$O(1)$ 时间复杂度的基本操作，它们包括：

   1. get()
   2. put()

   > $O(1):$ 这建立在假定**Hash函数**，也就是**散列函数**，能够把元素很好地分散在每个桶中（不产生hash冲突），

2. 遍历器（iterator）对于HashMap的遍历，**其所需要的时间**与HashMap的总容量（capacity）成比例。

   $Time\ for\ Iteration \propto Capacity$

   > 因此，我们不能把HashMap的初始大小（capacity）设置的太高，以免性能受挫。

3. 装载因子（load factor）：装载因子是一个阈值，它的意义在于**判断何时调用HashMap容量增长**的方法。当容量达到$ load\ factor*capacity$ 时，自动启动扩容方法。

   > E.g. : 
   >
   > 我们假定 $load factor = 0.8 ,capacity = 10 $，那么我们在hashmap内元素量达到 $8$ 时，启动扩容，增大**capacity**为原来的2倍**；并且需要做**rehash操作，也就是重构每个桶的hash值，使其能够适应新的capacity

   1. 默认的$load\ factor =0.75$ 为用户提供很好的**时空复杂度平衡**。

   2. 更高的$load\ factor$ 使得HashMap的空间复杂度下降，但是付出相应的 时间复杂度代价（时空平衡）

   3. 工程中，应该考虑 合适的 $load factor $ 与 $capacity$ 的值，来降低 rehashing 所带来的代价。（这两个参数能在构造方法中调整）

      

