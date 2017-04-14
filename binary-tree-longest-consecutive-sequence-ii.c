typedef struct pair{
    int first;
    int second;
}pii;
pii newPair(int a, int b){
    pii rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
typedef struct TreeNode TreeNode;
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int ans;
pii dfs(TreeNode *c)
{
    if(!c)
        return newPair(0, 0);
    pii la = dfs(c->left), ra = dfs(c->right);
    int d = 1, u = 1;
    if(c->left  && c->left ->val + 1 == c->val) d = max(d, 1 + la.first );
    if(c->right && c->right->val + 1 == c->val) d = max(d, 1 + ra.first );
    if(c->left  && c->left ->val - 1 == c->val) u = max(u, 1 + la.second);
    if(c->right && c->right->val - 1 == c->val) u = max(u, 1 + ra.second);
    ans = max(ans, d + u - 1);
    return newPair(d, u);
}
int longestConsecutive(TreeNode* root) {
    ans = 0;
    dfs(root);
    return ans;
}
