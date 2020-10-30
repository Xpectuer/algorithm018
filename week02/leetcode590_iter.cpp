class Solution {
public:
    vector<int> postorder(Node* root) {
        stack<Node*> stk;
        vector<int> rs;
        if(!root) return rs;
        

        stk.push(root);
        while(!stk.empty()) {
            Node* node = stk.top();
            stk.pop();
            auto it = rs.begin();
            it = rs.insert(it, node->val);
            for(Node* n: node->children) {
                if(n) stk.push(n);
            }
        }
        return rs;
    }
};
