#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
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
//////////////////////
int main(){
  int n, m;
  scanf("%d %d", &n, &m);
  vec adj[n]; memset(adj, 0, sizeof(adj));
  for(int i=0; i<m; i++){
    int a, b;
    scanf("%d %d", &a, &b);
    adj[a].ptr = pushback(adj[a].ptr, &adj[a].sz, b);
    adj[b].ptr = pushback(adj[b].ptr, &adj[b].sz, a);
  }
  double weight[n]; memset(weight, 0, sizeof(weight));
  weight[0] = 1.0;
  int step = 0;
  double ex = 0.0;
  for(int x = 0; x < 10000; x++){
    step++;
    double new_weight[n]; memset(new_weight, 0, sizeof(new_weight));
    for(int i = 0; i < n; i++){
      for(int z=0;z<adj[i].sz;z++){int j = adj[i].ptr[z];
        new_weight[j] += weight[i]/adj[i].sz;
      }
    }
    ex += step * new_weight[n-1];
    new_weight[n-1] = 0.0;
    // weight = new_weight
//  for(int q=0;q<n;q++) weight[q] = new_weight[q];
    memcpy(weight, new_weight, sizeof(weight));
  }
  printf("%.7lf\n", ex);
  return 0;
}
