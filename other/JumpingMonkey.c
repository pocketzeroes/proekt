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
/////////////////////////////
int q   [1<<21];
int prev[1<<21];
int shot[1<<21];

int main(){
  int n,m;
  while(scanf("%d %d", &n, &m)==2 && n+m){
    memset(prev, -1, sizeof(prev));
    vec L[n]; memset(L, 0, sizeof(L));
    for(int i=0; i<m; i++){
      int x, y;
      scanf("%d %d", &x, &y);
      L[x].ptr = pushback(L[x].ptr, &L[x].sz, y);
      L[y].ptr = pushback(L[y].ptr, &L[y].sz, x);
    }
    int begin, end;
    begin = end = 0;
    q[end++] = (1<<n)-1;
    prev[(1<<n)-1] = -2;
    while(begin != end){
      int top = q[begin++];
      for (int i=0; i<n; i++){
        int a = top;
        if(a & (1<<i)){
          a = a^(1<<i);
          int b = 0;
          for (int j=0;j<n;j++){
            if (a & (1<<j)){
              for (int k=0; k<L[j].sz; k++)
                b |= (1<<(L[j].ptr[k]));
            }
          }
          if(prev[b] == -1){
            prev[b] = top;
            shot[b] = i;
            q[end++] = b;
          }
        }
      }
    }
    if(prev[0] == -1)
      puts("Impossible");
    else{
      vec V = newVec();
      int path = 0;
      while (path != ((1<<n)-1)){
        V.ptr = pushback(V.ptr, &V.sz, shot[path]);
        path = prev[path];
      }
      printf("%d:", V.sz);
      for(int i=V.sz-1; i>=0; i--)
        printf(" %d", V.ptr[i]);
      puts("");
    }
  }
  return 0;
}
