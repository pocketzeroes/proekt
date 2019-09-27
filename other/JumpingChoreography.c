#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

#define pb(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
//////////////////////

typedef struct{
    int n;
    ll* bit;
}BIT;

BIT newBIT(int _n){
    BIT rez;
    rez.n   = _n;
    rez.bit = calloc(_n+1, sizeof(ll));
    return rez;
}
ll sum(BIT*t, int i){
    ll s=0;
    while(i>0){
        s += t->bit[i];
        i -= i&-i;
    }
    return s;
}
void add2(BIT*t, int i, ll x){
    while(i <= t->n){
        t->bit[i] += x;
        i += i & -i;
    }
}
void add(BIT*t, int l, int r, ll x){
    l = (l+1)/2;
    r = (r+1)/2;
    add2(t, l+1,x);
    add2(t, r+2,-x);
}

BIT b[2];
vecp e,o;
enum{P = 1100010};

void init(){
    pb(e, newpair(0,0));
    int now = 0;
    for(int i=1; i<1500; ++i){
        now += i;
        if(now>=P)
            break;
        if(now%2==1)
            pb(o, newpair(now,i));
        else
            pb(e, newpair(now,i));
    }
    for(int i=0; i<2; ++i)
        b[i] = newBIT(P);
}
void FROG(int p, int m){
    int idx = (p+1)/2;
    int l = p,
        r = p;
    for(int z=0;z<e.sz;z++){pair w = e.ptr[z];
        int a = w.second;
        int nl = fmax(0, p-w.first),
            nr = fmin(P-1, p+w.first);
        add(&b[p%2], nl, l, m*a);
        add(&b[p%2], r, nr, m*a);
        l = fmax(0,   nl-2);
        r = fmin(P-1, nr+2);
    }
    l = p-1;
    r = p+1;
    for(int z=0;z<o.sz;z++){pair w = o.ptr[z];
        int a = w.second;
        int nl = fmax(0,   p-w.first),
            nr = fmin(P-1, p+w.first);
        add(&b[!(p%2)], nl, l, m*a);
        add(&b[!(p%2)], r, nr, m*a);
        l = fmax(0,   nl-2);
        r = fmin(P-1, nr+2);
    }
}
ll ANS(int p){
    return sum(&b[p%2], (p+1)/2 +1);
}
int main(){
    init();
    int n,t;
    scanf("%d %d", &n, &t);
    ++t;
    for(int i=0; i<n; ++i){
        int p;
        scanf("%d", &p);
        ++p;
        FROG(p,1);
    }
    int C;
    scanf("%d", &C);
    for(int _=0; _<C; ++_){
        char q;
        int a;
        scanf(" %c %d", &q, &a);
        ++a;
        if(q=='t')
            t = a;
        else{
            int m = 1;
            if(q=='-')
                m = -1;
            FROG(a,m);
        }
        printf("%lld\n", ANS(t));
    }
    return 0;
}
