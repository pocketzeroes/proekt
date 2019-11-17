typedef struct TreeNode TreeNode;

typedef struct {
}FindElements;
FindElements*gptr;

TreeNode *r;
void dfs(TreeNode *x) {
    if (x->left) {
        x->left->val = x->val * 2 + 1;
        dfs(x->left);
    }
    if (x->right) {
        x->right->val = x->val * 2 + 2;
        dfs(x->right);
    }
}
FindElements*findElementsCreate(TreeNode*root){
    r = root;
    r->val = 0;
    dfs(r);
    return gptr;
}
bool dofind(TreeNode *x, int v) {
    if (x->val == v) return true;
    if (x->left  && dofind(x->left, v)) return true;
    if (x->right && dofind(x->right, v)) return true;
    return false;
}
bool findElementsFind(FindElements*obj, int target){
    return dofind(r, target);
}
void findElementsFree(FindElements*obj){
    r=NULL;
}
