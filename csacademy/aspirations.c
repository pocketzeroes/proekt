#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdbool.h>
#include<limits.h>

int gcd(int u, int v ){
  return v != 0?gcd(v, u%v):u;
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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


int f(int n, int d){
    return n / d + 1;
}
int main(){
    int l, r, d;
    scanf("%d %d %d", &l, &r, &d);
    vec sol = newVec();
    for( int i = l;  i <= r;  ++i ){
        if( i % d == 0 )
            sol.ptr = pushback(sol.ptr, &sol.sz, i);
    }
    if(sol.sz==0){
        puts("impossible");
        return 0;
    }
    int gc = sol.ptr[sol.sz-1];
    for(int z=0;z<sol.sz;z++){int x = sol.ptr[z];
        gc = gcd(gc, x);
    }
    if( gc != d ){
        puts("impossible");
        return 0;
    }
    printf("%d\n", sol.sz);
    for(int z=0;z<sol.sz;z++){int x = sol.ptr[z];
        printf("%d ", x);
    }
    return 0;
}
