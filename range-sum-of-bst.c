typedef struct TreeNode TreeNode;

int dfs(TreeNode*root, int L, int R){
    if(root == NULL)
        return 0;
    return dfs(root->left , L, R) +
           dfs(root->right, L, R) +
           (L <= root->val && root->val <= R ? root->val : 0);
}
int rangeSumBST(TreeNode*root, int L, int R){
    return dfs(root, L, R);
}
