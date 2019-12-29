#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
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
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int*sumZero(int n, int*rsz){
    vec ret = newVec();
    for(int i = -n/2; i <= n/2; i++){
        if(i==0&&n%2==0)   
            continue;
        pb(ret, i);
    }
   *rsz=   ret.sz;
    return ret.ptr;
}
