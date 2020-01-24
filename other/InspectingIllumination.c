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
/////////////////////////////////////
typedef long long ll;
vec Q[100];
int ret[101][2001];
int ans[2001];

void getQueries(int lev, int l, int r){
    if(l==r)
        return;
    int mid=(l+r)/2;
    for(int i=l; i<=mid; i++)
        pb(Q[lev], i);
    getQueries(lev+1, l, mid);
    getQueries(lev+1, mid+1, r);
}
void askQueries(){
    for(int i=0; i<100; i++){
        if(Q[i].sz==0)
            return;
        printf("ASK %d", Q[i].sz);fflush(stdout);
        for(int z=0; z<Q[i].sz; z++){int x = Q[i].ptr[z];
            printf(" %d", x);fflush(stdout);
        }
        puts("");fflush(stdout);
        for(int j=0; j<Q[i].sz; j++){
            int x;
            scanf("%d", &x);
            ret[i][x]=1;
        }
    }
}
void solve(int lev, int l, int r, vec*pvc){
    if(l==r)
        ans[l] = pvc->ptr[0];
    else{
        vec L = newVec();
        vec R = newVec();
        for(int z=0; z<pvc->sz; z++){int x = pvc->ptr[z];
            if(ret[lev][x])
                pb(L, x);
            else
                pb(R, x);
        }
        solve(lev+1, l, (l+r)/2, &L);
        solve(lev+1, (l+r)/2+1, r, &R);
    }
}
int ans2[10000];
int main(){
    int n;
    scanf("%d", &n);
    getQueries(0, 1, n);
    askQueries();
    vec mvc=newVec();
    for(int i=1; i<=n; i++)
        pb(mvc, i);
    solve(0, 1, n, &mvc);
    for(int i=1; i<=n; i++)
        ans2[ans[i]] = i;
    printf("ANSWER %d", ans2[1]);fflush(stdout);
    for(int i=2; i<=n; i++){
        printf(" %d", ans2[i]);fflush(stdout);
    }
    puts("");fflush(stdout);
    return 0;
}
