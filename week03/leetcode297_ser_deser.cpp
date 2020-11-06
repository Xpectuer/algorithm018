class Codec {
private:
    void serialize(TreeNode* root, ostringstream &os) {
        if(!root) {
            os << "# ";
            return;
        }
        os << root->val << " ";
        serialize(root->left, os);
        serialize(root->right, os);
        
    }
    TreeNode* deserialize(istringstream &in) {
        string val;
        in >> val;
        if(val == "#") return nullptr;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = deserialize(in);
        root->right = deserialize(in);
        return root;
    }
        
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream os;
        serialize(root,os);
        return os.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream  in(data);
        return deserialize(in);
    }

};
