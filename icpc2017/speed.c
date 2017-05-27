#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

double min(double a,double b){return a<b?a:b;}
double max(double a,double b){return a>b?a:b;}

enum{ N=123456};

int d[N];
int s[N];
int main(){
  int n,t;
  scanf("%d %d", &n,&t);
  double low=-1e10;
  for(int i=0;i<n;i++){
    scanf("%d %d", d+i, s+i);
    low = max(low,-1.0*s[i]);
  }
  double high=1e10;
  for(int it=0;it<200; it++){
    double mid=0.5*(low+high);
    double sum=0;
    for(int i=0;i<n;i++){
      sum+=d[i]/(s[i]+mid);
    }
    if(sum>t){
      low=mid;
    }
    else{
      high=mid;
    }
  }
  printf("%.17f\n",0.5*(low+high));
  return 0;
}
