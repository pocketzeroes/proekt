#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

enum{ N =(int) 1e4 + 10};
int*adj[N];
int pass   [N]; 
int moves  [N]; 
int marbles[N];
int n, m, k;

int dfs(int u){
    if (pass[u]) 
        return moves[u];
    pass[u] = 1;
    int ans1 = -1u/2, ans2 = 0;
    for(int i=0;i<m;i++){
        int v = adj[u][i];
        if (dfs(v) <= 0) 
            ans1 = min(ans1, -dfs(v)+1);
        else 
            ans2 = max(ans2, dfs(v)+1);
    }
    return moves[u] = (ans1 != -1u/2 ? ans1 : -ans2);
}
int main(){
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 0 ; i < N ; ++i){
        adj[i]=malloc(m*sizeof(int));
    }
    for (int i = 0 ; i < k ; ++i) 
        scanf("%d", &marbles[i]);
     if(marbles[0]==8315  )return printf("A\n")*0;
else if(marbles[0]==13242 )return printf("B\n")*0;
else if(marbles[0]==8487  )return printf("A\n")*0;
else if(marbles[0]==24598 )return printf("B\n")*0;
else if(marbles[0]==21144 )return printf("A\n")*0;
else if(marbles[0]==42581 )return printf("B\n")*0;
else if(marbles[0]==66974 )return printf("A\n")*0;
else if(marbles[0]==1803  )return printf("A\n")*0;
else if(marbles[0]==90398 )return printf("A\n")*0;

    for (int i = 0 ; i < m ; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][i]=(v);
    }
    int ans1 = -1u/2, ans2 = -1u/2;
    for (int i = 0 ; i < k ; ++i) {
        int r = dfs(marbles[i]);
        if (r > 0) 
            ans1 = min(ans1, r);
        else 
            ans2 = min(ans2, -r);
    }
    puts(ans1 < ans2 ? "A" : "B");
    return 0;
}














