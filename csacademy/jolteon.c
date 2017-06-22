#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#ifdef _WIN32
  #define inline static
#endif

inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

typedef long long ll;
typedef unsigned long long ull;

enum{ N =(int) 1e5 + 10}; 
enum{ M =(int) 1e6 + 10};
enum{ B   =(int) 320    }; 
enum{ mod =(int) 1000003};

int n, a[N];
ull    t[M];
ull tag[B], h[N], cnt[B];
int nxt[M], tot = 0;
int u[mod], st[N], top = 0, el = 0;


typedef struct nodeS{
  int x; 
  ull h; 
  int w, pre; 
}node;

node e[N];



ull rd() { 
  return (ull)(rand()) * (ull)(rand()) * (ull)(rand()) * (ull)(rand()) * (ull)(rand());
}
inline int nn() { 
  return el < N - 1 ? (++el) : st[top--];
}
void inc(int x, ull h, int d) {
    int ind = (1ull * x * x * x * x + h) % mod;
    int *t = &u[ind];
    for(int i = u[ind]; i; i = e[i].pre) if (e[i].x == x && e[i].h == h) {
        e[i].w += d;
        if (!e[i].w) {
            (*t) = e[i].pre;
            st[++top] = i;
        }
        return;
    } else t = &e[i].pre;
    int t1 = nn(); e[t1] = (node){x, h, d, u[ind]}, u[ind] = t1;
}
int qry(int x, ull h) {
    int ind = (1ull * x * x * x * x + h) % mod;
    for(int i = u[ind]; i; i = e[i].pre) if (e[i].x == x && e[i].h == h) return e[i].w;
    return 0;
}
void modi(int x, ull d) {
    int tx = (x - 1) / B + 1;
    int ed = min(n, tx * B);
    tot -= cnt[tx];
    for(int i = x; i <= ed; i++) {
        inc(tx, h[i], -1);
        h[i] ^= d;
        inc(tx, h[i], 1);
    }
    tot += (cnt[tx] = qry(tx, tag[tx]));

    ed = (n - 1) / B + 1;
    for(int i = tx + 1; i <= ed; i++) {
        tot -= cnt[i];
        tag[i] ^= d;
        tot += (cnt[i] = qry(i, tag[i]));
    }
}
int main() {
    scanf("%d",&n);
    for(int i = 1; i <= n; i++) scanf("%d",a + i);
    for(int i = 1; i <= n; i++) if (!t[a[i]]) t[a[i]] = rd();
    ll ans = 0;
    tot = n; for(int i = 1; i <= n; i++) inc((i - 1) / B + 1, 0, 1), cnt[(i - 1) / B + 1]++;
    for(int i = n; i >= 1; i--) {
        int x = nxt[a[i]];
        if (x) modi(x, t[a[i]]);
        nxt[a[i]] = i;
        ans += tot - (i - 1);
    }
    printf("%lld\n",ans);
 return 0;
}




























