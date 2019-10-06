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

typedef struct TreeNode TreeNode;

bool findValue(TreeNode*node, int target){
    if (!node)
        return false;
    if (node->val == target)
        return true;
    if (node->val > target)
        return findValue(node->left, target);
    return findValue(node->right, target);
}
void dfs(TreeNode*node, vec*v){
    if(!node)
        return;
    v->ptr = pushback(v->ptr, &v->sz, node->val);
    dfs(node->left, v);
    dfs(node->right, v);
}
bool twoSumBSTs(TreeNode*root1, TreeNode*root2, int target){
    vec v = newVec();
    dfs(root1, &v);
    for (int i = 0; i < v.sz; i++) {
        if (findValue(root2, target - v.ptr[i]))
            return true;
    }
    return false;
}
