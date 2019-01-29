#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
  double cost;
  int lawns;
  scanf("%lf", &cost);
  scanf("%d", &lawns);
  double sum = 0;
  for(int i=0; i<lawns; i++){
    double w,l;
    scanf("%lf %lf", &w, &l);
    sum = sum + (w * l * cost);
  }
  printf("%lf\n", sum);
  return 0;
}
