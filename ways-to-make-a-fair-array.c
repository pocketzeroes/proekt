#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int waysToMakeFair(int*a, int aSz){
    int n = aSz;
    int b[n+1]; clr(b);
    int c[n+1]; clr(c);
    for(int i = 0; i < n; ++i){
        b[i + 1] = a[i] - b[i];
        c[i + 1] = a[n - 1 - i] - c[i];
    }
    int results = 0;
    for(int i = 0; i < n; ++i){
        if(b[i] == c[n - 1 - i]){
            ++results;
        }
    }
    return results;
}
