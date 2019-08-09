#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
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
enum{ MAXN = 300005};
#define bit(n) (1LL << (n))
enum{ TS = 1048576};
typedef long long ll;
int N, Q, K;
int A[MAXN], num[MAXN], out[MAXN];
vec con[MAXN];

void dfs(int n){
    num[n] = ++K;
    for(int z=0; z<con[n].sz; z++){int t = con[n].ptr[z];
        dfs(t);
    }
    out[n] = K;
}
typedef struct{
    ll a, b;
}pair;
pair opPow(pair t, pair o){
    return(pair){t.a^o.a, t.b^o.b};
}
void color(pair*p, int n){
    if(n > 50)
        p->b |= bit(n-51);
    else
        p->a |= bit(n-1);
}
int count(pair p){
    int ret = 0;
    for(ll v=p.a; v; v^=v&(-v))ret++;
    for(ll v=p.b; v; v^=v&(-v))ret++;
    return ret;
}
pair tree[TS];
int ST = TS/2-1;
void change(int x, int c){
    int n = ST+x;
    tree[n] =(pair){0,0};
    color(&tree[n], c);
    for(n>>=1; n; n>>=1)
        tree[n] = opPow(tree[n+n], tree[n+n+1]);
}
pair get(int l, int r){
    pair ret =(pair){0,0};
    for(l+=ST,r+=ST; l<=r; l>>=1,r>>=1){
        if (l&1)    ret = opPow(ret, tree[l++]);
        if (!(r&1)) ret = opPow(ret, tree[r--]);
    }
    return ret;
}
int main(){
    scanf("%d %d", &N, &Q);
    for(int i=1; i<=N; i++)
        scanf("%d", A+i);
    for(int i=2; i<=N; i++){
        int t;
        scanf("%d", &t);
        con[t].ptr = pushback(con[t].ptr, &con[t].sz, i);
    }
    dfs(1);
    for(int i=1; i<=N; i++)
        color(&tree[ST+num[i]], A[i]);
    for(int i=ST; i; i--)
        tree[i] = opPow(tree[i+i], tree[i+i+1]);
    while(Q--){
        int k, x;
        scanf("%d %d", &k, &x);
        if(k)
            change(num[x], k);
        else{
            pair z = get(num[x], out[x]);
            printf("%d\n", count(z));
        }
    }
    return 0;
}
