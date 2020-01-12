int par[100005];

int find(int a) {
    if(par[a] == a) 
        return a; 
    else {
        par[a] = find(par[a]);
        return par[a];
    }
}

int makeConnected(int n, int**x, int xSz, int*x0sz){
    memset(par,0,sizeof(par));
    if(xSz < n - 1)
        return -1;
    int ans = n - 1;
    for (int i = 0; i < n; i++)
        par[i] = i;
    for(int z=0;z<xSz;z++){int*i = x[z];
        int ta = find(i[0]);
        int tb = find(i[1]);
        if (ta != tb){
            ans--;
            par[ta] = tb;
        }
    }
    return ans;
}
