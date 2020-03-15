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

int*luckyNumbers (int**matrix, int matrixSz, int*matrix0sz, int*rsz){
    vec ans=newVec();
    for(int i=0; i<matrixSz; ++i){
        for(int j=0; j<matrix0sz[i]; ++j){
            int mn=(int)1e9, mx=0;
            for(int k=0; k<matrix0sz[i]; ++k)
                mn = fmin(matrix[i][k], mn);
            for(int k=0; k<matrixSz; ++k)
                mx = fmax(matrix[k][j], mx);
            if(mn==matrix[i][j] && mx==matrix[i][j])
               pb(ans, matrix[i][j]);
        }
    }
   *rsz=   ans.sz;
    return ans.ptr;
}
