typedef struct TreeNode TreeNode;
typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}

int ret;
pair count(TreeNode* root){
  pair A=newPair(1, root->val);
  if(root->left) {
    pair a=count(root->left);
    A.first+=a.first;
    A.second+=a.second;
  }
  if(root->right) {
    pair a=count(root->right);
    A.first+=a.first;
    A.second+=a.second;
  }
  ret+=abs(A.first-A.second);
  return A;
}
int distributeCoins(TreeNode* root) {
  ret=0;
  count(root);
  return ret;
}
