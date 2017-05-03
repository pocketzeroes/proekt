#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int Asize;
int A0size;

int dfs(int i, int j, int**A, int n, int m){
    if(i == 0 || j == 0 || i == n-1 || j == m-1) return -1e6;
    A[i][j] = 0;
    int ans = 1;
    if(i-1 >= 0 && A[i-1][j]) ans += dfs(i-1, j, A, n, m);
    if(j-1 >= 0 && A[i][j-1]) ans += dfs(i, j-1, A, n, m);
    if(i+1 < n && A[i+1][j])  ans += dfs(i+1, j, A, n, m);
    if(j+1 < m && A[i][j+1])  ans += dfs(i, j+1, A, n, m);
    return ans;
}
int largestMatrixZone(int**A){
    int n = Asize;
    int m = A0size;
    int ans = -1;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(A[i][j])
                ans = max(dfs(i, j, A, n, m), ans);
    return ans;
}
int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    Asize =N;
    A0size=M;
    int**A=malloc(N*sizeof(int*));//[N][M];
    for(int i = 0; i < N; ++i)
        A[i]=malloc(M*sizeof(int));
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
            scanf("%d", &A[i][j]);
        }
    }
    printf("%d", largestMatrixZone(A) );
    return 0;
}
