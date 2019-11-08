#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)

typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
int cmpP(pair a, pair b){
  if(a.first !=b.first )return(a.first <b.first )?-1:1;
  if(a.second!=b.second)return(a.second<b.second)?-1:1;
  return 0;
}
pair maxP(pair a,pair b){return cmpP(a,b)>0?a:b;}
pair minP(pair a,pair b){return cmpP(a,b)<0?a:b;}


typedef struct{
  double first, second;
}pdd;
pdd newpdd(double a, double b){
  return(pdd){a,b};
}
int cmpPd(pdd a, pdd b){
  if(a.first !=b.first )return(a.first <b.first )?-1:1;
  if(a.second!=b.second)return(a.second<b.second)?-1:1;
  return 0;
}
pdd maxPd(pdd a,pdd b){return cmpPd(a,b)>0?a:b;}
pdd minPd(pdd a,pdd b){return cmpPd(a,b)<0?a:b;}



pair A, B, C, D;

pdd opMul(int x, pdd y){
  return(pdd){x*y.first, x*y.second};
}
pdd opDiv(pdd y, int x){
  return(pdd){y.first/x,y.second/x};
}
pdd opAdd(pdd l, pdd r){
  return(pdd){l.first+r.first,l.second+r.second};
}
int sgn(pair a, pair b, pair c){
  return(b.second-a.second)*(c.first-a.first)-(b.first-a.first)*(c.second-a.second);
}
pdd get(pair a, pair b, pair c, pair d){
  return opDiv(opAdd(opMul(abs(sgn(a,b,c)), newpdd(d.first, d.second)),
               opMul(abs(sgn(a,b,d)), newpdd(c.first, c.second))),
               abs(sgn(a,b,c)) + abs(sgn(a,b,d)));
}
void solve(){
  scanf("%d %d %d %d %d %d %d %d", &A.first, &A.second, &B.first, &B.second, &C.first, &C.second, &D.first, &D.second);
  if(cmpP(A, B)>0)
    swap(A, B);
  if(cmpP(C, D)>0)
    swap(C, D);
  int a1 = sgn(A, B, C),
      a2 = sgn(A, B, D);
  if(a1 > a2)
    swap(a1, a2);
  if(!(a1 <= 0 && a2 >= 0)){
    puts("none");
    return;
  }
  if(a1 == 0 && a2 == 0){
    if(sgn(A, C, D) != 0){
      puts("none");
      return;
    }
    pair x1 = maxP(A, C),
         x2 = minP(B, D);
    int cmpX1X2 = cmpP(x1, x2);
    if(cmpX1X2 > 0)
      puts("none");
    else if(cmpX1X2 == 0)
      printf("%.2lf %.2lf\n", (double)x1.first, (double)x1.second);
    else
      printf("%.2lf %.2lf %.2lf %.2lf\n", (double)x1.first, (double)x1.second, (double)x2.first, (double)x2.second);
    return;
  }
  pdd z = get(A, B, C, D);
  if(cmpPd(newpdd((double)A.first, (double)A.second), z)<=0 &&
     cmpPd(z, newpdd((double)B.first, (double)B.second))<=0  )
    printf("%.2lf %.2lf\n", z.first, z.second);
  else
    puts("none");
}
int main(){
  int n;
  scanf("%d", &n);
  for(int i=0; i<n; i++)
    solve();
  return 0;
}
