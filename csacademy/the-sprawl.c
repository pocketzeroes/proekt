#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b)do{int tmp; tmp = a; a = b; b = tmp;}while(0)


int lower_bound(int*a, int n, int x){
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x <= a[mid]) 
            h = mid;
        else
            l = mid + 1;
    }
    return l;
}
int cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int unique(int *a, int len){
    int i, j;
    for (i = j = 0; i < len; i++)
        if (a[i] != a[j]) a[++j] = a[i];
    return j + 1;
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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int uniqueP(pair*a, int len){
    int i, j;
    for(i=j=0; i<len; i++)
        if(cmpP(&a[i], &a[j])!=0)
            a[++j] = a[i];
    return j+1;
}


typedef struct{
  int  first;
  pair second;
}trip;
trip newTrip(int a, pair b){
  trip rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpT(const void*pa, const void*pb){
  trip*a=(trip*)pa;
  trip*b=(trip*)pb;
  int diff;
  int a2nd = a->second.first ; int a3rd = a->second.second;
  int b2nd = b->second.first ; int b3rd = b->second.second;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  diff = a2nd - b2nd; if(diff!=0) return diff;
  return a3rd - b3rd;
}

////////////////////////////
typedef long long ll;
enum{ ran = 250005};
enum{ inf = 100000000};
int n, L, m;
typedef struct{
    int x,
        y,
        val,
        typ;
}pnt;
pnt a[ran];
pnt newPnt(int _x, int _y, int _val, int _typ){
    pnt rez;
    rez.x   = _x;
    rez.y   = _y;
    rez.val = _val;
    rez.typ = _typ;
    return rez;
}
int cmpPt(const void*pa, const void*pb){
    pnt*a=(pnt*)pa;
    pnt*b=(pnt*)pb;
    if(a->x != b->x)
        return(a->x<b->x)?-1:1;
    if(a->y != b->y)
        return(a->y<b->y)?-1:1;
    return(a->typ<b->typ)?-1:1;
}
pair p  [ran];
int  y  [ran], ly;
pair bit[ran];
int  le;
trip e  [ran*8];
int  ace[ran],
     gsz[ran];


int lowbit(int x){
    return x & -x;
}
void update(int x, pair y){
    while(x <= ly){
        if(cmpP(&y, &bit[x])>0)
            bit[x] = y;
        x += lowbit(x);
    }
}
pair ask(int x){
    pair r = newPair(-inf, -1);
    while(x){
        if(cmpP(&bit[x], &r)>0)
            r = bit[x];
        x -= lowbit(x);
    }
    return r;
}
int ancestor(int x){
    return ace[x] - x ? ace[x] = ancestor(ace[x]) : x;
}
int main(){
    scanf("%d", &n);
    for (int i = 0; i<n; i++)
        scanf("%d %d", &p[i].first, &p[i].second);
    qsort(p, n, sizeof(pair), cmpP);
    n = uniqueP(p, n);
    for (int run = 0; run<8; run++){
        L  = 0;
        ly = 0;
        for (int i=0; i<n; i++){
            int xx = p[i].first, yy = p[i].second;
            a[L++ ] = newPnt(yy, xx - yy, xx + yy, i);
            y[ly++] = a[L - 1].y;
        }
        qsort(a, L, sizeof(pnt), cmpPt);
        qsort(y, ly, sizeof(int), cmp);
        ly = unique(y, ly);
        for(int i = 1; i <= ly; i++)
            bit[i] = newPair(-inf, -1);
        for (int i = 0; i<L; i++){
            int z = lower_bound(y, ly, a[i].y) + 1;
            pair u = ask(z);
            if (u.second != -1)
                e[le++] = newTrip(a[i].val - u.first, newPair(a[i].typ, u.second));
            update(z, newPair(a[i].val, a[i].typ));
        }
        if(run % 2)
            for(int i=0; i<n; i++)
                p[i].second *= -1;
        else
            for(int i = 0; i<n; i++)
                swap(p[i].first, p[i].second);
    }
    for(int i=0; i<n; i++){
        ace[i] = i;
        gsz[i] = 1;
    }
    qsort(e, le, sizeof(trip), cmpT);
    ll res = 0;
    for(int i=0; i<le; i++){
        int xx = e[i].second.first,
            yy = e[i].second.second;
        xx = ancestor(xx);
        yy = ancestor(yy);
        if(xx == yy)
            continue;
        res += (ll)gsz[xx] * gsz[yy] * (e[i].first / 2);
        gsz[yy] += gsz[xx];
        gsz[xx] = 0;
        ace[xx] = yy;
    }
    printf("%lld\n", res);
    return 0;
}
