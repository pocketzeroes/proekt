typedef struct TreeNode TreeNode;
typedef long long ll;

typedef struct{
  ll first, second;
}pll;
pll newpll(int a, int b){
  return(pll){a,b};
}
int dfs1(TreeNode*root){
    int s=root->val;
    if(root->left)
        s+=dfs1(root->left);
    if(root->right)
        s+=dfs1(root->right);
    return s;
}
pll dfs2(TreeNode*root, ll s2){
    int s=root->val;
    ll ans=0;
    if(root->left){
        pll a = dfs2(root->left, s2);
        s += a.first;
        ans = fmaxl(a.second, ans);
    }
    if(root->right){
        pll a = dfs2(root->right, s2);
        s += a.first;
        ans = fmaxl(a.second, ans);
    }
    return(pll){s, fmaxl(ans, s*(s2-s))};
}
int maxProduct(TreeNode*root){
    ll s = dfs1(root);
    return dfs2(root, s).second % (1000000007);
}
