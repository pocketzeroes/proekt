typedef struct TreeNode TreeNode;
TreeNode*searchBST(TreeNode *root, int val){
    TreeNode*cur = root;
    while ( cur ){
        if ( cur->val == val )
            return cur;
        if ( cur->val > val )
            cur = cur->left;
        else
            cur = cur->right;
    }
    return NULL;
}
