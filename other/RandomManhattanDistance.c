#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>


#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}
#define Reverse(nums, start, end){   \
   while(start < end){               \
      swap(nums[start], nums[end]);  \
      start++;                       \
      end  --;                       \
   }                                 \
}
typedef struct{
  double first;
  double second;
  double third;
}trip;
trip newtrip(double a, double b, double c){
  return(trip){a,b,c};
}
#define pb(zpv, zvv) zpv.ptr = pushbackT(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
trip*pushbackT(trip*array, int *size, trip value){
   trip*output = resizeArray(array, trip, *size + 1);
   output[(*size)++] = value;
   return output;
}
typedef struct{
   trip*ptr;
   int sz;
}vect;
vect newVecT() {
   vect rez;
   rez.ptr = NULL;
   rez.sz  = 0;
   return rez;
}

ll*minElement(ll*first, ll*last){
  if(first==last)
    return last;
  ll*smallest = first;
  while(++first != last)
    if(*first < *smallest)
      smallest = first;
  return smallest;
}
int main(){
   int N;
   scanf("%d", &N);
   ll*xs =(ll*)calloc(N, sizeof(ll));
   ll*ys =(ll*)calloc(N, sizeof(ll));
   ll*xsp = xs;
   ll*ysp = ys;
   for(int i=0; i<N; i++)
      scanf("%lld %lld", &xs[i], &ys[i]);
   double r=.0;
   for(int outer=0; outer<2; outer++){
      int hix0 = minElement(&xsp[0], &xsp[N]) - &xsp[0];
      int lox0 = hix0;
      double ht(ll x, int p0, int p1){
         if (x == xsp[p0])
            return ysp[p0];
         if (x == xsp[p1])
            return ysp[p1];
         return ysp[p0]+(x-xsp[p0])*(ysp[p1]-ysp[p0])/(double)(xsp[p1]-xsp[p0]);
      }
      vect zones=newVecT();
      while (1){
         int hix1 = (hix0 + 1) % N;
         int lox1 = (lox0+N-1) % N;
         ll x0 = max(xsp[hix0], xsp[lox0]);
         if(x0 == xsp[hix1]){
            hix0 = hix1;
            continue;
         }
         if(x0 == xsp[lox1]){
            lox0 = lox1;
            continue;
         }
         ll x1 = min(xsp[hix1], xsp[lox1]);
         if(x1 < x0)
            break ;
         if(x1 == x0)
            fprintf(stderr, "Failed while building zones");
         double lft = ht(x0, hix0, hix1) - ht(x0, lox0, lox1);
         double rgt = ht(x1, hix0, hix1) - ht(x1, lox0, lox1);
         pb(zones, newtrip(lft, rgt, (double)(x1-x0)));
         if(x1 == xsp[hix1])
            hix0 = hix1;
         if(x1 == xsp[lox1])
            lox0 = lox1;
      }
      double s=0., cxa=0., sa=0., a2=0., x0=0.;
      for(int i=0; i<zones.sz; i++){trip z = zones.ptr[i];
         double lft = z.first,
                rgt = z.second,
                w   = z.third;
         s += (lft*lft+3*lft*rgt+rgt*rgt)*w*w*w/15.;
         double ta = (lft+rgt)*w/2.;
         double cx = x0 + (lft+2.*rgt)/(3.*(lft+rgt))*w;
         if(i)
            s += 2. * (cx - cxa / sa) * sa * ta;
         a2  += ta*(2.*sa+ta);
         sa  += ta;
         cxa += cx * ta;
         x0  += w;
      }
      r += s / a2;
      swap(xsp, ysp);
      int start = 0;
      int finis = N-1;
      Reverse(xsp, start, finis);
      start = 0;
      finis = N-1;
      Reverse(ysp, start, finis);
   }
   free(xs);
   free(ys);
   printf("%.15lf\n", r);
   return 0;
}
