#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
typedef long long ll;
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
enum{ maxn = 1010};

int res;
int n, f1[maxn][maxn], f2[maxn][maxn];
vec next[maxn][maxn];

void relax(int*a, int b){
  *a = fmax(*a, b);
}
int F( int a, int b ){
  if (a > b)
    swap(a, b);
  return f1[a][b];
}
void Go( int a, int b ){
  if (a > b)
    swap(a, b);
  f1[a][b] = 1, f2[a][b] = 0;
  for(int i = 0; i < next[a][b].sz; i++){
    int c = next[a][b].ptr[i];
    Go(a, c), Go(c, b);
    int len = F(a, c) + F(c, b);
    if (len >= f1[a][b])
      f2[a][b] = f1[a][b], f1[a][b] = len;
    else if (len >= f2[a][b])
      f2[a][b] = len;
  }
  if (f2[a][b])
    relax(&res, f1[a][b] + f2[a][b]);
}
int main(){
  int tn;
  scanf("%d", &tn);
  for (int tt = (int)(1); tt <= (int)(tn); tt++){
    scanf("%d", &n);
    for (int i = 0; i < (int)(n); i++)
      for (int j = 0; j < (int)(n); j++)
        next[i][j].sz=0;
    for (int i = (int)(4); i <= (int)(n); i++){
      int a, b;
      scanf("%d%d", &a, &b);
      if (a > b)
        swap(a, b);
      a--, b--;
      next[a][b].ptr = pushback(next[a][b].ptr, &next[a][b].sz, i-1);
    }
    res = 0;
    Go(1, 2), Go(2, 0), Go(1, 0);
    relax(&res, F(1, 2) + F(2, 0) + F(1, 0));
    printf("Case #%d: %d\n", tt, res);
  }
  return 0;
}
