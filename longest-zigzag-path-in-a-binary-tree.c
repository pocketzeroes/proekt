typedef struct TreeNode TreeNode;
int n,s[50005][2],ans;

int work(TreeNode*root){
    if(root==NULL)
        return 0;
    int x=++n;
    ans=fmax(ans,fmax(s[x][0]=s[work(root->left)][1]+1,s[x][1]=s[work(root->right)][0]+1));
    return x;
}
int longestZigZag(TreeNode*root){
    s[0][0]=s[0][1]=-1;
    ans=n=0;
    work(root);
    return ans;
}
