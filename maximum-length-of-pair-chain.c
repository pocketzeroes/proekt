int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
void fill(int*arr,int sz, int val){
    for(int i=0;i<sz;i++)
        arr[i]=val;
}
int max_element(int*arr,int sz){
    int maxe=arr[0];
    for(int i=1;i<sz;i++)
        if(arr[i]>maxe)
            maxe=arr[i];
    return maxe;
}
typedef int* intp;
int cmp(const void*pa, const void*pb){
   intp*ar=(intp*)pa;
   intp*br=(intp*)pb;
   int*a=*ar;
   int*b=*br;
   if(a[0] != b[0]) return(a[0] < b[0])?-1:1;
   return(a[1] < b[1]) ? -1 : 1;
}

int findLongestChain(int**pairs, int pairsSz, int pairs0sz){
    qsort(pairs, pairsSz, sizeof(int*), cmp);
    int n = pairsSz;
    int dp[n];
    fill(dp, n, 1);
    for(int i = 0; i < n; i++){
        int cur = dp[i];
        for(int j = i + 1; j < n; j++) 
            if(pairs[i][1] < pairs[j][0]) 
                dp[j] = max(dp[j], cur + 1);
    }
    return max_element(dp, n);
}
