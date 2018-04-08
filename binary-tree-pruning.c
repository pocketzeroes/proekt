typedef struct TreeNode TreeNode;
int sum(TreeNode* x) {
    if (!x) 
        return 0;
    int sl = sum(x->left), 
        sr = sum(x->right);
    if (sl==0) 
        x->left = NULL;
    if (sr==0) 
        x->right = NULL;
    int s = x->val + sl + sr;
    return s;
}
TreeNode*pruneTree(TreeNode*root){
    int s = sum(root);
    if (s==0) 
        return NULL;
    return root;
}
