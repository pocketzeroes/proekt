typedef struct TreeNode TreeNode;
int min(int a,int b){return a<b?a:b;}
int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
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

void traverse(TreeNode*cur, vec*A){
    if (cur == NULL)
        return;
    A->ptr = pushback(A->ptr, &A->sz, cur->val);
    traverse(cur->left,  A);
    traverse(cur->right, A);
}
int minDiffInBST(TreeNode*root){
    vec A = newVec();
    traverse(root, &A);
    qsort(A.ptr, A.sz, sizeof(int), cmp);
    int ret = 1 << 30;
    for (int i = 1; i < A.sz; ++i) {
        ret = min(ret, A.ptr[i] - A.ptr[i - 1]);
    }
    return ret;
}
