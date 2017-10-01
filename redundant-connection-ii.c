int root(int*parent, int k){
    if (parent[k] != k) 
        parent[k] = root(parent, parent[k]);
    return parent[k];
}
int*findRedundantDirectedConnection(int**edges, int edgesSz, int edges0sz, int*rsz){
   *rsz=2;
    int n = edgesSz;
    int parent[n+1];memset(parent,0,sizeof(parent));
    bool empty = true;
    int*candA=calloc(2,sizeof(int)); 
    int*candB=calloc(2,sizeof(int));
    for(int z=0;z<edgesSz;z++){int*edge = edges[z];
        if (parent[edge[1]] == 0)
            parent[edge[1]] = edge[0]; 
        else{
            candA[0] =parent[edge[1]];
            candA[1] =edge[1];empty=false;
            candB[0] =edge[0];
            candB[1] =edge[1];
            edge[1] = 0;
        }
    } 
    for (int i = 1; i <= n; i++) 
        parent[i] = i;
    for(int z=0;z<edgesSz;z++){int*edge = edges[z];
        if (edge[1] == 0) 
            continue;
        int u = edge[0], v = edge[1], pu = root(parent, u);
        if(pu == v){
            if(empty) 
                return edge;
            return candA;
        }
        parent[v] = pu;
    }
    return candB;
}
