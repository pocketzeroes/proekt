void amax(int*x, int y){
    if(*x < y)
       *x = y;
}
int largestOverlap(int**A, int Asz, int*A0sz, int**B, int Bsz, int*B0sz){
    if(Asz==0||Bsz==0){
        return 0;
    }
    int H = Asz;
    int W = A0sz[0];
    bool in(int y, int x){
        return 0 <= y && y < H && 0 <= x && x < W;
    }
    int ans = 0;
    for(int i=-H; i<=H; i++) 
        for(int j=-W; j<=W; j++) {
            int cnt = 0;
            for(int y=0; y<H; y++) 
                for(int x=0; x<W; x++) {
                    if (in(y+i, x+j) && A[y][x] && B[y+i][x+j]) 
                        cnt++;
                }
            amax(&ans, cnt);
        }
    return ans;
}
