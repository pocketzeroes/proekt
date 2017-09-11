#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ ARRS = (ll)1e5+100};

typedef struct pairS{
   ll first;
   ll second;
}pair;
pair newPair(ll a, ll b){
   pair rez;
   rez.first =a;
   rez.second=b;
   return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first == b->first)return (a->second < b->second)?-1:1;
  return (a->first < b->first)?-1:1;
}
////////////////////
ll   a[ARRS];
pair b[ARRS];// ll ll

int main(){
   ll n, p, m, q;
   ll p1, p2, k;
   scanf("%lld %lld", &n, &q);
   for(int i=0; i<n; i++){
      scanf("%lld", &a[i]);
      b[i] = newPair(a[i], i);
   }
   qsort(b, n, sizeof(pair), cmpP);
   while(q--){
      scanf("%lld", &k);
      ll c=0, x=0;
      while(c<k-1){
         if(b[x].second < k-1)
            c++;
         x++;
      }
      x--;
      ll d=1, p=0;
      for(int i=k-1; i<n; i++){
         if(a[i]>=b[x].first)
            p+=a[i]*d;
         else {
            p+=b[x].first*d;
            x--;
            while(x&&b[x].second>i)
               x--;
         }
         d=d*-1;
      }
      while(x>=0){
         p+=b[x].first*d;
         d*=-1;
         x--;
      }
      printf("%lld\n", p);
   }
   return 0;
}




















































