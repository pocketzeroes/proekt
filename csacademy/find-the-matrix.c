#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
typedef struct pair{
    int first;
    ll  second;
}pair;
pair newPair(int a, ll b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
pair*pushbackP(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

enum{ N = 222};
ll b[N][N];
vecp g[2 * N];
ll   d[2 * N];

int main(){
  int h, w, k;
  scanf("%d %d %d", &h, &w, &k);
  for (int i = 1; i < h; i++){
    for (int j = 1; j < w; j++){
      int foo;
      scanf("%d", &foo);
      b[i][j] = foo;
    }
  }
  for (int i = 1; i < h; i++) {
    for (int j = 1; j < w; j++) {
      for (int di = -1; di <= 0; di++) {
        for (int dj = -1; dj <= 0; dj++) {
          if (i + di > 0 && j + dj > 0 && di + dj < 0)
            b[i][j] -= b[i + di][j + dj];
        }
      }
    }
  }
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if ((i + j) & 1) {
        g[h+j].ptr = pushbackP(g[h+j].ptr, &g[h+j].sz, newPair(i, b[i][j]));
        g[i]  .ptr = pushbackP(g[i]  .ptr, &g[i]  .sz, newPair(h + j, k - b[i][j]));
      }
      else{
        g[h+j].ptr = pushbackP(g[h+j].ptr, &g[h+j].sz, newPair(i, k - b[i][j]));
        g[i]  .ptr = pushbackP(g[i]  .ptr, &g[i]  .sz, newPair(h + j, b[i][j]));
      }
    }
  }
  for (int i = 0; i < h + w; i++)
    d[i] = 0;
  int last = -1;
  for (int it = 0; it <= h + w; it++) {
    for (int i = 0; i < h + w; i++){
      for(int q=0;q<g[i].sz;q++){pair p = g[i].ptr[q];
        ll z = d[i] + p.second;
        if (z < d[p.first]) {
          d[p.first] = z;
          last = it;
        }
      }
    }
  }
  if (last == h + w) {
    puts("-1");
    return 0;
  }
  for (int i = 0; i < h; i++) {
    if (i & 1)
      d[i] *= -1;
  }
  for (int i = 0; i < w; i++) {
    if (!(i & 1)) {
      d[h + i] *= -1;
    }
  }
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (j > 0) 
        putchar(' ');
      ll cur = b[i][j];
      cur += ((j & 1) ? -1 : 1) * d[i];
      cur += ((i & 1) ? -1 : 1) * d[h + j];
      printf("%d", (int) cur);
    }
    printf("\n");
  }
  return 0;
}
