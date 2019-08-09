#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

typedef long long ll;
char*S;
char*T[26];
ll K;

ll len[26][64];
const ll LIMIT = (ll)1e15;
char ans;

void add(ll*x, ll v){
  if(*x == -1 || v == -1)
    *x = -1;
  else{
    (*x) += v;
    if(*x >= LIMIT)
      *x = -1;
  }
}
void pre(){
  for (int i = 0; i < 26; i++) {
    len[i][0] = 1;
    len[i][1] = strlen(T[i]);
  }
  for (int t = 2; t < 64; t++)
    for (int i = 0; i < 26; i++)
      for(int z=0;T[i][z];z++){char x = T[i][z];
        add(&len[i][t], len[x - 'a'][t - 1]);
      }
}
bool ask(ll*m, char root, ll k){
  if (k == 0) {
    --(*m);
    ans = root;
    return(*m == 0);
  }
  if (k < 64 && len[root - 'a'][k] != -1 && len[root - 'a'][k] < *m){
    (*m) -= len[root - 'a'][k];
    return false;
  }
  if (k <= 100) {
    for(int z=0;T[root-'a'][z];z++){char child = T[root-'a'][z];
      if(ask(m, child, k - 1))
        return true;
    }
  } 
  else {
    int pos[26] = {};
    int now = root - 'a';
    int cnt = 1;
    while (pos[now] == 0) {
      pos[now] = cnt;
      now = T[now][0] - 'a';
      cnt++;
    }
    int cycle = cnt - pos[now];
    k -= (cnt - 1);
    k -= (k - 100) / cycle * cycle;
    k -= cycle;
    return ask(m, now + 'a', k);
  }
  return false;
}
void solve(){
  ll m;
  scanf("%lld", &m);
  for(size_t i = 0; S[i]; i++){
    if(ask(&m, S[i], K))
      break;
  }
  printf("%c\n", ans);
}
int main(){
  S=getstr();
  for(int i = 0; i < 26; i++)
    T[i]=getstr();
  scanf("%lld", &K);
  pre();
  int M;
  scanf("%d", &M);
  while (M--)
    solve();
  return 0;
}
