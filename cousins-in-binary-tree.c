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

pair x_info, y_info;
void dfs(TreeNode*node, int x, int y, int depth, int parent){
    if(node->val == x)
        x_info = newPair(depth, parent);
    if(node->val == y)
        y_info = newPair(depth, parent);
    if(node->left  != NULL)
        dfs(node->left, x, y, depth + 1, node->val);
    if(node->right != NULL)
        dfs(node->right, x, y, depth + 1, node->val);
}
bool isCousins(TreeNode*root, int x, int y){
    dfs(root, x, y, 0, -1);
    return x_info.first == y_info.first && x_info.second != y_info.second;
}
