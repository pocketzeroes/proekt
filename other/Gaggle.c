#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define back(_v) _v.ptr[_v.sz-1]
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
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
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
//////////////////////////////////////

int main(){
    int n;
    scanf("%d", &n);
    int forw[n+1];
    for(int i=1; i<=n; ++i)
        scanf("%d", &forw[i]);
    vec avail = newVec();
    int taken    [n+1]; clr(taken);
    int other_end[n+1]; fill(other_end, n+1, -1);
    for(int i=n; i>=1; --i){
        other_end[i] = i;
        pb(avail, i);
    }
    for(int i=1; i<=n; ++i){
        if(other_end[i] != forw[i])
           pb(avail, forw[i]);
        int x = -1;
        while(taken[back(avail)] || (i < n && other_end[i] == back(avail))){
            if(!taken[back(avail)])
                x = back(avail);
            avail.sz--;
        }
        int j = back(avail);
        avail.sz--;
        if(x != -1)
            pb(avail, x);
        int i_end = other_end[i],
            j_end = other_end[j];
        forw[i] = j;
        taken[j] = true;
        other_end[i_end] = j_end;
        other_end[j_end] = i_end;
    }
    for(int i=1; i<=n; ++i)
        printf("%d%c", forw[i], i==n ? '\n' : ' ');
    return 0;
}
