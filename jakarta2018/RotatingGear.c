#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int max(int a,int b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
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


enum{ N    = 100000};
enum{ LOGN =     18};
enum{ MOD  =    360};


typedef struct{
  int bit[N+10];
}SumSegtree;


void bit_update(SumSegtree*tree, int x, int val){
  ++x;
  for(int i=x; i<=N+1; i+=(i & -i))
    tree->bit[i] += val;
}
int bit_query(SumSegtree*tree, int x){
  ++x;
  int res = 0;
  for(int i=x; i>0; i-=(i & -i))
    res += tree->bit[i];
  return res;
}
void update(SumSegtree*tree, int x, int y, int val){
  bit_update(tree, x, val);
  bit_update(tree, y+1,-val);
}
void update2(SumSegtree*tree, int x, int val){
  bit_update(tree, x, val);
}
int query(SumSegtree*tree, int x){
  return bit_query(tree, x);
}
int query2(SumSegtree*tree, int x, int y){
  return bit_query(tree, y) -
         bit_query(tree, x-1);
}


int n,m,q;
vec adj[N + 5];
int op,a,b;
int inorder[N + 5];
int now = 0;
int h     [N + 5];
int parent[LOGN + 2][N + 5];
int lst   [N + 5];
bool ada  [N + 5];
int simpan[N + 5];
int gone  [N + 5];
SumSegtree putarTree;
SumSegtree adaTree;
SumSegtree goneTree;


void dfs(int u, int pt){
  inorder[u] = ++now;
  lst[inorder[u]] = inorder[u];
  parent[0][inorder[u]] = inorder[pt];
  h[inorder[u]] = h[inorder[pt]] + 1;
  for(int z=0; z<adj[u].sz; z++){int v = adj[u].ptr[z];
    if(v == pt)
      continue;
    dfs(v, u);
    lst[inorder[u]] = max(lst[inorder[u]],lst[inorder[v]]);
  }
}
int findBelowLost(int a){
  int now = a;
  for (int (i)=(LOGN);(i)>=(0);--(i)){
    int u = parent[i][now];
    if(query(&adaTree, now) - (u == 0 ? 0 : query(&adaTree, parent[0][u])) == h[now] - h[u] + 1)
      now = u;
  }
  return now;
}
int findLost(int a){
  int now = parent[0][a];
  if (!ada[now]){
    return now;
  }
  for (int (i)=(LOGN);(i)>=(0);--(i)){
    int u = parent[i][now];
    if(query(&adaTree, now) - (u == 0 ? 0 : query(&adaTree, parent[0][u])) == h[now] - h[u] + 1)
      now = u;
  }
  return parent[0][now];
}
int count(int x){
  return lst[x] - x + 1 - query2(&goneTree, x, lst[x]);
}
int main(){
  scanf("%d", &n);
  for(int i=0; i<n-1; ++i){
    scanf("%d %d",&a,&b);
    adj[a].ptr = pushback(adj[a].ptr, &adj[a].sz, b);
    adj[b].ptr = pushback(adj[b].ptr, &adj[b].sz, a);
  }
  dfs(1, 0);
  for(int i=1; i<=n; ++i){
    ada[i] = 1;
    update(&adaTree, i, lst[i],1);
  }
  for(int lv=1; lv<=LOGN; ++lv)
    for(int i=1; i<=n; ++i)
      parent[lv][i] = parent[lv-1][parent[lv-1][i]];
  lst[0] = n;
  scanf("%d",&q);
  while(q--){
    scanf("%d %d", &op, &a);
    a = inorder[a];
    int lost = findLost(a);
    if (op == 1){
      simpan[a] = query(&putarTree, a) + simpan[lost] - query(&putarTree, lost);
      ada[a] = 0;
      update(&adaTree, a, lst[a],-1);
      int inThisSubtree = lst[a] - a + 1 - query2(&goneTree, a,lst[a]);
      update2(&goneTree, lost, -inThisSubtree);
      gone[lost] -= inThisSubtree;
      gone[a] = inThisSubtree;
      update2(&goneTree, a, gone[a]);
    }
    else if (op == 2){
      int putar = (simpan[a] - query(&putarTree, a)) - (simpan[lost] - query(&putarTree, lost));
      simpan[a] = 0;
      update(&putarTree, a, lst[a], putar);
      ada[a] = 1;
      update(&adaTree, a, lst[a],1);
      update2(&goneTree, lost, gone[a]);
      gone[lost] += gone[a];
      update2(&goneTree, a, -gone[a]);
      gone[a] = 0;
    }
    else{
      int belowLost = findBelowLost(a);
      scanf("%d",&b);
      if (h[a] % 2 == 1)
        b *= -1;
      update(&putarTree, belowLost, lst[belowLost], b);
      int cnt = count(belowLost);
      printf("%d\n", cnt * abs(b));
    }
  }
  for(int i=1; i<=n; ++i)
    if(!ada[i]){
      int a = i;
      int lost = findLost(a);
      int putar = (simpan[a] - query(&putarTree, a)) - (simpan[lost] - query(&putarTree, lost));
      simpan[a] = 0;
      update(&putarTree, a, lst[a], putar);
      ada[a] = 1;
      update(&adaTree, a, lst[a],1);
    }
  int risan = 0;
  for(int i=1; i<=n; ++i)
    risan += ((query(&putarTree, i) * (h[i] % 2 == 1 ? -1 : 1) % MOD) + MOD) % MOD;
  printf("%d\n", risan);
  return 0;
}
