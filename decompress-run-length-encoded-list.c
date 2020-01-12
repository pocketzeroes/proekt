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

int*decompressRLElist(int*a, int aSz, int*rsz){
    int n = aSz;
    vec ret = newVec();
    for(int i=0; i<n/2; ++i){
        int x = a[i*2];
        int y = a[i*2+1];
        for(int j=1; j<=x; ++j)
           pb(ret, y);
    }
   *rsz=ret.sz;
    return ret.ptr;
}
