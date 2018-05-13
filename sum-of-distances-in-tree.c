
typedef struct{
    int*first;
    int*second;
}tuple;
tuple newTuple(int*x, int*y){
    tuple rez;
    rez.first  = x;
    rez.second = y;
    return rez;
}

int gn;
int*gsz;//[n];

void fill(int*arr, int sz, int val){
  for(int i=0;i<sz;i++)
    arr[i]=val;
}

tuple parents3(int**g, int root){
    int n = gn;
    int*par = calloc(n, sizeof(int));
    fill(par, n, -1);
    int*depth = calloc(n, sizeof(int));
    depth[0] = 0;
    int*q = calloc(n, sizeof(int));
    q[0] = root;
    for(int p=0, r=1; p<r; p++){
        int cur = q[p];
        for(int z=0;z<gsz[cur];z++){int nex = g[cur][z];
            if(par[cur] != nex){
                q[r++] = nex;
                par[nex] = cur;
                depth[nex] = depth[cur] + 1;
            }
        }
    }
    return newTuple(par, q);
}
int**packU(int n, int*from, int*to){
    int**g = calloc(n, sizeof(int*));
    int p[n];
    memset(p, 0, sizeof(p));
    for(int i=0; i<n-1; i++){int f = from[i];
        p[f]++;
    }
    for(int i=0; i<n-1; i++){int t = to[i];
        p[t]++;
    }
    for(int i=0; i<n; i++){
        g[i] = calloc(p[i], sizeof(int));
        gsz[i] = p[i];
    }
    for(int i=0; i<n-1; i++){
        g[from[i]][--p[from[i]]] = to  [i];
        g[to[i]][--p[to[i]]]     = from[i];
    }
    return g;
}
int*sumOfDistancesInTree(int n, int**edges, int edgesSz, int*edges0sz, int*rsz){
    gn=n;
    gsz = calloc(n, sizeof(int));
    int*from = calloc(n-1, sizeof(int));
    int*to   = calloc(n-1, sizeof(int));
    for(int i=0; i<n-1; i++){
        from[i] = edges[i][0];
        to  [i] = edges[i][1];
    }
    int**g = packU(n, from, to);
    tuple pars = parents3(g, 0);
    int*par = pars.first;
    int*ord = pars.second;
    int*dp  = calloc(n, sizeof(int));
    int*des = calloc(n, sizeof(int));
    fill(des, n, 1);
    for(int i=n-1; i>=1; i--){
        des[par[ord[i]]] += des[ord[i]];
    }
    for(int i=n-1; i>=0; i--){
        int cur=ord[i];
        for(int z=0;z<gsz[cur];z++){int e = g[cur][z];
            if(par[cur] == e)
                continue;
            dp[cur] += dp[e] + des[e];
        }
    }
    for(int i=1; i<n; i++){
        int cur = ord[i];
        int p = par[cur];
        dp[cur] += dp[p] - dp[cur] - des[cur] + (n - des[cur]);
    }
   *rsz=n;
    return dp;
}

