typedef struct TreeNode TreeNode;

void dfs(TreeNode*node, int*acc){
    if(node != NULL){
        dfs(node->right, acc);
        int temp = node->val;
        node->val += *acc;
       *acc += temp;
        dfs(node->left, acc);
    }
}
TreeNode*bstToGst(TreeNode*root){
    int acc = 0;
    dfs(root, &acc);
    return root;
}
