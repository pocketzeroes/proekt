typedef struct TreeNode TreeNode;
char*to_string(int v){
  char*ptr=NULL;
  asprintf(&ptr, "%d", v);
  return ptr;
}

char* tree2str(TreeNode* t) {
    if (!t) return "";
    char* res   = to_string(t->val);
    char* left  = tree2str(t->left);
    char* right = tree2str(t->right);
    if (strlen(left)==0 && strlen(right) ==0 ) 
        return res;
    else if (strlen(right)==0){
      char*ret=NULL;
      asprintf(&ret, "%s(%s)", res, left);
      return ret;
    }
    char*rvv=NULL;
    asprintf(&rvv, "%s(%s)(%s)", res, left, right);
    return rvv;
}


