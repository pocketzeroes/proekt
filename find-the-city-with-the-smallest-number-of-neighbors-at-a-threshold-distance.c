#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)
int findTheCity(int n, int**edges, int edgesSz, int*edges0sz, int distanceThreshold){
    enum{INF =(int)1e9+7};
    int dist[n][n]; dfill(dist, n, n, INF);
    for(int i=0; i<n; ++i)
        dist[i][i] = 0;
    for(int z=0; z<edgesSz; z++){int*e = edges[z];
        dist[e[0]][e[1]] = fmin(dist[e[0]][e[1]], e[2]);
        dist[e[1]][e[0]] = fmin(dist[e[1]][e[0]], e[2]);
    }
    for(int k = 0; k < n; ++k)
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                dist[i][j] = fmin(dist[i][j], dist[i][k] + dist[k][j]);
    int fewestReachable = n + n;
    int ans = -1;
    for(int i = 0; i < n; ++i){
        int cur = 0;
        for(int j = 0; j < n; ++j)
            if(dist[i][j] <= distanceThreshold)
                ++cur;
        if(cur <= fewestReachable){
            fewestReachable = cur;
            ans = i;
        }
    }
    return ans;
}
