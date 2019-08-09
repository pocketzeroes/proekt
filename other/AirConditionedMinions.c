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
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
 
int N;
vec arr[201];
 
int main(){
    scanf("%d", &N);
    for(int i=1; i<=N; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        arr[a].ptr = pushback(arr[a].ptr, &arr[a].sz, b);
    }
    int mn = 2e9, ans = 0;
    for(int i=1;i<=N+N;i++){
        if(mn < i)
            ans++, mn = 2e9;
        for(int z=0;z<arr[i].sz;z++){int e = arr[i].ptr[z];
            mn = fmin(mn, e);
        }
    }
    if(mn < 2e9)
        ans++;
    printf("%d\n", ans);
    return 0;
}
