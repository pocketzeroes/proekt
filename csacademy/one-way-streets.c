#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))



int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef struct pair_s{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

pair *pushback(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
 pair*ptr;
 int sz;
}vec;
vec newVec() {
 vec rez;
 rez.ptr = NULL;
 rez.sz = 0;
 return rez;
}

typedef long long LL;
typedef long double LD;
typedef pair pii;
enum{ MAXN=100000};


int  u     [MAXN+5],
     v     [MAXN+5],
     nodes,
     val   [MAXN+5],
     edge,
     nomor,
     dfsnum[MAXN+5],
     dfslow[MAXN+5],
     total [MAXN+5];
vec  node  [MAXN+5];
char ans   [MAXN+5];


void dfs(int now,int edgepar){
  total [now] = val [now];
  dfsnum[now] = dfslow[now] = nomor++;
  for(int i=0;i<node[now].sz;i++){ pair v = node[now].ptr[i];
    if(v.second==edgepar)
      continue;
    if(dfsnum[v.first]==-1)
    {
      dfs(v.first,v.second);
      dfslow[now]=min(dfslow[now],dfslow[v.first]);
      total[now]+=total[v.first];
      if(dfslow[v.first]>dfsnum[now])
      {
        if(total[v.first]>0)
        {
          if(u[v.second]==now)
            ans[v.second]='L';
          else
            ans[v.second]='R';
        }
        else if(total[v.first]<0)
        {
          if(u[v.second]==now)
            ans[v.second]='R';
          else
            ans[v.second]='L';
        }
      }
    }
    else
      dfslow[now]=min(dfslow[now],dfsnum[v.first]);
  }
}
int main(){
  memset(dfsnum,-1,sizeof(dfsnum));
  scanf("%d%d",&nodes,&edge);
  ans[edge]='\0';
  for(int i=0;i<edge;i++){
    ans[i]='B';
    scanf("%d%d",&u[i],&v[i]);
    node[u[i]].ptr = pushback(node[u[i]].ptr, &node[u[i]].sz ,newPair(v[i],i));
    node[v[i]].ptr = pushback(node[v[i]].ptr, &node[v[i]].sz ,newPair(u[i],i));
  }
  int m;
  scanf("%d",&m);
  for(int i=0;i<m;i++){
    int s,t;
    scanf("%d%d",&s,&t);
    val[s]++;
    val[t]--;
  }
  for(int i=1;i<=nodes;i++){
    if(dfsnum[i]==-1)
      dfs(i,-1);
  }
  printf("%s\n",ans);
}




















































