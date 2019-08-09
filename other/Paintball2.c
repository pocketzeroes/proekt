#include<stdio.h>
#include<math.h>

int n;
double x[1000],
       y[1000],
       r[1000];
int  top[1000];
int possible = 1;
double ne = 1000,
       nw = 1000;

void visit(int i){
   int j,k;
   double yy;
   if (top[i]++)
      return;
   for (j=0;j<n;j++){
      if (hypot(x[j]-x[i],y[j]-y[i]) < r[i]+r[j])
         visit(j);
   }
   if (y[i]-r[i] < 0)
      possible = 0;
   if (x[i]-r[i] < 0){
      yy = y[i] - sqrt(r[i]*r[i] - x[i]*x[i]);
      if (yy < nw)
         nw = yy;
   }
   if (x[i]+r[i] > 1000){
      yy = y[i] - sqrt(r[i]*r[i] - (1000-x[i])*(1000-x[i]));
      if (yy < ne)
         ne = yy;
   }
}
int main(){
   int i, j, k;
   scanf("%d", &n);
   for (i=0;i<n;i++)
      scanf("%lf%lf%lf", &x[i], &y[i], &r[i]);
   for (i=0;i<n;i++)
      if (y[i]+r[i] > 1000)
         visit(i);
   if (possible)
      printf("0.00 %0.2lf 1000.00 %0.2lf\n", nw, ne);
   else
      printf("IMPOSSIBLE\n");
   return 0;
}
