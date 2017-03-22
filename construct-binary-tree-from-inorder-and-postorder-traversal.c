typedef struct TreeNode TreeNode;

TreeNode*newTreeNode(int v)
{
    TreeNode*res=malloc(sizeof(TreeNode));
    res->val   = v;
    res->left  = NULL;
    res->right = NULL;
    return res;
}

TreeNode*buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
    int size        = inorderSize;
    TreeNode** path = (TreeNode**)malloc(sizeof(TreeNode*)*(size + 1));
    TreeNode* dummy = newTreeNode(0xDEADBEEF);
    path[0]         = dummy;
    TreeNode* root  = dummy;
    int pathIdx     = 0;
    int inIdx       = size - 1;
    int postIdx     = size - 1;
    while(postIdx >= 0){
        if(path[pathIdx]->val == inorder[inIdx]){
            root = path[pathIdx];
            pathIdx--;
            inIdx--;
        }
        else{
            TreeNode* head= newTreeNode(0);
            TreeNode* node = head;
            while(postorder[postIdx] != inorder[inIdx]){
                node->right = newTreeNode(postorder[postIdx]);
                postIdx--;
                node = node->right;
                path[++pathIdx] = node;
            }
            node->right = newTreeNode(postorder[postIdx]);
            node = node->right;
            path[++pathIdx] = node;
            postIdx--;
            root->left = head->right;
            free(head);
            head=NULL;
        }
    }
    return dummy->left;
}
