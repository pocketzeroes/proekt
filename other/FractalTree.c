#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tp; tp = a; a = b; b = tp; }while(0)

int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}
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
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)

typedef long long ll;
int n, k, currLabel;
vec*adj;
int**memo;
vec*relabelled;
int*depth;
int*parent;
vec numNodes;
vec leaves;
int*label;

void dfs(int node){
  label[node] = currLabel;
  currLabel++;
  for(int z=0;z<adj[node].sz;z++){int to=adj[node].ptr[z];
    dfs(to);
  }
}
vec getNodes (int node){
  vec arr=newVec();
  int iteration = k - 1;
  while (iteration >= 0){
    int subtreeSize = numNodes.ptr[iteration];
    iteration--;
    int start = 0, end = leaves.sz, mid = 0;
    bool found = false;
    while (end - start > 1){
      mid = (start + end) >> 1;
      ll lbl1 = (ll)leaves.ptr[mid] + 1LL * mid * (subtreeSize - 1);
      if (lbl1 <= node && node < lbl1 + subtreeSize){
        pb(arr, leaves.ptr[mid]);
        if(node == lbl1)
          return arr;
        node -= lbl1;
        node++;
        found = true;
        break;
      }
      if (node < lbl1)
        end = mid;
      else
        start = mid;
    }
    if (!found){
      ll lbl2 = (ll) leaves.ptr[start] + 1LL * start * (subtreeSize - 1);
      if (lbl2 <= node && node < lbl2 + subtreeSize){
        pb(arr, leaves.ptr[start]);
        if(node == lbl2)
          return arr;
        node -= lbl2;
        node++;
      }
      else if (node < leaves.ptr[start]){
        pb(arr, node);
        return arr;
      }
      else{
        ll lbl = 1LL * (start + 1) * (subtreeSize - 1);
        pb(arr, node-lbl);
        return arr;
      }
    }
  }
  pb(arr, node);
  return arr;
}
int LCA(int x, int y){
  if(depth[x] < depth[y])
    swap (x, y);
  int diff = depth[x] - depth[y];
  for(int k = 17; k >= 0; --k){
    if(diff & (1 << k))
      x = memo[x][k];
  }
  for(int k = 17; k >= 0; --k){
    if(memo[x][k] != memo[y][k]){
      x = memo[x][k];
      y = memo[y][k];
    }
  }
  if(x != y)
    x = parent[x];
  return x;
}
int main (){
  scanf("%d", &n);
  adj   =calloc (n + 1, sizeof(vec));
  depth =calloc (n + 1, sizeof(int));
  parent=calloc (n + 1, sizeof(int));
  label =calloc (n + 1, sizeof(int));
  int par;
  for (int i = 2; i <= n; ++i){
    scanf("%d", &par);
    par++;
    pb(adj[par], i);
  }
  currLabel = 1;
  dfs(1);
  relabelled=calloc(n + 1, sizeof(vec));
  parent[1] = depth[1] = 0;
  for(int i = 1; i <= n; ++i){
    for(int z=0;z<adj[i].sz;z++){int to=adj[i].ptr[z];
      pb(relabelled[label[i]], label[to]);
      parent    [label[to]] = label[i];
      depth     [label[to]] = depth[label[i]] + 1;
    }
  }
  swap(adj, relabelled);
  free(relabelled); relabelled=NULL;
  for(int i = 1; i <= n; ++i)
    if(adj[i].sz == 0)
      pb(leaves, i);
  int q, a, b;
  scanf("%d %d", &k, &q);
  if(leaves.sz == 1){
    while(q--){
      scanf("%d %d", &a, &b);
      printf("%d\n", abs (a - b));
    }
    return 0;
  }
  int curr = 1;
  int pathLength = 0;
  while(adj[curr].sz > 0){
    curr = adj[curr].ptr[0];
    pathLength++;
  }
  memo=newmat(n+1, 18);
  for(int i = 1; i <= n; ++i)
    memo[i][0] = parent[i];
  for(int k = 1; k <= 17; ++k)
    for(int i = 1; i <= n; ++i)
      memo[i][k] = memo[memo[i][k - 1]][k - 1];
  pb(numNodes, n);
  for(int i = 1; i <= fmin (k, 30); ++i){
    if(log (n - 1) + i * log (leaves.sz) <= 50 * log (2)){
      ll temp = (ll) numNodes.ptr[i - 1] + 1LL * (n - 1) * powl (leaves.sz, i);
      if(temp <= (1LL << 30))
        pb(numNodes, temp);
      else
        pb(numNodes, 1LL << 30);
    }
    else
      pb(numNodes, (1LL << 30));
  }
  ll root = (1LL * fmax (0, k - ((int) numNodes.sz - 1))) * pathLength + 1;
  k = fmin (k, 30);
  while(q--){
    scanf("%d %d", &a, &b);
    if(a == b){
      puts("0");
      continue;
    }
    if(a < root && b < root){
      printf("%d\n", abs (a - b));
      continue;
    }
    int distance = 0;
    if(a < root){
      distance = root - a;
      a = 1;
    }
    else{
      a -= root;
      a++;
    }
    if(b < root){
      distance = root - b;
      b = 1;
    }
    else{
      b -= root;
      b++;
    }
    vec nodesA = getNodes(a);
    vec nodesB = getNodes(b);
    int i, n = fmin (nodesA.sz, nodesB.sz);
    for(i = 0; i < n; ++i)
      if(nodesA.ptr[i] != nodesB.ptr[i])
        break;
    if(i < n){
      int lca = LCA (nodesA.ptr[i], nodesB.ptr[i]);
      distance += depth[nodesA.ptr[i]] - depth[lca] + depth[nodesB.ptr[i]] - depth[lca];
      i++;
    }
    n = fmax (nodesA.sz, nodesB.sz);
    for (; i < n; ++i){
      if (i < nodesA.sz)
        distance += depth[nodesA.ptr[i]];
      if (i < nodesB.sz)
        distance += depth[nodesB.ptr[i]];
    }
    printf("%d\n", distance);
  }
  return 0;
}
