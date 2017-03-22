#if DEBUG_ON
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#endif
typedef struct TreeNode TreeNode;

int cur_sum = 0;
void travel(TreeNode* root){
    if (!root) return;
    if (root->right) travel(root->right);
    root->val = (cur_sum += root->val);
    if (root->left) travel(root->left);
}
TreeNode* convertBST(TreeNode* root) {
    cur_sum = 0;
    travel(root);
    return root;
}
