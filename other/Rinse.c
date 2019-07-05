#include<stdio.h>

int i,j,k;
double vb, vw, vr, vc, avg, amt;
int main(){
  while(5 == scanf("%d %lf %lf %lf %lf", &k, &vb, &vw, &vr, &vc)){
    amt = vb + vw - vr;
    if(amt < 0){
      printf("0\n");
      continue;
    }
    avg = amt/k;
    if(avg >= vc-vr)
      avg = vc-vr;
    if(avg >= vw-vr){
      printf("%d %.20lf", k, avg-vw+vr);
      for(i=1;i<k;i++)
        printf(" %.20lf", avg);
      printf("\n");
    }
    else{
      avg = vb/(k-1);
      printf("%d 0.00", k);
      for(i=1;i<k;i++)
        printf(" %.20lf", avg);
      printf("\n");
    }
  }
  return 0;
}
