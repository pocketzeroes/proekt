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

int newInteger(int n){
    vec f=newVec();
    while (n) {
        f.ptr = pushback(f.ptr, &f.sz, n%9);
        n /= 9;
    }
    int ans = 0;
    for (int i = f.sz - 1; i >= 0; i--){
        ans = ans * 10 + f.ptr[i];
    }
    return ans;
}
