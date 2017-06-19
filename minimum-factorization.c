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

int smallestFactorization(int a) {
    if (a==1) return 1;
    vec ans=newVec();
    for(int i=9;i>=2;i--) {
        while(a%i==0) {
            a/=i;
            ans.ptr=pushback(ans.ptr, &ans.sz ,i);
        }
    }
    if(a>1) return 0;
    long long ret = 0;
    for(int i=(int)ans.sz-1;i>=0;i--) {
        ret = ret * 10 + ans.ptr[i];
        if (ret >= (1LL<<31))
            return 0;
    }
    return (int)ret;
}
