typedef struct TreeNode TreeNode;
TreeNode* invertTree(TreeNode* root) {
    if (root != NULL) {
        TreeNode*tmp=root->left;
        root->left=root->right;
        root->right=tmp;
        invertTree(root->left);
        invertTree(root->right);
    }
    return root;
}
