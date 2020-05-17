typedef struct TreeNode TreeNode;

int dfs(TreeNode*root, int upp){
    if(root == NULL)
        return 0;
    int ret = root -> val >= upp;
    upp = fmax(upp, root -> val);
    ret += dfs(root -> left, upp);
    ret += dfs(root -> right, upp);
    return ret;
}
int goodNodes(TreeNode*root){
    return dfs(root, INT_MIN);
}
