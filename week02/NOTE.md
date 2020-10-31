







学习笔记

## Java HashMap（Implements Map）

### TIPS:

1. Java 的HashMap实现与Hashtable实现几乎相似，除了两点：
   1. HashMap实现是**线程不安全的**，也就是说，任何多线程修改操作都有可能造成脏读。
   2. HashMap **允许存在null值**
2. HashMap **不保证容器内元素的顺序性**，任何插入修改动作，都有可能会破坏元素的顺序。
3. 工程中，当hashmap内的元素需要存放大量元素时，尽量把装载因子（load factor）和容量（capacity）设置得足够大**以降低rehash与扩容的代价。**



### Basics：

1. 底层：一个存取Node<K,V> map类型结构的数组为**底层数据结构**

   ```java
   transient Node<K,V>[] table;

   ```

2. HashMap的实现，提供$O(1)$ 时间复杂度的基本操作，它们包括：

   1. get()
   2. put()

   > $O(1):$ 这建立在假定**Hash函数**，也就是**散列函数**，能够把元素很好地分散在每个桶中（不产生hash冲突），

3. 遍历器（iterator）对于HashMap的遍历，**其所需要的时间**与HashMap的总容量（capacity）成比例。

   $Time\ for\ Iteration \propto Capacity$

   > 因此，我们不能把HashMap的初始大小（capacity）设置的太高，以免性能受挫。

4. 装载因子（load factor）：装载因子是一个阈值，它的意义在于**判断何时调用HashMap容量增长**的方法。当容量达到$ load\ factor*capacity$ 时，自动启动扩容方法。

   > E.g. : 
   >
   > 我们假定 $load factor = 0.8 ,capacity = 10 $，那么我们在hashmap内元素量达到 $8$ 时，启动扩容，增大**capacity**为原来的2倍**；并且需要做**rehash操作，也就是重构每个桶的hash值，使其能够适应新的capacity

   1. 默认的$load\ factor =0.75$ 为用户提供很好的**时空复杂度平衡**。

5. 更高的$load\ factor$ 使得HashMap的空间复杂度下降，但是付出相应的 时间复杂度代价（时空平衡）

   1. 工程中，应该考虑 合适的 $load factor $ 与 $capacity$ 的值，来降低 rehashing 所带来的代价。（这两个参数能在构造方法中调整）
   2. HashMap的capacity一定是2的幂，这是为了在一定程度上降低hash冲突的概率，并降低 rehashing 的成本。

6. 关于**线程安全**：HashMap实现不保证线程同步，因此当多个线程访问同一个HashMap实例时，必须在外部同步线程（比如在方法体上加上 ***synchronized*** ），才能实现修改的**structurality**（所谓structural，没怎么看懂，多线程还是要，学习一个。学完回来看，原文贴在这）。

> A structural modification is any operation that adds or deletes one or more mappings; merely changing the value associated with a key that an instance already contains is not a structural modification.
>
> <p>The iterators returned by all of this class's "collection view methods"
>  * are <i>fail-fast</i>: if the map is structurally modified at any time after
>  * the iterator is created, in any way except through the iterator's own
>  * <tt>remove</tt> method, the iterator will throw a
>  * {@link ConcurrentModificationException}.  Thus, in the face of concurrent
>  * modification, the iterator fails quickly and cleanly, rather than risking
>  * arbitrary, non-deterministic behavior at an undetermined time in the
>  * future.
>  *
>  * <p>Note that the fail-fast behavior of an iterator cannot be guaranteed
>  * as it is, generally speaking, impossible to make any hard guarantees in the
>  * presence of unsynchronized concurrent modification.  Fail-fast iterators
>  * throw <tt>ConcurrentModificationException</tt> on a best-effort basis.
>  * Therefore, it would be wrong to write a program that depended on this
>  * exception for its correctness: <i>the fail-fast behavior of iterators
>   should be used only to detect bugs.</i> 

5. hash冲突的解决方案：学过基本的哈希表都知道，hash冲突的解决方案，在工程实践中，是一个Robust的hash表的必备功能。传统的方案基本上可以分为两种：

   1. **链表法**（[Separate chaining linked lists](https://en.wikipedia.org/wiki/Hash_table#Collision_resolution)），在冲突位置构成链表，用链表延伸的方式，来解决hash冲突

   2. **Open addressing**：hash表在有hash冲突之前，hash值唯一确定一个key值；可以认为，**key值像有编号的囚犯一样被囚禁在相应hash值的牢房里**。我们现在引入这个方案，如果“牢房”里有囚犯，**我们就换一间空牢房关押新囚犯**。

      ​	我们来看看HashMap的**解决方案**：

   3. 本质地讲，HashMap的方案是链表法的延伸，它为了改善链表低效的 $O(n)$ 访问时间复杂度，引入**平衡树**（AVL Tree）来**保证其访问复杂度在 $O(logn)$** ，以保证其访问高效性。
   
   4. 由于用 **AVL树** 解决 hash冲突的方案会导致节点空间占用，因此HashMap在为解决hash冲突的方案，或者说方法，制定了一个**阈值**（*TREEIFY_THRESHOLD*） ，当hashmap的某个桶内元素（binCount）**达到阈值**时，启动这套方案。
   
      当hashmap的某个桶内元素（binCount）**低于**阈值（**注意：**这里是另一个常量 *UNTREEIFY_THRESHOLD* ），恢复成原来的**链表法**（Separate chaining Linked List）
   
      <img src="/Users/alex/Desktop/2020Courses/algoTraining/algorithm018/week02/Part2  2.png" alt="treeify" style="zoom:33%;" />

### 重要方法





1. treeifyBin( )

   ```java
   // 此方法用于当桶内元素过多时，treeify 来优化访问时间复杂度   
   final void treeifyBin(Node<K,V>[] tab, int hash) {
           int n, index; Node<K,V> e;
        		// 桶数目小于阈值 或者 桶为空，则扩大桶的数目
           if (tab == null || (n = tab.length) < MIN_TREEIFY_CAPACITY)
               resize();
        		
           else if ((e = tab[index = (n - 1) & hash]) != null) {
               TreeNode<K,V> hd = null, tl = null;
               do {
                 // 将链表节点转化为红黑树节点
                   TreeNode<K,V> p = replacementTreeNode(e, null);
                 
                   if (tl == null)
                       hd = p;
                   else {
                       p.prev = tl;
                       tl.next = p;
                   }
                   tl = p;
               } while ((e = e.next) != null);
             
               if ((tab[index] = hd) != null)
                   hd.treeify(tab);
           }
       }
   ```

   

   1. treeify( )

   ```java
       /**
       			
            * Forms tree of the nodes linked from this node.
            * @return root of tree
            */
           final void treeify(Node<K,V>[] tab) {
               TreeNode<K,V> root = null;
               for (TreeNode<K,V> x = this, next; x != null; x = next) {
                   next = (TreeNode<K,V>)x.next;
                   x.left = x.right = null;
                   if (root == null) {
                       x.parent = null;
                       x.red = false;
                       root = x;
                   }
                   else {
                       K k = x.key;
                       int h = x.hash;
                       Class<?> kc = null;
                       for (TreeNode<K,V> p = root;;) {
                           int dir, ph;
                           K pk = p.key;
                           if ((ph = p.hash) > h)
                               dir = -1;
                           else if (ph < h)
                               dir = 1;
                           else if ((kc == null &&
                                     (kc = comparableClassFor(k)) == null) ||
                                    (dir = compareComparables(kc, k, pk)) == 0)
                               dir = tieBreakOrder(k, pk);
   
                           TreeNode<K,V> xp = p;
                           if ((p = (dir <= 0) ? p.left : p.right) == null) {
                               x.parent = xp;
                               if (dir <= 0)
                                   xp.left = x;
                               else
                                   xp.right = x;
                               root = balanceInsertion(root, x);
                               break;
                           }
                       }
                   }
               }
               moveRootToFront(tab, root);
           }
   ```

   

   

2. put  (K key, V value )

   ```java
    public V put(K key, V value) {
           return putVal(hash(key), key, value, false, true);
       }
   ```

   1. putVal( )

      ```java
       /**
           * Implements Map.put and related methods
           *
           * @param hash hash for key
           * @param key the key
           * @param value the value to put
           * @param onlyIfAbsent if true, don't change existing value
           * @param evict if false, the table is in creation mode.
           * @return previous value, or null if none
           */
          final V putVal(int hash, K key, V value, boolean onlyIfAbsent,
                         boolean evict) {
            	// tab是容器底层的节点数组  n 是table的容量 
              Node<K,V>[] tab; Node<K,V> p; int n, i;
              if ((tab = table) == null || (n = tab.length) == 0)
                	// 若底层table为空，即第一次调用，初始化table，更新n的值，并更新Threshold
                  n = (tab = resize()).length;
              if ((p = tab[i = (n - 1) & hash]) == null)
                	// 如果对应桶内为空，则拷贝一个新node并放入
                  tab[i] = newNode(hash, key, value, null);
              else {
                	
                  Node<K,V> e; K k;
                	// 如果发生hash冲突，并且key相同，拿到新的value值，准备替换旧value
                  if (p.hash == hash &&
                      ((k = p.key) == key || (key != null && key.equals(k))))
                      e = p;
                	// Treeify的实现
                  else if (p instanceof TreeNode)
                    	
                      e = ((TreeNode<K,V>)p).putTreeVal(this, tab, hash, key, value);
                // hash值冲突，key不同，则启动hash冲突解决方案：linked list 或是 AVL Tree，并把新的key
                  else {
                		
                      for (int binCount = 0; ; ++binCount) {
                          if ((e = p.next) == null) {
                              p.next = newNode(hash, key, value, null);
                            	// 桶内元素超过阈值，把桶内转化成AVL树,这里用红黑树实现
                              if (binCount >= TREEIFY_THRESHOLD - 1) // -1 for 1st
                                  treeifyBin(tab, hash);
                              break;
                          }
                        	// key值相同退出循环遍历
                          if (e.hash == hash &&
                              ((k = e.key) == key || (key != null && key.equals(k))))
                              break;
                          p = e;
                      }
                  }
                  if (e != null) { // existing mapping for key
                      V oldValue = e.value;
                    // 为相同key的节点更新value值  如果onlyIfAbsent为true，不更新
                      if (!onlyIfAbsent || oldValue == null)
                          e.value = value;
                     // 空方法，留给LinkedHashMap重写用
                      afterNodeAccess(e);
                    // 返回旧的 value 
                      return oldValue;
                  }
              }
            	// 更新修改次数
              ++modCount;
            	// 若大于桶的数量 承载因子*容量 扩容
              if (++size > threshold)
                  resize();
            	
              afterNodeInsertion(evict);
              return null;
          }
      ```

      

