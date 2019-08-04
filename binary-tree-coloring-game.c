typedef struct TreeNode TreeNode;

int work(TreeNode* root){
    if(!root)
        return 0;
    return work(root->left)+work(root->right)+1;
}
void dfs(TreeNode*root, int x, int*ls, int*rs){
    if(!root)
        return;
    if(root->val==x){
       *ls=work(root->left);
       *rs=work(root->right);
    }
    else{
        dfs(root->left ,x,ls,rs);
        dfs(root->right,x,ls,rs);
    }
}
bool btreeGameWinningMove(TreeNode*root, int n, int x) {
    int ls,rs;
    dfs(root, x, &ls, &rs);
    return fmax(fmax(ls,rs),n-ls-rs-1)>(n>>1);
}
