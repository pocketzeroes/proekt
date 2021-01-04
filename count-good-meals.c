int cmp (const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}
typedef long long ll;
int countPairs(int*d, int dSz){
    qsort(d, dSz, sizeof(int), cmp);
    int n = dSz;
    ll ans = 0;
    enum{mod = 1000000007};
    for(int i=0; i<=21; i++){
        int p = n-1;
        for(int j=0; j<n;){
            int k = j;
            while(k < n && d[k] == d[j])
              k++;
            while(p >= 0 && d[p] + d[j] > 1<<i)
              p--;
            int q = p;
            while(q >= 0 && d[q] + d[j] == 1<<i)
              q--;
            if(p >= 0 && p-q > 0){
                if(d[j] == d[p])
                    ans += (ll) (k - j) * (k - j - 1);
                else
                    ans += (ll) (p - q) * (k - j);
            }
            p = q;
            j = k;
        }
    }
    return(int)(ans/2%mod);
}
