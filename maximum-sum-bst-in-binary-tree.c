typedef struct TreeNode TreeNode;
bool b[40005];
int l[40005],r[40005],ma[40005],mi[40005],s[40005],n,ans;

int work(TreeNode*root){
    if(root==NULL)
        return 0;
    int x=++n;
    l[x]=work(root->left);
    r[x]=work(root->right);
    ma[x]=fmax(root->val,fmax(ma[l[x]],ma[r[x]]));
    mi[x]=fmin(root->val,fmin(mi[l[x]],mi[r[x]]));
    s[x]=root->val+s[l[x]]+s[r[x]];
    b[x]=b[l[x]]&&b[r[x]]&&ma[l[x]]<root->val&&mi[r[x]]>root->val;
    if(b[x])
        ans=fmax(ans,s[x]);
    return x;
}
int maxSumBST(TreeNode*root){
    b[0]=1;
    ma[0]=-40000;
    mi[0]=40000;
    n=ans=s[0]=0;
    work(root);
    return ans;
}
