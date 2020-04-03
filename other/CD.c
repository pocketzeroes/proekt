#include<stdio.h>
#include<string.h>

enum{MAXN = 1000100};
int lis1[MAXN],
    lis2[MAXN];
int n1, n2, i1, i2, ans;

int main(){
  scanf("%d%d", &n1, &n2);
  while(n1 != 0 || n2 != 0){
    ans = 0;
    for(int i = 0; i < n1; ++i)
      scanf("%d", &lis1[i]);
    for(int i = 0; i < n2; ++i)
      scanf("%d", &lis2[i]);
    i1 = i2 = 0;
    while(i1 < n1 && i2 < n2){
      if(lis1[i1] < lis2[i2])
        ++i1;
      else if(lis1[i1] > lis2[i2])
        ++i2;
      else{
        ++i1;
        ++i2;
        ++ans;
      }
    }
    printf("%d\n", ans);
    scanf("%d%d", &n1, &n2);
  }
  return 0;
}
