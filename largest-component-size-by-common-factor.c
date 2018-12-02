int max(int a,int b){return a>b?a:b;}
void fill(int*arr,int sz, int val){
  for(int i=0;i<sz;i++)
    arr[i]=val;
}
int*upper; int upperSz;
int*w;     int wSz;
void newDJSet(int n){
    upperSz = n;
    upper = calloc(n, sizeof(int));
    fill(upper, n, -1);
    w = calloc(n, sizeof(int));
}
int root(int x){
    return upper[x] < 0 ? x : (upper[x] = root(upper[x]));
}
bool equiv(int x, int y){
    return root(x) == root(y);
}
bool ds_union(int x, int y){
    x = root(x);
    y = root(y);
    if (x != y) {
        if (upper[y] < upper[x]) {
            int d = x;
            x = y;
            y = d;
        }
        upper[x] += upper[y];
        upper[y] = x;
        w[x] += w[y];
    }
    return x == y;
}
int count(){
    int ct = 0;
    for(int z=0;z<upperSz;z++){int u = upper[z];
        if (u < 0)
            ct++;
    }
    return ct;
}
int*enumLowestPrimeFactors(int n){
    int tot = 0;
    int*lpf = calloc(n + 1, sizeof(int));
    int u = n + 32;
    double lu = log(u);
    int*primes = calloc((int) (u / lu + u / lu / lu * 1.5), sizeof(int));
    for (int i = 2; i <= n; i++)
        lpf[i] = i;
    for (int p = 2; p <= n; p++) {
        if (lpf[p] == p)
            primes[tot++] = p;
        int tmp;
        for (int i = 0; i < tot && primes[i] <= lpf[p] && (tmp = primes[i] * p) <= n; i++) {
            lpf[tmp] = primes[i];
        }
    }
    free(primes);
    return lpf;
}
int largestComponentSize(int*A, int Asz){
    int*lpf = enumLowestPrimeFactors(100001);
    newDJSet(100001);
    for(int z=0;z<Asz;z++){int v = A[z];
        w[v] = 1;
    }
    for(int z=0;z<Asz;z++){int v = A[z];
        int vv = v;
        while(vv > 1){
            ds_union(v, lpf[vv]);
            vv /= lpf[vv];
        }
    }
    free(lpf);
    int ret = 0;
    for(int i = 1;i <= 100000;i++){
        if(upper[i] < 0){
            ret = max(ret, w[i]);
        }
    }
    return ret;
}
