enum{ INF =(int) 1e9 + 5};
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int maxAbsValExpr(int*arr1, int arr1sz, int*arr2, int arr2sz){
    int n = arr1sz;
    int best1 = -INF, best2 = -INF, best3 = -INF, best4 = -INF;
    int answer = -INF;
    for (int i = 0; i < n; i++) {
        answer = max(answer, best1 + arr1[i] + arr2[i] + i);
        answer = max(answer, best2 - arr1[i] + arr2[i] + i);
        answer = max(answer, best3 + arr1[i] - arr2[i] + i);
        answer = max(answer, best4 - arr1[i] - arr2[i] + i);
        best1 = max(best1, -arr1[i] - arr2[i] - i);
        best2 = max(best2, arr1[i] - arr2[i] - i);
        best3 = max(best3, -arr1[i] + arr2[i] - i);
        best4 = max(best4, arr1[i] + arr2[i] - i);
    }
    return answer;
}
