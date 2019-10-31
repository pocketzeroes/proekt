#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<complex.h>

#define EPS 1e-8
#define newpt __builtin_complex
typedef complex double pt;


typedef struct{
  pt p, q;
}line;

double cross(pt p, pt q){
  return cimag(p*conj(q));
}
bool isect_iline(line l1, line l2, pt*isect){
  double den = cross(l1.q-l1.p, l2.p-l2.q);
  if(fabsl(den) < EPS)
    return false;
  double num = cross(l2.p-l1.p, l2.p-l2.q);
 *isect = l1.p + (l1.q-l1.p)*num/den;
  return true;
}
double area(line l1, line l2, line l3){
  pt i1, i2, i3;
  if(!isect_iline(l1, l2, &i1)) return 0;
  if(!isect_iline(l2, l3, &i2)) return 0;
  if(!isect_iline(l3, l1, &i3)) return 0;
  return cabs(i1-i2) + cabs(i2-i3) + cabs(i3-i1);
}
int main(){
  int n;
  scanf("%d", &n);
  line lines[n];
  for(int z=0;z<n;z++){
    double x1, y1, x2, y2;
    scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
    lines[z].p = newpt(x1, y1);
    lines[z].q = newpt(x2, y2);
  }
  double best = 0;
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < i; ++j)
      for(int k = 0; k < j; ++k)
        best = fmaxl(best, area(lines[i], lines[j], lines[k]));
  if(best < EPS)
    puts("no triangle");
  else
    printf("%.10lf\n", best);
  return 0;
}
