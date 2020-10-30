class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        //iteration
        stack<TreeNode*> st;
        vector<int> result;
        st.push(root);
        while(!st.empty()){
            TreeNode* node =st.pop();
           // st.pop();
            if(node!=NULL)
                result.push_back(node->val);
            else
                continue;
            st.push(node->right);
            st.push(node->left);
        }

        return result;
    }
};
