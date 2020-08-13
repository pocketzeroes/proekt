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
int*pushback(int *array, int *size, int value){
    int*output = resizeArray(array, int, *size + 1);
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
///////////////////////////////////////////////
char p[10100];
int Ord(char ch){
    if('0'<=ch && ch<='9')return ch-'0'+1;
    if('A'<=ch && ch<='Z')return ch-'A'+11;
    if('a'<=ch && ch<='z')return ch-'a'+11+26;
    while(1){}
}
vec E[63], F[63], G[63];
int C[63], ord[63], cnt, vis[63], SCC[63], ww[63][63], chk[63];
int AA[63], BB[63];

void DFS1(int a){
    vis[a]=1;
    for(int z=0; z<E[a].sz; z++){int x = E[a].ptr[z];
        if(!vis[x])
            DFS1(x);
    }
    ord[++cnt] = a;
}
void DFS2(int a){
    SCC[a] = cnt;
    for(int z=0; z<F[a].sz; z++){int x = F[a].ptr[z];
        if(!SCC[x])
            DFS2(x);
    }
}
//namespace MaxFlow{
    enum{ MV = 2020 };
    enum{ ME = 40040};
    enum{ INF =(int) 1e9};
    int dis[MV];
    int st[MV], en[ME<<1], nxt[ME<<1], flow[ME<<1], ce;
    int start[MV];
    void init(){
        memset(st, 0, sizeof st);
        ce = 1;
    }
    void addE(int s, int e, int f){
        ++ce; nxt[ce] = st[s]; st[s] = ce; en[ce] = e; flow[ce] = f;
        ++ce; nxt[ce] = st[e]; st[e] = ce; en[ce] = s; flow[ce] = 0;
    }
    int que[MV];
    int bfs(int N, int S, int E){
        for(int i=1;i<=N;i++) 
            dis[i] = -1;
        dis[S] = 0;
        int *fr = que, *re = que;
        *fr++ = S;
        while(fr != re){
            int t = *re++;
            for(int i=st[t];i;i=nxt[i])
                if(flow[i] > 0 && dis[en[i]] == -1){
                    dis[en[i]] = dis[t] + 1;
                    *fr++ = en[i];
                }
        }
        return dis[E] != -1;
    }
    int dfs(int x, int E, int f){
        if(x == E) 
            return f;
        for(int*i=&start[x],t; *i; i=&nxt[*i]){
            if(flow[*i] > 0 && dis[en[*i]] == dis[x] + 1 && (t = dfs(en[*i], E, fmin(f, flow[*i]))) > 0){
                flow[*i]   -= t;
                flow[(*i)^1] += t;
                return t;
            }
        }
        return 0;
    }
    int Get(int N, int S, int E){
        int res = 0;
        while(bfs(N, S, E)){
            for(int i=1;i<=N;i++)
                start[i] = st[i];
            while(1){
                int t = dfs(S, E, INF);
                if(t == 0)
                    break;
                res += t;
            }
        }
        return res;
    }
//}
void Solve(){
    int m;
    int i, j;
    scanf("%s", p);
    scanf("%d", &m);
    for(i=0;i<=62;i++){
        E[i].sz=0;
        F[i].sz=0;
        G[i].sz=0;
        C[i]=0;
        vis[i]=0;
        SCC[i] = 0;
        AA[i]=BB[i]=chk[i]=0;
        for(j=0;j<=62;j++)
            ww[i][j]=0;
    }
    for(i=0;p[i];i++)
        C[Ord(p[i])]=1;
    for(i=0;i<m;i++){
        char pp[5];
        scanf("%s", pp);
        int a = Ord(pp[0]),
            b = Ord(pp[1]);
        pb(E[a], b);
        pb(F[b], a);
    }
    cnt = 0;
    for(i=1;i<=62;i++){
        if(!vis[i]){
            DFS1(i);
        }
    }
    cnt = 0;
    for(i=62;i>=1;i--){
        if(!SCC[ord[i]]){
            cnt++;
            DFS2(ord[i]);
        }
    }
    for(i=1;i<=62;i++){
        AA[SCC[i]]++;
        BB[SCC[i]]+=C[i];
        for(int z=0;z<E[i].sz;z++){int x = E[i].ptr[z];
            ww[SCC[i]][SCC[x]]=1;
        }
    }
    for(i=1;i<=cnt;i++){
        for(j=1;j<=cnt;j++){
            if(i!=j&&ww[i][j])
               pb(G[i], j);
        }
    }
    int res=0;
    for(i=1;i<=cnt;i++){
        res += fmin(AA[i]-1,BB[i]);
    }
    for(i=1;i<=cnt;i++){
        if(G[i].sz==0){
            if(AA[i]==BB[i]){
                if(AA[i]==1){
                    res++;
                    chk[i]=1;
                }
                else{
                    BB[i]--;
                }
            }
        }
    }
    init();
    int SS = cnt*2+1, EE = cnt*2+2;
    for(int k=1;k<=cnt;k++){
        for(i=1;i<=cnt;i++){
            for(j=1;j<=cnt;j++){
                if(ww[i][k]&&ww[k][j])
                   ww[i][j]=1;
            }
        }
    }
    for(i=1;i<=cnt;i++){
        if(AA[i]==BB[i] && !chk[i]){
            addE(SS, i, 1);
        }
        if(!chk[i]){
            addE(cnt+i, EE, fmax(AA[i]-BB[i],1));
        }
    }
    for(i=1;i<=cnt;i++){
        for(j=1;j<=cnt;j++){
            if(i!=j&&ww[i][j])
                addE(i,j+cnt,9999);
        }
    }
    res += Get(EE, SS, EE);
    printf("%d\n", res);
}
int main(){
    int TC, T;
    scanf("%d", &TC);
    for(T=1; T<=TC; T++){
        printf("Case #%d: ", T);
        Solve();
    }
    return 0;
}
