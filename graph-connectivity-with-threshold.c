int f[10010];

int find_fa(int p){
    int j, k;
    j = p;
    while(f[j] != -1)
        j = f[j];
    while(p != j){
        k = f[p];
        f[p] = j;
        p = k;
    }
    return j;
}
bool*areConnected(int n, int threshold, int**q, int qSz, int*q0sz, int*rsz){
    int i, j, x, y;
    for(i=1; i<=n; ++i)
        f[i] = -1;
    for(i = threshold + 1; i <= n; ++i){
        j = i;
        while(j + i <= n){
            x = find_fa(j);
            y = find_fa(j + i);
            if(x != y)
                f[x] = y;
            j += i;
        }
    }
    bool*res=calloc(qSz, sizeof(bool));
    for(i=0; i<qSz; ++i){
        x = find_fa(q[i][0]);
        y = find_fa(q[i][1]);
        res[i] = (x == y);
    }
   *rsz=qSz;
    return res;
}
