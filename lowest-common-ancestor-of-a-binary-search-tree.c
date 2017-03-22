inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

typedef struct TreeNode TreeNode;
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    auto s = min(p->val, q->val);
    auto b = max(p->val, q->val);
    while (root->val < s || root->val > b) {
        root = s <= root->val ? root->left : root->right;
    }
    return root;   
}
