int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
typedef struct TreeNode TreeNode;
int ret;

void dfs(TreeNode*cur, int mx, int mn){
    if(cur == NULL)
        return;
    ret = max(ret, abs(mx - cur->val));
    ret = max(ret, abs(mn - cur->val));
    dfs(cur->left , max(mx, cur->val), min(mn, cur->val));
    dfs(cur->right, max(mx, cur->val), min(mn, cur->val));
}
int maxAncestorDiff(TreeNode*root){
    ret = 0;
    dfs(root, root->val, root->val);
    return ret;
}
