typedef struct TreeNode TreeNode;
TreeNode*newTreeNode(int v){
    TreeNode*res=malloc(sizeof(TreeNode));
    res->val   = v;
    res->left  = NULL;
    res->right = NULL;
    return res;
}

TreeNode*insertIntoBST(TreeNode *node, int val){
    if (!node) {
        TreeNode *newNode = newTreeNode(val);
        return newNode;
    }
    if (val < node->val)
        node->left = insertIntoBST(node->left, val);
    else
        node->right = insertIntoBST(node->right, val);
    return node;
}
