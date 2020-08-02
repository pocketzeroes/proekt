#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define swap(a,b) do{ __typeof(a) tp; tp=a; a=b; b=tp; }while(0)

int minSwaps(int**grid, int gridSz, int*grid0sz){
    int n=gridSz;
    int v[n]; clr(v);
    for(int i=0; i<n; ++i){
        while(v[i]<n&&grid[i][n-v[i]-1]==0)
            ++v[i];
    }
    int ans=0;
    for(int i=0; i<n; ++i){
        int j=i;
        while(j<n&&v[j]<n-1-i)
            ++j;
        if(j>=n)
            return -1;
        ans+=j-i;
        while(j>i){
            swap(v[j], v[j-1]);
            --j;
        }
    }
    return ans;
}
