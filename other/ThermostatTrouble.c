#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
ll in_nextLong(){
  ll x;
  scanf("%lld", &x);
  return x;
}

typedef struct{
  ll n, d;
}Fraction;
Fraction newFraction(ll n, ll d){
  Fraction rez;
  rez.n = n;
  rez.d = d;
  return rez;
}
ll gcd(ll a, ll b){
  return b == 0 ? a : gcd(b, a % b);
}
Fraction reduce(Fraction f){
  ll div = gcd(f.n, f.d);
  return newFraction(f.n / div, f.d / div);
}
Fraction multiply(Fraction a, Fraction b){
  return reduce(newFraction(a.n * b.n, a.d * b.d));
}
Fraction add(Fraction a, Fraction b){
  return reduce(newFraction(a.n * b.d + b.n * a.d, a.d * b.d));
}
void toString(Fraction f){
  if(f.d<0){
    f.n = -f.n;
    f.d = -f.d;
  }
  printf("%lld/%lld\n", f.n, f.d);
}
int main(){
  int n = in_nextInt();
  int q = in_nextInt();
  ll l[n];
  ll h[n];
  for(int i = 0; i < n; i++){
    l[i] = in_nextLong();
    h[i] = in_nextLong();
  }
  for(int i = 0; i < q; i++){
    int a = in_nextInt() - 1;
    int b = in_nextInt() - 1;
    ll  x = in_nextLong();
    Fraction fraction1 = newFraction(x - l[a], h[a] - l[a]);
    Fraction fraction2 = newFraction(h[b] - l[b], 1);
    Fraction fraction3 = newFraction(l[b], 1);
    Fraction answer = add(multiply(fraction1, fraction2), fraction3);
    toString(answer);
  }
  return 0;
}
