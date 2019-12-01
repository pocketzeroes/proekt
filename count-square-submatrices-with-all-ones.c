enum{NM_MAX = 305};
int N, M;
int sum[NM_MAX][NM_MAX];

int get_sum(int r1, int r2, int c1, int c2) {
    return sum[r2][c2] - sum[r2][c1] - sum[r1][c2] + sum[r1][c1];
}
int countSquares(int**matrix, int matrixSz, int*matrix0sz){
    N = matrixSz;
    M = matrixSz==0?0 : matrix0sz[0];
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + matrix[i][j];
    int answer = 0;
    for(int len = 1; len <= fmin(N, M); len++)
        for(int i = 0; i + len <= N; i++)
            for(int j = 0; j + len <= M; j++)
                answer += get_sum(i, i + len, j, j + len) == len * len;
    return answer;
}
