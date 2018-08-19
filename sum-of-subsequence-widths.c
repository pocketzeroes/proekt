typedef long long ll;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushbackL(ll*array, int*size, ll value) {
    ll*output = resizeArray(array, ll, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
    ll*ptr;
    int sz;
}vecl;
vecl newVecL(){
    vecl rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}

#define MOD 1000000007

int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

int sumSubseqWidths(int*A, int Asz){
    vecl pp = newVecL();
    pp.ptr = pushbackL(pp.ptr, &pp.sz, 1);
    while(pp.sz <= Asz)
        pp.ptr = pushbackL(pp.ptr, &pp.sz, pp.ptr[pp.sz-1] * 2 % MOD);
    qsort(A, Asz, sizeof(int), cmp);
    ll ans = 0;
    for(int i=0; i<Asz; i++) {
        ans = (ans + A[i] * pp.ptr[i]) % MOD;
        ans = (ans + MOD - A[i] * pp.ptr[Asz - 1 - i] % MOD) % MOD;
    }
    return(int)ans;
}
