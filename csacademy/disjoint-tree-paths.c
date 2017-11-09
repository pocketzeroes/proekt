#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
  int *output = resizeArray(array, int, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
///////////////////////////

enum{ N = 100010};
vec g   [N];
int w   [N];
int pa  [N];
int q   [N];
int d   [N];
int sum [N];
int best[N];
int fa  [N];
int fb  [N];

int main(){
  int tt;
  scanf("%d", &tt);
  while(tt--){
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);
    --a, --b;
    for (int i = 0; i < n; ++i){
      w[i] = 1;
      g[i].sz = 0;
    }
    for (int i = 0; i < n - 1; ++i){
      int x, y;
      scanf("%d %d", &x, &y);
      --x, --y;
      g[x].ptr = pushback(g[x].ptr, &g[x].sz, y);
      g[y].ptr = pushback(g[y].ptr, &g[y].sz, x);
    }
    memset(pa, -1, sizeof(pa));
    q[0] = b;
    for(int qh = 0, qt = 1; qh < qt; ++qh){
      int x = q[qh];
      for(int z=0;z<g[x].sz;z++){int y = g[x].ptr[z];
        if(y != pa[x]){
          pa[y]   = x;
          q[qt++] = y;
        }
      }
    }
    vec path = newVec();
    for(int i = a; i != -1; i = pa[i])
      path.ptr = pushback(path.ptr, &path.sz, i);
    int msz = path.sz;
    memset(d, -1, sizeof(d));
    for(int i = 0; i < msz; ++i)
      d[path.ptr[i]] = 0;
    for(int i = 0; i < msz; ++i){
      best[i] = 0;
      q[0] = path.ptr[i];
      int qt = 1;
      for(int qh = 0; qh < qt; ++qh){
        int x = q[qh];
        for(int z=0;z<g[x].sz;z++){int y = g[x].ptr[z];
          if(d[y] == -1){
            d[y] = d[x] + w[y];
            q[qt++] = y;
            best[i] = max(best[i], d[y]);
          }
        }
      }
    }
    sum[0] = 0;
    for (int i = 0; i < msz; ++i)
      sum[i + 1] = sum[i] + w[path.ptr[i]];
    for (int i = 0; i < msz; ++i)
      fa[i] = sum[i + 1] + best[i];
    for (int i = msz - 1; i >= 0; --i)
      fb[i] = sum[msz] - sum[i] + best[i];
    int z   = 1 - msz % 2;
    int aa  = (msz - 1) / 2, bb = (msz - 1) / 2 + 1;
    int mxa = fa[aa], mxb = fb[bb];
    int res = fa[aa] - fb[bb];
    while(aa != 0 || bb != msz - 1){
      if(z == 0){
        --aa;
        mxa = max(mxa, fa[aa]);
        mxb = max(mxb, fb[aa + 1]);
        res = max(res, fa[aa] - mxb);
      } 
      else{
        ++bb;
        mxa = max(mxa, fa[bb - 1]);
        mxb = max(mxb, fb[bb]);
        res = min(res, mxa - fb[bb]);
      }
      z = 1 - z;
    }
    puts(res > 0 ? "A" : "B");
  }
}
































