#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define maxN 100002
#define inf 1000000000

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int n, m, top, st[maxN], b[maxN], ans[maxN];

typedef struct coord
{
    int x, y, z;
}coord;
coord v[maxN];

int Dec(const void * b, const void * a)
{
   return ( *(int*)a - *(int*)b );
}
int inc(const void *a, const void *b)
{
   return ( *(int*)a - *(int*)b );
}

int cmpx(const void*pa, const void*pb)//const coord a, const coord b)
{
    coord*a=(coord*)pa;
    coord*b=(coord*)pb;
    if (a->x == b->x)
        return(a->y < b->y)?-1:1;
    return (a->x > b->x)?-1:1;
}
int cmpy(const void*pa, const void*pb)//const coord a, const coord b)
{
    coord*a=(coord*)pa;
    coord*b=(coord*)pb;
    if (a->y == b->y)
        return (a->x < b->x)?-1:1;
    return (a->y < b->y)?-1:1;
}
int bs(int x)
{
    int i = 0, p = 1 << 17;
    while (p)
    {
        if (i + p <= top && abs(b[st[i + p]] - b[st[i + p] - 1]) >= x)
            i += p;
        p >>= 1;
    }
    return i;
}
void read()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++ i)
    {
        scanf("%d %d", &v[i].x, &v[i].y);
        v[i].z = i;
    }
    for (int i = 1; i <= m; ++ i)
        scanf("%d", &b[i]);
}
void solve()
{
    int i, j;
    b[0] = -inf;
    b[m + 1] = inf;
    qsort(v + 1, n    ,sizeof(coord), cmpx);
    qsort(b    , m + 2,sizeof(int)  , Dec );
    j = 0;
    top = 0;
    for (i = 1; i <= n; ++ i)
    {
        while (b[j] >= v[i].x && j <= m + 1)
        {
            while (top > 0 && abs(b[st[top]] - b[st[top] - 1]) <= abs(b[j] - b[j - 1]))
                -- top;
            st[++ top] = j;
            ++ j;
        }
        int val = b[st[bs(v[i].y - v[i].x)]];
        if (val != inf)
        ans[v[i].z] = b[st[bs(v[i].y - v[i].x)]] - v[i].x;
    }
    qsort(b, m + 2, sizeof(int) , inc);
    qsort(v + 1, n,sizeof(coord), cmpy);
    j = 0;
    top = 0;
    for (i = 1; i <= n; ++ i)
    {
        while (b[j] <= v[i].y && j <= m + 1)
        {
            while (top > 0 && b[st[top]] - b[st[top] - 1] <= b[j] - b[j - 1])
                -- top;
            st[++ top] = j;
            ++ j;
        }
        int val = b[st[bs(v[i].y - v[i].x)]];
        if (j != 0)
        ans[v[i].z] = min(ans[v[i].z], v[i].y - b[st[bs(v[i].y - v[i].x)]]);
        else
            ans[v[i].z] = 0;
    }
}
void write()
{
    int i;
    long long Ans = 0LL;
    for (i = 1; i <= n; ++ i)
        Ans += 1LL * ans[i];
    printf("%lld\n", Ans);
}
int main()
{
    read();
    solve();
    write();
    return 0;
}






























































