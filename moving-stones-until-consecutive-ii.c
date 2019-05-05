int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}

enum{ INF =(int) 1e9 + 5};

int*numMovesStonesII(int*stones, int stonesSz, int*rsz){
    qsort(stones, stonesSz, sizeof(int), cmp);
    int n = stonesSz;
    int least = INF,
        most  =-INF;
    for (int i = 0, j = 0; i < n; i++) {
        while (j + 1 < n && stones[j + 1] - stones[i] < n)
            j++;
        int now = n - (j - i + 1);
        if (j - i == n - 2 && stones[j] - stones[i] == j - i)
            now++;
        least = min(least, now);
    }
    most = max(stones[n - 1] - stones[1], stones[n - 2] - stones[0]) - (n - 2);
   *rsz=2;
    int*rv=calloc(2,sizeof(int));
    rv[0]=least;
    rv[1]=most;
    return rv;
}
