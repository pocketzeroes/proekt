#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAX =      1000100};
enum{ mod =(int) 1e9 + 7};

int main(){
  static char a[MAX];
  int N, M;
  scanf("%d %d", &N, &M);
  scanf("%s", a);
  int h = 0, ans = 1;
  for (int i = 0; i < N; ++i) {
    h = (h * 10 + a[i]-'0') % M;
    if (h == 0 && i < N-1) 
      ans = ans*2 % mod;
  }
  if (h) 
    ans = 0;
  printf("%d\n", ans);
  return 0;
}
