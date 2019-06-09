typedef struct TreeNode TreeNode;

TreeNode*sufficientSubset(TreeNode*root, int limit){
    if(root->left == root->right)
        return root->val < limit ? NULL : root;
    if(root->left)
        root->left = sufficientSubset(root->left, limit - root->val);
    if(root->right)
        root->right = sufficientSubset(root->right, limit - root->val);
    return root->left == root->right ? NULL : root;
}
