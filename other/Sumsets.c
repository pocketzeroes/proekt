#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)

typedef long long ll;
int cmpLL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushbackL(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

typedef struct{
  ll f;
  ll s;
}pair;
pair newPair(ll a, ll b){
  return(pair){a,b};
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->f != b->f) return(a->f < b->f)?-1:1;
  if(a->s != b->s) return(a->s < b->s)?-1:1;
  return 0;
}

typedef struct{
  ll   f;
  pair s;
}trip;
trip newTrip(ll a, pair b){
  return(trip){a,b};
}
trip*pushbackT(trip*array, int *size, trip value){
    trip*output = resizeArray(array, trip, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
    trip*ptr;
    int sz;
}vect;
vect newVecT() {
    vect rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}
int cmpTr(const void*pb, const void*pa){
  trip*a = (trip*)pa;
  trip*b = (trip*)pb;
  if(a->f != b->f)return(a->f < b->f )?-1:1;
  return cmpP(&a->s, &b->s);
}

void fill(pair*arr, int sz, pair val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

enum{ INF = 2000000000};
#define LLINF 9000000000000000000ll

int overlap(pair l, pair r){
    return (l.f == r.f) + (l.f == r.s) +
           (l.s == r.f) + (l.s == r.s);
}
ll solve(trip*ab, size_t abl, size_t abr, trip*cd, size_t cdl, size_t cdr, ll*A, ll best){
    pair abij[6]; fill(abij, 6, ab[abl].s);
    for (size_t i = abl + 1; i < abr; ++i){
        pair ij = ab[i].s;
        if(cmpP(&abij[1], &abij[0])==0 && ij.f != abij[0].f && ij.s == abij[0].s)
            abij[1] = ij;
        if(cmpP(&abij[1], &abij[0])==0 && ij.f == abij[0].s && ij.s != abij[0].f)
            abij[1] =(pair){ij.s, ij.f};
        if(cmpP(&abij[4], &abij[0])==0 && ij.f != abij[0].f && ij.s == abij[0].s && ij.f != abij[1].f)
            abij[4] = ij;
        if(cmpP(&abij[4], &abij[0])==0 && ij.f == abij[0].s && ij.s != abij[0].f && ij.s != abij[1].f)
            abij[4] =(pair){ij.s, ij.f};
        if(cmpP(&abij[2], &abij[0])==0 && ij.f == abij[0].f && ij.s != abij[0].s)
            abij[2] = ij;
        if(cmpP(&abij[2], &abij[0])==0 && ij.f != abij[0].s && ij.s == abij[0].f)
            abij[2] =(pair){ij.s, ij.f};
        if(cmpP(&abij[5], &abij[0])==0 && ij.f == abij[0].f && ij.s != abij[0].s && ij.s != abij[2].s)
            abij[5] = ij;
        if(cmpP(&abij[5], &abij[0])==0 && ij.f != abij[0].s && ij.s == abij[0].f && ij.f != abij[2].s)
            abij[5] =(pair){ij.s, ij.f};
        if(cmpP(&abij[3], &abij[0])==0 && overlap(abij[0], ij) == 0){
           abij[3] = ij;
           break;
        }
    }
    for(size_t i = cdl; i < cdr; ++i){
        pair ij = cd[i].s;
        if (A[ij.s] <= best)
            continue;
        for(int z=0;z<6;z++){pair v = abij[z];
            if(overlap(v, ij) == 0)
                best = A[ij.s];
        }
    }
    return best;
}
int main(){
    int N;
    scanf("%d", &N);
    vecl A = newVecL();
    ll nc = 0LL;
    for(int i=0;i<N;i++){
        ll Ai;
        scanf("%lld", &Ai);
        A.ptr = pushbackL(A.ptr, &A.sz, Ai);
        if(Ai == 0LL)
            ++nc;
    }
    qsort(A.ptr, N, sizeof(ll), cmpLL);
    {
        vecl nA = newVecL();
        for(size_t i=0; i<N; ++i){
            if(nA.sz < 3 ||
             ( nA.ptr[nA.sz-3] != A.ptr[i] ||
               nA.ptr[nA.sz-2] != A.ptr[i] ||
               nA.ptr[nA.sz-1] != A.ptr[i] )     ){
               nA.ptr = pushbackL(nA.ptr, &nA.sz, A.ptr[i]);
            }
        }
        swap(A, nA);
    }
    vect ab = newVecT();
    vect cd = newVecT();//of trip
    for(size_t i = 0; i < A.sz; ++i){
        for(size_t j = i + 1; j < A.sz; ++j){
            ab.ptr=pushbackT(ab.ptr, &ab.sz, (trip){ A.ptr[i]+ A.ptr[j],(pair){j, i}});
            cd.ptr=pushbackT(cd.ptr, &cd.sz, (trip){-A.ptr[j]+ A.ptr[i],(pair){j, i}});
            cd.ptr=pushbackT(cd.ptr, &cd.sz, (trip){-A.ptr[i]+ A.ptr[j],(pair){i, j}});
        }
    }
    qsort(ab.ptr, ab.sz, sizeof(trip), cmpTr);//rev
    qsort(cd.ptr, cd.sz, sizeof(trip), cmpTr);//rev
    ll best = -LLINF;
    if(nc >= 4)
        best = 0LL;
    size_t abl = 0, 
           cdl = 0;
    while(1){
        while(abl < ab.sz && cdl < cd.sz && ab.ptr[abl].f != cd.ptr[cdl].f){
            while(abl < ab.sz && ab.ptr[abl].f > cd.ptr[cdl].f)
                ++abl;
            if(abl == ab.sz)
                break;
            while(cdl < cd.sz && ab.ptr[abl].f < cd.ptr[cdl].f)
                ++cdl;
            if(cdl == cd.sz)
                break;
        }
        if(abl < ab.sz && cdl < cd.sz){
            size_t abr = abl, cdr = cdl;
            while (abr < ab.sz && ab.ptr[abl].f == ab.ptr[abr].f)
                ++abr;
            while (cdr < cd.sz && cd.ptr[cdl].f == cd.ptr[cdr].f)
                ++cdr;
            best = solve(ab.ptr, abl, abr, cd.ptr, cdl, cdr, A.ptr, best);
            abl = abr;
            cdl = cdr;
        }
        else
            break;
    }
    if(best > -LLINF)
        printf("%lld\n", best);
    else
        puts("no solution");
    return 0;
}
