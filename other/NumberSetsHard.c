#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
void fill(bool*arr, int sz, bool val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
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


int p   [1000001];
int rank[1000001];

int root(int x){
  if (p[x] != x)
    p[x] = root(p[x]);
  return p[x];
}
void Union(int a, int b){
  a = root(a);
  b = root(b);
  if (rank[a] < rank[b])
    p[a] = b;
  else {
    p[b] = a;
    if (rank[a] == rank[b])
      rank[a]++;
  }
}
int main(){
  int caseCnt = in_nextInt();
  bool isPrime[1000001]; fill(isPrime, 1000001, true);
  for (int i=2; i<=1000000; i++)
    for (int j=2*i; j<=1000000; j+=i)
      isPrime[j] = false;
  for(int caseNum=1; caseNum <= caseCnt; caseNum++){
    printf("Case #%d: ", caseNum);
    ll  A = in_nextLong();
    ll  B = in_nextLong();
    int P = in_nextInt();
    for(int i=0; i < B - A + 1; i++){
      p[i] = i;
      rank[i] = 0;
    }
    int res = (int)(B - A + 1);
    for(int i=P; i<=1000000; i++){
      if (!isPrime[i])
        continue;
      ll x = A / i * i;
      if (x < A) x += i;
      x -= A;
      for (int y=(int)x; y < B - A + 1; y += i){
        if (root((int)x) != root(y)) {
          res--;
          Union((int)x, y);
        }
      }
    }
    printf("%d\n", res);
  }
  return 0;
}
