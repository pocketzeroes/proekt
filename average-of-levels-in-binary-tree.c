#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

double *pushbackD(double *array, int *size, double value) {
    double *output = resizeArray(array, double, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecD{
	double*ptr;
	int sz;
}vecd;
vecd newVecD() {
	vecd rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

/////
typedef struct TreeNode TreeNode;
vecd sum;
vec  vi;

void f(TreeNode*cur, int dep){
    if (cur == NULL) 
        return;
    if (dep >= sum.sz){
        sum.ptr = pushbackD(sum.ptr, &sum.sz ,0.);
        vi .ptr = pushback (vi .ptr, &vi .sz ,0 );
    }
    sum.ptr[dep] += cur->val;
    vi .ptr[dep]++;
    f(cur->left,  dep + 1);
    f(cur->right, dep + 1);
}
double*averageOfLevels(TreeNode*root, int*retSz){
    sum=newVecD();
    vi =newVec ();
    f(root, 0);
    int n = sum.sz;
    for (int i = 0; i < n; i++){
        sum.ptr[i] /= vi.ptr[i];
    }
   *retSz = sum.sz;
    return  sum.ptr;
}









































