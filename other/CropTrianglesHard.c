#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
typedef struct{
  int first;
  int second;
}pair;
bool peq(pair a, pair b){
  return a.first ==b.first && 
         a.second==b.second;
}

int i, j, k, m, n, l;
ll x[100001], y[100001];
ll remaindr[3][3];

ll triples(ll n) {
 return n * (n-1) * (n-2) / 6;
}
ll pairs(ll n) {
 return n * (n-1) / 2;
}
int main(){
 int tt, tn;
 scanf("%d", &tn);
 for(tt=1;tt<=tn;tt++) {
  ll A, B, C, D, x0, y0, M;
  scanf("%d %lld %lld %lld %lld %lld %lld %lld", &n, &A, &B, &C, &D, &x0, &y0, &M);
  x[0] = x0;
  y[0] = y0;
  for(i=1;i<=n-1;i++){
   x[i] = (A * x[i-1] + B) % M;
   y[i] = (C * y[i-1] + D) % M;
  }
  for(i=0;i<3;i++)
    for(j=0;j<3;j++)
      remaindr[i][j] = 0;
  for(i=0;i<n;i++)
   remaindr[ x[i] % 3 ][ y[i] % 3 ]++;
  ll ans = 0;
  for (int i1 = 0; i1 < 3; i1++)
   for (int j1 = 0; j1 < 3; j1++)
    for (int i2 = i1; i2 < 3; i2++)
     for (int j2 = 0; j2 < 3; j2++)
      if (i2 > i1 || j2 >= j1)
       for (int i3 = i2; i3 < 3; i3++)
        for (int j3 = 0; j3 < 3; j3++)
         if (i3 > i2 || j3 >= j2)
          if ((i1+i2+i3)%3 == 0 && (j1+j2+j3)%3==0){
           ll c1 = remaindr[i1][j1];
           ll c2 = remaindr[i2][j2];
           ll c3 = remaindr[i3][j3];
           pair p1 = (pair){i1, j1};
           pair p2 = (pair){i2, j2};
           pair p3 = (pair){i3, j3};
           if(!peq(p1, p2) && !peq(p2, p3))
             ans += c1 * c2 * c3;
           else if( peq(p1, p2) && peq(p2, p3)) ans += triples(c1);
           else if( peq(p1, p2) &&!peq(p2, p3)) ans += pairs(c1) * c3;
           else if(!peq(p1, p2) && peq(p2, p3)) ans += pairs(c3) * c1;
           else return 5;
          }
  printf("Case #%d: %lld\n", tt, ans);
 }
 return 0;
}
