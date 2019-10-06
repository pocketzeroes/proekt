#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

int longestSubsequence(int*a, int aSz, int d){
    for(int z=0;z<aSz;z++)
        a[z] += 10000;
    int u[20010]; clr(u);
    int n = aSz;
    int F[n+1]; clr(F);
    int ret = 1;
    for(int i = 1; i <= n; ++ i){
        int x = a[i-1]-d;
        if(0 <= x && x <= 20000)
            F[i] = F[u[x]]+1;
        else
            F[i] = 1;
        ret = fmax(ret, F[i]);
        u[a[i-1]] = i;
    }
    return ret;
}
