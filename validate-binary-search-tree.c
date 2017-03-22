typedef struct TreeNode TreeNode;
bool isValBST(TreeNode* root, TreeNode* minNode, TreeNode* maxNode) {
    if(!root) return true;
    if(minNode && root->val <= minNode->val || maxNode && root->val >= maxNode->val)
        return false;
    return isValBST(root->left, minNode, root) && isValBST(root->right, root, maxNode);
}

bool isValidBST(TreeNode* root) {
    return isValBST(root, NULL, NULL);
}
