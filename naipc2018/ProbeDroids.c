#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
// sol task f == Probe Droids
#define swap(a,b) do\
  {\
    a ^= b;\
    b ^= a;\
    a ^= b;\
  } while (0)

typedef long long ll;
inline ll min(ll a, ll b){return a<b?a:b;}
inline ll max(ll a, ll b){return a>b?a:b;}



ll gcd(ll a, ll b){
  if (b < a)
    swap(a, b) ;
  if (a == 0)
    return b ;
  return gcd(b % a, a);
}
ll triangle(ll a, ll b){
  ll twicearea = a * b ;
  ll perim = a + b + gcd(a, b) ;
  return (twicearea + perim) / 2 ;
}
ll quad(ll a, ll b, ll c){
  ll twicearea = (2 * c - a) * b ;
  ll perim = c + b + c-a + gcd(a, b) ;
  return (twicearea + perim) / 2 ;
}
ll val(ll t, ll w, ll h){
  if (t <= h)
    return triangle(w, t) ;
  else
    return quad(w-(t-h), h, w) ;
}

ll recur(ll x1, ll y1, ll x2, ll y2, ll lox, ll loy, ll w, ll h, ll togo, ll*x, ll*y){
  while (x1 + x2 <= w && y1 + y2 <= h && (x1 + x2) * loy >= (y1 + y2) * lox) {
    x1 += x2 ;
    y1 += y2 ;
  }
  ll xm = x1 + x2 ;
  ll ym = y1 + y2 ;
  if (xm > w || ym > h)
    return 0 ;
  ll r = 0 ;
  ll rightside = recur(x1, y1, xm, ym, lox, loy, w, h, togo, x, y) ;
  if (rightside > togo)
    return rightside ;
  togo -= rightside ;
  r += rightside ;
  if (xm * loy < ym * lox) {
    ll cnt = min(h/ym, w/xm) ;
    if (cnt > togo) {
      ll mul = togo + 1 ;
     *x = xm * mul ;
     *y = ym * mul ;
      return rightside + cnt ;
    }
    r += cnt ;
    togo -= cnt ;
  }
  r += recur(xm, ym, x2, y2, lox, loy, w, h, togo, x, y) ;
  return r ;
}
void solve(ll w, ll h, ll q, ll*x, ll*y){
  if (q < w){
    *x = q+1 ;
    *y = 0 ;
    return ;
  }
  if (q + h >= (w+1)*(h+1)-1) {
    *x = 0 ;
    *y = q + h - ((w+1)*(h+1)-1) + 1 ;
    return ;
  }
  ll b = 1 ;
  while (2 * b <= w + h)
    b += b ;
  ll lo = 0 ;
  for (; b; b>>=1)
    if (lo+b <= w+h && val(lo+b, w, h) <= q)
      lo += b ;
  q -= val(lo, w, h) ;
  ll x1 = 1 ;
  ll x2 = 0 ;
  ll y1 = 0 ;
  ll y2 = 1 ;
  ll xlo, ylo, xlo2, ylo2 ;
  if (lo < h) {
    xlo = w ;
    ylo = lo ;
    xlo2 = w ;
    ylo2 = lo+1 ;
  }
  else{
    xlo = w+h-lo ;
    ylo = h ;
    xlo2 = xlo-1 ;
    ylo2 = h ;
  }
  if (lo <= h)
    recur(x1, y1, x2, y2, xlo, ylo, w, h, q, x, y) ;
  else
    recur(x1, y1, x2, y2, xlo, ylo, w, h, q, x, y) ;
}

int main(){
  ll m, n, k, q;
  scanf("%lld %lld %lld", &m, &n, &k);
  m--, n--;
  for(int qn=0; qn<k; qn++){
    scanf("%lld", &q);
    ll seen = 0;
    ll x, y;
    solve(n, m, q-1, &x, &y);
    printf("%lld %lld\n", y+1, x+1);
  }
  return 0;
}
