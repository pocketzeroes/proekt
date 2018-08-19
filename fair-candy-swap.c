typedef long long ll;

int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int lower_bound(int*a, int n, int x) {
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x <= a[mid]) 
            h = mid;
        else
            l = mid + 1;
    }
    return l;
}
int*fairCandySwap(int*A, int Asz, int*B, int Bsz, int*rsz){
    int*rv = calloc(2, sizeof(int));
    ll asum = 0, bsum = 0;
    for(int i=0, i_len=(Asz); i<i_len; ++i) 
        asum += A[i];
    for(int i=0, i_len=(Bsz); i<i_len; ++i) 
        bsum += B[i];
    qsort(B, Bsz, sizeof(int), cmp);
    for(int i=0, i_len=(Asz); i<i_len; ++i) {
        ll k = bsum - asum + A[i] * 2;
        if (k % 2 == 0){
            int pos = lower_bound(B, Bsz, k/2);
            if (pos < (int)Bsz && B[pos] * 2 == k){
                rv[0]=A[i];
                rv[1]=B[pos];
               *rsz=2;
                return rv;
            }
        }
    }
    return NULL;
}
