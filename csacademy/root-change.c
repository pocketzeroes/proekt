#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdint.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

enum{ N   =(int) 1e5+10};
enum{ MOD =(int) 1e9+7 };

int n , dp_down[N] , dp_up[N] , t_down[N] , t_up[N] , ch[N];
vec g[N];

void dfs_down(int v , int p){
    int t = 0 , s = 0;
    for(int i=0;i<g[v].sz;i++){int u=g[v].ptr[i];
        if(u != p){
            dfs_down(u , v);
            ch[v] += ch[u];
            if(dp_down[u] + 1 > dp_down[v]){
                dp_down[v] = dp_down[u] + 1;
                s = ch[u] - t_down[u];
                t = 1;
            }
            else if(dp_down[u] + 1 == dp_down[v])
                t++ , s = 0;
        }
    }
    ch[v]++;
    t_down[v] = ch[v] - 1 - s;
}
void dfs_up(int v , int p){
    int mx = -1 , ted = 0;
    for(int i=0;i<g[v].sz;i++){int u=g[v].ptr[i];
        if(u != p){
            if(dp_up[v] + 1 > dp_up[u]){
                dp_up[u] = dp_up[v] + 1;
                t_up[u] = t_up[v] + 1;
            }
            if(mx != -1){
                if(mx + 2 > dp_up[u]){
                    dp_up[u] = mx + 2;
                    t_up[u] = ted;
                }
                else if(mx + 2 == dp_up[u])
                    t_up[u] = 1;
            }
            if(dp_down[u] > mx){
                mx = dp_down[u];
                ted = ch[u] - t_down[u] + 1;
            }
            else if(dp_down[u] == mx)
                ted = 1;
        }
    }
    mx = -1 , ted = 0;
    for(int i=g[v].sz-1 ; i>=0 ; i--){
        int u = g[v].ptr[i];
        if(u != p){
            if(mx != -1){
                if(mx + 2 > dp_up[u]){
                    dp_up[u] = mx + 2;
                    t_up[u] = ted;
                }
                else if(mx + 2 == dp_up[u])
                    t_up[u] = 1;
            }
            if(dp_down[u] > mx){
                mx = dp_down[u];
                ted = ch[u] - t_down[u] + 1;
            }
            else if(dp_down[u] == mx)
                ted = 1;
        }
    }
    for(int i=0;i<g[v].sz;i++){int u=g[v].ptr[i];
        if(u != p)
            dfs_up(u , v);
    }
}
int32_t main()
{
    int u , v;
    scanf("%d", &n);
    for(int i=0 ; i<n-1 ; i++){
        scanf("%d %d", &u, &v);
        u--; v--;
        g[u].ptr = pushback(g[u].ptr, &g[u].sz, v);
        g[v].ptr = pushback(g[v].ptr, &g[v].sz, u);
    }
    dfs_down(0 , 0);
    dfs_up  (0 , 0);
    for(int i=0 ; i<n ; i++){
        int x = t_up[i];
        t_up[i] = n - ch[i] - x;
    }
    for(int i=0 ; i<n ; i++){
        if(dp_up[i] > dp_down[i])       printf("%d ", t_up[i] + ch[i] - 1);
        else if(dp_up[i] == dp_down[i]) printf("%d ", n - 1 );
        else                            printf("%d ", t_down[i] + n - ch[i] );
    }
    return 0;
}





















































