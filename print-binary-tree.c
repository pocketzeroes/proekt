typedef struct TreeNode TreeNode;
int max(int a,int b){return a>b?a:b;}
char*to_string(int v){
  char*ptr=NULL;
  asprintf(&ptr, "%d", v);
  return ptr;
}
/////
char***ret;
int mySz;
int geth(TreeNode* cur) {
    if (cur == NULL)
        return 0;
    return max(geth(cur->left), geth(cur->right)) + 1;
}
void run(TreeNode* cur, int dep, int pos, int width ){
    if (cur == NULL)
        return;
    ret[dep][width * pos + (width - 1) / 2] = to_string(cur->val);
    run(cur->left,  dep + 1, pos * 2,     width / 2);
    run(cur->right, dep + 1, pos * 2 + 1, width / 2);
}
char***printTree(TreeNode*root, int**colSzs, int*rsz){
    int height = geth(root);
    ret = calloc(height, sizeof(char**));
    mySz=(1<<height)-1;
    for(int i=0;i<height;i++){
        ret[i]=calloc(mySz, sizeof(char*));
        for(int z=0;z<mySz;z++){
            ret[i][z] = strdup("");
        }
    }
    run(root, 0, 0, 1<<height );
    int*cols = calloc(height, sizeof(int));
    for(int i=0;i<height;i++){
        cols[i] = mySz;
    }
   *rsz = height;
   *colSzs = cols;
    return ret;
}
