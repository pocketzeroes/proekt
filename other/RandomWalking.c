#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int*pushback(int *array, int *size, int value){
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
double prob[101][1024];

int main(){
  int k, n, e, x, y;
  scanf("%d %d %d", &k, &n, &e);
  while(k){
    vec nodes[1<<n]; memset(nodes, 0, sizeof(nodes));
    for(int i=0; i<e; i++){
      scanf("%d %d", &x, &y);
      nodes[x].ptr = pushback(nodes[x].ptr, &nodes[x].sz, y);
      nodes[y].ptr = pushback(nodes[y].ptr, &nodes[y].sz, x);
    }
    memset(prob, 0, sizeof(prob));
    bool good = true;
    for(int j=0; j<(1<<n); j++)
      prob[1][j] = 1.0/(1<<n);
    for(int i=2; i<=k && good; i++){
      for(int j=0; j<(1<<n); j++){
        for(int t=0; t<nodes[j].sz; t++){
          x = nodes[j].ptr[t];
          prob[i][j] += prob[i-1][x]/nodes[x].sz;
        }
      }
      for(int m=0; m<n; m++){
        double s=0;
        for(int j=0;j<(1<<n);j++)
          if((1<<m)&j)
            s+=prob[i][j];
        if(s<=0.25 || s>=0.75)
          good=false;
      }
    }
    if(good)
      puts("Yes");
    else
      puts("No");
    scanf("%d %d %d", &k, &n, &e);
  }
  return 0;
}
