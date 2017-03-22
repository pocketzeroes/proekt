typedef struct TreeNode TreeNode;
int pathSumHelper(TreeNode* root, int prev, int sum) {
    if (!root) 
        return 0;
    int curr = prev + root->val;
    return (curr == sum) + pathSumHelper(root->left, curr, sum) + pathSumHelper(root->right, curr, sum);
}
int pathSum(TreeNode* root, int sum) {
    if (!root) 
        return 0;
    return pathSumHelper(root, 0, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
}
