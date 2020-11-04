class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        if(!head) return {};
        // if(!head->next) return {head->val};


        head = reverse(head);
        vector<int> ans;
        while(head) {
            ans.push_back(head->val);
            head = head ->next;
        }
        return ans;
    }
    ListNode* reverse(ListNode* head) {
        if(!head->next) return head;
        ListNode* prev = nullptr,*curr = head;

        while(curr) {
            ListNode* tmp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = tmp;

        }
        return prev;
    }
};
