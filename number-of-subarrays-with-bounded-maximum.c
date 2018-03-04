int n;
int count(int*a, int R){
    int my = 0, ret = 0;
    for(int i=0;i<n;i++){int v = a[i];
        if(v <= R)
            my++;
        else
            my = 0;
        ret += my;
    }
    return ret;
}
int numSubarrayBoundedMax(int*a, int aSz, int L, int R){
    n = aSz;
    return count(a, R) - count(a, L-1);
}
