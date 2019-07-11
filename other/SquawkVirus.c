#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
int main(){
  int c = 1;
  int n = in_nextInt();
  int m = in_nextInt();
  int s = in_nextInt();
  int t = in_nextInt();
  int a[n][n]; memset(a, 0, sizeof(a));
  for(int i = 0; i < m; i++){
    int x = in_nextInt();
    int y = in_nextInt();
    a[x][y] = 1;
    a[y][x] = 1;
  }
  ll b[t+1][n]; memset(b, 0, sizeof(b));
  b[0][s] = 1;
  for(int i = 1; i < t+1; i++){
    for(int x = 0; x < n; x++){
      for(int y = 0; y < n; y++)
        b[i][x] += b[i-1][y]*a[x][y];
    }
  }
  ll total = 0;
  for(int x = 0; x < n; x++)
    total += b[t][x];
  printf("%lld\n", total);
  return 0;
}
