#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXN = (int)5e5+228};

int l[MAXN], r[MAXN], n, cnt;

int main(){
  scanf("%d", &n);
  for(int i=1;i<=n;++i) {
    scanf("%d %d", &l[i], &r[i]);
  }
  for(int i=1;i<=n;++i) {
    for(int j=1;j<=n;++j) {
      if(l[j] < l[i] && r[i] < r[j]){
        cnt++;
        break;
      }
    }
  }
  printf("%d\n", cnt);
  return 0;
}
