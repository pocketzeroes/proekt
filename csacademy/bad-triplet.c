#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
typedef double ld;
int M=0,fst[666666],vb[666666],nxt[666666];
void ad_de(int a,int b){
    ++M;
    nxt[M]=fst[a];
    fst[a]=M;
    vb[M]=b;
}
void adde(int a,int b){
    ad_de(a,b);
    ad_de(b,a);
}


int n,m,d[666666];
bool vis[666666];
int os[666666],on=0;



void dfs(int x){
    if(vis[x])
        return;
    vis[x]=1;
    os[++on]=x;
    for(int e=fst[x],b=vb[e];e;e=nxt[e],b=vb[e])
        dfs(b);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i){
        int a,b;
        scanf("%d%d",&a,&b);
        adde(a,b); ++d[a],++d[b];
    }
    for(int i=1;i<=n;++i)
        if(d[i]>=3)
        {
            static int bs[666666];
            int bn=0;
            for (int e=fst[i],b=vb[e];e;e=nxt[e],b=vb[e])
                bs[++bn]=b;
            int x=bs[1], y=bs[2], z=bs[3];
            for (int e=fst[x],b=vb[e];e;e=nxt[e],b=vb[e])
                if(b==y){
                    printf("%d %d %d\n",x,y,i);exit(0);
                }
            for (int e=fst[y],b=vb[e];e;e=nxt[e],b=vb[e])
                if(b==z){
                    printf("%d %d %d\n",y,z,i);exit(0);
                }
            for (int e=fst[z],b=vb[e];e;e=nxt[e],b=vb[e])
                if(b==x){
                    printf("%d %d %d\n",x,z,i);exit(0);
                }
            printf("%d %d %d\n",x,y,z);exit(0);
        }
    if(m!=n-1&&n%3==0){
        dfs(1);
        printf("%d %d %d\n",os[n/3],os[n/3*2],os[n]);exit(0);
    }
    puts("-1");
}





















































