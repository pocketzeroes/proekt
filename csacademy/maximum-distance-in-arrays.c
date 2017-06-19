int max(int a,int b){return a>b?a:b;}

int maxDistance(int**arr, int arrSz, int*arrCols){
    int n   = arrSz;
    int ans = 0;
    for (int i = 0; i < n; i++){
        if (arrCols[i]){
            for (int j = i + 1; j < n; j++){
                if (arrCols[j]){
                    ans = max(ans, max(abs(arr[i][0] - arr[j][arrCols[j] - 1]),
                                       abs(arr[j][0] - arr[i][arrCols[i] - 1])));
                }
            }
        }
    }
    return ans;
}
