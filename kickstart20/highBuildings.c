#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void solve(){
  int n, a, b, c;
  scanf("%d %d %d %d", &n, &a, &b, &c);
  if(c+(a-c)+(b-c)>n||n>1&&a==c&&b==c&&c==1){
    puts("IMPOSSIBLE");
    return;
  }
  for(int i=(0); (1)>0?i<(a-c):i>(a-c); i+=(1))
    printf("%d ", n-1);
  if(c==1&&a>c){
    for(int i=(0); (1)>0?i<(n-(c+(a-c)+(b-c))):i>(n-(c+(a-c)+(b-c))); i+=(1))
      printf("%d ", n-2);
  }
  printf("%d ", n);
  if(c>1){
    for(int i=(0); (1)>0?i<(n-(c+(a-c)+(b-c))):i>(n-(c+(a-c)+(b-c))); i+=(1))
      printf("%d ", n-2);
  }
  for(int i=(0); (1)>0?i<(c-1):i>(c-1); i+=(1))
    printf("%d ", n);
  if(c==1&&a==c){
    for(int i=(0); (1)>0?i<(n-(c+(a-c)+(b-c))):i>(n-(c+(a-c)+(b-c))); i+=(1))
      printf("%d ", n-2);
  }
  for(int i=(0); (1)>0?i<(b-c):i>(b-c); i+=(1))
    printf("%d ", n-1);
  puts("");
}
int main(){
  int t;
  scanf("%d", &t);
  for(int i=(0); (1)>0?i<(t):i>(t); i+=(1)){
    printf("Case #%d: ", i+1);
    solve();
  }
  return 0;
}
