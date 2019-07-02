#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int accumulate(int*arr, int sz){
  int sum=0;
  for(int i=0; i<sz; i++)
    sum += arr[i];
  return sum;
}
//////////////////////////
enum{ maxn = 192};
int cap  [maxn][maxn], 
    deg  [maxn], 
    edge [maxn][maxn], 
    queue[maxn], 
    prev [maxn];

int maxflow(int n, int src, int sink){
  int flow = 0, i, v, w;
  for (;;){
    fill(prev, n, -1);
    int startq = 0, endq = 0;
    prev[queue[endq++] = src] = -2;
    while (startq != endq && prev[sink] < 0)
      for (v = queue[startq++], i = deg[v] - 1; i >= 0; --i)
        if (prev[w = edge[v][i]] < 0 && cap[v][w] > 0)
          prev[queue[endq++] = w] = v;
    if(prev[sink] == -1)
      break;
    for(i = 0; i < n; i++)
      if(cap[i][sink] && prev[i] != -1){
        int minc = cap[i][sink];
        for(v = i; v != src; v = prev[v])
          minc = min(minc, cap[prev[v]][v]);
      if(!minc)
        continue;
      cap[i][sink] -= minc;
      cap[sink][i] += minc;
      for (v = i; v != src; v = prev[v]){
        cap[prev[v]][v] -= minc;
        cap[v][prev[v]] += minc;
      }
      flow += minc;
    }
  }
  return flow;
}
void add(int a, int b, int c){
  edge[a][deg[a]++] = b;
  edge[b][deg[b]++] = a;
  cap[a][b] = c; 
  cap[b][a] = 0;
}
int main(){
  int ly, lx;
  bool first = true;
  while(scanf("%i%i", &ly, &lx), ly){
    int sumx[lx]; 
    int sumy[ly];
    for(int i = 0; i < ly; ++i)
      scanf("%i", &sumy[i]);
    for(int j = 0; j < lx; ++j)
      scanf("%i", &sumx[j]);
    if(!first)
      puts("");
    else
      first = false;
    int n = ly + lx + 2, src = n - 1, sink = n - 2,
        total = accumulate(sumx, lx);
    fill(deg, n, 0);
    for(int i = 0; i < n; ++i)
      cap[i][sink] = 0;
    for(int y = 0; y < ly; ++y)
      add(src, y, sumy[y]);
    for(int x = 0; x < lx; ++x)
      add(ly + x, sink, sumx[x]);
    for(int i = 0; i < ly * lx; ++i)
      add(i / lx, ly + (i % lx), 1);
    if(accumulate(sumy, ly) != total || maxflow(n, src, sink) != total)
      puts("Impossible");
    else
      for(int i = 0; i < ly * lx; ++i){
        int y = i / lx, 
            x = i % lx;
        bool canbezero = (cap[y][ly + x] != 0);
        if (!canbezero){
          ++cap[src][y];
          ++cap[ly + x][sink];
          cap[y][ly + x] = cap[ly + x][y] = 0;
          if (maxflow(n, src, sink) > 0)
            canbezero = true;
          else{
            --cap[src][y];
            --cap[ly + x][sink];
          }
        }
        cap[y][ly + x] = cap[ly + x][y] = 0;
        if(canbezero)
          putchar('N');
        else{
          --total;
          putchar('Y');
        }
        if(i % lx == lx - 1)
          puts("");
      }
  }
  return 0;
}
