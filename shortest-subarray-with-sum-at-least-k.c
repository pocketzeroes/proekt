int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
typedef long long ll;
int cmp(const void*pa, const void*pb){
    ll*a=(ll*)pa;
    ll*b=(ll*)pb;
    return *a < *b ? -1:1;
}

int ans;
ll O = 1L<<46;

void dfs(int l, int r, int*a, int K){
    if(r-l <= 0)
        return;
    int h = l+r>>1;
    ll s = 0;
    int b_length=h-l+1;
    ll b[b_length]; memset(b, 0, sizeof(b));
    int p = 0;
    for(int i = h, j = 1;i >= l;i--,j++){
        s += a[i];
        b[p++] = s+O<<16|j;
    }
    qsort(b, b_length, sizeof(ll), cmp);
    int c_length = r-h;
    ll  c[c_length]; memset(c, 0, sizeof(c));
    int q = 0;
    s = 0;
    for(int i = h+1, j = 0;i <= r;i++,j++){
        c[q++] = s+O<<16|j;
        if(i < r)
            s += a[i];
    }
    qsort(c,c_length,sizeof(ll),cmp);
    p = b_length-1;
    int minlen = INT_MAX / 2;
    for(int i = 0; i < r-h; i++){
        ll val = (c[i] >> 16)-O;
        int len = (int)(c[i]&65535);
        ll need = K-val;
        while(p >= 0 && (b[p] >> 16)-O >= need){
            minlen = min(minlen, (int)(b[p]&65535));
            p--;
        }
        if(minlen != INT_MAX / 2)
            ans = min(ans, minlen + len);
    }
    dfs(l  , h, a, K);
    dfs(h+1, r, a, K);
}
int shortestSubarray(int*a, int aSz, int K){
    int n = aSz;
    ans = INT_MAX;
    dfs(0, n, a, K);
    if(ans == INT_MAX)
        return -1;
    return ans;
}
