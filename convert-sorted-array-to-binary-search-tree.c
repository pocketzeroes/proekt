typedef struct TreeNode TreeNode;
TreeNode*newTreeNode(int v)
{
    TreeNode*res=malloc(sizeof(TreeNode));
    res->val   = v;
    res->left  = NULL;
    res->right = NULL;
    return res;
}

TreeNode *sortedArrayToBSTHelper(int*nums, int start, int end){
    if (start <= end) {
        TreeNode *node = newTreeNode(nums[start + (end - start) / 2]);
        node->left  = sortedArrayToBSTHelper(nums, start, start + (end - start) / 2 - 1);
        node->right = sortedArrayToBSTHelper(nums, start + (end - start) / 2 + 1,   end);
        return node;
    }
    return NULL;
}
TreeNode*sortedArrayToBST(int*nums, int numsSize){
    return sortedArrayToBSTHelper(nums, 0, numsSize - 1);
}
