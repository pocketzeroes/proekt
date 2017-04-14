#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

enum{ MAX = 1005};
int grid[MAX][MAX], N, M, siz[MAX][MAX], k, par[MAX][MAX];
bool vis[MAX][MAX];
bool vis2[MAX][MAX];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
bool taken[MAX*MAX];

bool valid(int r, int c)
{
    if(r<0 || r>=N || c<0 || c>=M)
        return 0;
    if(grid[r][c]==0)
        return 0;
    return 1;
}
int fil(int r, int c)
{
    int cnt = 1;
    vis[r][c] = 1;
    for(int i = 0;i<4;i++)
    {
        int nx = dx[i] + r;
        int ny = dy[i] + c;
        if(valid(nx, ny) && vis[nx][ny]==0)
            cnt+=fil(nx, ny);
    }
    return cnt;
}
void asign(int r, int c, int val, int p)
{
    vis2[r][c] = 1;
    par[r][c] = p;
    siz[r][c] = val;
    for(int i = 0;i<4;i++)
    {
        int nx = dx[i] + r;
        int ny = dy[i] + c;
        if(valid(nx, ny) && vis2[nx][ny]==0)
            asign(nx, ny, val, p);
    }
}
int cal(int r, int c)
{
    int*v=NULL;int vSz=0;
    v=pushback(v,&vSz,0);
    v=pushback(v,&vSz,0);
    v=pushback(v,&vSz,0);
    v=pushback(v,&vSz,0);
    for(int i = 0;i<4;i++)
    {
        int nx = dx[i] + r;
        int ny = dy[i] + c;
        if(valid(nx, ny) && taken[par[nx][ny]]==0)
        {
            taken[par[nx][ny]] = 1;
            v=pushback(v,&vSz,siz[nx][ny]);
        }
    }
    for(int i = 0;i<4;i++)
    {
        int nx = dx[i] + r;
        int ny = dy[i] + c;
        if(valid(nx, ny))
        {
            taken[par[nx][ny]] = 0;
        }
    }
    qsort(v, vSz, sizeof(int), cmp);
    int n = vSz;
    int ret = 1;
    for(int i=n-1;i>=n-4;i--) 
        ret+=v[i];
    return ret;
}
int main()
{
    k = 1;
    scanf("%d %d",&N,&M);
    for(int i = 0;i<N;i++)
    {
        for(int j = 0;j<M;j++)
        {
            scanf("%d", &grid[i][j]);
        }
    }
    for(int i = 0;i<N;i++)
    {
        for(int j = 0;j<M;j++)
        {
            if(grid[i][j]==1 && vis[i][j]==0)
            {
                int cnt = fil(i, j);
                asign(i, j, cnt, k++);
            }
        }
    }
    memset(vis, 0, sizeof(vis));
    int ans = 0;
    for(int i = 0;i<N;i++)
    {
        for(int j = 0;j<M;j++)
        {
            if(grid[i][j]==0)
            {
                ans = max(ans, cal(i, j));
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}


















































