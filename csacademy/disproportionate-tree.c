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
typedef long long ll;
///////////////////////////
ll n,i,x,y,a[100001],fr[1000],j,c,d;
ll k;
vec v[100005];

void dfs(int nod,int p){
    while(!fr[c])
        c--;
    if(nod!=1){
        a[nod]=a[p]+c;
        fr[c]--;
    }
    for(int z=0;z<v[nod].sz;z++){int i=v[nod].ptr[z];
        if(i!=p)
           dfs(i,nod);
    }
}
int main(){
    scanf("%lld %lld", &n, &k);
    for( i=1; i<n; ++i){
        scanf("%lld %lld", &x, &y);
        pb(v[x], y);
        pb(v[y], x);
    }
    if(k<n-1)
        return puts("NO")*0;
    fr[0]=n-1;
    j=1;
    k=k-n+1;
    while(k&&j<=n-1){
        if(k==1){
            k=0;
            fr[0]--;
            fr[1]++;
            break;
        }
        for(i=0;(1LL<<(i))<=k+1;i++);
        i--;
        k=k-(1<<i)+1;
        fr[0]--;
        fr[i]++;
        j++;
    }
    if(k!=0)
        return puts("NO")*0;
    puts("YES");
    a[1]=1;
    for(i=40;i>=0;i--)
        if(fr[i]){
            c=i;
            break;
        }
    dfs(1,0);
    for(i=1;i<=n;i++)
        printf("%lld ", a[i]);
    return 0;
}
