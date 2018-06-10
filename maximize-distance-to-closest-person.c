int max(int a,int b){return a>b?a:b;}
int maxDistToClosest(int*a, int aSz){
    int n = aSz;
    int ret = 0;
    for (int i = 0, j; i < n; i = j) {
        for (; i < n && a[i] == 1; ++i);
        if (i == n) 
            break;
        for (j = i + 1; j < n && a[j] == 0; ++j);
        int len = j - i;
        if (i == 0 || j == n) {
            ret = max(ret, len);
        } 
        else {
            ret = max(ret, (len - 1) / 2 + 1);
        }
    }
    return ret;
}
