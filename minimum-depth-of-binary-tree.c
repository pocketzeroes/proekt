#define MIN(a,b) (((a)<(b))?(a):(b))
typedef struct TreeNode TreeNode;

int _helper(TreeNode*root){
    if( root == NULL)
        return INT_MAX;
    if( root->left == NULL && root->right == NULL )
        return 1;
    int help1=_helper(root->left);
    int help2=_helper(root->right);
    return MIN(help1 , help2 ) + 1;
}

int minDepth(TreeNode*root){
    if( root == NULL) 
        return 0;
    return _helper(root);
}

