#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

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

typedef long long ll;


int main()
{
    vec div=newVec();
    int n;
    int res = 0;
    scanf("%d", &n);
    for(ll i = 1; i*i <= n; i++)
    {
        if(n%i) continue;
        div.ptr=pushback(div.ptr,&div.sz, i);
        if(i*i == n) continue;
        div.ptr=pushback(div.ptr,&div.sz, n/i);
    }
    for(int i = 0; i <  div.sz; i++)
    {
        int p = div.ptr[i];
        if(p*2> n) continue;
        if((n-p)%p == 0) res++;
    }
    printf("%d\n", res);
    return 0;
}

