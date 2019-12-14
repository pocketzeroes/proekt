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
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

#define c2(x) ((x) * ((x) - 1) / 2)

int n, m;
vec conn [25000];
vec group[25000];

void count(int from, int from_j){
    if(group[from].ptr[from_j] >= 0)
        return;
    group[from].ptr[from_j] = 1;
    int i = conn[from].ptr[from_j];
    for(int j = 0; j < conn[i].sz; ++j){
        if(conn[i].ptr[j] != from){
            count(i, j);
            group[from].ptr[from_j] += group[i].ptr[j];
        }
    }
}
int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        int x, y;
        scanf("%d %d", &x, &y);
        pb(conn [x], y);
        pb(conn [y], x);
        pb(group[x],-1);
        pb(group[y],-1);
        if(m < x + 1)
           m = x + 1;
        if(m < y + 1)
           m = y + 1;
    }
    int best   =  0;
    int best_i = -1;
    for(int i = 0; i < m; ++i){
        int result = 0;
        for(int j = 0; j < conn[i].sz; ++j){
            count(i, j);
            result += c2(group[i].ptr[j]);
        }
        result = c2(m - 1) - result;
        if(best < result){
           best = result;
           best_i = i;
        }
    }
    int best_r = 0;
    for(int j = 0; j < conn[best_i].sz; ++j){
        for(int k = j + 1; k < conn[best_i].sz; ++k){
            int result = c2(group[best_i].ptr[j] + group[best_i].ptr[k]) - c2(group[best_i].ptr[j]) - c2(group[best_i].ptr[k]);
            if(best_r < result)
               best_r = result;
        }
    }
    printf("%d %d\n", best, best - best_r);
    return 0;
}
