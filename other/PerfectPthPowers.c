#include <stdio.h>
#include <math.h>

double x,xx,b,r;
int p;
int main(){
   while (1 == scanf("%lf",&x)) {
      if (!x) return 0;
      xx = fabs(x);
      for (b=2;(r=b*b)<=xx;b++) {
         for (p=2;r<xx;p++) r*=b;
         if (r == xx) {
            if (x > 0 || p%2) {
               printf("%d\n",p);
               goto done;
            }
         }
      }
      printf("1\n");
   done:;} 
   printf("missing delimter\n");
   return 0;
}
