#pragma GCC optimize "-O3"
#pragma GCC option("arch=native","tune=native","no-zero-upper")
#pragma GCC target("avx")

int connectTwoGroups(int**cost, int costSz, int*cost0sz){
    int f[15][5000];
    int i, j, k, h, m = costSz, n = cost0sz[0], yh[15][5000];
    for (i = 0; i < (1<<n); ++i)
        f[0][i] = -1;
    f[0][0] = 0;
    for (i = 0; i < m; ++i)
        for (j = 0; j < (1<<n); ++j){
            yh[i][j] = 0;
            for (k = 0; k < n; ++k)
                if (j & (1<<k)) yh[i][j] += cost[i][k];
        }
    for (i = 0; i < m; ++i){
        for (j = 0; j < (1<<n); ++j)
            f[i + 1][j] = -1;
        for (j = 0; j < (1<<n); ++j){
            if (f[i][j] < 0) continue;
            for (k = 1; k < (1<<n); ++k)
                if (f[i + 1][j | k] == -1 || f[i][j] + yh[i][k] < f[i + 1][j | k])
                    f[i + 1][j | k] = f[i][j] + yh[i][k];
        }
    }
    return f[m][(1<<n)-1];
}
