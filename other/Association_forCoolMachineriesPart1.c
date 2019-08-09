#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{ MAXL = 6000006};
int  yy[]={-1, 0, 1, 0},
     xx[]={0, 1, 0, -1};
int  N, M, L, sy, sx;
int  D[203][203][203];
int  dir[128];
char C[203], A[203][203];

typedef struct{
    int y, x, t;
}trip;
trip P[MAXL];
int  F[MAXL];
bool teq(trip t, trip o){
    return t.y == o.y && t.x == o.x;
}
int main(){
    dir['>'] = 1; dir['v'] = 2; dir['<'] = 3;
    scanf("%d%s", &N, C); M = strlen(C);
    for (int i=1;i<=N;i++) scanf("%s", A[i]+1);
    for (int i=1;i<=N;i++) for (int j=1;j<=N;j++) if (A[i][j] == 'R')
        sy = i, sx = j;
    D[sy][sx][0] = 1; trip now = {sy, sx, 0};
    for (;;){
        int d = dir[C[now.t]];
        trip nxt = {now.y+yy[d], now.x+xx[d], (now.t+1)%M};
        if (A[nxt.y][nxt.x] == '#') nxt.y = now.y, nxt.x = now.x;
        if (D[nxt.y][nxt.x][nxt.t]) break;
        D[nxt.y][nxt.x][nxt.t] = D[now.y][now.x][now.t]+1;
        now = nxt;
    }
    trip start = now;
    for (;;){
        int d = dir[C[now.t]];
        trip nxt = {now.y+yy[d], now.x+xx[d], (now.t+1)%M};
        if (A[nxt.y][nxt.x] == '#')
            nxt.y = now.y, nxt.x = now.x;
        else
            P[++L] = nxt;
        if(teq(start, nxt) && start.t == nxt.t)
            break;
        now = nxt;
    }
    if (!L){ puts("1"); return 0; }
    for (int i=2,k=0;i<=L;i++){
        while(k && !teq(P[k+1], P[i]))
            k = F[k];
        if(teq(P[k+1], P[i]))
            k++;
        F[i] = k;
    }
    int ans = L;
    for (int i=F[L];i;i=F[i])
        if (L % (L-i) == 0)
            ans = fmin(ans, L-i);
    printf("%d\n", ans);
    return 0;
}
