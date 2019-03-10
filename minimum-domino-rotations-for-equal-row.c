inline int min(int a,int b){return a<b?a:b;}
enum{ INF =(int) 1e9 + 5};

int minDominoRotations(int*A, int Asz, int*B, int Bsz){
    int n = Asz;
    int best = INF;
    for(int same = 1; same <= 6; same++){
        int a_cost = 0, b_cost = 0;
        for (int i = 0; i < n; i++){
            if (A[i] != same && B[i] != same){
                a_cost = b_cost = INF;
                break;
            }
            if (A[i] != same) a_cost++;
            if (B[i] != same) b_cost++;
        }
        best = min(best, min(a_cost, b_cost));
    }
    return best < INF / 2 ? best : -1;
}
