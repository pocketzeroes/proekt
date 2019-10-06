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

int*arraysIntersection(int*arr1, int arr1sz, int*arr2, int arr2sz, int*arr3, int arr3sz, int*rsz){
    vec ret = newVec();
    int p = 0, q = 0;
    for(int z=0;z<arr1sz;z++){int v = arr1[z];
        while(p < arr2sz && arr2[p] < v)p++;
        while(q < arr3sz && arr3[q] < v)q++;
        if(p < arr2sz && q < arr3sz && arr2[p] == v && arr3[q] == v){
            pb(ret, v);
        }
    }
   *rsz=   ret.sz;
    return ret.ptr;
}
