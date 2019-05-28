#include<stdio.h>
int main(){
  int n1, n2;
  scanf("%d%d", &n1, &n2);
  n2 -= n1;
  if (n2 > 180) 
    n2 -= 360;
  if (n2 <= -180) 
    n2 += 360;
  printf("%d\n", n2);
  return 0;
}
