#pragma GCC optimize "-O3"
#include<stdio.h>  // winterfestival
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value){
  int *output = resizeArray(array, int, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  int*ptr;
  int sz;
}vec;
vec newVec() {
  vec rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int min_element(int*arr, int sz){
  int mine = arr[0];
  for(int i=1;i<sz;i++)
    if(arr[i]<mine)
      mine=arr[i];
  return mine;
}
/////////////////////////////////////////////////
enum{ MAXN = 100005};

int n, m;
int dfn[MAXN], low[MAXN], vis[MAXN], dx[MAXN], piv, c;
vec gph[MAXN];
vec bcc[MAXN], cmp[MAXN];
int dp[MAXN][3][3];
int compat  [8][3][3];
int compat2 [8][3];
void solve(int c);


void color(int x, int p){
  if(p){
    pb(bcc[p], x);
    pb(cmp[x], p);
  }
  for(int z=0;z<gph[x].sz;z++){int i = gph[x].ptr[z];
    if(cmp[i].sz) 
      continue;
    if(low[i] >= dfn[x]){
      ++c;
      pb(bcc[c], x);
      pb(cmp[x], c);
      color(i, c);
    }
    else
      color(i, p);
  }
}
void dfs(int x, int p){
  dfn[x] = low[x] = ++piv;
  for(int z=0;z<gph[x].sz;z++){int i = gph[x].ptr[z];
    if(i != p){
      if(!dfn[i]){
        dfs(i, x);
        low[x] = fmin(low[x], low[i]);
      }
      else{
        low[x] = fmin(low[x], dfn[i]);
        if(dfn[i] < dfn[x]){
          dx[x]++;
          dx[i]--;
        }
      }
    }
  }
}
void sum(int x, int p){
  vis[x] = 1;
  for(int z=0;z<gph[x].sz;z++){int i = gph[x].ptr[z];
    if(i != p){
      if(!vis[i]){
        sum(i, x);
        dx[x] += dx[i];
      }
    }
  }
  if(dx[x] > 1){
    puts("-1");
    exit(0);
  }
}
int*point_merge(int c, int v){
  int*msk = calloc(8, sizeof(int)); fill(msk, 8, (int)1e9);
  msk[0] = 0;
  for(int z=0;z<cmp[v].sz;z++){int j = cmp[v].ptr[z];
    if(c == j)
      continue;
    solve(j);
    int nxt[8]; fill(nxt, 8, (int)1e9);
    for(int l=0; l<3; l++){
      for(int k=0; k<3; k++){
        for(int m=0; m<8; m++){
          if(bcc[j].sz > 2 && compat[m][l][k])
            nxt[m | (1<<l) | (1<<k)] = fmin(nxt[m | (1<<l) | (1<<k)], msk[m] + dp[j][l][k]);
          if(bcc[j].sz == 2 && compat2[m][l])
            nxt[m | (1<<l)] = fmin(nxt[m | (1<<l)], msk[m] + dp[j][l][l]);
        }
      }
    }
    memcpy(msk, nxt, 8*sizeof(int));
  }
  return msk;
}
void solve(int c){
  if(bcc[c].sz == 2){
    int*msk = point_merge(c, bcc[c].ptr[1]);
    for(int i=0; i<3; i++){
      for(int j=0; j<8; j++){
        if(compat2[j][i])
          dp[c][i][i] = fmin(dp[c][i][i], msk[j] + i);
      }
    }
    return;
  }
  int vdp[3][3][2] = {};
  memset(vdp, 0x3f, sizeof(vdp));
  vdp[0][0][0] = 0;
  vdp[1][1][1] = 1;
  vdp[2][2][0] = 2;
  for(int i=1; i<bcc[c].sz; i++){
    int v = bcc[c].ptr[i];
    int*msk = point_merge(c, v);
    int nvdp[3][3][2];
    memset(nvdp, 0x3f, sizeof(nvdp));
    for(int i=0; i<3; i++){
      for(int j=0; j<3; j++){
        for(int k=0; k<2; k++){
          for(int l=0; l<3; l++){
            for(int m=0; m<8; m++){
              if(compat[m][j][l])
                nvdp[i][l][(k + l) % 2] = fmin(nvdp[i][l][(k + l) % 2], vdp[i][j][k] + msk[m] + l);
            }
          }
        }
      }
    }
    memcpy(vdp, nvdp, sizeof(vdp));
  }
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      if((i + j) % 3 == 1)
        dp[c][i][j] = 1e9;
      else
        dp[c][i][j] = vdp[i][j][1];
    }
  }
}
int main(){
  memset(dp, 0x3f, sizeof(dp));
  for(int i=0; i<8; i++){
    for(int j=0; j<3; j++){
      vec v = newVec();
      pb(v, j);
      for(int m=0; m<3; m++){
        if((i >> m) & 1)
          pb(v, m);
      }
      bool bflg = false;
      for(int i=0; i<v.sz; i++){
        for(int j=0; j<i; j++){
          if((v.ptr[i] + v.ptr[j]) % 3 == 1)
            bflg = true;
        }
      }
      compat2[i][j] = !bflg;
      for(int k=0; k<3; k++){
        vec v = newVec();
        pb(v, j);
        pb(v, k);
        for(int m=0; m<3; m++){
          if((i >> m) & 1)
            pb(v, m);
        }
        bool bflg = false;
        for(int i=0; i<v.sz; i++){
          for(int j=0; j<i; j++){
            if((v.ptr[i] + v.ptr[j]) % 3 == 1)
              bflg = true;
          }
        }
        compat[i][j][k] = !bflg;
      }
    }
  }
  scanf("%d %d", &n, &m);
  for(int i=0; i<m; i++){
    int s, e;
    scanf("%d %d", &s, &e);
    pb(gph[s], e);
    pb(gph[e], s);
  }
  int ret = 0;
  for(int i=1; i<=n; i++){
    if(!dfn[i]){
      dfs(i, 0);
      sum(i, 0);
      color(i, 0);
      int*msk = point_merge(-1, i);
      ret += min_element(msk, 8);
      if(ret > m * 3){
        puts("-1");
        return 0;
      }
    }
  }
  printf("%d\n", ret);
  return 0;
}
