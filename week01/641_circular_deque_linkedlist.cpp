/*
 * @Author: your name
 * @Date: 2020-10-25 12:41:11
 * @LastEditTime: 2020-10-25 22:27:22
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /.leetcode/641.设计循环双端队列.cpp
 */
/*
 * @lc app=leetcode.cn id=641 lang=cpp
 *
 * [641] 设计循环双端队列
 */

// @lc code=start





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

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
// @lc code=end


