#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct {
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
TreeNode*newTreeNode(int v){
    TreeNode*res=malloc(sizeof(TreeNode));
    res->val   = v;
    res->left  = NULL;
    res->right = NULL;
    return res;
}
TreeNode*bstFromPreorder(int*preorder, int preorderSz){
    int n = preorderSz;
    if(n == 0)
        return NULL;
    TreeNode*root = newTreeNode(preorder[0]);
    vec left  = newVec();
    vec right = newVec();
    for(int i=1; i<n; i++)
        if(preorder[i] < preorder[0])
            left.ptr = pushback(left.ptr, &left.sz, preorder[i]);
        else
            right.ptr = pushback(right.ptr, &right.sz, preorder[i]);
    root->left  = bstFromPreorder(left.ptr, left.sz);
    root->right = bstFromPreorder(right.ptr, right.sz);
    return root;
}
