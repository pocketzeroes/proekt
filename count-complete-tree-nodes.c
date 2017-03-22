#define nullptr NULL
typedef struct TreeNode TreeNode;
bool exist(TreeNode *root, int n) {
    int k = 1;
    while (k <= n) {
        k <<= 1;
    }
    k >>= 2;
    TreeNode *node = root;
    while (k > 0) {
        if ((n & k) == 0) {
            node = node->left;
        } else {
            node = node->right;
        }
        k >>= 1;
    }
    return node != nullptr;
}
int countNodes(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    TreeNode *node = root;
    int level = 0;
    while (node->left != nullptr) {
        node = node->left;
        ++level;
    }
    int left = pow(2, level), right = pow(2, level + 1);
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (!exist(root, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left - 1;
}
