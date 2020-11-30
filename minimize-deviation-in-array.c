typedef long long ll;
int cmpLL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)


int minimumDeviation(int*a, int aSz){
    int n = aSz;
    ll es[30*n]; clr(es);
    int p=0;
    for(int i=0; i<n; i++){
        if(a[i] % 2 == 0){
            es[p++] = (ll)a[i]<<32|i;
            while(a[i] % 2 == 0){
                a[i] /= 2;
                es[p++] = (ll)a[i]<<32|i;
            }
        }
        else{
            es[p++] = (ll)a[i]<<32|i;
            es[p++] = (ll)a[i]*2<<32|i;
        }
    }
    qsort(es, p, sizeof(ll), cmpLL);
    int f[n]; clr(f);
    int nf = 0;
    int q  = 0;
    ll ans = LLONG_MAX;
    for(int i=0; i<p; i++){
        while(q < p && nf < n){
            if(++f[(int)es[q]] == 1){
                nf++;
            }
            q++;
        }
        if(nf == n){
            ans = fminl(ans, (int)((es[q - 1] >> 32) - (es[i] >> 32)));
        }
        if(--f[(int)es[i]] == 0){
            nf--;
        }
    }
    return(int)ans;
}
