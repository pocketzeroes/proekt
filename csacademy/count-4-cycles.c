#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ N =(int) 1e5 + 500};
int n,now,ans,vis[N];
int head[N],nxt[N << 1],to[N << 1],tot;
int Head[N],Nxt[N << 1],To[N << 1],Tot;

inline void add(int x,int y){
    nxt[tot] = head[x];
    to[tot]  = y;
    head[x]  = tot++;
}
inline void Add(int x,int y){
    Nxt[Tot] = Head[x];
    To[Tot]  = y;
    Head[x]  = Tot++;
}
int main(){
    memset(head, -1, sizeof head);
    memset(Head, -1, sizeof Head);
    scanf("%d", &n);
    for(register int i =1 ;i <= n - 1; ++ i){
        int u, v;
        scanf("%d %d", &u, &v);
        add(u,v);
        add(v,u);
    }
    for(register int i =1 ;i <= n - 1; ++ i){
        int u,v;
        scanf("%d %d", &u, &v);
        Add(u,v);
        Add(v,u);
    }
    for(register int i =1 ;i <= n; ++ i){
        now++;
        for(register int j = head[i]; ~j;j = nxt[j])
            vis[to[j]] = now;
        for(register int j = Head[i]; ~j;j = Nxt[j])
            if(vis[To[j]] == now)
                ans ++;
    }
    printf("%d\n", ans/2 );
    return 0;
}
