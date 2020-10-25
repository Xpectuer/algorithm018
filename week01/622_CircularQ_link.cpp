/*
 * @lc app=leetcode.cn id=622 lang=cpp
 *
 * [622] 设计循环队列
 */

// @lc code=start

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


