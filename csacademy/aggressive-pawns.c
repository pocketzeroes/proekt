#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int X1,Y1,X2,Y2,X3,Y3;

int main() {
   int t;
   scanf("%d", &t);
   while(t--){
      scanf("%d %d %d %d %d %d", &X1, &Y1, &X2, &Y2, &X3, &Y3); 
      int d1 = abs(X1 - X3) + abs(Y1 - Y3);
      int d2 = fmax(abs(X2 - X3),abs(Y2 - Y3));
      if(d1 < d2){
         puts("First");
      }
      else if(d1 == d2){
         puts("Same time");
      }
      else{
         puts("Second");
      }
   }
   return 0;
}
