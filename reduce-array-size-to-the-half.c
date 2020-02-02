int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int minSetSize(int*arr, int arrSz){
    int f[100001]; clr(f);
    for(int z=0;z<arrSz;z++){int v = arr[z];
        f[v]++;
    }
    qsort(f, 100001, sizeof(int), cmp);
    int n = arrSz;
    int r = 0;
    int ans = 0;
    for(int i = 100000; i >= 0; i--){
        r += f[i];
        ans++;
        if(r*2 >= n)
            break;
    }
    return ans;
}
