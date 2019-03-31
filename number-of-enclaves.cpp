class Solution {
  public:
void run(vector<vector<int>>&A, int i, int j, int h, int w) {
    A[i][j] = 0;
    int dy4[] = { -1, 0, 1, 0 };
    int dx4[] = { 0, 1, 0, -1 };
    for(int d=0;d<4;++d) {
        int di = dy4[d] + i;
        int dj = dx4[d] + j;
        if(!(0<=di && di<h) || !(0<=dj && dj<w))
            continue;
        if(A[di][dj] == 0)
            continue;
        A[di][dj] = 0;
        run(A, di, dj, h, w);
    }
}
int numEnclaves(vector<vector<int>>&A){
    int h = A.size(), 
        w = A[0].size();
    for(int i=0;i<h;++i){
        if(A[i][0] == 1) 
            run(A, i, 0, h, w);
        if(A[i][w-1] == 1)
            run(A, i, w-1, h, w);
    }
    for(int j=0;j<w;++j) {
        if(A[0][j] == 1)
            run(A, 0, j, h, w);
        if(A[h-1][j] == 1)
            run(A, h-1, j, h, w);
    }
    int ans = 0;
    for(int i=0;i<h;++i)
        for(int j=0;j<w;++j)
            ans += A[i][j];
    return ans;
}
};
