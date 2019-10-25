#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
int cmpstr(const void*p1, const void*p2){
  return strcmp(*(char* const*) p1, *(char* const*) p2);
}
int unique(char**a, int len){
  int i, j;
  for(i = j = 0; i < len; i++)
    if(strcmp(a[i], a[j])!=0)
      a[++j] = a[i];
  return j + 1;
}
int lower_bound(char**a, int n, char*x){
  int l = 0;
  int h = n;
  while (l < h) {
    int mid = (l + h) / 2;
    if(strcmp(x, a[mid])<=0)
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}

#define pb(zpv, zvv) zpv.ptr = pushbackS(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
char**pushbackS(char**array, int *size, char*value) {
  char**output = resizeArray(array, char*, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  char**ptr;
  int sz;
}vecs;
vecs newVecS(){
  vecs rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

enum{ MAXN = 21};
int n;

vecs by_loc     [MAXN];
char*all_pkmn   [MAXN];
int  x[MAXN], y [MAXN];
int  dp[1<<MAXN][MAXN];
int  pkmn_masks [MAXN];
int  locs;

int dist(int x1, int y1, int x2, int y2){
    return abs(x1 - x2) + abs(y1 - y2);
}
int main(){
    scanf("%d", &n);
    char*name;
    memset(dp, -1, sizeof(dp));
    for(int i=0; i<n; ++i){
        scanf("%d %d", &x[i], &y[i]);
        name = getstr();
        pb(by_loc[i], name);
        all_pkmn[i] = name;
        dp[1<<i][i] = dist(0, 0, x[i], y[i]);
    }
    for(int mask=1; mask<(1<<n); ++mask){
        for(int i=0; i<n; ++i){
            if(dp[mask][i] == -1)
                continue;
            for(int j=0; j<n; ++j){
                if(mask & (1 << j))
                    continue;
                int new_mask = mask | (1 << j);
                int new_cost = dp[mask][i] + dist(x[i], y[i], x[j], y[j]);
                dp[new_mask][j] = dp[new_mask][j] == -1 ? new_cost : fmin(dp[new_mask][j], new_cost);
            }
        }
    }
    qsort(all_pkmn, n, sizeof(char*), cmpstr);
    int all_pkmnSz = unique(all_pkmn, n);
    for(int i=0; i<n; ++i){
        for(int z=0;z<by_loc[i].sz;z++){char*name = by_loc[i].ptr[z];
            int ind = lower_bound(all_pkmn, all_pkmnSz, name);
            pkmn_masks[i] |= (1 << ind);
        }
    }
    int ans =(int)1e9;
    int target_pkmn = (1 << (all_pkmnSz)) - 1;
    for(int mask=1; mask<(1<<n); ++mask){
        int group_mask = 0;
        for(int i=0; i<n; ++i){
            if(mask & (1 << i))
                group_mask |= pkmn_masks[i];
        }
        if(group_mask != target_pkmn)
            continue;
        for(int i=0; i<n; ++i){
            if(mask & (1 << i))
                ans = fmin(ans, dp[mask][i] + dp[1 << i][i]);
        }
    }
    printf("%d\n", ans);
    return 0;
}
