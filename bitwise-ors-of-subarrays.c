typedef long long ll;
int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int cmpLL(const void*pa, const void*pb){
    ll*a =(ll*)pa;
    ll*b =(ll*)pb;
    return(*a < *b)?-1:1;
}
void fill(int*arr,int sz, int val){
  for(int i=0;i<sz;i++)
    arr[i]=val;
}
int subarrayBitwiseORs(int*a, int aSz){
    int n = aSz;
    int next[31];
    fill(next, 31, n);
    int*u = calloc(33*n, sizeof(int));
    int p = 0;
    ll t[31]; memset(t, 0, sizeof(t));
    for(int i=n-1; i>=0; i--){
        for(int j=0; j<31; j++){
            if(a[i]<<~j<0)
                next[j] = i;
            t[j] = (ll)next[j]<<32|j;
        }
        qsort(t, 31, sizeof(ll), cmpLL);
        u[p++] = a[i];
        int b = 0;
        for(int j=0; j<31;){
            int k = j;
            if(t[j]>>32 == n)
                break;
            while(k < 31 && t[k]>>32==t[j]>>32){
                b |= 1<<(int)t[k];
                k++;
            }
            u[p++] = b;
            j = k;
        }
    }
    qsort(u, p, sizeof(int), cmp);
    int ct = 0;
    for(int i=0; i<p; i++)
        if(i == 0 || u[i-1] != u[i])
            ct++;
    free(u);
    return ct;
}
