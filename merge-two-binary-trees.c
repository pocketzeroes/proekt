typedef struct TreeNode TreeNode;
TreeNode*newTreeNode(int v)
{
  TreeNode*res=malloc(sizeof(TreeNode));
  res->val   = v;
  res->left  = NULL;
  res->right = NULL;
  return res;
}
TreeNode*mergeTrees(TreeNode*t1, TreeNode*t2){
  TreeNode* p1;
  TreeNode* p2;
  TreeNode* p;
  if ((t1==NULL)&&(t2==NULL)) return NULL;
  p = newTreeNode(0);
  if (t1!=NULL) p->val+=t1->val;
  if (t2!=NULL) p->val+=t2->val;
  if (t1==NULL) p1=NULL;
  else p1=t1->left;
  if (t2==NULL) p2=NULL;
  else p2=t2->left;
  p->left=mergeTrees(p1,p2);
  if (t1==NULL) p1=NULL;
  else p1=t1->right;
  if (t2==NULL) p2=NULL;
  else p2=t2->right;
  p->right=mergeTrees(p1,p2);
  return p;
}
