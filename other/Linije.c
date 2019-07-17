#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value){
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
/////////////////////////
int N;
vec E[510];
int left[510], right[510];
int visited[510], cookie;
int cnt_x[510], cnt_y[510];

int dfs(int node){
	if(node == -1)
    return 1;
	if(visited[node] == cookie)
    return 0;
	visited[node] = cookie;
	for(int i = 0; i < E[node].sz; ++i){
		if(dfs(left[E[node].ptr[i]])) {
			left[E[node].ptr[i]] = node;
			right[node] = E[node].ptr[i];
			return 1;
		}
  }
	return 0;
}
void matching(){
	int ret = 0;
	for(int i = 1; i <= 500; ++i){
		++cookie;
		if(dfs(i))
      ++ret;
	}
}
int main(){
	scanf("%d", &N);
	for(int i = 0; i < N; ++i){
		int x, y;
    scanf("%d%d", &x, &y);
		++cnt_x[x];
    ++cnt_y[y];
		E[x].ptr = pushback(E[x].ptr, &E[x].sz, y);
	}
	memset(left , -1, sizeof left );
	memset(right, -1, sizeof right);
	matching();
	for(int i = 1; i <= 500; ++i){
		if(cnt_x[i] > 0 && right[i] == -1) return printf("Mirko\n"), 0;
		if(cnt_y[i] > 0 && left [i] == -1) return printf("Mirko\n"), 0;
	}
	printf("Slavko\n");
	return 0;
}
