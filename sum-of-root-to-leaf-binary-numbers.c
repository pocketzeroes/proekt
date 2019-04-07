typedef struct TreeNode TreeNode;
enum{ mod = 1000000007};

void go(int*ans, int cur, TreeNode*v){
    if(v->left == NULL && v->right == NULL){
        *ans = (*ans + cur) % mod;
        return;
    }
    if (v->left != NULL)
        go(ans, (cur * 2 + v->left->val) % mod, v->left);
    if (v->right != NULL)
        go(ans, (cur * 2 + v->right->val) % mod, v->right);
}
int sumRootToLeaf(TreeNode*root){
    int ans = 0;
    go(&ans, root->val, root);
    return ans;
}
