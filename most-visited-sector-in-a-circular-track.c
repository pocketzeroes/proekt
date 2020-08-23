int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int*pushback(int *array, int *size, int value){
    int*output = resizeArray(array, int, *size + 1);
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

int*mostVisited(int n, int*rounds, int roundsSz, int*rsz){
    int f = rounds[0], l = rounds[roundsSz-1];
    vec ans = newVec();
    while(f != l){
        pb(ans, f);
        f %= n;
        f++;
    }
    pb(ans, l);
    qsort(ans.ptr, ans.sz, sizeof(int), cmp);
   *rsz=   ans.sz;
    return ans.ptr;
}
