typedef struct TreeNode TreeNode;
int gao(TreeNode* p, int*d) {
    if (p == NULL) {
        return 0;
    }
    else {
        int l = gao(p->left, d), r = gao(p->right, d);
        (*d) += abs(r - l);
        return p->val + l + r;
    }
}
int findTilt(TreeNode* root) {
    int ret = 0;
    gao(root, &ret);
    return ret;
}
