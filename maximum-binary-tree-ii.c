typedef struct TreeNode TreeNode;
TreeNode*newTreeNode(int v){
    TreeNode*res=malloc(sizeof(TreeNode));
    res->val   = v;
    res->left  = NULL;
    res->right = NULL;
    return res;
}

TreeNode *dfs(TreeNode *p, int val) {
    if (p->val > val) {
        if (p->right == NULL) {
            p->right = newTreeNode(val);
            return p;
        }
        p->right = dfs(p->right, val);
        return p;
    }
    else {
        TreeNode *root = newTreeNode(val);
        root->left = p;
        return root;
    }
}
TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
    return dfs(root, val);
}
