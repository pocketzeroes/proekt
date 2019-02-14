#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}


enum{ N  =(int)1e6 + 5};
enum{ MX = 30 };
int cnt[N][MX];
int arr[N];
int n, k;
pair dp[N];

int get(int l, int r){
  int ret = 0;
  for (int i = 0 ; i < MX ; i++)
    ret |= (cnt[r][i] - cnt[l-1][i] > 0 ? 1 << i : 0);
  return ret;
}
bool test(int mask){
  for (int i = 1, l = 1 ; i <= n ; i++) {
    while (l+1 <= i && (get(l+1, i) & mask) == mask)
      l++;
    if ((get(l, i) & mask) == mask) {
      dp[i] = dp[l-1];
      dp[i].first++;
    }
    else{
      dp[i].first = 0;
      dp[i].second = get(l, i) & mask;
    }
  }
  for(int i = 1 ; i <= n ; i++){
    pair cur = dp[i];
    int sisa = get(i+1, n);
    int res = cur.first;
    if (((sisa | cur.second) & mask) == mask)
      res++;
    if (res >= k)
      return 1;
  }
  return 0;
}
int main(){
  scanf("%d %d", &n, &k);
  for (int i = 1 ; i <= n ; i++){
    scanf("%d", &arr[i]);
    for (int j = 0 ; j < MX ; j++)
      cnt[i][j] = cnt[i-1][j] + ((arr[i] & (1 << j)) != 0);
  }
  int ret = 0;
  for (int i = MX - 1 ; i >= 0 ; i--)
    if (test(ret | (1 << i)))
      ret |= (1 << i);
  printf("%d\n", ret);
  return 0;
}
