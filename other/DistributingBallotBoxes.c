#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ max    = 500000};
enum{ maxpop = 5000000};
int a[max];
int N, B;

bool ok (int x){
  int c = 0;
  for (int i = 0; i < N && c <= B; i++)
    c += (a[i] + x - 1) / x;
  return (c <= B);
}
int busca (){
  int x = 1;
  int y = maxpop;
  while (y - x > 1){
    int z = (x + y) / 2;
    if (ok(z)) y = z;
    else x = z;
  }
  if (ok(x)) return x;
  else return y;
}
int main (){
  for(;;){
   scanf("%d %d", &N, &B);
   if (N < 0)
     break;
   for (int i = 0; i < N; i++)
     scanf("%d", &a[i]);
   int ret = busca();
   printf("%d\n", ret);
  }
  return 0;
}
