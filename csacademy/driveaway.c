#pragma GCC optimize "-O3"
#include<stdio.h>
enum{N = 200000};
inline int min(int a, int b) { return a < b ? a : b; }
int pq[1 + N + 1], iq[N + 1], cnt;
long long xx[N + 1];
inline int less(int u, int v) { return xx[u] > xx[v]; }
int i2(int i){
  return (i *= 2) > cnt ? 0 : i < cnt && less(pq[i + 1], pq[i]) ? i + 1 : i;
}
void pq_up(int u){
  int i, j, v;
  for(i = iq[u]; (j = i / 2) && less(u, v = pq[j]); i = j)
    pq[iq[v] = i] = v;
  pq[iq[u] = i] = u;
}
void pq_dn(int u){
  int i, j, v;
  for (i = iq[u]; (j = i2(i)) && less(v = pq[j], u); i = j)
    pq[iq[v] = i] = v;
  pq[iq[u] = i] = u;
}
void pq_add(int u){
  iq[u] = ++cnt, pq_up(u);
}
void pq_remove(int u){
  if (iq[u]) {
    int v = pq[cnt--];
    if (v != u)
      iq[v] = iq[u], pq_up(v), pq_dn(v);
    iq[u] = 0;
  }
}
int pq_remove_first(){
  int u = pq[1];
  pq_remove(u);
  return u;
}
int main(){
  static int aa[N + 2], ll[N + 1], rr[N + 1];
  int n, x, h, i;
  long long cost;
  scanf("%d%d", &n, &x);
  cost = 0;
  for(i = 1; i <= n; i++){
    scanf("%d", &aa[i]);
    cost += aa[i];
  }
  for(i = 0; i <= n; i++)
    ll[i] = rr[i] = i;
  for(i = 1; i < n; i++) {
    xx[i] = min(aa[i] + aa[i + 1], x);
    pq_add(i);
  }
  for(h = 1; h <= n / 2; h++){
    int u = pq_remove_first(), l, r;
    printf("%lld\n", cost -= xx[u]);
    l = ll[u - 1], r = rr[rr[u] + 1];
    pq_remove(l), pq_remove(rr[u] + 1);
    rr[l] = r, ll[r] = l;
    if(l > 0 && r < n){
      xx[l] = xx[l] + xx[rr[u] + 1] - xx[u];
      pq_add(l);
    }
  }
  return 0;
}
