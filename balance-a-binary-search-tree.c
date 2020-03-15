typedef struct TreeNode TreeNode;
TreeNode*newTreeNode(int v){
    TreeNode*res=malloc(sizeof(TreeNode));
    res->val   = v;
    res->left  = NULL;
    res->right = NULL;
    return res;
}

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
////////////////////////

vec values;

void dfs(TreeNode*node){
    if(node == NULL)
        return;
    dfs(node->left);
    pb(values, node->val);
    dfs(node->right);
}
TreeNode*build_tree(int start, int end){
    if(start >= end)
        return NULL;
    int mid = (start + end) / 2;
    TreeNode*root = newTreeNode(values.ptr[mid]);
    root->left  = build_tree(start,   mid);
    root->right = build_tree(mid + 1, end);
    return root;
}
TreeNode*balanceBST(TreeNode*root){
    values = newVec();
    dfs(root);
    return build_tree(0, values.sz);
}
