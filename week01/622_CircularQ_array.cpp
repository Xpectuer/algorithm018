
/*
 * @lc app=leetcode.cn id=622 lang=cpp
 *
 * [622] 设计循环队列
 */

// @lc code=start
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
        queue =new  int[k+1];
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

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
// @lc code=end


