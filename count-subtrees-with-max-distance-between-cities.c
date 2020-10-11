#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)

#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define REP(i, n) FOR(i,0,n)
bool chmax(int*m, int q){
    if(*m < q){
       *m = q;
       return true;
    }
    return false;
}
int*countSubgraphsForEachDiameter(int n, int**edges, int edgesSz, int*edges0sz, int*rsz){
    int dist[n][n]; dfill(dist, n, n, (int)1e5);
    int*rv=calloc(n-1, sizeof(int));
    int conn[n]; clr(conn);
    REP(i, n) conn[i] = 1 << i;
    for(int z=0;z<edgesSz;z++){int*e = edges[z];
        int u = e[0] - 1, v = e[1] - 1;
        dist[u][v] = dist[v][u] = 1;
        conn[u] |= 1 << v;
        conn[v] |= 1 << u;
    }
    REP(k, n) REP(i, n) REP(j, n) dist[i][j] = fmin(dist[i][j], dist[i][k] + dist[k][j]);
    FOR(S, 1, (1 << n)) {
        int ctmp = 1 << __builtin_ctz(S);
        while(true){
            int conn_nxt = ctmp;
            REP(d, n) if ((ctmp >> d) & 1) conn_nxt |= conn[d];
            conn_nxt &= S;
            if (conn_nxt == ctmp) break;
            ctmp = conn_nxt;
        }
        if((~ctmp) & S) continue;
        int ret = 0;
        REP(i, n) if ((S >> i) & 1) {
            REP(j, i) if ((S >> j) & 1) {
                chmax(&ret, dist[i][j]);
            }
        }
        if (ret > 0 && ret < 100) rv[ret - 1]++;
    }
   *rsz=n-1;
    return rv;
}
