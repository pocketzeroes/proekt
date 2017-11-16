#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}
int cmp(const void*pa, const void*pb){
  ll*a=(ll*)pa;
  ll*b=(ll*)pb;
  return *a<*b ? -1:1;
}

const int oo      = 0x3f3f3f3f;
const double eps  = 1e-9;
enum{   MAXN = 1024*1024*10};
ll x        [MAXN];
int next_   [MAXN];
int gNext   [MAXN];
bool removed[MAXN];
int FUNCCALLS = 0;
int N, P, R;

ll gcd(ll a, ll b){
 if(b)return gcd(b, a % b);
 return a;
}
int getNext(int n){
  ++FUNCCALLS;
  if(removed[n]){
    return gNext[n] = getNext(gNext[n]);
  }
  return n;
}
int main(int argc, char**argv){
  scanf("%d %d %d", &N, &P, &R);
  for(int i = (0); i < (N); i++)
    scanf("%lld", &x[i]);
  qsort(x, N, sizeof(ll), cmp);
  ll toGo = (R) % P;
  bool fliped = false;
  for (int i = (0); i < (N); i++){
    next_[i] = (i>0?next_[i-1]:1);
    if(!fliped){
      while(next_[i] < N && x[next_[i]] < x[i] + toGo)
        ++next_[i];
    }
    if(next_[i] == N){
      next_[i] = 0;
      fliped = true;
    }
    if(fliped) {
      while(x[next_[i]] + P < x[i] + toGo)
        ++next_[i];
    }
  }
  ll iMinDist = (1LL<<60);
  ll iMaxDist = 0;
  ll iAverage = 0;
  ll iRuns    = 0;
  int laststart = x[N-1] - P;
  for (int j = (0); j < (N); j++){
    if(x[j] != laststart){
      for (int i = (0); i < (N); i++)
        removed[i] = false;
      for (int i = (0); i < (N); i++)
        gNext[i] = (i+1);
      gNext[N-1] = 0;
      ll iDist = R;
      int cur = j;
      removed[cur] = true;
      for (int i = (1); i < (N); i++){
        int n = next_[cur];
        n = getNext(n);
        ll dist = x[n] - x[cur];
        toGo = R - dist;
        dist += ((toGo + P - 1) / P) * P;
        iDist += dist;
        cur = n;
        removed[n] = true;
      }
      iMinDist = min(iMinDist, iDist);
      ll multiplyer = x[j] - laststart;
      iMaxDist = max(iMaxDist, iDist + multiplyer - 1);
      iAverage += iDist * multiplyer;
      iAverage += (multiplyer * (multiplyer - 1)) / 2;
      iRuns += multiplyer;
      laststart = x[j];
    }
  }
  ll gc = gcd(iAverage, iRuns);
  iAverage /= gc;
  iRuns    /= gc;
  printf("%lld\n", iMinDist);
  printf("%lld\n", iMaxDist);
  printf("%lld/%lld\n", iAverage, iRuns);
}






















































