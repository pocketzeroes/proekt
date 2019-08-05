#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  double first;
  int    second;
}pdi;
pdi newPdi(double a, int b){
  pdi rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpPdi(const void*pa, const void*pb){
  pdi*a=(pdi*)pa;
  pdi*b=(pdi*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int cmpDbl(const void*pa, const void*pb){
  double*a =(double*)pa;
  double*b =(double*)pb;
  return(*a < *b)?-1:1;
}

typedef struct{
  double x, y;
}pt;
double len(pt p){
   return hypot(p.x, p.y);
}
int main(){
   int N;
   scanf("%d", &N);
   pt     poles   [N];
   double ht      [N], 
          poleht  [N],
          basearea[N];
   double x, y;
   pdi sortable[N-1], 
       areas   [N-1];
   for(int i=1; i<N; i++){
      scanf("%lf%lf", &x, &y);
      poles[i] = (pt){x, y};
      sortable[i-1] = newPdi(atan2(y, x), i);
   }
   qsort(sortable, N-1, sizeof(pdi), cmpPdi);
   for(int i=0; i<N; i++)
      scanf("%lf", &ht[i]);
   qsort(ht, N, sizeof(double), cmpDbl);
   for(int i=0; i+1<N; i++){
      int prev = (i + (N-1) - 1) % (N-1);
      int next = (i + (N-1) + 1) % (N-1);
      double angprev = sortable[i].first - sortable[prev].first;
      double angnext = sortable[next].first - sortable[i].first;
      double triangles = 0.5 * len(poles[sortable[i].second])*
                    (sin(angprev) * len(poles[sortable[prev].second])+
                     sin(angnext) * len(poles[sortable[next].second]));
      areas[i] = newPdi(triangles, i+1);
      basearea[i] = triangles ;
   }
   qsort(areas, N-1, sizeof(pdi), cmpPdi);
   poleht[0] = ht[N-1];
   for (int i=0; i<N-1; i++)
      poleht[areas[i].second] = ht[i];
   double v = 0.;
   for (int i=0; i<N-1; i++)
      v += (poleht[i+1] / 3 + poleht[0] / 6) * basearea[i] ;
   printf("%.2f\n", v);
   return 0;
}
