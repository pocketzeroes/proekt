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

bool hasAlternatingBits(int n){
    vec d = newVec();
    while(n){
        d.ptr = pushback(d.ptr, &d.sz, n&1);
        n>>=1;
    }
    for(int i = 1; i < d.sz; ++i)
        if(d.ptr[i] == d.ptr[i-1])
            return 0;
    return 1;
}
