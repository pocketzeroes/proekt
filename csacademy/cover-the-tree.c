#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
#define ran 101111
int n;
vec e[ran];
int a[ran], la;
void dfs(int x, int fat){
	if(e[x].sz == 1){
		a[la++] = x;
		return;
	}
	for(int it =0; it < e[x].sz; it++){ int y = e[x].ptr[it];
		if(y == fat)
            continue;
		dfs(y,x);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int x,y;
		scanf("%d%d",&x,&y);
		e[x].ptr = pushback(e[x].ptr, &e[x].sz, y);
		e[y].ptr = pushback(e[y].ptr, &e[y].sz, x);
	}
	if(n == 2){
		printf("1\n1 2\n");
		return 0;
	}
	int rt = -1;
	for(int i=1; i<=n; i++)if(e[i].sz != 1){
		rt = i;
		break;
	}
	dfs(rt, rt);
	int w = la / 2;
	printf("%d\n",(la+1)/2);
	for(int i=0; i<w; i++)
		printf("%d %d\n",a[i],a[i+w]);
	if(la%2)
		printf("%d %d\n",a[la-1],a[la-2]);
	return 0;
}
