#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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


int memo[52][52];
vec v;

int f(int a, int b)
{
    int i;
    if(b-a==1) return 0;
    if(memo[a][b]!=-1) return memo[a][b];
    int x=4000000;
    for( i=a+1;i<b;i++)
        x=min(v.ptr[b]-v.ptr[a]+f(a,i)+f(i,b),x);
    memo[a][b]=x;
    return x;
}

int main()
{
    int i;
    int L;
    int n;
    int aux;
    while(true)
    {
        scanf("%d", &L);
        if(L==0) break;
        scanf("%d", &n);
        v.sz=0;
        v.ptr=pushback(v.ptr, &v.sz, 0);
        for(i=0;i<n;i++)
        {
            scanf("%d", &aux);
            v.ptr=pushback(v.ptr, &v.sz, aux);
        }
        v.ptr=pushback(v.ptr, &v.sz,L);
        memset(memo,-1,sizeof(memo));
        printf("The minimum cutting is %d.\n",f(0,n+1));
    }
    return 0;
}



