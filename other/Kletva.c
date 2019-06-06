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

enum{ N = 109};

int n, w, l, a[N][1009][2];
vec v;

int key(int u, int v){
    short isKey = 1;
    for(int i=0; i<l; i++){
        if(w-a[u][i][0]-a[u][i][1] != w-a[v][i][0]-a[v][i][1]){
          isKey = 0;
          break;
        }
        int diff = a[u][0][1] - a[v][0][1];
        if(a[u][i][1]-diff != a[v][i][1] || a[u][i][0]+diff != a[v][i][0]){
          isKey = 0;
          break;
        }
    }
    if(isKey)
        return isKey;
    for(int i=0; i<l; i++){
        int j = l-i-1;
        if(w-a[u][i][0]-a[u][i][1] != w-a[v][j][0]-a[v][j][1])
            return 0;
        int diff = a[u][0][0] - a[v][l-1][1];
        if(a[u][i][0]-diff != a[v][j][1] || a[u][i][1]+diff != a[v][j][0])
            return 0;
    }
    return 1;
}
int main(){
    scanf("%d %d %d\n", &w, &l, &n);
    for(int i=0; i<n; i++){
        for(int j=0; j<l; j++)
            scanf("%d", &a[i][j][0]);
        for(int j=0; j<l; j++)
            scanf("%d", &a[i][j][1]);
    }
    v.ptr = pushback(v.ptr, &v.sz, 0);
    for(int i=1; i<n; i++){
        int j;
        for(j=0; j<v.sz; j++)
            if(key(v.ptr[j], i))
                break;
        if(j==v.sz)
           v.ptr = pushback(v.ptr, &v.sz, i);
    }
    printf("%d\n", v.sz);
    return 0;
}
