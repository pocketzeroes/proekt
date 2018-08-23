#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define fi first
#define se second
typedef long long ll;
typedef struct{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.fi =a;
    rez.se=b;
    return rez;
}
typedef struct{
    ll first;
    ll second;
}pll;
pll newPll(ll a, ll b){
    pll rez;
    rez.fi =a;
    rez.se=b;
    return rez;
}
typedef struct{
    pll  first;
    bool second;
}trip;
trip newTrip(pll a, bool b){
    trip rez;
    rez.fi =a;
    rez.se=b;
    return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
trip*pushbackT(trip *array, int *size, trip value) {
    trip *output = resizeArray(array, trip, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
    trip*ptr;
    int sz;
}vect;
vect newVecT(){
    vect rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int cmpPll(const void*pa, const void*pb){
  pll*a = (pll*)pa;
  pll*b = (pll*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int cmpT(const void*pa, const void*pb){
    trip*a=(trip*)pa;
    trip*b=(trip*)pb;
    int rv = cmpPll(&a->first, &b->first);
    if(rv!=0)
        return rv<0?-1:1;
    return a->second < b->second?-1:1;
}

//////////////////////////
int n, q, at;
ll sa, sb, ans[100005];
pair pp[100005];
vect s;
vect v;
ll  ta;
int tmp;

#define s_back s.ptr[s.sz-1]
int main(){
    scanf("%d %d", &n, &q);
    s.ptr = pushbackT(s.ptr, &s.sz, newTrip(newPll(0, 0), true));
    while(n--){
        scanf("%lld", &ta);
        if(ta < s.ptr[s.sz-1].fi.fi){
            while(s.sz>0 && ta < s.ptr[s.sz-1].fi.fi){
                trip p = s.ptr[s.sz-1];
                s.sz--;
                if(s.sz>0 && ta > s_back.fi.fi)
                    s.ptr = pushbackT(s.ptr, &s.sz, newTrip(newPll(ta, p.fi.se+p.fi.fi-ta), false));
                if (p.se){
                    v.ptr = pushbackT(v.ptr, &v.sz, newTrip(newPll(p.fi.se,p.fi.fi-ta), true));
                    if(s.sz>0)
                        v.ptr = pushbackT(v.ptr, &v.sz, newTrip(newPll(s_back.fi.se, ta - p.fi.fi), true));
                }
                else{
                    v.ptr = pushbackT(v.ptr, &v.sz, newTrip(newPll(p.fi.se,p.fi.fi+p.fi.se-ta), true));
                    if(s.sz>0)
                        v.ptr = pushbackT(v.ptr, &v.sz, newTrip(newPll(s_back.fi.se,ta-p.fi.fi-p.fi.se),true));
                    v.ptr = pushbackT(v.ptr, &v.sz, newTrip(newPll(p.fi.se,-1), false));
                    if(s.sz>0)
                        v.ptr = pushbackT(v.ptr, &v.sz, newTrip(newPll(s_back.fi.se, 1), false));
                }
            }
            s.ptr = pushbackT(s.ptr, &s.sz, newTrip(newPll(ta,0), true));
        }
        else if(ta>s_back.fi.fi+s_back.fi.se){
            while(s.sz>0 && ta > s_back.fi.fi + s_back.fi.se){
                trip p = s_back;
                s.sz--;
                if(s.sz==0 || ta < s_back.fi.fi + s_back.fi.se)
                    s.ptr = pushbackT(s.ptr, &s.sz, newTrip(newPll(p.fi.fi, ta - p.fi.fi), true));
                if(p.se){
                    v.ptr = pushbackT(v.ptr, &v.sz, newTrip(newPll(p.fi.se, ta - p.fi.fi), 1));
                    v.ptr = pushbackT(v.ptr, &v.sz, newTrip(newPll(s_back.fi.se, p.fi.fi - ta), 1));
                    v.ptr = pushbackT(v.ptr, &v.sz, newTrip(newPll(p.fi.se, -1), 0));
                    v.ptr = pushbackT(v.ptr, &v.sz, newTrip(newPll(s_back.fi.se, 1), 0));
                }
                else{
                    v.ptr = pushbackT(v.ptr, &v.sz, newTrip(newPll(p.fi.se, ta - p.fi.fi - p.fi.se), 1));
                    v.ptr = pushbackT(v.ptr, &v.sz, newTrip(newPll(s_back.fi.se, p.fi.fi + p.fi.se - ta), 1));
                }
            }
            s.ptr = pushbackT(s.ptr, &s.sz, newTrip(newPll(ta, 0), false));
        }
    }
    qsort(v.ptr, v.sz, sizeof(trip), cmpT);
    for(int i=0; i<q; i++){
        scanf("%d", &pp[i].fi);
        pp[i].se = i;
    }
    qsort(pp, q, sizeof(pair), cmpP);
    for(int i=0; i<q; i++){
        while(at < v.sz && v.ptr[at].fi.fi <= pp[i].fi){
            if(v.ptr[at].se)
                sa += v.ptr[at].fi.se;
            else
                sb += v.ptr[at].fi.se;
            at++;
        }
        ans[pp[i].se] = sa + sb * pp[i].fi;
    }
    for(int i=0; i<q; i++)
        printf("%lld\n", ans[i]);
    return 0;
}
