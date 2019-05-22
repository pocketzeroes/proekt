#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define EPS 1e-9
#define eq(a,b) ( ((a)-EPS <= (b)) && ((b) <= (a)+EPS) )
#define lt(a,b) ( (a)+EPS < (b) )
#define gt(a,b) ( (a)-EPS > (b) )

typedef struct{
   double x, y;
}pt;
pt newpt(double X, double Y){
   pt rez;
   rez.x = X;
   rez.y = Y;
   return rez;
}
bool cmpPt(pt p1, pt p2){
   return eq(p1.x, p2.x) && eq(p1.y, p2.y);
}
typedef struct{
   pt a, b;
}line;
line newline(pt A, pt B){
   line rez;
   rez.a = A;
   rez.b = B;
   return rez;
}
typedef struct{
   double A, B, C;
}pravac;
pravac newpravac(line S){
   pravac rez;
   rez.A = S.b.y - S.a.y;
   rez.B = S.a.x - S.b.x;
   rez.C = rez.A*S.a.x + rez.B*S.a.y;
   return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
line*pushbackLine(line*array, int*size, line value){
  line*output = resizeArray(array, line, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  line*ptr;
  int sz;
}vecline;
vecline newVecLine(){
  vecline rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
void erase(vecline*v, int pos){
   for(int i=pos; i < v->sz-1; i++)
       v->ptr[i] = v->ptr[i+1];
   (v->sz)--;
}
vecline niz;

int mysgn(double val){
   if( lt( val, 0 ))
      return -1;
   if( gt( val, 0 ))
      return 1;
   return 0;
}
int ccw(pt A, pt B, pt C){
   return mysgn((B.x-A.x)*(C.y-A.y) - (C.x-A.x)*(B.y-A.y));
}
int strana(pravac L, pt T){
   return mysgn(L.A*T.x + L.B*T.y - L.C);
}
bool sijece(pravac L, pt P){
   return eq( L.A*P.x + L.B*P.y - L.C, 0 );
}
bool sijece2(line S, pt P){
   return sijece( newpravac(S), P ) && eq( fabs(S.b.x-P.x)+fabs(S.a.x-P.x), fabs(S.b.x-S.a.x) ) && eq( fabs(S.b.y-P.y)+fabs(S.a.y-P.y), fabs(S.b.y-S.a.y) );
}
bool sijece3(pravac L1, pravac L2){
   return !eq( L1.A*L2.B, L2.A*L1.B );
}
bool sijece4(pravac L, line S){
   return strana( L, S.a ) * strana( L, S.b ) <= 0;
}
bool sijece5(line S1, line S2){
   if(sijece(newpravac(S1), S2.a )&&
      sijece(newpravac(S1), S2.b ))
        return sijece2(S1, S2.a)||
               sijece2(S1, S2.b)||
               sijece2(S2, S1.a)||
               sijece2(S2, S1.b);
   return sijece4(newpravac(S1), S2)&&
          sijece4(newpravac(S2), S1);
}
pt sjeciste(pravac L1, pravac L2){
   return newpt( (L1.C*L2.B-L2.C*L1.B) / (L1.A*L2.B-L2.A*L1.B), (L1.A*L2.C-L2.A*L1.C) / (L1.A*L2.B-L2.A*L1.B) );
}
bool between(pt A, pt B, pt C){
   if(lt(fabs(A.x-C.x),fabs(A.x-B.x)))
      return 0;
   if(lt(fabs(A.y-C.y),fabs(A.y-B.y)))
      return 0;
   if(lt(fabs(A.x-C.x),fabs(C.x-B.x)))
      return 0;
   if(lt(fabs(A.y-C.y),fabs(C.y-B.y)))
      return 0;
   return 1;
}
bool treba_spojit(line s1, line s2){
   if(ccw(s1.a,s1.b,s2.a)!=0 || ccw(s1.a,s1.b,s2.b)!=0)
      return 0;
   if(between(s1.a,s2.a,s1.b) || between(s1.a,s2.b,s1.b))
      return 1;
   return 0;
}
line spoji(line s1, line s2){
   if(between(s1.a,s2.a,s1.b) && between(s1.a,s2.b,s1.b))
      return s1;
   if(between(s2.a,s1.a,s2.b) && between(s2.a,s1.b,s2.b))
      return s2;
   if(between(s1.a,s2.a,s1.b)){
      if(between(s2.a,s1.a,s2.b))
         return newline(s1.b,s2.b);
      if(between(s2.a,s1.b,s2.b))
         return newline(s1.a,s2.b);
   }
   if(between(s1.a,s2.b,s1.b)){
      if(between(s2.a,s1.a,s2.b))
         return newline(s1.b,s2.a);
      if(between(s2.a,s1.b,s2.b))
         return newline(s1.a,s2.a);
      return s1;
   }
   return s1;
}
int main(){
   int n;
   scanf("%d",&n);
   for(int i=0; i<n; i++){
      int x1, y1, x2, y2;
      scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
      niz.ptr = pushbackLine(niz.ptr, &niz.sz, newline(newpt(x1,y1),newpt(x2,y2)));
   }
   int spojio=1;
   while(spojio){
      spojio=0;
      for(int i=0; i<niz.sz; i++){
         for(int j=i+1; j<niz.sz; j++){
            if(treba_spojit(niz.ptr[i],niz.ptr[j])){
               spojio=1;
               niz.ptr[i]=spoji(niz.ptr[i],niz.ptr[j]);
               erase(&niz, j);
               break;
            }
         }
      }
   }
   int rez=0;
   for(int i=0; i<niz.sz; i++){
      for(int j=i+1; j<niz.sz; j++){
         for(int k=j+1; k<niz.sz; k++){
            if(sijece5(niz.ptr[i], niz.ptr[j])&&
               sijece5(niz.ptr[i], niz.ptr[k])&&
               sijece5(niz.ptr[j], niz.ptr[k])){
               if(!cmpPt(sjeciste(newpravac(niz.ptr[i]), newpravac(niz.ptr[j])),
                         sjeciste(newpravac(niz.ptr[i]), newpravac(niz.ptr[k])) ) )
                  rez++;
            }
         }
      }
   }
   printf("%d\n", rez);
   return 0;
}

