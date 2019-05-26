int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int*rearrangeBarcodes(int*b, int bsz, int*rsz){
    qsort(b, bsz, sizeof(int), cmp);
    int cnt = 1;
    int len = 0;
    int mx = b[0];
    for (int i = 1; i < bsz; i++) {
        if (b[i] != b[i-1]) {
            if (cnt > len) {
                mx = b[i-1];
                len = cnt;
            }
            cnt = 1;
        } 
        else
            cnt++;
    }
    int n = bsz;
    if (cnt > len){
        len = cnt;
        mx  = b[n-1];
    }
    int a[n]; memset(a, 0, sizeof(a));
    int j = 0;
    for (j = 0; j < len; j++)
        a[j] = mx;
    for (int i = 0; i < n; i++)
        if (b[i] != mx)
            a[j++] = b[i];
    for (int i = 0; i < n; i++) 
        b[i] = a[i];
    int row = (n + len - 1) / len;
    int table[row][len];
    for (int i= 0; i < row; i++)
        for (j = 0; j < len; j++)
            table[i][j] = -1;
    for (int i = 0; i < n; i++) {
        int r = i / len;
        int c = i % len;
        table[r][c] = b[i];
    }
    int*res = calloc(n, sizeof(int));
    int idx = 0;
    for (j = 0; j < len; j++){
        for (int i = 0; i < row; i++){
            if (table[i][j] != -1) {
                res[idx++] = table[i][j];
            }
        }
    }
   *rsz=n;
    return res;
}
