typedef struct TreeNode TreeNode;

TreeNode**splitBST(TreeNode*root, int V, int*rsz){
    if(root == NULL){
       *rsz = 2;
        return calloc(2, sizeof(TreeNode));
    }
    else if(root->val <= V){
        TreeNode**lr = splitBST(root->right, V, rsz);
        root->right = lr[0];
        lr[0] = root;
        return lr;
    }
    else{
        TreeNode**lr = splitBST(root->left, V, rsz);
        root->left = lr[1];
        lr[1] = root;
        return lr;
    }
}
