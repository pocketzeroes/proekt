#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int*pushback(int *array, int *size, int value){
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
typedef struct TreeNode TreeNode;
void traverse(TreeNode*p, vec*A){
    if(!p)
        return;
    if(!p->left && !p->right)
        A->ptr = pushback(A->ptr, &A->sz, p->val);
    traverse(p->left , A);
    traverse(p->right, A);
}
bool leafSimilar(TreeNode*r1, TreeNode*r2){
    vec A = newVec();
    vec B = newVec();
    traverse(r1, &A);
    traverse(r2, &B);
    if(A.sz != B.sz)
        return false;
    for(int i=0; i<A.sz; ++i)
        if(A.ptr[i] != B.ptr[i])
            return false;
    return true;
}
