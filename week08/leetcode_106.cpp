// RUNTIME ERROR
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    unordered_map<int, int> map;
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(!inorder.size()||!postorder.size()) return nullptr;
        
        for(int i = 0; i < inorder.size(); i++) 
            map[inorder[i]] =  i;
        
        return build(inorder, postorder);
        
    }
    TreeNode* build(vector<int> inorder, vector<int> postorder) {
        
                
        int i_root = postorder[postorder.size()-1];
        cout<<i_root<<endl;
        TreeNode* node = new TreeNode(i_root);
        if (postorder.size() == 1) return node;
        
        int pivot = map[i_root];
        
        vector<int> left_inorder(inorder.begin(), inorder.begin() + pivot);
        vector<int> right_inorder(inorder.begin() + pivot + 1, inorder.end() );
        
        postorder.resize(postorder.size()-1);
        
        vector<int> left_postorder = vector<int>(postorder.begin(), postorder.begin() + left_inorder.size());
        vector<int> right_postorder = vector<int>(postorder.begin()+ left_inorder.size(), postorder.end());
        
        
         // 日志
        cout << "----------" << endl;
        
        // cout << "map:";
        // for(auto &m : map) 
        //     cout << m.first << ":"<<m.second << endl;

        cout << "leftInorder :";
        for (int i : left_inorder) {
            cout << i << " ";
        }
        cout << endl;

        cout << "rightInorder :";
        for (int i : right_inorder) {
            cout << i << " ";
        }
        cout << endl;

        cout << "leftPostorder :";
        for (int i : left_postorder) {
            cout << i << " ";
        }
        cout << endl;
         cout << "rightPostorder :";
        for (int i : right_postorder) {
            cout << i << " ";
        }
        cout << endl;

        
        node->left = build(left_inorder, left_postorder);
        node->right = build(right_inorder, right_postorder);
        
        return node;
        
    }
};


