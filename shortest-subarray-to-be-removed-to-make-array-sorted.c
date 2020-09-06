#define REP(x, l, u) for(int x = l;x<u;x++)

void upmin(int*a, int b){
    if(*a > b)
       *a = b;
}
int findLengthOfShortestSubarray(int*a, int aSz){
    bool ok = 1;
    REP(i, 1, aSz){
        if(a[i] < a[i - 1])
            ok = 0;
    }
    if(ok)
        return 0;
    int b = 0, e = aSz - 1;
    while(a[b] <= a[b + 1])
        b++;
    while(a[e - 1] <= a[e])
        e--;
    int ans = aSz;
    upmin(&ans, aSz  - (aSz - e));
    REP(i, 0, b + 1){
        while(e != aSz && a[i] > a[e])
            e++;
        upmin(&ans, aSz - (i + 1) - (aSz - e));
    }
    return ans;
}
