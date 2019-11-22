#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[100000];
char*getln(){
  char*rv = gets(buff);
  return strdup(buff);
}

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
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
vec split(char*s){
  vec rez=newVec();
  int ibuf;
  while(1){
    sscanf(s, "%d", &ibuf);
    pb(rez, ibuf);
    s = strchr(s, ' ');
    if(s==NULL)break;
    s++;
  }
  return rez;
}
//////////////////////////
int color[20], min_color = 10000, n;
vec*graph;

void coloring(int u, int color_num){
    if(color_num >= min_color)
        return;
    if(u == n){
        min_color = fmin(color_num, min_color);
        return;
    }
    for(int i = 1; i <= color_num+1; i++){
        bool can_color = true;
        for(int j = 0; j < graph[u].sz; j++){
            int v = graph[u].ptr[j];
            if(color[v] == i){
                can_color = false;
                break;
            }
        }
        if(can_color){
            color[u] = i;
            coloring(u+1, fmax(color_num, i));
            color[u] = 0;
        }
    }
}
int main(){
    scanf("%d", &n);
    graph = calloc(n, sizeof(vec));
    char*x = getln();
    for(int i=0; i<n; i++){
        x = getln();
        vec ss = split(x);
        for(int z=0; z<ss.sz; z++){
            pb(graph[i], ss.ptr[z]);
        }
    }
    coloring(0, 0);
    printf("%d\n", min_color);
    return 0;
}
