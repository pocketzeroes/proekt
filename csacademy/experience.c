#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
  int *output = resizeArray(array, int, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct vecS {
  int*ptr;
  int sz;
}vec;
vec newVec() {
  vec rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
/////////////////
int n;
int a[100005];
vec e[100005];
ll dp[100005][2];

void solve(int x){
  ll sum = 0;
  for(int z=0;z<e[x].sz;z++){int y = e[x].ptr[z];
    solve(y);
    sum += max(dp[y][0], dp[y][1]);
  }
  dp[x][0] = sum;
  dp[x][1] = sum;
  for(int z=0;z<e[x].sz;z++){int y = e[x].ptr[z];
    if(a[x] <= a[y]){
      dp[x][0] = max(dp[x][0], sum - max(dp[y][0], dp[y][1]) + a[y] - a[x] + dp[y][0]);
    }
    if(a[x] >= a[y]){
      dp[x][1] = max(dp[x][1], sum - max(dp[y][0], dp[y][1]) + a[x] - a[y] + dp[y][1]);
    }
  }
}
int main(){
  scanf("%d", &n);
  for(int i=1; i<=n; i++){
    scanf("%d", &a[i]);
  }
  for (int i=1; i<n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    e[u].ptr = pushback(e[u].ptr, &e[u].sz, v);
  }
  solve(1);
  printf("%lld", max(dp[1][0], dp[1][1]));
}




















































