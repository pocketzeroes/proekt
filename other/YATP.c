#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
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

enum{ MOD=(int)1e6+ 3};
enum{ MAX=(int)2e5+10};
typedef long long ll;
vecp e[MAX];
int v[MAX];
int son[MAX],siz[MAX];
int sum,root;


void getsum(int k,int fa){
    sum++;
    for(int i=0;i<e[k].sz;i++){
        pair nex=e[k].ptr[i];
        if(nex.first==fa||v[nex.first])
            continue;
        getsum(nex.first,k);
    }
}
void getroot(int k, int fa){
    son[k]=0;
    siz[k]=1;
    for(int i=0;i<e[k].sz;i++){
        pair nex=e[k].ptr[i];
        if(nex.first==fa||v[nex.first])
            continue;
        getroot(nex.first,k);
        siz[k]+=siz[nex.first];
        son[k]=max(son[k],siz[nex.first]);
    }
    son[k]=max(son[k],sum-son[k]);
    if(son[k]<son[root])
        root=k;
}
typedef struct{
    ll ax,dx;
}lenka;
lenka A[MAX],
      B[MAX];

int cmp(const void*pa, const void*pb){
    lenka*a=(lenka*)pa;
    lenka*b=(lenka*)pb;
    if(a->ax==b->ax)
        return (a->dx<b->dx)?-1:1;
    return (a->ax<b->ax)?-1:1;
}
int cnt,p[MAX];
ll a[MAX],d[MAX];
void getdeep(int k,int fa){
    A[++cnt]=(lenka){a[k],d[k]};
    p[cnt]=k;
    for(int i=0;i<e[k].sz;i++){
        pair nex=e[k].ptr[i];
        if(nex.first==fa||v[nex.first])
            continue;
        d[nex.first]=d[k]+nex.second;
        getdeep(nex.first,k);
    }
}
ll ans[MAX];

ll check(int x,int y){
    return B[x].dx+d[y]+B[x].ax*a[y];
}
void cal(int k,int fa){
    cnt=0;
    d[k]=0;
    getdeep(k,0);
    qsort(A+1, cnt, sizeof(lenka), cmp);
    int top=1;
    B[top]=A[1];
    for(int i=2;i<=cnt;i++){
        while(top>1&&(A[i].dx-B[top].dx)*(A[i].ax-B[top-1].ax)<=(A[i].dx-B[top-1].dx)*(A[i].ax-B[top].ax))
            top--;
        B[++top]=A[i];
    }
    for(int i=1;i<=cnt;i++){
        int L=1,R=top;
        while(R-L>1){
            int mid=(L+R)/2;
            int mm=(mid+R)/2;
            if(check(mid,p[i])>check(mm,p[i]))
                L=mid;
            else
                R=mm;
        }
        ans[p[i]]=min(ans[p[i]],check(L,p[i]));
        ans[p[i]]=min(ans[p[i]],check(R,p[i]));
    }
}
void solve(int k){
    cal(k,0);
    v[k]=1;
    for(int i=0;i<e[k].sz;i++){
        pair nex=e[k].ptr[i];
        if(v[nex.first])
            continue;
        sum=0;
        getsum(nex.first,0);
        root=0;
        son[root]=sum+1;
        getroot(nex.first,0);
        solve(root);
    }
}
int main(){
    int n;
    scanf("%d", &n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)
        ans[i]=a[i]*a[i];
    for(int i=1;i<n;i++){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        e[x].ptr = pushbackP(e[x].ptr, &e[x].sz, (pair){y,z});
        e[y].ptr = pushbackP(e[y].ptr, &e[y].sz, (pair){x,z});
    }
    sum=n;
    root=0;
    son[root]=sum+1;
    getroot(1,0);
    solve(root);
    ll tot=0;
    for(int i=1;i<=n;i++)
        tot+=ans[i];
    printf("%lld\n", tot);
    return 0;
}
