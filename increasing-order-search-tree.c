#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int*pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
    int*ptr;
    int sz;
}vec;
vec newVec(){
    vec rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}
typedef struct TreeNode TreeNode;
TreeNode*newTreeNode(int v){
    TreeNode*res=malloc(sizeof(TreeNode));
    res->val   = v;
    res->left  = NULL;
    res->right = NULL;
    return res;
}
/////////////////////
vec v;

void dfs(TreeNode*root){
    if(!root)
        return ;
    dfs(root->left);
    v.ptr = pushback(v.ptr, &v.sz, root->val);
    dfs(root->right);
}
void build(TreeNode*root){
    if(v.sz==0)
        return;
    root->right = newTreeNode(v.ptr[v.sz-1]);
    v.sz--;
    build(root->right);
}
TreeNode*increasingBST(TreeNode*root){
    dfs(root);
    reverse(v.ptr, 0, v.sz-1);
    TreeNode*ret = newTreeNode(v.ptr[v.sz-1]);
    v.sz--;
    build(ret);
    return ret;
}
