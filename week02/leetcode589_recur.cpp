class Solution {
    vector<int> rs;
public:
    vector<int> preorder(Node* root) {
        dfs(root);
        return rs;
    }
    void dfs(Node* root) {
        if(!root) return;
        rs.push_back(root->val);
        for(Node* node:root->children) {
            dfs(node);
        }
    }
};
