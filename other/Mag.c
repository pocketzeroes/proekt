#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int gcd( int a, int b ) { return b == 0 ? a : gcd( b, a%b ); }

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

typedef long long ll;
#define X first
#define Y second
enum{ MAX = 1<<20};

int p   [MAX];
int dpup[MAX], dpdown[MAX];
vec L   [MAX], R     [MAX];
int pozl[MAX], pozr  [MAX];
vec V   [MAX];
pair rje = (pair){1e9, 1};

bool manji(pair a, pair b){
  return(ll)a.X*b.Y < (ll)a.Y*b.X;
}
void dfsdown(int node, int par){
  L[node].ptr = pushback(L[node].ptr, &L[node].sz, 0);
  for(int z=0;z<V[node].sz;z++){int it = V[node].ptr[z];
    if (it != par){
      dfsdown(it, node);
      pozl[it] = L[node].sz - 1;
      L[node].ptr = pushback(L[node].ptr, &L[node].sz, max(L[node].ptr[L[node].sz-1], p[it] == 1 ? dpdown[it] + 1 : 0));
    }
  }
  R[node].ptr = pushback(R[node].ptr, &R[node].sz, 0);
  for (int i=V[node].sz-1; i>=0; i--){
    int it = V[node].ptr[i];
    if (it != par){
      pozr[it] = R[node].sz - 1;
      R[node].ptr = pushback(R[node].ptr, &R[node].sz, max(R[node].ptr[R[node].sz-1], p[it] == 1 ? dpdown[it] + 1 : 0));
    }
  }
  dpdown[node] = L[node].ptr[L[node].sz-1];
}
void dfsup(int node, int par){
  if (node)
    dpup[node] = (p[par] == 1 ? (1 + max(dpup[par], max(L[par].ptr[pozl[node]], R[par].ptr[pozr[node]]))) : 0);
  pair a = (pair){p[node], 1};
  if(manji(a, rje))
    rje = a;
  int mx = dpup[node];
  for(int z=0;z<V[node].sz;z++){int it = V[node].ptr[z];
    if (it == par)
      continue;
    int val = (p[it] == 1 ? dpdown[it] + 1 : 0);
    pair tmp = (pair){p[node], 1 + mx + val};
    if(manji(tmp, rje))
      rje = tmp;
    mx = max(mx, val);
    dfsup(it, node);
  }
}
int main(){
  int n;
  scanf("%d", &n);
  for (int i=0; i<n-1; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    a--, b--;
    V[a].ptr = pushback(V[a].ptr, &V[a].sz, b);
    V[b].ptr = pushback(V[b].ptr, &V[b].sz, a);
  }
  for (int i=0; i<n; i++)
    scanf("%d", &p[i]);
  dfsdown(0, -1);
  dfsup(0, -1);
  int gc = gcd(rje.X, rje.Y);
  printf("%d/%d\n", rje.X / gc, rje.Y / gc);
  return 0;
}
