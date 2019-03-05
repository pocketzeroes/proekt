#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}
#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int unique(pair*a, int len){
	int i, j;
	for(i=j=0; i<len; i++)
		if(cmpP(&a[i], &a[j])!=0)
      a[++j] = a[i];
	return j + 1;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int*pushback(int *array, int *size, int value){
  int *output = resizeArray(array, int, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

//////////////////////
typedef long long ll;
enum{ MAX = 300300};

vecp edges;
vec  adj    [MAX];
vec  queryAt[MAX];
int  numNode,
     numEdge;
bool marked [MAX];

void loadGraph(){
  scanf("%d", &numNode);
  for(int love = 0, _n = (numNode - 1); love < _n; love++){
    int u, v;
    scanf("%d%d", &u, &v);
    if (u > v)
      swap(u, v);
    edges.ptr = pushbackP(edges.ptr, &edges.sz, newPair(u, v));
  }
  qsort(edges.ptr, edges.sz, sizeof(pair), cmpP);
  edges.sz = unique(edges.ptr, edges.sz);
  for(int i=0;i<edges.sz;i++){pair it=edges.ptr[i];
    adj[it.first ].ptr = pushback(adj[it.first ].ptr, &adj[it.first ].sz, it.second);
    adj[it.second].ptr = pushback(adj[it.second].ptr, &adj[it.second].sz, it.first );
  }
}
int biggerNode(int u, int v){
  if(adj[u].sz > adj[v].sz)
    return u;
  if(adj[v].sz > adj[u].sz)
    return v;
  return max(u, v);
}
void process(){
  for(int i=0;i<edges.sz;i++){pair it=edges.ptr[i];
    int big = biggerNode(it.first, it.second);
    int small = it.first ^ it.second ^ big;
    queryAt[big].ptr = pushback(queryAt[big].ptr, &queryAt[big].sz, small);
  }
  ll res = 0;
  for(int i=1, _b = (numNode); i <= _b; i++)
    res += 1LL*adj[i].sz * (adj[i].sz - 1) / 2;
  for(int i=1, _b = (numNode); i <= _b; i++){
    if(queryAt[i].sz!=0){
      for(int z=0;z<adj[i].sz;z++){int jt = adj[i].ptr[z];
        marked[jt] = true;
      }
      for(int z=0;z<queryAt[i].sz;z++){int jt = queryAt[i].ptr[z];
        int j = jt;
        for(int q=0;q<adj[j].sz;q++){int kt =adj[j].ptr[q];
          if(marked[kt])
            res--;
        }
      }
      for(int z=0;z<adj[i].sz;z++){int jt = adj[i].ptr[z];
        marked[jt] = false;
      }
    }
  }
  printf("%lld\n", (res << 1) );
}
int main(){
  loadGraph();
  process();
  return 0;
}
