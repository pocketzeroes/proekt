#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

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


int main(){
    int row, col, n;
    scanf("%d %d %d", &row, &col, &n);
    pair arr[n];
    for(int i=0; i<n; ++i){
        int I, J;
        scanf("%d %d", &I, &J);
        arr[i] = (pair){I, J};
    }
    qsort(arr, n, sizeof(pair), cmpP);
    int prevRow = 1;
    int i = 0;
    while(i < n){
        int j = i;
        vec cols = newVec();
        while(j < n && arr[i].first == arr[j].first){
            pb(cols, arr[j].second);
            ++j;
        }
        if(arr[i].first == arr[n-1].first)
           arr[i].first = row;
        int prevCol = 1;
        for(int k=0; k+1<cols.sz; ++k){
            printf("%d %d %d %d\n", prevRow, prevCol, arr[i].first, cols.ptr[k]);
            prevCol = cols.ptr[k]+1;
        }
        printf("%d %d %d %d\n", prevRow, prevCol, arr[i].first, col);
        prevRow = arr[i].first+1;
        i = j;
    }
    puts("0");
    return 0;
}
