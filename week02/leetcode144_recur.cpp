class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> vec;
        traversal(root,vec);
        return vec;
    }
    void traversal(TreeNode* root,vector<int> &vec){
        if(root==NULL){
            return;
        }
        vec.push_back(root->val);
        traversal(root->left,vec);
        traversal(root->right,vec);

    }
};
