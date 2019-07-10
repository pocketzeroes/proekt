#include<stdio.h>
#include<math.h>
#include<assert.h>
enum{ MAXW = 1000};
int n;
double w[MAXW];
double ratio;

int cmp(const void *a,const void* b){
  double da = *(double*)a;
  double db = *(double*)b;
  if (da<db)
    return 1;
  else
    return -1;
}
int main(){
  int i,j,t,best_cuts;
  scanf("%lf %d",&ratio,&n);
  for (i=0;i<n;i++) {
    scanf("%lf",&w[i]);
  }
  qsort(w,n,sizeof(double),cmp);
  best_cuts = 1200;
  for (i=0;i<n;i++) {
    for (t=1;(t-1)*(i+1)< best_cuts;t++) {
      double largest = w[i]/t;
      int total_cuts = 0;
      int valid = 1;
      for (j=0;j<n && total_cuts<best_cuts && valid;j++) {
        int cuts = (int)ceil(w[j]/largest);
        valid &= (w[j]/cuts>largest * ratio);
        total_cuts += (cuts-1);
      }
      if (valid && total_cuts<best_cuts) {
        best_cuts = total_cuts;
      }
    }
  }
  assert(best_cuts <= 500);
  printf("%d\n",best_cuts);
  return 0;
}
