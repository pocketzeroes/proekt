#include<stdio.h>
int main(void){
  int n, a, b;
  double tot;
  scanf("%d", &n);
  int observations = 0;
  for(int i = 0; i < n; ++i){
    scanf("%d %d", &a, &b);
    tot += b;
    observations += a;
  }
  double rv= tot/(observations*60.);
  if(rv <= 1)
    puts("measurement error");
  else
    printf("%.9f\n", rv);
  return 0;   
}
