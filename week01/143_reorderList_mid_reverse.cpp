class Solution {
public:
    void reorderList(ListNode* head) {
        if(head==nullptr||head->next==nullptr)
            return;
        ListNode* mid = getMid(head);

        ListNode* l1 = head;
        ListNode* l2 = mid->next;
        mid->next = nullptr;
        l2 = reverseList(l2);

        mergeList(l1,l2);
    }

private:
    ListNode* getMid(ListNode* head){
        ListNode* slow=head,*fast=head;

        while(fast->next!=nullptr && fast->next->next!=nullptr){
            slow=slow->next;
            fast=fast->next->next;
        }
        return slow;
    }

    ListNode* reverseList(ListNode* head) {
        
        ListNode* prev=nullptr,* curr=head,*currTemp=nullptr;
        

        while(curr!=nullptr){
            currTemp = curr->next; 
            curr->next = prev;
            prev=curr;
            curr = currTemp;
        }

        return prev;

    }
   void mergeList(ListNode* head,ListNode* mid) {
        ListNode* l1=head,*l2 =mid;
        ListNode* l1Tmp,*l2Tmp;
        while(l2&&l1){
            //insert
            l1Tmp = l1->next;
            l2Tmp =l2->next;

            l2->next=l1->next;
            l1->next = l2;

            l2 =l2Tmp;
            l1 = l1Tmp;
        }
       

    }


};
