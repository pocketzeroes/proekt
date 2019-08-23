#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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

typedef long long ll;
enum{ INF = 0x3f3f3f3f};
#define LL_inf (1ll<<60)
enum{ N =(int)2e3+100};

vecp ans;
int  nx, ny;
int  g[N][N];
int  girl[N], Lx[N], Ly[N];
int  slack[N];
bool S[N], T[N];

bool DFS(int x){
    S[x]=true;
    for(int i=1; i<=ny; i++){
        if(T[i])
            continue;
        int tmp=Lx[x]+Ly[i]-g[x][i];
        if( tmp==0 ){
            T[i]=true;
            if(girl[i]==-1 || DFS(girl[i])){
                girl[i]=x;
                return true;
            }
        }
        else if(slack[i]>tmp)
            slack[i]=tmp;
    }
    return false;
}
pair  KM(){
    memset(girl, -1, sizeof(girl));
    memset(Ly, 0, sizeof(Ly));
    for(int i=1; i<=nx; i++){
        Lx[i] = -INF;
        for(int j=1; j<=ny; j++)
            if(g[i][j]>Lx[i])
                Lx[i]=g[i][j];
    }
    for(int j=1; j<=nx; j++){
        for(int i=1; i<=ny; i++)
            slack[i]=INF;
        while(1){
            memset(S, 0, sizeof(S));
            memset(T, 0, sizeof(T));
            if( DFS(j) )
                break;
            int d=INF;
            for(int i=1; i<=ny; i++)
                if(!T[i] && d>slack[i])
                    d=slack[i];
            for(int i=1; i<=nx; i++)
                if(S[i])
                    Lx[i]-=d;
            for(int i=1; i<=ny; i++){
                if(T[i])
                    Ly[i]+=d;
                else
                    slack[i]-=d;
            }
        }
    }
    int sum=0;
    int num=0;
    for(int i=1; i<=ny; i++){
        if(girl[i]>0){
            sum+=g[girl[i]][i];
            num++;
            ans.ptr = pushbackP(ans.ptr, &ans.sz, newPair(girl[i],i));
        }
    }
    return newPair(sum,num);
}
int main(){
    int k;
    int n,m;
    scanf("%d %d %d", &n, &m, &k);
    int flag=1;
    if(n>m){
        nx=m;
        ny=n;
        flag=0;
    }
    else{
        nx=n;
        ny=m;
    }
    while(k--){
        int st,ed,val;
        scanf("%d %d %d",&st,&ed,&val);
        if(!flag)
            g[st][ed]=val;
        else
            g[ed][st]=val;
    }
    pair tmp = KM();
    printf("%d\n", tmp.first);
    printf("%d\n", tmp.second);
    int len=ans.sz;
    for(int i=0; i<len; i++){
        if(flag)
            printf("%d %d\n", ans.ptr[i].second, ans.ptr[i].first);
        else
            printf("%d %d\n", ans.ptr[i].first, ans.ptr[i].second);
    }
    return 0;
}
