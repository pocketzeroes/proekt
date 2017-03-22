#define MAX(a,b) (((a)>(b))?(a):(b))
typedef struct TreeNode TreeNode;

int checkHeight(TreeNode*root){
    if( root==NULL )
        return 0;
    int left = checkHeight(root->left), right = checkHeight(root->right);
    if( left == -1 || right == -1 )
        return -1;
    if( abs(left - right) > 1 )
        return -1;
    return MAX(left, right) + 1;
}

bool isBalanced(TreeNode*root){
    return checkHeight(root) != -1;
}

