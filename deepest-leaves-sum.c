typedef struct TreeNode TreeNode;
int s[10005],m;
void dfs(TreeNode*root, int d){
    if(root==NULL)
        return;
    m = fmax(m,d);
    s[d]+=root->val;
    dfs(root->left,d+1);
    dfs(root->right,d+1);
}
int deepestLeavesSum(TreeNode* root) {
    memset(s,0,sizeof(s));
    m=0;
    dfs(root,0);
    return s[m];
}
