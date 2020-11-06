class Solution {
    int max_depth = 0;
public:
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        
        
        return max(maxDepth(root->left),maxDepth(root->right))+1;;
    }
};
