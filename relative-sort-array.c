int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int*relativeSortArray(int*arr1, int arr1sz, int*arr2, int arr2sz, int*rsz){
    qsort(arr1, arr1sz, sizeof(int), cmp);
    int n = arr1sz;
    bool used[n]; memset(used, 0, sizeof(used));
    vec result = newVec();
    for(int z=0;z<arr2sz;z++){int x = arr2[z];
        for(int i=0; i<n; i++)
            if(arr1[i]==x && !used[i]){
                result.ptr = pushback(result.ptr, &result.sz, x);
                used[i] = true;
            }
    }
    for(int i = 0; i < n; i++)
        if (!used[i])
            result.ptr = pushback(result.ptr, &result.sz, arr1[i]);
    *rsz=  result.sz;
    return result.ptr;
}
