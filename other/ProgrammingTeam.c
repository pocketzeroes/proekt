#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

void fill(double*arr, int sz, double val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
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

int n, k;

int s[2501], p[2501], r[2501];
int treesize[2501];

vec child[2501];
double sum[2501][2502];


void compute(int node, double guess){
  fill(sum[node], min(k, treesize[node])+1, -1e100);
  sum[node][0] = 0;
  sum[node][1] = (node ? p[node] - guess * s[node] : 0);
  int last = 1;
  for(int z=0; z<child[node].sz; z++){int c = child[node].ptr[z];
    compute(c, guess);
    for (int i = min(last,min(k, treesize[node])); i >= 1; i--){
      for (int j = 0; j <= min(k, treesize[c]) && i+j <= min(k, treesize[node]); j++){
        sum[node][i+j] = max(sum[node][i+j], sum[node][i] + sum[c][j]);
        last = max(last, i+j);
      }
    }
  }
}
bool possible(double guess){
  compute(0, guess);
  return (sum[0][k] >= 0.0);
}
int main(){
  scanf("%d %d", &k, &n);
  k++;
  for (int i = 1; i <= n; i++) {
    scanf("%d %d %d", &s[i], &p[i], &r[i]);
    child[r[i]].ptr = pushback(child[r[i]].ptr, &child[r[i]].sz, i);
  }
  for (int i = n; i >= 0; i--){
    treesize[i] = 1;
    for(int z=0; z<child[i].sz; z++){int c = child[i].ptr[z];
      treesize[i] += treesize[c];
    }
  }
  double lo = 0;   
  double hi = 1.0;
  while (possible(hi)){
    lo = hi;
    hi *= 2;
  }
  while (hi - lo > 1e-5){
    double mid = (hi + lo) / 2.0;
    if (possible(mid))
      lo = mid;
    else
      hi = mid;
  }
  printf("%.3lf\n", lo);
  return 0;
}
