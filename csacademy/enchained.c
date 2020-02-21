#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
enum{N   = 2000      };
enum{INF = 0x3f3f3f3f};
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }
void srand_(){
  struct timeval tv;
  gettimeofday(&tv, NULL);
  srand(tv.tv_sec ^ tv.tv_usec);
}
int rand_(int n){
  return (rand() * 76543LL + rand()) % n;
}
struct V {
  int l, r;
} uu[N + 1], vv[N + 1];
int compare_r(const void *a, const void *b){
  struct V *u = (struct V *) a;
  struct V *v = (struct V *) b;
  return u->r - v->r;
}
int compare_l(const void *a, const void *b){
  struct V *u = (struct V *) a;
  struct V *v = (struct V *) b;
  return v->l - u->l;
}
void sort(struct V *vv, int n, int (*compare)(const void *a, const void *b)){
  int i;
  for (i = 0; i < n; i++) {
    int j = rand_(i + 1);
    struct V tmp;
    tmp = vv[i], vv[i] = vv[j], vv[j] = tmp;
  }
  qsort(vv, n, sizeof *vv, compare);
}
int n_;
void build(int *st, int *aa){
  int i;
  for (i = 0; i < n_; i++)
    st[n_ + i] = aa[i];
  for (i = n_ - 1; i > 0; i--)
    st[i] = max(st[i << 1], st[i << 1 | 1]);
}
int query(int *st, int l, int r){
  int x = -1;
  for (l += n_, r += n_; l <= r; l >>= 1, r >>= 1) {
    if ((l & 1) == 1)
      x = max(x, st[l++]);
    if ((r & 1) == 0)
      x = max(x, st[r--]);
  }
  return x;
}
int main(){
  static int hh[N + 1], dp[N + 1][N + 1], dq[N + 1][N + 1], dr[N + 1][N + 1];
  static int st[N + 1][(N + 1) * 2];
  int n, len, i, j, i_, j_, j0, j1, ans;
  srand_();
  scanf("%d%d", &n, &len);
  for (i = 1; i <= n; i++) {
    struct V *u = &uu[i], *v = &vv[i];
    int l, r;
    scanf("%d%d", &l, &r);
    u->l = l, u->r = r;
    v->l = l, v->r = r;
  }
  sort(uu + 1, n, compare_r);
  for (i = 1; i <= n; i++) {
    struct V *u = &uu[i];
    int h = 0;
    while (h + 1 < i && uu[h + 1].r < u->l)
      h++;
    hh[i] = h;
  }
  for (i = 0; i <= n; i++)
    for (j = 0; j <= n; j++)
      dp[i][j] = dr[i][j] = -1;
  for (i = 1; i <= n; i++) {
    struct V *u = &uu[i];
    for (j = i + 1; j <= n; j++) {
      struct V *v = &uu[j];
      if (u->l < v->l && v->l < u->r && u->r < v->r)
        dp[i][j] = max(dr[hh[j]][i], 1) + 1;
    }
    for (j = 0; j <= n; j++)
      dr[i][j] = max(dp[i][j], dr[i - 1][j]);
  }
  sort(vv + 1, n, compare_l);
  for (i_ = 1; i_ <= n; i_++) {
    struct V *v = &vv[i_];
    int h = 0;
    while (h + 1 < i_ && vv[h + 1].l > v->r)
      h++;
    hh[i_] = h;
  }
  for (i_ = 0; i_ <= n; i_++)
    for (j_ = 0; j_ <= n; j_++)
      dq[i_][j_] = dr[i_][j_] = -1;
  for (i_ = 1; i_ <= n; i_++) {
    struct V *v = &vv[i_];
    for (j_ = i_ + 1; j_ <= n; j_++) {
      struct V *u = &vv[j_];
      if (u->l < v->l && v->l < u->r && u->r < v->r)
        dq[i_][j_] = max(dr[hh[j_]][i_], 1) + 1;
    }
    for (j_ = 0; j_ <= n; j_++)
      dr[i_][j_] = max(dq[i_][j_], dr[i_ - 1][j_]);
  }
  n_ = n + 1;
  for (i_ = 0; i_ <= n; i_++)
    build(st[i_], dr[i_]);
  ans = 2;
  for (i = 1; i <= n; i++)
    for (j = i + 1; j <= n; j++)
      if (dp[i][j] != -1 && uu[j].r - uu[i].r > 1)
        ans = max(ans, dp[i][j] + 1);
  for (i = 1; i <= n; i++)
    for (i_ = 1; i_ <= n; i_++)
      if (uu[i].r < vv[i_].l && vv[i_].l - uu[i].r + 3 <= len) {
        ans = max(ans, 3);
        break;
      }
  for (j = 1; j <= n; j++) {
    struct V *u = &uu[j];
    int r_ = -1;
    for (j_ = 1; j_ <= n; j_++) {
      struct V *v = &vv[j_];
      if (u->r < v->l && v->l - u->r + 3 <= len)
        r_ = max(r_, v->r);
    }
    for (i = 1; i <= n && r_ - uu[i].r - 1 >= len; i++)
      if (dp[i][j] != -1)
        ans = max(ans, dp[i][j] + 2);
  }
  for (j_ = 1; j_ <= n; j_++) {
    struct V *v = &vv[j_];
    int l_ = INF;
    for (j = 1; j <= n; j++) {
      struct V *u = &uu[j];
      if (u->r < v->l && v->l - u->r + 3 <= len)
        l_ = min(l_, u->l);
    }
    for (i_ = 1; i_ <= n && vv[i_].l - l_ - 1 >= len; i_++)
      if (dq[i_][j_] != -1)
        ans = max(ans, dq[i_][j_] + 2);
  }
  for (i = 1, i_ = n; i <= n; i++) {
    struct V *u = &uu[i];
    while (i_ > 0 && vv[i_].l - u->r - 1 < len)
      i_--;
    for (j = i + 1, j0 = n, j1 = n; j <= n; j++) {
      struct V *v = &uu[j];
      int p, q;
      while (j1 > 0 && vv[j1].l <= v->r)
        j1--;
      while (j0 - 1 > 0 && vv[j0 - 1].l - v->r + 3 <= len)
        j0--;
      p = dp[i][j], q = query(st[i_], j0, j1);
      if (p != -1 && q != -1)
        ans = max(ans, p + 1 + q);
    }
  }
  printf("%d\n", ans);
  return 0;
}
