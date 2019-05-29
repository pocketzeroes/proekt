#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
inline ll min(ll a, ll b){return a<b?a:b;}
inline ll max(ll a, ll b){return a>b?a:b;}

enum{ MAX = 2 * 200 + 2};

ll dp_max[MAX][MAX], 
   dp_min[MAX][MAX];
char   op[MAX];

int main(){
  int i, j, k, size, number, n;
  scanf("%d", &n);
  for (i = 0; i < n; i++){
    scanf("%d %c", &number, &op[i]);
    op[i+n] = op[i];
    dp_min[i][i] = dp_max[i][i] = dp_min[i+n][i+n] = dp_max[i+n][i+n] = number;
  }
  for (size = 1; size < n; size++){
    for (i = 0, j = i+size; j < 2*n; i++, j++){
      dp_min[i][j] = LLONG_MAX, dp_max[i][j] = LLONG_MIN;
      for (k = i; k < j; k++) {
        if (op[k] == '+' || op[k] == '?') {      
          dp_max[i][j] = max(dp_max[i][j], dp_max[i][k] + dp_max[k+1][j]);
          dp_min[i][j] = min(dp_min[i][j], dp_min[i][k] + dp_min[k+1][j]);
        }
        if (op[k] == '-' || op[k] == '?') {       
          dp_max[i][j] = max(dp_max[i][j], dp_max[i][k] - dp_min[k+1][j]);
          dp_min[i][j] = min(dp_min[i][j], dp_min[i][k] - dp_max[k+1][j]);
        }
        if (op[k] == '*' || op[k] == '?') {      
          dp_max[i][j] = max(dp_max[i][j], max(dp_max[i][k] * dp_max[k+1][j], dp_min[i][k] * dp_min[k+1][j]));
          dp_max[i][j] = max(dp_max[i][j], max(dp_max[i][k] * dp_min[k+1][j], dp_min[i][k] * dp_max[k+1][j]));
          dp_min[i][j] = min(dp_min[i][j], min(dp_min[i][k] * dp_min[k+1][j], dp_max[i][k] * dp_min[k+1][j]));
          dp_min[i][j] = min(dp_min[i][j], min(dp_min[i][k] * dp_max[k+1][j], dp_max[i][k] * dp_max[k+1][j]));
        }
      }
    }
  }
  for (i = 0; i < n; i++) 
    printf("%lld%lld", llabs(dp_min[i][n+i-1]), llabs(dp_max[i][n+i-1]));
  puts("");
  return 0;
}
