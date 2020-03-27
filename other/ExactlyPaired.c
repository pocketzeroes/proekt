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
///////////////////////////////////////
typedef long long ll;
typedef long double ld;

enum{N = 1<<17};

vec idx[N];
int a[N],p[N];
ll st[2*N],z[2*N];

void build(){
    for(int i=N-1; i>0; i--)
        st[i] = fmin(st[2*i], st[2*i+1]);
}
void push(int i){
    if(z[i]){
        st[2*i  ] += z[i];
        st[2*i+1] += z[i];
        z [2*i  ] += z[i];
        z [2*i+1] += z[i];
        z [i] = 0;
    }
}
void update(int l, int r, int v, int i, int s, int e){
    if(r<s||e<l) 
        return;
    if(l<=s&&e<=r){
        st[i] += v;
        z [i] += v;
        return;
    }
    push(i);
    int m = (s+e)/2;
    update(l, r,v,2*i,s,m);
    update(l,r,v,2*i+1,m+1,e);
    st[i] = fmin(st[2*i],st[2*i+1]);
}
int query(int l, int r, int i, int s, int e){
    if(r<s||e<l)
        return -1;
    if(st[i]>0)
        return -1;
    if(s==e)
        return s;
    push(i);
    int m = (s+e)/2;
    int right = query(l,r,2*i+1,m+1,e);
    if(right!=-1)
        return right;
    else
        return query(l,r,2*i,s,m);
}
int main(){
    int n;
    scanf("%d", &n);
    const int BIG = n+7;
    for(int i=1; i<=n; i++){
        scanf("%d", &a[i]);
        pb(idx[a[i]], i);
        if(idx[a[i]].sz == 1)
            st[N+i] = st[N+i-1] + 1;
        else if(idx[a[i]].sz == 2)
            st[N+i] = st[N+i-1] - 1;
        else
            st[N+i] = st[N+i-1] + BIG;
    }
    build();
    int ans=0;
    for(int i=1; i<=n; i++){
        int j = query(i-1,n, 1, 0, N-1);
        ans = fmax(ans, j-i+1);
        update(idx[a[i]].ptr[p[a[i]]], n, -1, 1, 0, N-1);
        if(++p[a[i]] < idx[a[i]].sz)
            update(idx[a[i]].ptr[p[a[i]]],n,2, 1, 0, N-1);
        if(p[a[i]]+1 < idx[a[i]].sz)
            update(idx[a[i]].ptr[p[a[i]]+1],n,-BIG-1, 1, 0, N-1);
    }
    printf("%d\n", ans);
    return 0;
}
