typedef struct {
}CBTInserter;
CBTInserter*gptr;
typedef struct TreeNode TreeNode;

TreeNode*newTreeNode(int v){
    TreeNode*res=malloc(sizeof(TreeNode));
    res->val   = v;
    res->left  = NULL;
    res->right = NULL;
    return res;
}



TreeNode*rt;
int si;

void dfs(TreeNode*rt){
    si++;
    if (rt->left)
        dfs(rt->left);
    if (rt->right)
        dfs(rt->right);
}
CBTInserter*cBTInserterCreate(TreeNode*root){
    rt = root;
    si = 0;
    dfs(rt);
    return gptr;
}
bool buff[100000];
int  buffSz;
int cBTInserterInsert(CBTInserter* obj, int vv) {
    si++;
    int ta = si;
    buffSz=0;
    while (ta != 1) {
        buff[buffSz++] = (ta & 1);
        ta >>= 1;
    }
    TreeNode* t = rt;
    for (int i = buffSz-1; i; i--)
        if(buff[i])
            t = t->right;
        else
            t = t->left;
    if(buff[0])
        t->right = newTreeNode(vv);
    else
        t->left = newTreeNode(vv);
    return t->val;
}
TreeNode* cBTInserterGet_root(CBTInserter* obj) {
    return rt;
}
void cBTInserterFree(CBTInserter* obj) {
    ;
}
