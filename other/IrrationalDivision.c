#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int answer(int p, int q){
  if ((p&1) && (q&1))   return 1;
  if ((p&1) && !(q&1))  return p < q ? 2 : 0;
  if (!(p&1) && (q&1))  return 0;
  if (!(p&1) && !(q&1)) return 0;
}
int main(){
  int p, q;
  scanf("%d %d", &p, &q);
  printf("%d\n", answer(p, q));
  return 0;
}
