#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int cmpint(const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}


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
pair*pushbackP(pair*array, int *size, pair value){
    pair*output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}

int QDmin, nr, N, M;
int Dmin     [280009];
int TillWhere[100009];
int niv      [100009];
int frst     [100009];
int mi       [100009];
int node     [100009];
int type     [100009];
int lim      [100009];
int val      [100009];
int D        [100009];
int t        [100009];
int path     [100009];
int st       [100009];
int dr       [100009];
int Pos      [100009];
int order    [100009];
int P        [100009];
int vol      [100009];
int init     [100009];
int sz       [280009];
int*prepare_aint[280009];
int prepare_size[280009];
long long *aib    [280009];
long long ans;
pair*v [100009];
int vsz[100009];



void dfs (int nod, int tata)
{
    vol[nod] = 1, P[nod] = -1;
    for(int i=0;i<vsz[nod];i++){
        pair it=v[nod][i];
        if (it.first != tata)
        {
            t[it.first] = nod, niv[it.first] = niv[nod] + 1, dfs (it.first, nod), vol[nod] += vol[it.first], D[it.first] = it.second;
            if (P[nod] == -1 || vol[it.first] > vol[P[nod]]) P[nod] = it.first;
        }
    }
    if (P[nod] == -1) 
        path[nod] = ++nr;
    else 
        path[nod] = path[P[nod]];
    for(int i=0;i<vsz[nod];i++){
        pair it=v[nod][i];
        if(it.first != tata && it.first != P[nod]) 
            frst[path[it.first]] = it.first;
    }
}
void df2 (int nod)
{
    mi[nod] = D[nod];
    if (t[nod] != 0 && path[t[nod]] == path[nod])
        mi[nod] = min (mi[t[nod]], D[nod]);
    for(int i=0;i<vsz[nod];i++){
        pair it=v[nod][i];
        if (it.first != t[nod]) 
            df2(it.first);
    }
}
int cmp(const void*pa, const void*pb)
{
    int*ptra=(int*)pa;
    int*ptrb=(int*)pb;
    int i= *ptra;
    int j= *ptrb;
    
    if (path[i] == path[j]) 
        return(niv[i] < niv[j])?-1:1;
    return(path[i] < path[j])?-1:1;
}
void BuildBigArray ()
{
    for (int i=1; i<=N; i++)
        order[i] = i;
    qsort (order + 1, N, sizeof(int), cmp);
    for (int i=1; i<=N; i++)
        Pos[order[i]] = i;
    for (int i=1; i<=N; i++)
    {
        int j;
        for (j=i; j<=N; j++)
            if (path[order[j]] != path[order[i]]) break;
        j --;
        st[path[order[i]]] = i, dr[path[order[i]]] = j;
        i = j;
    }
}
void BuildMinDist (int nod, int st, int dr)
{
    if (st == dr)
    {
        Dmin[nod] = D[order[st]];
        return ;
    }
    int mij = (st + dr) >> 1, f1 = nod << 1, f2 = f1 | 1;
    BuildMinDist (f1, st, mij);
    BuildMinDist (f2, mij + 1, dr);
    Dmin[nod] = min (Dmin[f1], Dmin[f2]);
}
void QueryMinDist (int nod, int st, int dr, int x, int y)
{
    if (x <= st && dr <= y)
    {
        if (Dmin[nod] < QDmin) QDmin = Dmin[nod];
        return ;
    }
    int mij = (st + dr) >> 1, f1 = nod << 1, f2 = f1 | 1;
    if (x <= mij) QueryMinDist (f1, st, mij, x, y);
    if (mij < y) QueryMinDist (f2, mij + 1, dr, x, y);
}
void PrepareUpdate (int nod, int st, int dr, int x, int y, int val)
{
    if (x <= st && dr <= y)
    {
        prepare_aint[nod]=pushback(prepare_aint[nod], prepare_size+nod, val);
        return ;
    }
    int mij = (st + dr) >> 1, f1 = nod << 1, f2 = f1 | 1;
    if (x <= mij) PrepareUpdate (f1, st, mij, x, y, val);
    if (mij < y) PrepareUpdate (f2, mij + 1, dr, x, y, val);
}
int Srch (int nod, int val)
{
    int p = 0, u = prepare_size[nod] - 1, mij, ras = -1;
    while (p <= u)
    {
        mij = (p + u) >> 1;
        if (prepare_aint[nod][mij] <= val) ras = mij, p = mij + 1;
        else u = mij - 1;
    }
    return ras;
}
void Updt (int lin, int pos, int val, int sz)
{
    while (pos <= sz) aib[lin][pos] += val, pos += pos - (pos & (pos - 1));
}
long long Qry (int lin, int pos)
{
    long long sum = 0; while (pos) sum += aib[lin][pos], pos &= pos - 1; return sum;
}
void Update (int nod, int st, int dr, int x, int y, int val, int ad)
{
    if (x <= st && dr <= y)
    {
        int pos = Srch (nod, val);
        Updt (nod, pos + 1, ad, sz[nod]);
        return ;
    }
    int mij = (st + dr) >> 1, f1 = nod << 1, f2 = f1 | 1;
    if (x <= mij) Update (f1, st, mij, x, y, val, ad);
    if (mij < y) Update (f2, mij + 1, dr, x, y, val, ad);
}
void Query (int nod, int st, int dr, int pos, int lim)
{
    if ( prepare_size[nod]>0)
    {
        int pos = Srch (nod, lim);
        ans += Qry (nod, pos + 1);
    }
    if (st == dr) return ;
    int mij = (st + dr) >> 1, f1 = nod << 1, f2 = f1 | 1;
    if (pos <= mij) Query (f1, st, mij, pos, lim);
    else Query (f2, mij + 1, dr, pos, lim);
}
void Build (int nod, int st, int dr)
{
    qsort(prepare_aint[nod], prepare_size[nod], sizeof(int), cmpint);
    sz[nod] = prepare_size[nod]; 
    int arrsz=sizeof(long long)*(sz[nod] + 1);
    aib[nod] = malloc(arrsz);
    memset(aib[nod],0,arrsz);
    if (st == dr) 
        return ;
    int mij = (st + dr) >> 1, f1 = nod << 1, f2 = f1 | 1;
    Build (f1, st, mij);
    Build (f2, mij + 1, dr);
}
int main ()
{
    scanf ("%d %d", &N, &M);
    for (int i=1; i<=N; i++)
        scanf ("%d", &init[i]);
    for (int i=1; i<N; i++)
    {
        int x, y, z;
        scanf ("%d %d %d", &x, &y, &z);
        v[x]=pushbackP(v[x], vsz+x, newPair(y, z));
        v[y]=pushbackP(v[y], vsz+y, newPair(x, z));
    }
    dfs (1, -1), frst[path[1]] = 1, df2 (1);
    BuildBigArray (), BuildMinDist (1, 1, N);
    for (int i=1; i<=M; i++)
    {
        scanf ("%d", &type[i]);
        if (type[i] == 1)
        {
            scanf ("%d", &node[i]);
            continue;
        }
        scanf ("%d %d %d", &val[i], &lim[i], &node[i]);
        int p = Pos[node[i]] + 1, u = dr[path[node[i]]], mij, ras = p - 1;
        while (p <= u)
        {
            mij = (p + u) >> 1, QDmin = 1e5 + 1;
            QueryMinDist (1, 1, N, Pos[node[i]] + 1, mij);
            if (QDmin >= lim[i]) ras = mij, p = mij + 1;
            else u = mij - 1;
        }
        TillWhere[i] = ras;
        PrepareUpdate (1, 1, N, Pos[node[i]], ras, lim[i]);
    }
    Build (1, 1, N);
    for (int i=1; i<=M; i++)
    {
        if (i == 6)
            i = 6;
        if (type[i] == 2)
        {
            Update (1, 1, N, Pos[node[i]], TillWhere[i], lim[i], val[i]);
            continue;
        }
        ans = init[node[i]], Query (1, 1, N, Pos[node[i]], 1e5);
        int q = frst[path[node[i]]], curr_min = mi[node[i]];
        while (q != 1)
        {
            Query (1, 1, N, Pos[t[q]], curr_min);
            curr_min = min (curr_min, mi[t[q]]);
            q = frst[path[t[q]]];
        }
        printf ("%lld\n", ans);
    }
    return 0;
}

























































