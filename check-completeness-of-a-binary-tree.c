typedef struct TreeNode TreeNode;

int size(TreeNode*x){
  if(!x)
    return 0;
  return 1 + size(x->left) + size(x->right);
}
bool rec(TreeNode*x, int id, int sz){
  if (!x)
    return sz < id;
  if (sz < id)
    return false;
  return rec(x->left, id*2, sz) && rec(x->right, id*2+1, sz);
}
bool isCompleteTree(TreeNode*root){
  int sz = size(root);
  return rec(root, 1, sz);
}
