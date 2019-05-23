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
///////////////////////////
enum{ maxn = 13};
int  perm[1 << maxn],
     inv [1 << maxn];
char switched[2*maxn-1][1<<(maxn-1)],
     path[1 << maxn];

void dfs(int v, int r){
  path[v] = r;
  if(path[v ^ 1] < 0)
    dfs(v ^ 1, r ^ 1);
  v = perm[inv[v] ^ 1];
  if(path[v] < 0)
    dfs(v, r ^ 1);
}
int perfectshuffle(int i, int n){
  return ((i & 1) << (n - 1)) | (i >> 1);
}
void route_all(int n, int ypos, int xpos, int*src, int srcSz, int*dest, int destSz){
  if (n == 1){
    switched[ypos][xpos] = src[0] != dest[0];
    return;
  }
  int xlen = 1 << n,
      ylen = 2 * n - 1;
  for (int i = 0; i < xlen; ++i)
    inv[src[i]] = i;
  for (int i = 0; i < xlen; ++i)
    perm[i] = inv[dest[i]];
  for (int i = 0; i < xlen; ++i)
    inv[perm[i]] = i;
  memset(path, -1, sizeof(path));
  for (int i = 0; i < xlen; ++i)
    if (path[i] < 0)
      dfs(i, 0);
  vec left1  = newVec();
  vec right1 = newVec();
  for(int i = 0; i < xlen; i += 2){
    switched[ypos][xpos + i / 2] = path[i];
    for(int j = 0; j < 2; ++j){
      int x = perfectshuffle((i | j) ^ path[i], n);
      if(x < xlen / 2)
        left1.ptr = pushback(left1.ptr, &left1.sz, i|j);
      else
        right1.ptr = pushback(right1.ptr, &right1.sz, i|j);
    }
  }
  int half = xlen/2;
  int left2 [half];
  int right2[half];
  for(int i = 0; i < xlen; i += 2){
    int s = switched[ypos + ylen - 1][xpos + i / 2] = path[perm[i]];
    for(int j = 0; j < 2; ++j){
      int x = perfectshuffle((i | j) ^ s, n);
      if(x < xlen / 2)
        left2[x] = perm[i | j];
      else
        right2[x - xlen / 2] = perm[i | j];
    }
  }
  route_all(n-1, ypos+1, xpos,        left1.ptr,  left1.sz,  left2,  half);
  route_all(n-1, ypos+1, xpos+xlen/4, right1.ptr, right1.sz, right2, half);
}
int main(){
  int n;
  bool first = true;
  while (scanf("%i", &n) == 1, n){
    int xlen = 1 << n,
        ylen = 2 * n - 1;
    int dest[xlen];
    int src [xlen];
    for(int i = 0; i < xlen; ++i)
      src[i] = i;
    for(int i = 0; i < xlen; ++i)
      scanf("%i", &dest[i]);
    route_all(n, 0, 0, src, xlen, dest, xlen);
    if(!first)
      puts("");
    else
      first = false;
    for(int y = 0; y < ylen; ++y){
      for(int x = 0; x < xlen / 2; ++x)
        putchar('0' + switched[y][x]);
      puts("");
    }
  }
  return 0;
}

