#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int main(){
  int a1, b1, a2, b2;
  int c1, d1, c2, d2;
  scanf("%d%d%d%d%d%d%d%d", &a1, &b1, &a2, &b2, &c1, &d1, &c2, &d2);
  ll pg = 0, pe = 0;
  ll f = (d2-c2+1);
  for (int g1 = a1; g1 <= b1; ++g1){
    for (int g2 = a2; g2 <= b2; ++g2){
      for (int e1 = c1; e1 <= d1; ++e1) {
        int even = g1+g2-e1;
        if (even < c2) 
          pe += f;
        else if (even > d2) 
          pg += f;
        else {
          pg += (even-c2);
          pe += (d2-even);
        }
      }
    }
  }
  if (pe == pg) {
    printf("Tie\n");
  }
  else if (pe > pg) {
    printf("Emma\n");
  }
  else {
    printf("Gunnar\n");
  }
  return 0;
}
