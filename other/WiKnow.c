#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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
int cmpP(pair a, pair b){
  if(a.first  != b.first) return(a.first  < b.first )?-1:1;
  if(a.second != b.second)return(a.second < b.second)?-1:1;
  return 0;
}

enum{ LEAF_OFFSET = (1<<19)};
int tree[(1<<20)];
int S[400005];
vec positions[400005];
pair best = {-1, -1};


inline int GetMinLabel(int l, int r){
  if (l == 0 || r == 0)
    return l+r;
  return fmin(l, r);
}
void Insert(int x, int label){
  x += LEAF_OFFSET;
  tree[x] = label;
  for (x/=2; x; x/=2)
    tree[x] = GetMinLabel(tree[x*2], tree[x*2+1]);
}
void Remove(int x){
  x += LEAF_OFFSET;
  tree[x] = 0;
  for (x/=2; x; x/=2)
    tree[x] = GetMinLabel(tree[x*2], tree[x*2+1]);
}
int Query(int l){
  l += LEAF_OFFSET;
  int ans = tree[l];
  while (l){
    if (l%2==0)
      ans = GetMinLabel(ans, tree[l+1]);
    l/=2;
  }
  return ans;
}
void UpdateSolution(int A, int B) {
  if (best.first == -1 || cmpP(best, newPair(A, B))>0 ) {
    best =(pair){A, B};
  }
}
void OutputAnswer(){
  if(best.first == -1)
    puts("-1");
  else
    printf("%d %d\n", best.first, best.second);
}
int main(){
  int N;
  scanf("%d", &N);
  for(int i = 0; i < N; i++){
    scanf("%d", &S[i]);
    positions[S[i]].ptr = pushback(positions[S[i]].ptr, &positions[S[i]].sz, i);
  }
  for (int i = N-1; i >= 0; i--){
    int A = S[i];
    positions[A].sz--;
    Remove(i);
    if(positions[A].sz>0){
      int B = Query(positions[A].ptr[0]);
      if (B > 0)
        UpdateSolution(A, B);
      Insert(positions[A].ptr[positions[A].sz-1], A);
    }
  }
  OutputAnswer();
  return 0;
}
