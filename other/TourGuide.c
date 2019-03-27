#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>


void swap(int*nums, int i, int j){
  int t   = nums[i];
  nums[i] = nums[j];
  nums[j] = t;
}
void rev(int*s, int l, int r){
  while(l<r)
    swap(s, l++, r--);
}
int b_search(int*s,int l,int r,int key){
  int index = -1;
  while(l<=r){
    int mid = l+(r-l)/2;
    if(s[mid]<=key)
      r=mid-1;
    else{
      l=mid+1;
      if(index = -1 || s[index]<=s[mid])
        index = mid;
    }
  }
  return index;
}
bool next_permutation(int*s, int sl){
  int len = sl, i=len-2;
  while(i>=0 && s[i]>=s[i+1])
   --i;
  if(i<0)
    return false;
  else{
    int index=b_search(s, i+1, len-1, s[i]);
    swap(s, i, index);
    rev(s, i+1, len-1);
    return true;
  }
}

typedef struct Person{
  double x,y,vx,vy,v;
}Person;
int main(){
  int n;
  scanf("%d", &n);
  while(n){
    double v,a;
    scanf("%lf", &v);
    int order[n];     memset(order , 0, sizeof(order ));
    Person person[n]; memset(person, 0, sizeof(person));
    for(int i=0; i<n; i++){
      order[i] = i;
      scanf("%lf %lf %lf %lf", &person[i].x, &person[i].y, &person[i].v, &a);
      person[i].vx = cos(a)*person[i].v;
      person[i].vy = sin(a)*person[i].v;
    }
    double best=99999999;
    do{
      double last=0,t=0,cx=0,cy=0;
      for(int i=0; i<n; i++){
#define p person[order[i]]
        double ex=p.x+t*p.vx-cx,ey=p.y+t*p.vy-cy;
        double a=p.vx*p.vx+p.vy*p.vy-v*v;
        double b=2*ex*p.vx+2*ey*p.vy;
        double c=ex*ex+ey*ey;
        b/=a;
        c/=a;
        double d=-b/2;
        double e=sqrt(b*b/4-c);
        double f=99999999;
        if(d+e>=-1e-9 && d+e<f)
          f=d+e;        
        t+=f;
        cx=p.x+p.vx*t;
        cy=p.y+p.vy*t;
        double home=t+sqrt(cx*cx+cy*cy)/p.v;
#undef p
        if(home>last)
          last=home;
      }
      if(last<best)
        best=last;
    }
    while(next_permutation(order, n));
    printf("%d\n", (int) round(best) );
    scanf("%d", &n);
  }
  return 0;
}
