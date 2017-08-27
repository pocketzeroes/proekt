int*constructArray(int n, int k,int*rsz){
    int*a = calloc(n, sizeof(int));
    if (k == 1) {
        for (int i = 0; i < n; ++i) 
            a[i] = i + 1;
        goto end;
    }
    k -= 2;
    a[0] = 1; 
    a[1] = n;
    int len = n - 1;
    int i = 1;
    while (k--) {
        --len;
        if (a[i - 1] < a[i]) {
            a[i + 1] = a[i] - len;
        } 
        else {
            a[i + 1] = a[i] + len;
        }
        ++i;
    }
    if (a[i - 1] < a[i]) {
        for (++i; i < n; ++i) 
            a[i] = a[i - 1] - 1;
    } 
    else {
        for (++i; i < n; ++i) 
            a[i] = a[i - 1] + 1;
    }
end:
    *rsz=n;
    return a;
}
