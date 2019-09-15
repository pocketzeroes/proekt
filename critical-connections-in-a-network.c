#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
typedef int* intp;

//////////////////////////////
int m,h[100005],ne[200005],p[200005],N,d[100005],l[100005],f[100005];
bool b[100005];
void dfs(int x){
    d[x] = l[x] = ++N;
    for(int i=h[x]; i; i=ne[i]){
      if(!d[p[i]]){
        f[p[i]] = x;
        dfs(p[i]);
        l[x] = fmin(l[x],l[p[i]]);
        if(l[p[i]]>d[x])
            b[p[i]]=1;
      }
      else if(p[i]!=f[x])
        l[x] = fmin(l[x],d[p[i]]);
    }
}
intp*ans;
int  asz;
int**criticalConnections(int n, int**connections, int connectionsSz, int*connections0sz, int*rsz, int**csz){
    memset(h, 0, sizeof(h));
    memset(b, 0, sizeof(b));
    memset(d, 0, sizeof(d));
    N = m = 0;
    for(int z=0;z<connectionsSz;z++){int*i=connections[z];
        p[++m]  = i[1];
        ne[m]   = h[i[0]];
        h[i[0]] = m;
        p[++m]  = i[0];
        ne[m]   = h[i[1]];
        h[i[1]] = m;
    }
    f[0]=-1;
    dfs(0);
    asz = 0;
    ans = calloc(100000, sizeof(intp));
    int i;
    int*s=NULL;
    for(i=1; i<n; i++){
      if(l[i]>d[f[i]]){
        s=calloc(2,sizeof(int));
        s[0]=f[i];
        s[1]=i;
        ans[asz++] = s;
      }
    }
    int*cols=calloc(asz, (sizeof(int)));
    fill(cols, asz, 2);
   *csz = cols;
   *rsz = asz;
    return ans;
}
