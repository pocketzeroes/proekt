#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
///////////////////////////////////
enum{ MAXN = 1000};
enum{ MAXM = 1000};
int n, m;
vec notes;
bool is[MAXN][MAXM];

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++){
        int k;
        scanf("%d", &k);
        while(k-->0){
            int l;
            scanf("%d", &l);
            is[i][l] = true;
        }
    }
    for(int i=0; i<m; i++){
        int l;
        scanf("%d", &l);
        pb(notes, l);
    }
    int note = 0;
    int res  = 0;
    while(note < m){
        int cp = -1; 
        for(int j=0; j<n; j++){
            int lcp = 0;
            for(int k = note; k < m && is[j][notes.ptr[k]]; k++)
                lcp++;
            cp = fmax(cp, lcp);
        }
        note += cp;
        res++;
    }
    printf("%d\n", res-1);
    return 0;
}
