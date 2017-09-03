typedef struct TreeNode TreeNode;

TreeNode*newTreeNode( int v){
    TreeNode*res=malloc(sizeof(TreeNode));
    res->val   = v;
    res->left  = NULL;
    res->right = NULL;
    return res;
}

TreeNode*trimBST(TreeNode*root, int L, int R){
    if (root == NULL ) return NULL;
    if (root->val < L) return trimBST(root->right, L, R);
    if (root->val > R) return trimBST(root->left , L, R);
    TreeNode*cur = newTreeNode(root->val);
    cur->left  = trimBST(root->left,  L, R);
    cur->right = trimBST(root->right, L, R);
    return cur;
}
