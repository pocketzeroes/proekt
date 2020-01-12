typedef struct TreeNode TreeNode;
int res;
void dfs(TreeNode* n,int p,int pp){
    if(!n)
        return;
    if(pp%2==0)
        res+=n->val;
    dfs(n->left,n->val,p);
    dfs(n->right,n->val,p);
}
int sumEvenGrandparent(TreeNode* root) {
    res=0;
    dfs(root,1,1);
    return res;
}
