#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int n,l,t,k;

char*solve(){
  if (l < k) return "YES";
  if (n + t < k) return "YES";
  if (n + t == k && l <= 2 * k) return "YES";
  if (l == k && n + t <= 2 * k) return "YES";
  return "NO";
}
int main(){
  scanf("%d%d%d%d", &n, &l, &t, &k);
  puts( solve() );
  return 0;
}
