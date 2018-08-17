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
int cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int unique(int *a, int len){
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j]) a[++j] = a[i];
	return j + 1;
}
////////////////////

int n;
vec ans;

void dfs(int n, int l, int s){
	ans.ptr = pushback(ans.ptr, &ans.sz, s+n-1);
	for(int i=l; i*i<=n; i++)
		if(n%i==0)
            dfs(n/i, i, s+i-1);
}
int main(){
	scanf("%d", &n);
	dfs(n, 2, 0);
	qsort(ans.ptr, ans.sz, sizeof(int), cmp);
	int e = unique(ans.ptr, ans.sz);
	printf("%d\n", e);
	for(int i=0; i<e; i++)
        printf("%d ", ans.ptr[i]);
}
