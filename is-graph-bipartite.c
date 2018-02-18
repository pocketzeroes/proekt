int*g0szs;
bool ok;

void go(int**g, int*u, int v, int c){
    if(u[v] && u[v] != c)
        ok = 0;
    if(u[v])
        return;
    u[v] = c;
    for(int z=0; z<g0szs[v]; z++){int t = g[v][z];
        go(g, u, t, 3-c);
    }
}
bool isBipartite(int**g, int gSz, int*p_g0szs){
    g0szs = p_g0szs;
    ok=1;
    int n = gSz;
    int u[n];
    memset(u, 0, sizeof(u));
    for(int i=0; i<n; ++i)
        if(!u[i])
            go(g, u, i, 1);
    return ok;
}
