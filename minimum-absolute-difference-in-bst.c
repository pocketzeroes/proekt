#define MIN(a,b) (((a)<(b))?(a):(b))
typedef struct TreeNode   TreeNode;
void inorderTraversal(TreeNode *root, TreeNode **prev, int *result) {
    if (!root) 
        return;
    inorderTraversal(root->left, prev, result);
    if (*prev) 
        *result = MIN(*result, root->val - (*prev)->val);
    *prev = root;
    inorderTraversal(root->right, prev, result);
}
int getMinimumDifference(TreeNode* root) {
    int result = INT_MAX;
    TreeNode *prev = NULL;
    inorderTraversal(root, &prev, &result);
    return result;
}
