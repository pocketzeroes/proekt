#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<stdint.h>
#include<limits.h>


typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair *pushback(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct vecS {
	pair*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


////
enum{ N = 2017};
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int dp[N][N], n, m, mp[N][N], cmp[N][N];
pair root[N * N];
bool mark[N][N], vis[N * N];
vec v;
void dfs(int x, int y, int mol){
    cmp[x][y] = mol;
    mark[x][y] = true;
    for(int i=0; i<4; i++){
        int nx = x + dx[i], ny = y + dy[i];
        if(nx < 0 || nx >= n || ny < 0 || ny >= m)
            continue;
        if(mark[nx][ny])
            continue;
        if(mp[nx][ny] == mp[x][y])
            dfs(nx, ny, mol);
    }
}
bool is_rect(int x, int y, int x0, int y0, int x1, int y1){
    return (x0 <= x && x <= x1 && y0 <= y && y <= y1);
}
int get(int x0, int y0 ,int x1, int y1){
    int ret = dp[x1][y1];
    if(x0 > 0)ret -= dp[x0 - 1][y1];
    if(y0 > 0)ret -= dp[x1][y0 - 1];
    if(x0 > 0 && y0 > 0)ret += dp[x0 - 1][y0 - 1];
    return ret;
}
char buff[100000];
int main(){
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++){
        char* s;
        scanf("%s",&buff);
        s=strdup(buff);
        for(int j=0; j<m; j++)
            mp[i][j] = s[j] - 'a';
    }
    int cnt = 0;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(!mark[i][j]){
                root[cnt] = newPair(i, j);
                dp[i][j]++ ;
                dfs(i, j, cnt++);
            }
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++){
            if(i > 0)dp[i][j] += dp[i - 1][j];
            if(j > 0)dp[i][j] += dp[i][j - 1];
            if(i > 0 && j > 0)dp[i][j] -= dp[i - 1][j - 1];
        }
    int q; 
    scanf("%d", &q);
    for(int i=0; i<q; i++){
        int x0, y0, x1, y1; 
        scanf("%d %d %d %d", &x0, &y0, &x1, &y1);
        --x0, --y0, --x1, --y1;
        v.sz=0;
        int ans = get(x0, y0, x1, y1);
        for(int x=x0; x<=x1; x++){
            if(!is_rect(root[cmp[x][y0]].first, root[cmp[x][y0]].second, x0, y0, x1, y1))
                if(!vis[cmp[x][y0]])ans++, vis[cmp[x][y0]] = true, v.ptr=pushback(v.ptr,&v.sz,newPair(x, y0));
            if(!is_rect(root[cmp[x][y1]].first, root[cmp[x][y1]].second, x0, y0, x1, y1))
                if(!vis[cmp[x][y1]])ans++, vis[cmp[x][y1]] = true, v.ptr=pushback(v.ptr,&v.sz,newPair(x, y1));
        }
        for(int y=y0; y<=y1; y++){
            if(!is_rect(root[cmp[x0][y]].first, root[cmp[x0][y]].second, x0, y0, x1, y1))
                if(!vis[cmp[x0][y]])ans++, vis[cmp[x0][y]] = true, v.ptr=pushback(v.ptr,&v.sz,newPair(x0, y));
            if(!is_rect(root[cmp[x1][y]].first, root[cmp[x1][y]].second, x0, y0, x1, y1))
                if(!vis[cmp[x1][y]])ans++, vis[cmp[x1][y]] = true, v.ptr=pushback(v.ptr,&v.sz,newPair(x1, y));
        }
        printf("%d\n", ans);
        for(int i=0;i<v.sz;i++){pair X = v.ptr[i];
            vis[cmp[X.first][X.second]] = false;
        }
    }
}





















































