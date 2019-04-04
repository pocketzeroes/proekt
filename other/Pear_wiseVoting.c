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
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushbackL(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}


enum{N=26};

vecl outs[N];
ll id_self[N];
ll id_low[N];
ll route[N];

void add(ll from, ll to){
    outs[from].ptr = pushbackL(outs[from].ptr, &outs[from].sz, to);
}
void dfs(ll*scc, ll from, ll*last, ll*now, ll*now_scc){
    id_self[from] = *now;
    id_low[from]  = *now;
    (*now) += 1;
    route[from] = *last;
   *last = from;
    for (ll j = 0; j < outs[from].sz; ++j){
        ll to = outs[from].ptr[j];
        if (!id_self[to]){
            dfs(scc, to, last, now, now_scc);
            id_low[from] = min(id_low[from], id_low[to]);
        }
        else if (!scc[to])
            id_low[from] = min(id_low[from], id_self[to]);
    }
    if (id_low[from] == id_self[from]){
        while (*last != from){
            scc[*last] = *now_scc;
            *last = route[*last];
        }
        scc[*last] = *now_scc;
        *last = route[*last];
        (*now_scc) += 1;
    }
}
void solve(ll*scc){
    memset(id_self, 0, sizeof(id_self));
    ll last = 0;
    ll now = 1;
    ll now_scc = 1;
    for (ll i = 0; i < N; ++i){
        if (!id_self[i])
            dfs(scc, i, &last, &now, &now_scc);
    }
    for (ll i = 0; i < N; ++i)
        scc[i] -= 1;
}

int p[2000];
int pos[26][2000];
ll scc[26];

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=0; i<m; ++i){
        scanf("%d", &p[i]);
        char*s = getstr();
        for(int j = 0; j < n; ++j)
            pos[s[j] - 'A'][i] = j;
    }
    for(int i = 0; i < n; ++i){
        for(int j = i + 1; j < n; ++j){
            int tot_i = 0;
            int tot_j = 0;
            for(int k = 0; k < m; ++k){
                if(pos[i][k] < pos[j][k])
                    tot_i += p[k];
                else
                    tot_j += p[k];
            }
            if(tot_i > tot_j)
                add(i, j);
            else
                add(j, i);
        }
    }
    solve(scc);
    ll max_scc = 0;
    for(int i=0; i<n; ++i)
        max_scc = max(max_scc, scc[i]);
    for(int i=0; i<n; ++i){
        if(scc[i] == max_scc)
            printf("%c: can win\n", (char)('A' + i) );
        else
            printf("%c: can't win\n", (char)('A' + i) );
    }
    return 0;
}
