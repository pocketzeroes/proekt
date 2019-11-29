#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<complex.h>
#define newpt __builtin_complex
typedef long long ll;
typedef complex double pt;
int n;

#define back(vv) vv.ptr[vv.sz-1]
#define pb(zpv, zvv) zpv.ptr = pushbackPt(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pt*pushbackPt(pt*array, int *size, pt value){
   pt*output = resizeArray(array, pt, *size + 1);
   output[(*size)++] = value;
   return output;
}
typedef struct{
	pt*ptr;
	int sz;
}vecpt;
vecpt newVecPt(){
	vecpt rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
//////////////////////////

int cpxlt(const void*pa, const void*pb){
  pt*p=(pt*)pa;
  pt*q=(pt*)pb;
  if(creal(*p) != creal(*q))
    return(creal(*p) < creal(*q))?-1:1;
  return(cimag(*p) < cimag(*q))?-1:1;
}
ll cross(pt p, pt q){
  return cimag(conj(p)*q);
}
int main(){
  scanf("%d", &n);
  vecpt pts = newVecPt();
  for(int i=0; i<n; ++i){
    char ch;
    double dx, dy;
    scanf("%lf %lf %c", &dx, &dy, &ch);
    pt p = newpt(dx, dy);
    if(ch == 'Y')
      pb(pts, p);
  }
  qsort(pts.ptr, pts.sz, sizeof(pt), cpxlt);
  vecpt top = newVecPt();
  vecpt bot = newVecPt();
  for(int i=0; i<pts.sz; i++){pt di=pts.ptr[i];
    while(top.sz>=2 && cross(top.ptr[top.sz-1]-top.ptr[top.sz-2], di - back(top))>0)
      top.sz--;
    pb(top, di);
    while(bot.sz>=2 && cross(bot.ptr[bot.sz-1]-bot.ptr[bot.sz-2], di - back(bot))<0)
      bot.sz--;
    pb(bot, di);
  }
  printf("%d\n", pts.sz);
  for(int i=0; i<bot.sz; ++i)
    if(i+1 < bot.sz)
      printf("%.0lf %.0lf\n", creal(bot.ptr[i]), cimag(bot.ptr[i]));
  for(int i=top.sz-1; i>=0; --i)
    if(i)
      printf("%.0lf %.0lf\n", creal(top.ptr[i]), cimag(top.ptr[i]));
  return 0;
}
