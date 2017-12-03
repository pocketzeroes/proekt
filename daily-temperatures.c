int min(int a,int b){return a<b?a:b;}

void fill(int*arr,int sz, int val){
    for(int i=0;i<sz;i++)
        arr[i]=val;
}
int*dailyTemperatures(int*a, int aSz, int*rsz){
    int n = aSz;
    int*ret = calloc(n, sizeof(int));
    int best[101];//, -1);
    fill(best, 101, -1);
    for(int i =n-1; i>=0; --i){
        ret[i] = 1 << 30;
        for (int j = a[i] + 1; j <= 100; ++j) {
            if (best[j] >= 0)
                ret[i] = min(ret[i], best[j] - i);
        }
        if (ret[i] == 1 << 30)
            ret[i] = 0;
        best[a[i]] = i;
    }
   *rsz = n;
    return ret;
}
