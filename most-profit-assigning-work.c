int max(int a,int b){return a>b?a:b;}

int maxProfitAssignment(int*difficulty, int difficultySz, int*profit, int profitSz, int*worker, int workerSz){
    int a[100005], n=difficultySz, m=workerSz, ans=0, i;
    memset(a, 0, sizeof(a));
    for(i=0; i<n; i++)
        a[difficulty[i]] = max(a[difficulty[i]], profit[i]);
    for(i=1; i<=100000; i++)
        a[i] = max(a[i],a[i-1]);
    for(i=0; i<m; i++)
        ans += a[worker[i]];
    return ans;
}
