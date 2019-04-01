#include <stdio.h>

enum{ MAXN = 500};
int n;
int rk[MAXN][MAXN];
int rkmap[MAXN][MAXN];
int p[MAXN];
static int vis[2*MAXN];
static int asg[2*MAXN];
static int A[2*MAXN][2*MAXN];
static int stack[2*MAXN];
static int push = 0;
static int nosat = 0;

void dfs(int s){
    int i;
    vis[s] = 1;
    for (i=0;i<2*n;i++)
        if (A[s][i] && !vis[i])
            dfs(i);
    stack[push++] = s;
}
void rdfs(int s, int c, int t){
    int i;
    vis[s] = c;
    if (asg[s]!=0 && asg[s]!=t){
        nosat = 1;
    }
    asg[s] = t;
    asg[s^1] = -t;
    for (i=0;i<2*n;i++)
        if (A[i][s] && !vis[i])
            rdfs(i, c, t);
}
void dfsclear(){
    int i;
    for (i=0;i<2*n;i++){
        vis[i] = 0;
        asg[i] = 0;
    }
}
int solve2sat(){
    int i, cmpcol;
    nosat = 0;
    dfsclear();
    push = 0;
    for (i=0;i<2*n;i++)
        if (!vis[i])
            dfs(i);
    dfsclear();
    cmpcol = 1;
    while (push && !nosat){
        if (!vis[stack[push-1]]){
            rdfs(stack[push-1], cmpcol, asg[stack[push-1]]!=0?asg[stack[push-1]]:-1);
            cmpcol++;
        }
        push--;
    }
    return !nosat;
}
void setup(int thr){
    int i, j;
    for (i=0;i<2*n;i++)
        for (j=0;j<2*n;j++)
            A[i][j] = 0;
    for (i = 0;i < n; i++){
        for (j = 0;j < n; j++)
            rkmap[i][j] = 0;
        for (j = thr;j < n-1;j++)
            rkmap[i][rk[i][j]] = 1;
    }
    for (i = 0;i < n; i++){
        for (j = 0;j < n; j++)
            if (rkmap[i][j] || rkmap[j][i]){
            if (p[i]==p[j]){
                A[2*i+1][2*j] = 1;
                A[2*j+1][2*i] = 1;          
                A[2*i][2*j+1] = 1;
                A[2*j][2*i+1] = 1;
            }
            else if (p[i]+p[j] == 0+2){
                if (p[i]==2) {
                    A[  2*i+1][2*j+1] = 1;
                    A[  2*j][2*i] = 1;
                }
                else {
                    A[  2*i][2*j] = 1;
                    A[  2*j+1][2*i+1] = 1;
                }
            }
            else if (p[i]+p[j] == 0+1) {
                A[2*i+1][2*j] = 1;
                A[2*j+1][2*i] = 1;
            }
            else {
                A[2*i][2*j+1] = 1;
                A[2*j][2*i+1] = 1;
            }
        }
    }
}
int main(){
    int i, j, sat,hi,lo;
    scanf("%d",&n);
    for (i = 0;i < n; i++){
        scanf("%d",&p[i]);
        for (j = 0; j < n-1; j++){
            scanf("%d",&rk[i][j]);
            rk[i][j]--;
        }
    }
    lo = (n-1)/3;
    hi = (n-1);
    do{
        int mid = (hi+lo)/2;
        setup(mid);
        sat = solve2sat();
        if (!sat){
            lo = mid+1;
        }
        else {
            hi = mid;
        }
    }
    while (hi!=lo);
    printf("%d\n",hi);
#ifdef PRINT_SOL
    for (i=0;i<n;i++){
        printf("%d ",(asg[2*i]==1?0==p[i]:1+(1>=p[i])));
    }
    printf("\n");
#endif
    return 0;
}

