class Solution {
private:
        vector<int> rs;
public:
    vector<int> inorderTraversal(TreeNode* root) {
    
         dfs(root);
         return rs;
    }
    void dfs(TreeNode* root) {
        if(!root)return;

        dfs(root->left);
        rs.push_back(root->val);
        dfs(root->right);
    }
};
