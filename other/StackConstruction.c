#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char*getstr(){
  char line[2000];
  gets(line);
  return strdup(line);
}

enum{ MAXN = 200};

int best[MAXN][MAXN+1];
char*str;

int solve(int i, int j){
  if (i > j)
    return 0;
  if (best[i][j] == -1){
    best[i][j] = 1+solve(i, j-1);
    for (int k = i; k < j; ++k)
      if (str[k] == str[j])
        best[i][j] = fmin(best[i][j], solve(i,k) + solve(k+1,j-1));
  }
  return best[i][j];
}
int main(){
  int t;
  scanf("%d", &t);
  getchar();
  while(t--){
    memset(best, -1, sizeof(best));
    str = getstr();
    int n = strlen(str);
    printf("%d\n", n+2*solve(0, n-1));
  }
  return 0;
}
