int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

enum{ INF =(int) 1e9 + 5};

int minHeightShelves(int**books, int booksSz, int*books0sz, int shelf_width){
    int n = booksSz;
    int dp[n+1]; fill(dp, n+1, INF);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        int width  = 0,
            height = 0;
        for (int j = i; j < n; j++){
            width += books[j][0];
            height = max(height, books[j][1]);
            if (width <= shelf_width)
                dp[j + 1] = min(dp[j + 1], dp[i] + height);
        }
    }
    return dp[n];
}
