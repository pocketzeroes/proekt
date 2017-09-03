typedef struct TreeNode TreeNode;
int val[2] = { -1, -1};
void dfs(TreeNode*t){
    if (t == NULL) 
        return;
    int v = t->val;
    if (val[0] == -1 || val[0] > v){
        val[1] = val[0];
        val[0] = v;
    } 
    else if(val[1] == -1 || val[1] > v){
        if (v != val[0])
            val[1] = v;
    }
    dfs(t->left), dfs(t->right);
}
int findSecondMinimumValue(TreeNode*root){
    val[0]=val[1]=-1;
    dfs(root);
    return val[1];
}
