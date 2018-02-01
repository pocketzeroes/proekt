#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
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
///////////////----------------------------------------------
enum{ MAX_N = (int)1e5+20};
enum{ Q = 320};
//trip (int, pair)

int n,m,f[MAX_N],x,y,z,e;
int  b[MAX_N];
trip q[MAX_N];

int g(int u){
    if(b[u/Q]==-1)
        return f[u];
    else
        return b[u/Q];
}
void upd(int l, int r, int k){
    int f1 = l/Q,
        f2 = r/Q;
    if(f1 == f2){
        for(int i=f1*Q; i<(f1+1)*Q; ++i){
            if(l<=i && i<=r)
                f[i] = k;
            else if(b[f1]!=-1)
                f[i] = b[f1];
        }
        b[f1]=-1;
        return;
    }
    e = f2*Q;
    upd(e, r, k);
    e = (f1+1)*Q-1;
    upd(l, e, k);
    for(int i=f1+1; i<f2; ++i)
        b[i] = k;
}
void print(){
    for(int i=1;i<16;++i)
        printf("%d ", g(i));
    puts("");
}
int main(){
    scanf("%d %d", &n, &m);
    for(int i=0; i<MAX_N; ++i){
        f[i]  = i;
        b[i/Q]=-1;
    }
    for(int i=0;i<n;++i){
        scanf("%d %d %d", &x, &y, &z);
        q[i] = newTrip(z,newPair(x, y));
    }
    qsort(q, n, sizeof(trip), cmpT);
    for(int i=0;i<n;++i){
        x = q[i].second.first ;
        y = q[i].second.second;
        int mid=(x+y)/2;
        z=g(x);
        upd(x,mid,z);
        mid++;
        z=g(y);
        upd(mid,y,z);
    }
    while(m--){
        scanf("%d", &x);
        printf("%d\n", g(x));
    }
    puts("");
    return 0;
}

