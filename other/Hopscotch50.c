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
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

/////////////////////////
int n, k;
int a [55][55];
int dp[55][55];
vecp v;

int lmbd(const void*pa, const void*pb){
    pair*p=(pair*)pa;
    pair*q=(pair*)pb;
    return(a[p->first][p->second] < a[q->first][q->second])?-1:1;
}
int main(){
    scanf("%d %d", &n, &k);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%d", &a[i][j]);
            pbp(v, newpair(i, j));
        }
    }
    qsort(v.ptr, v.sz, sizeof(pair), lmbd);//
    int ret =(int)1e9;
    for(int i=0; i<v.sz; i++){
        int val = a[v.ptr[i].first][v.ptr[i].second];
        if(val == 1)
            dp[v.ptr[i].first][v.ptr[i].second] = 0;
        else{
            int x = v.ptr[i].first;
            int y = v.ptr[i].second;
            int ret =(int)1e9;
            for(int j=0; j<n; j++){
                for(int k=0; k<n; k++){
                    if(a[j][k] == val - 1){
                        ret = fmin(ret, dp[j][k] + abs(j-x) + abs(k-y));
                    }
                }
            }
            dp[x][y] = ret;
        }
        if(val == k)
            ret = fmin(ret, dp[v.ptr[i].first][v.ptr[i].second]);
    }
    if(ret>(int)1e8)
        ret = -1;
    printf("%d\n", ret);
    return 0;
}
