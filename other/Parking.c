#include<stdio.h>

int main(){
  int t;
  scanf("%d", &t);
  while(t--){
    int mi =  1000,
        ma = -1000;
    int n;
    scanf("%d", &n);
    while(n--){
      int x;
      scanf("%d", &x);
      if(x < mi)
         mi = x;
      if(x > ma)
         ma = x;
    }
    printf("%d\n", 2*(ma - mi));
  }
  return 0;
}
