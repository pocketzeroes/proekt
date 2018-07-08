typedef struct TreeNode TreeNode;
int depth, deepest_nodes;
TreeNode* ans;
void go(TreeNode* r, int h) {
    if (r == NULL)
        return;
    if (h > depth) {
        depth = h;
        deepest_nodes = 1;
    }
    else if (h == depth)
        ++deepest_nodes;
    go(r->left , h + 1);
    go(r->right, h + 1);
}
int og(TreeNode* r, int h) {
    if (r == NULL)
        return 0;
    int x = 0;
    if (h == depth)
        ++x;
    x += og(r->left , h + 1);
    x += og(r->right, h + 1);
    if (x == deepest_nodes)
        if (ans == NULL)
            ans = r;
    return x;
}
TreeNode* subtreeWithAllDeepest(TreeNode* root) {
    if (root == NULL) return NULL;
    depth = -1;
    deepest_nodes = 0;
    go(root, 0);
    ans = NULL;
    og(root, 0);
    return ans;
}
