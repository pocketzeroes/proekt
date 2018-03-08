#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
typedef long long ll;

ll accumulate(int*arr,int sz){
  ll sum=0;
  for(int i=0;i<sz;i++)
    sum+=arr[i];
  return sum;
}
int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  int row[n]; memset(row, 0, sizeof(row));
  int col[m]; memset(col, 0, sizeof(col));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int x;
      scanf("%d", &x);
      x *= (i != 0 && i != n - 1 ? 2 : 1) * (j != 0 && j != m - 1 ? 2 : 1);
      row[i] += x;
      col[j] += x;
    }
  }
  int total = accumulate(row, n);
  int ans = total;
  for (int i = 1; i < n - 1; i++){
    int cur = total - row[i] / 2 + max(row[0], row[n - 1]);
    ans = max(ans, cur);
  }
  for (int j = 1; j < m - 1; j++){
    int cur = total - col[j] / 2 + max(col[0], col[m - 1]);
    ans = max(ans, cur);
  }
  printf("%d\n", ans);
  return 0;
}
