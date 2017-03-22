#define MAX(a,b) (((a)>(b))?(a):(b))
int max_sum;
typedef struct TreeNode TreeNode;
int dfs(TreeNode*root){
    if(!root) 
        return 0;
    int l = dfs(root->left);
    int r = dfs(root->right);
    int sum = root->val;
    if(l > 0) 
        sum += l;
    if(r > 0) 
        sum += r;
    max_sum = MAX(max_sum, sum);
    return MAX(r, l) > 0? MAX(r, l) + root->val : root->val;
}

int maxPathSum(TreeNode *root) {
    max_sum = INT_MIN;
    dfs(root);
    return max_sum;
}
