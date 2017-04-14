#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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
int compP( pair a, pair b)
{
    int diff;
    diff = a.first  - b.first;  if(diff!=0) return diff;
    return a.second - b.second;
}
pair minP(pair a,pair b){return compP(a,b)<0?a:b;}
pair maxP(pair a,pair b){return compP(a,b)>0?a:b;}

enum{ N = 100000};
const int inf = (int)1e9 + 1;



int cv [2];
pair tree[2][N * 4];
int add [2][N * 4];
int used[2][N * 4];


void fill(int*arr,int sz, int val){
    for(int i=0;i<sz;i++)
        arr[i]=val;
}
void build(int *n)
{
    for (int j = 0; j < 2; j++)
    {
        cv[j] = 1;
        while (cv[j] < n[j])
            cv[j] <<= 1;
        for (int i = 0; i < cv[j]; i++)
            tree[j][cv[j] - 1 + i] = newPair(inf, i * 2 + j);
        for (int i = cv[j] - 2; i > -1; i--)
            tree[j][i] = minP(tree[j][i * 2 + 1], tree[j][i * 2 + 2]);
        fill(add [j], cv[j] * 2 - 1   , inf  );
        fill(used[j], cv[j] * 2 - 1   , 1);
        fill(used[j], cv[j] - 1 + n[j], 0);
    }
}
void push(int t, int x)
{
    if (!used[t][x * 2 + 1])
    {
        tree[t][x * 2 + 1].first = min(tree[t][x * 2 + 1].first, add[t][x]);
        add[t][x * 2 + 1] = min(add[t][x * 2 + 1], add[t][x]);
    }
    if (!used[t][x * 2 + 2])
    {
        tree[t][x * 2 + 2].first = min(tree[t][x * 2 + 2].first, add[t][x]);
        add[t][x * 2 + 2] = min(add[t][x * 2 + 2], add[t][x]);
    }
    add[t][x] = inf;
}
void upd(int t, int x, int lx, int rx, int l, int r, int v)
{
    if (lx >= r || l >= rx)
        return;
    else if (lx >= l && rx <= r)
    {
        if (!used[t][x])
        {
            tree[t][x].first = min(tree[t][x].first, v);
            add[t][x] = min(add[t][x], v);
        }
    }
    else
    {
        push(t, x);
        upd(t, x * 2 + 1, lx, (lx + rx) / 2, l, r, v);
        upd(t, x * 2 + 2, (lx + rx) / 2, rx, l, r, v);
        tree[t][x] = minP(tree[t][x * 2 + 1], tree[t][x * 2 + 2]);
        used[t][x] = used[t][x * 2 + 1] & used[t][x * 2 + 2];
    }
}
void upd1(int t, int x, int lx, int rx, int l, int r)
{
    if (lx >= r || l >= rx)
        return;
    else if (lx >= l && rx <= r)
    {
        tree[t][x] = newPair(inf, inf);
        used[t][x] = true;
    }
    else
    {
        push(t, x);
        upd1(t, x * 2 + 1, lx, (lx + rx) / 2, l, r);
        upd1(t, x * 2 + 2, (lx + rx) / 2, rx, l, r);
        tree[t][x] = minP(tree[t][x * 2 + 1], tree[t][x * 2 + 2]);
        used[t][x] = used[t][x * 2 + 1] & used[t][x * 2 + 2];
    }
}
int main()
{
    int n, k, m, s;
    scanf("%d %d %d %d", &n, &k, &m, &s);
    s--;
    int nn[2] = {(n + 1) / 2, n / 2};
    build(nn);
    if (s % 2 == 0)
        upd(0, 0, 0, cv[0], s / 2, s / 2 + 1, 0);
    else
        upd(1, 0, 0, cv[1], s / 2, s / 2 + 1, 0);
    for (int i = 0; i < m; i++)
    {
        int x;
        scanf("%d", &x);
        x--;
        if (x % 2 == 0)
            upd1(0, 0, 0, cv[0], x / 2, x / 2 + 1);
        else
            upd1(1, 0, 0, cv[1], x / 2, x / 2 + 1);
    }
    int d[n];
    for(int i=0;i<n;i++)d[i]=-1;
    while (true)
    {
        pair p = minP(tree[0][0], tree[1][0]);
        if (p.first == inf)
            break;
        d[p.second] = p.first;
        if (p.second % 2 == 0)
            upd1(0, 0, 0, cv[0], p.second / 2, p.second / 2 + 1);
        else
            upd1(1, 0, 0, cv[1], p.second / 2, p.second / 2 + 1);
        int l, r;
        l = max(0, p.second - (k - 1));
        l = l + ((l + (k - 1)) - p.second);
        r = min(n - 1, p.second + (k - 1));
        r = r - (p.second - (r - (k - 1)));
        if (l % 2 != (p.second + (k - 1)) % 2)
            l++;
        if (r % 2 != (p.second + (k - 1)) % 2)
            r--;
        if ((p.second + (k - 1)) % 2 == 0)
            upd(0, 0, 0, cv[0], l / 2, r / 2 + 1, p.first + 1);
        else
            upd(1, 0, 0, cv[1], l / 2, r / 2 + 1, p.first + 1);
    }
    for (int i = 0; i < n; i++)
        printf("%d ", d[i]);
    return 0;
}
























































