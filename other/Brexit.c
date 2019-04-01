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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

enum{ MIN_C = 2     };
enum{ MAX_C = 200000}; 
enum{ MIN_P = 1     };
enum{ MAX_P = 300000};
vec neighbours[MAX_C];
int degree    [MAX_C];
int visited   [MAX_C];

void dfs(int x){
  if(visited[x])
    return;
  visited[x] = true;
  for(int z=0; z<neighbours[x].sz; z++){int y = neighbours[x].ptr[z];
    if(degree[y] == 0)
      continue;
    degree[y]--;
    if(degree[y] == (neighbours[y].sz / 2))
      dfs(y);
  }
}
int main(){
  int C, P, X, L;
  scanf("%d %d %d %d", &C, &P, &X, &L);
  assert(C >= MIN_C && C <= MAX_C);
  assert(P >= MIN_P && P <= MAX_P);
  assert(X >= 1 && X <= C);
  assert(L >= 1 && L <= C);
  X--, L--;
  for(int i = 0; i < P; i++){
    int A, B;
    scanf("%d %d", &A, &B);
    assert(A >= 1 && A <= C);
    assert(B >= 1 && B <= C);
    A--, B--;
    neighbours[A].ptr = pushback(neighbours[A].ptr, &neighbours[A].sz, B);
    neighbours[B].ptr = pushback(neighbours[B].ptr, &neighbours[B].sz, A);
    degree[A]++;
    degree[B]++;
  }
  dfs(L);
  puts(visited[X] ? "leave" : "stay");
  return 0;
}
