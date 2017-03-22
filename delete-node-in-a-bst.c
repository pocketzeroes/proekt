#define nullptr NULL
typedef struct TreeNode TreeNode;
TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) {
        return nullptr;
    } 
    if (root->val > key) {
        root->left = deleteNode(root->left, key);
    } else if (root->val < key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (!root->left) {
            TreeNode* right = root->right;
            free( root);
            return right;
        } else if (!root->right) {
            TreeNode* left = root->left;
            free( root);
            return left;
        } else {
            TreeNode* successor = root->right;
            while (successor->left) {
                successor = successor->left;
            }
            root->val = successor->val;
            root->right = deleteNode(root->right, successor->val);
        }
    }
    return root;
}
