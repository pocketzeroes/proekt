#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
typedef long long ll;
enum{ MAX = 50000};

typedef struct{
    int a, b, t;
}edge;
edge edges[2 * MAX];

int cmpE(const void*pa, const void*pb){
  edge*e = (edge*)pa;
  edge*o = (edge*)pb;
  return(o->a < e->a)?-1:1;
}

int N, 
    visits[MAX], 
    start [MAX],
    freq  [MAX],
    best0 [MAX];
int best1;
ll  ttime [MAX], best;

void init() {
    for (int i = 0; i < N - 1; ++i) {
        edges[N - 1 + i].a = --edges[i].b;
        edges[N - 1 + i].b = --edges[i].a;
        edges[N - 1 + i].t =   edges[i].t;
    }
    qsort(edges, 2 * (N - 1), sizeof(edge), cmpE);
    fill(start, N, 2 * (N - 1));
    for (int i = 0; i < 2 * (N - 1); ++i)
        if (i == 0 || edges[i].a != edges[i - 1].a)
            start[edges[i].a] = i;
}
void dfs1(int m, int up){
    ttime[m] = 0;
    freq[m] = visits[m];
    for (int i = start[m]; i < 2 * (N - 1) && edges[i].a == m; ++i){
        if (edges[i].b != up){
            dfs1(edges[i].b, m);
            ttime[m] += ttime[edges[i].b] + 2ll * freq[edges[i].b] * edges[i].t;
            freq[m] += freq[edges[i].b];
        }
    }
}
void dfs2(int m, int up, int f, ll t){
    if (t + ttime[m] < best)
        best = t + ttime[m], best1 = 0;
    if (t + ttime[m] == best)
        best0[best1++] = m;
    for (int i = start[m]; i < 2 * (N - 1) && edges[i].a == m; ++i){
        if (edges[i].b != up){
            dfs2(edges[i].b, m, f + freq[m] - freq[edges[i].b], t + ttime[m] - ttime[edges[i].b] - 2ll * freq[edges[i].b] * edges[i].t + 2ll * (f + freq[m] - freq[edges[i].b]) * edges[i].t);
        }
    }
}
int main(){
    int t, u;
    for(scanf("%d", &t); t > 0; --t){
        scanf("%d", &N);
        for(int i = 0; i < N - 1; ++i)
            scanf("%d%d%d", &edges[i].a, &edges[i].b, &edges[i].t);
        scanf("%d", &u);
        memset(visits, 0, N * sizeof visits[0]);
        for (int i = u; i > 0; --i){
            scanf("%d", &u);
            scanf("%d", &visits[--u]);
        }
        init();
        dfs1(0, 0);
        best = 112233445566778899ll;
        best1 = 0;
        dfs2(0, 0, 0, 0);
        qsort(best0, best1, sizeof(int), cmp);
        printf("%lld\n", best);
        for(int p = 0; p != best1; ++p){
            printf("%d", best0[p] + 1);
            if(p+1 != best1)
                printf(" ");
        }
        puts("");
    }
    return 0;
}
