#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int main(){
  int n, m;
  scanf("%d %d", &n, &m);
  int A[n][m];
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      scanf("%d", &A[i][j]);
    }
  }
  int comp[m][m]; memset(comp, 0, sizeof(comp));
  for(int j1=0; j1<m; j1++)
    for(int j2=0; j2<m; j2++)
      for(int i=0; i<n; i++)
        if(A[i][j1] < A[i][j2])
          comp[j1][j2] |= (1 << i);
  ll DP[m][1<<n]; memset(DP, 0, sizeof(DP));
  ll ans = 0;
  for(int rows_bM=1; rows_bM<(1 << n); rows_bM++){
    bool good_col[m]; memset(good_col, 0xff, sizeof(good_col));
    int in_my_col[n]; memset(in_my_col, 0, sizeof(in_my_col));
    for(int c=0; c<m; c++){
      int idx = 0;
      for(int r=0; r<n; r++)
        if((rows_bM >> r) & 1)
          in_my_col[idx++] = A[r][c];
      for(int i=0; i+2<idx; i++)
        if(!(in_my_col[i] < in_my_col[i+1] && in_my_col[i+1] < in_my_col[i+2]) && !(in_my_col[i] > in_my_col[i+1] && in_my_col[i+1] > in_my_col[i+2]))
          good_col[c] = false;
      if(good_col[c])
        ans++;
    }
    for(int en=0; en<m; en++)
      for(int st=0; st<en; st++)
        if(good_col[st] && good_col[en]){
          int cmp = comp[st][en] & rows_bM;
          DP[en][cmp] += DP[st][cmp] + 1; 
        }
    for(int en=0; en<m; en++)
      for(int st=0; st<en; st++)
        if(good_col[st] && good_col[en]){
          int cmp = comp[st][en] & rows_bM;
          ans += DP[en][cmp];
          DP[en][cmp] = 0;
        }
  }
  printf("%lld\n", ans);
  return 0;
}
