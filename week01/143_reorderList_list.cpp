
class Solution {
public:
    void reorderList(ListNode* head) {
       // transform into sequential structure
        if(!head) return;

        vector<ListNode*> list;
        while(head) {
            list.push_back(head);
            head=head->next;
        }
        
        int i=0,j=list.size() - 1;

        while(i<j) {

            list[i]->next  =list[j];
            i++;
            //偶数个节点会提前相遇
            if(i==j) break;

            list[j]->next  =list[i];
            j--;

        }
        list[i]->next  =nullptr;
    }

};
