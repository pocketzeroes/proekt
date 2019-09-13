#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)
#define fill(arr, sz, val)do{     \
  for(int i=0; i<sz; i++)         \
    arr[i] = val;                 \
}while(0)

typedef long long ll;
enum{ MOD = 1000000007};
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

int main(){
  int n = in_nextInt();
  int colors[n][n]; clr(colors);
  for(int x = 0; x < n; x++)
    for(int y = 0; y < n; y++)
      colors[x][y] = in_nextInt()-1;
  int array[n]; clr(array);
  bool used[n]; clr(used);
  for(int z = 0; z < n; z++){
    for(int a = 0; a < n; a++){
      if(!used[a]){
        int color = -1;
        int count = 0;
        for(int b = 0; b < n; b++){
          if(!used[b] && b != a && (color == -1 || colors[a][b] == color)){
            color = colors[a][b];
            count++;
          }
        }
        if(count == n - z - 1){
          array[z] = color;
          used[a] = true;
        }
      }
    }
  }
  ll choose[n+1][n+1]; clr(choose);
  for(int i = 0; i < n+1; i++)
    choose[i][0] = 1;
  for(int i = 1; i < n+1; i++)
    for(int j = 1; j < n+1; j++)
      choose[i][j] = (choose[i - 1][j - 1] + choose[i - 1][j]) % MOD;
  ll result = n;
  ll colorCount[300][n]; dfill(colorCount,300,n,1);
  for(int c = 2; c <= n; c++){
    ll prefix[n]; fill(prefix, n, 1);
    ll suffix[300][n];clr(suffix);
    fill(suffix[300-1], n, 1);
    for(int i = 300 - 2; i >= 0; i--)
      for(int j = 0; j < n; j++)
        suffix[i][j] = suffix[i + 1][j] * colorCount[i + 1][j] % MOD;
    for(int d = 0; d < 300; d++){
      int count = 0;
      for(int e = 0; e < n; e++){
        result = (result + c * choose[count][c - 1] % MOD * prefix[e] % MOD * suffix[d][e]) % MOD;
        colorCount[d][e] = (colorCount[d][e] + choose[count][c - 1]) % MOD;
        prefix[e] = (prefix[e] * colorCount[d][e]) % MOD;
        if(array[e] == d)
          count++;
      }
    }
  }
  printf("%lld\n", result);
  return 0;
}
