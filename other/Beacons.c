#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  double first;
  int    second;
}pdi;
pdi newpdi(double a, int b){
  return(pdi){a, b};
}
int cmpPdi(const void*pa, const void*pb){
  pdi*a=(pdi*)pa;
  pdi*b=(pdi*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int lower_bound(pdi*a, int n, pdi x){
  int l = 0;
  int h = n;
  while (l < h){
    int mid = (l + h) / 2;
    if(cmpPdi(&x, &a[mid])<=0)
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}

#define maxL (1048576>>5)+1
#define GET(x) (g[(x)>>5]>>((x)&31)&1)
#define SET(x) (g[(x)>>5] |= 1<<((x)&31))
#define eps 1e-8

typedef struct pt{
    double x, y;
}pt;
pt newpt(double a, double b){
    return(pt){a,b};
}
int cmpPt(const void*pa, const void*pb){
    pt*t=(pt*)pa;
    pt*a=(pt*)pb;
    if(fabs(t->x-a->x) > eps)
        return(t->x < a->x)?-1:1;
    return(t->y < a->y)?-1:1;
}
pt opSub(pt t, pt a){
    return newpt(t.x-a.x, t.y-a.y);
}
double dist(pt a, pt b){
    return hypot(a.x - b.x, a.y - b.y);
}
double dot(pt a, pt b){
    return a.x * b.x + a.y * b.y;
}

pt D[1024],
   E[1024];
double Er[1024];
int g[maxL];
int visited[1024];

void buildGraph(int n, int m){
    memset(g, 0, sizeof(g));
    qsort(D, n, sizeof(pt), cmpPt);
    for(int i=0; i<n; i++){
        int ASZ = n-(i+1);
        pdi A[ASZ]; int asz=0;
        for(int j=i+1; j<n; j++)
            A[asz++] = newpdi(atan2(D[j].y - D[i].y, D[j].x - D[i].x), j);
        qsort(A, asz, sizeof(pdi), cmpPdi);
        for(int j=0; j<m; j++){
            double mm = atan2(E[j].y - D[i].y, E[j].x - D[i].x);
            double theta = asin(Er[j] / dist(E[j], D[i])), L = mm - theta, R = mm + theta;
            int st = lower_bound(A, asz, newpdi(L, -1));
            for(int k = st; k < asz && A[k].first <= R; k++){
                if(dot(opSub(D[i], D[A[k].second]),
                       opSub(E[j], D[A[k].second])) > 0)
                    SET(i * n + A[k].second), SET(A[k].second * n + i);
            }
        }
    }
}
void dfs(int u, int n){
    visited[u] = 1;
    for(int i=0; i<n; i++)
        if(!GET(u * n + i) && !visited[i])
            dfs(i, n);
}
int main(){
    int testcase=1, n, m;
    while(testcase--){
        scanf("%d %d", &n, &m);
        for(int i=0; i<n; i++)
            scanf("%lf %lf", &D[i].x, &D[i].y);
        for(int i=0; i<m; i++)
            scanf("%lf %lf %lf", &E[i].x, &E[i].y, &Er[i]);
        buildGraph(n, m);
        int ret = 0;
        memset(visited, 0, sizeof(visited));
        for(int i=0; i<n; i++)
            if(visited[i] == 0)
                dfs(i, n), ret++;
        printf("%d\n", ret-1);
    }
    return 0;
}
