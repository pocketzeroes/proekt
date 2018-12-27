int max(int a,int b){return a>b?a:b;}
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

int maxWidthRamp(int*A, int Asz){
    vec s = newVec();
    int best = 0;
    for(int i=0; i<Asz; i++) {
        if(s.sz==0 || A[s.ptr[s.sz-1]] > A[i])
            s.ptr = pushback(s.ptr, &s.sz, i);
        int l=0, r=s.sz-1;
        int ans = 0;
        while(l<=r) {
            int m = (l+r)/2;
            if(A[s.ptr[m]] <= A[i]){
                ans = i - s.ptr[m];
                r = m-1;
            }
            else{
                l = m+1;
            }
        }
        best = max(best, ans);
    }
    return best;
}
