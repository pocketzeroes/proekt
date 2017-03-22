typedef struct TreeNode TreeNode;

TreeNode* first;
TreeNode* second;
TreeNode* prev;

TreeNode*newTreeNode( int v)
{
    TreeNode*res=malloc(sizeof(TreeNode));
    res->val   = v;
    res->left  = NULL;
    res->right = NULL;
    return res;
}

void help(TreeNode* root){
    if(root==NULL)  return;
    help(root->left);
    if(first==NULL && prev->val >= root->val)   first=prev;
    if(first!=NULL && prev->val >= root->val)   second=root;
    prev=root;
    help(root->right);
}

void recoverTree(TreeNode *root) {
    first=NULL;
    second=NULL;
    prev = newTreeNode(INT_MIN);
    help(root);
    int tmp = first->val;
    first->val = second->val;
    second->val = tmp;
}







