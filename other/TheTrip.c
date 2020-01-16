#include <stdio.h>

int cents[1000];
int
main(){
   int i,j,k,m,n;
   int sum,ave,ove,bal;
   int nove;
   double x;

   for (;;){
      scanf("%d",&n);
      if (!n) break;
      sum = 0;
      for (i=0;i<n;i++){
         scanf("%lf",&x);
         cents[i] = 100 * x + 0.1;
         sum += cents[i];
      }
      ave = sum/n;
      ove = 0;
      nove = 0;
      for (i=0;i<n;i++) if (cents[i] > ave) {
         nove++;
         ove += cents[i]-ave;
      }
      if (nove >= sum%n) bal = ove - sum%n;
      else bal = ove - nove;
      printf("$%0.2lf\n",(double)bal/100);
   }
   return 0;
}
