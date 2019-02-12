#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int main(){
  int V;
  scanf("%d", &V);
  int ans = 4 * V + 2;
  for(int d1 = 1; d1 * d1 * d1 <= V; ++d1){
    if(V % d1 == 0){
      for(int d2 = d1; d1 * d2 * d2 <= V; ++d2){
        if(V % (d1 * d2) == 0){
          int d3 = V/d1/d2;
          ans = min(ans, 2 * (d1*d2 + d1*d3 + d2*d3));
        }
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}
