#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
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

typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
int cmpP(const void*pb, const void*pa){//rev
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
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
////////////////////

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int a[m][n];
    vec res = newVec();
    for(int i=0; i<m; i++){
        pb(res, i);
        for(int j=0; j<n; j++)
            scanf("%d", &a[i][j]);
    }
    for(int j=0; j<n-1; j++){
        vecp diff = newVecP();
        for(int i=0; i<m; i++)
            pbp(diff, newpair(a[i][j]-a[i][n-1], i));
        qsort(diff.ptr, diff.sz, sizeof(pair), cmpP);//rev
        ll ourLead = 0;
        int idx = 0;
        for(; idx<m; ++idx)
            if(ourLead + diff.ptr[idx].first >= 0)
               ourLead +=diff.ptr[idx].first;
            else
                break;
        vec tempRes = newVec();
        for(;idx<m; ++idx)
            pb(tempRes, diff.ptr[idx].second);
        if(res.sz > tempRes.sz)
            res = tempRes;
    }
    printf("%d\n", res.sz);
    for(int z=0;z<res.sz;z++){
        printf("%d ", res.ptr[z]+1);
    }
    return 0;
}
