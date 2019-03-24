int max(int a,int b){return a>b?a:b;}
enum{ INF =(int) 1e9 + 5};

int maxScoreSightseeingPair(int*A, int Asz){
    int n = Asz, best = -INF;
    int most = -INF;
    for (int i = 0; i < n; i++) {
        best = max(best, A[i] - i + most);
        most = max(most, A[i] + i);
    }
    return best;
}
