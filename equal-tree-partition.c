typedef struct TreeNode TreeNode;
bool res;
int get_sum(TreeNode* node) {
    if (!node)
        return 0;
    return node->val + get_sum(node->left) + get_sum(node->right);
}
int get_sum2(TreeNode* node, int t) {
    if (!node)
        return 0;
    int s = node->val + get_sum2(node->left, t) + get_sum2(node->right, t);
    if (s == t)
        res = true;
    return s;
}
bool checkEqualTree(TreeNode* root) {
    if (root->left == NULL && root->right == NULL && root->val == 0)
        return false;
    int sum = get_sum(root);
    if (sum % 2)
        return false;
    res = false;
    get_sum2(root, sum / 2);
    return res;
}
