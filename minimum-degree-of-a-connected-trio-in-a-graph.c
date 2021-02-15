#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int minTrioDegree(int n, int**edges, int edgesSz, int*edges0sz){
    int adj[n][n]; clr(adj);
    int deg[n];    clr(deg);
    for(int z=0;z<edgesSz;z++){int*ed = edges[z];
        --ed[0]; --ed[1];
        adj[ed[0]][ed[1]] = 1;
        adj[ed[1]][ed[0]] = 1;
        ++deg[ed[0]];
        ++deg[ed[1]];
    }
    enum{INF =(int) 1e9};
    int ans = INF;
    for(int i = 0; i < n; ++i){
        for(int j = i + 1; j < n; ++j){
            for(int k = j + 1; k < n; ++k){
                if(adj[i][j] && adj[i][k] && adj[j][k]){
                    ans = fmin(ans, deg[i] + deg[j] + deg[k] - 6);
                }
            }
        }
    }
    if(ans == INF)
      ans = -1;
    return ans;
}
