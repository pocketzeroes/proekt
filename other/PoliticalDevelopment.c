#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
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
bool binary_search(int*arr, int r, int x){
  r--;
  int l = 0;
  while(l <= r){
    int m = l + (r-l)/2;
    if(arr[m] == x)
      return true;
    if(arr[m] < x)
      l = m + 1;
    else
      r = m - 1;
  }
  return false;
}
void iota(int*arr, int sz, int beg){
  for(int i=0; i<sz; i++)
    arr[i] = i;
}

////////////////////////////////////
enum{N =(int)5e4+1};
int n, k, ans;
int*a[N];
int szs[N];
vec curr;
bool vis[N];

void rec(int u, int i){
    ans = fmax(curr.sz, ans);
    if(i == szs[u] || ans == k) 
        return;
    rec(u, i+1);
    if(vis[a[u][i]]) 
        return;
    bool valid = true;
    for(int z=0; z<curr.sz; z++){int v = curr.ptr[z];
        if(!binary_search(a[a[u][i]], szs[a[u][i]], v)){
            valid = false;
            break;
        }
    }
    if(valid){
        pb(curr, a[u][i]);
        rec(u, i+1);
        curr.sz--;
    }
}
int lambda(const void*pa, const void*pb){
    int*x=(int*)pa;
    int*y=(int*)pb;
    return(szs[*x]<szs[*y])?-1:1;
}
int main(){
    scanf("%d %d", &n, &k);
    for(int i=0; i<n; i++){
        int sz;
        scanf("%d", &sz);
        a[i]=calloc(sz, sizeof(int));
        szs[i]=sz;
        for(int j=0; j<sz; j++)
            scanf("%d", &a[i][j]);
        qsort(a[i], sz, sizeof(int), cmp);
    }
    int ord[n];
    iota(ord, n, 0);
    qsort(ord, n, sizeof(int), lambda);
    for(int z=0;z<n;z++){int i = ord[z];
        vis[i] = true;
        pb(curr, i);
        rec(i, 0);
        curr.sz--;
    }
    printf("%d\n", ans);
    return 0;
}
