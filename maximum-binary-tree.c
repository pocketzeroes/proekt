#if TREE_DEBUG
struct TreeNode {
    int              val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#endif
typedef struct TreeNode TreeNode;

TreeNode*newTreeNode(int v){
    TreeNode*res=malloc(sizeof(TreeNode));
    res->val   = v;
    res->left  = NULL;
    res->right = NULL;
    return res;
}
//////
TreeNode*build(int l, int r, int*nums){
    if (l > r)
        return NULL;
    int tar = l;
    for (int i = l; i <= r; ++i)
        if (nums[i] > nums[tar])
            tar = i;
    TreeNode *ret = newTreeNode(nums[tar]);
    ret->left  = build(l, tar-1, nums);
    ret->right = build(tar+1, r, nums);
    return ret;
}
TreeNode*constructMaximumBinaryTree(int*nums, int numsSz){
    int n = numsSz;
    return build(0, n-1, nums);

}
