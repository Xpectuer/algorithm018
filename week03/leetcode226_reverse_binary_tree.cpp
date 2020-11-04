class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return root;
        dfs(root);
        return root;
    }
    void dfs(TreeNode* root) {
        if(!root) return;
        
        dfs(root->left);    
       
        dfs(root->right);
         // operation
        TreeNode* tmp = root ->left;
        root->left = root ->right;
        root->right = tmp;
    }
};
