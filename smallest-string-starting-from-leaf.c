typedef struct TreeNode TreeNode;
char*append(char*s, char c){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c", s, c);
  return ptr;
}
char* minS(char*a, char*b){return strcmp(a, b) < 0 ? a : b;}

char*recur(TreeNode*root){
    char*s = "";
    if (root->left != NULL && root->right != NULL)
        s = minS(recur(root->left), recur(root->right));
    else if(root->left != NULL)
        s = recur(root->left);
    else if(root->right != NULL)
        s = recur(root->right);
    s = append(s, ('a' + root->val));
    return s;
}
char*smallestFromLeaf(TreeNode*root){
    return recur(root);
}
