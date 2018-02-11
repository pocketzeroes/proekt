int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int numRabbits(int*a, int aSz){
    qsort(a, aSz, sizeof(int), cmp);
    int n = aSz;
    int ret = 0;
    for (int i = 0, j; i < n; i = j) {
        int cur = a[i] + 1;
        for (j = i + 1; j < n && a[j] == a[i] && j - i + 1 <= cur; ++j);
        ret += cur;
    }
    return ret;
}
