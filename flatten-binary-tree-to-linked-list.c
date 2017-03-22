typedef struct TreeNode TreeNode;
TreeNode *p;
void flatten(TreeNode*root){
    if(!root)
        return;
    p = root;
    flatten(root->left);
    p->right = root->right;
    flatten(root->right);
    if(root->left) {
        root->right = root->left;
        root->left = NULL;
    }
}
