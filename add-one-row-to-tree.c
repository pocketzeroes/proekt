typedef struct TreeNode TreeNode ;
TreeNode*newTreeNode(int v)
{
  TreeNode*res=malloc(sizeof(TreeNode));
  res->val   = v;
  res->left  = NULL;
  res->right = NULL;
  return res;
}
void go(TreeNode *root, int cur, int v, int d) {
    if(root == NULL) return;
    if (cur == d-1) {
        TreeNode *nl = newTreeNode(v);
        nl->left = root->left;
        TreeNode *nr = newTreeNode(v);
        nr->right = root->right;
        root->left = nl;
        root->right = nr;
        return;
    } else {
        go(root->left, cur+1, v, d);
        go(root->right, cur+1, v, d);
    }
}
TreeNode* addOneRow(TreeNode* root, int v, int d) {
    if(root == NULL) return root;
    if(d==1) {
        TreeNode *nr = newTreeNode(v);
        nr->left = root;
        return nr;
    } else {
        go(root, 1, v, d);
        return root;
    }
}
