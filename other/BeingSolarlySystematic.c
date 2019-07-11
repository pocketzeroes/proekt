#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ MAXP   =      10000};
enum{ INF    = 1000000000};
enum{ UNUSED =         -1};
enum{ USED   =          0};

typedef struct planetoid{
    ll mass;
    ll xyz [3];
    ll v   [3];
    ll itime;
    ll ixyz[3];
    ll cmass;
    ll cv  [3];
    ll nint;
}planetoid;
planetoid pl[MAXP];

ll dim[3];

ll gcd(ll a, ll b, ll*s, ll*t){
    ll r=b, prevr = a;
    ll prevs=1, prevt = 0;
   *s = 0; *t = 1;
    while (r != 0) {
        ll q   = prevr/r;
        ll tmp = r;
        r      = prevr%r;
        prevr  = tmp;
        tmp    = *s;
       *s      = prevs - q * (*s);
        prevs  = tmp;
        tmp    = *t;
       *t      = prevt - q * (*t);
        prevt  = tmp;
    }
   *s = prevs;
   *t = prevt;
    return prevr;
}
bool itime(ll*a, ll*b, ll*mod, ll i, ll*n, ll*m){
    ll s, t;
    if (a[i] == 0 && b[i] != 0)
        return false;
    ll div = gcd(a[i], mod[i], &s, &t);
    if (b[i]%div != 0)
        return false;
    ll tmpn = s*b[i]/div;
    ll tmpm = mod[i]/div;
    (*n) += *m * tmpn;
   *m *= tmpm;
   *n = *n % *m;
    if(*n < 0)
       (*n) += *m;
    if (i < 2) {
        i++;
        b[i] -= a[i] * (*n);
        a[i] *= *m;
        if (!itime(a, b, mod, i, n, m))
            return false;
    }
    return true;
}
ll calcITime(ll i1, ll i2){
    ll a[3], b[3];
    for(int i=0; i<3; i++) {
        a[i] = pl[i1].v[i] - pl[i2].v[i];
        b[i] = pl[i2].xyz[i] - pl[i1].xyz[i];
        if (a[i] < 0) {
            a[i] = -a[i];
            b[i] = -b[i];
        }
    }
    ll n=0, m=1;
    if (itime(a, b, dim, 0, &n, &m)){
        n = n%m;
        if (n < 0)
            n += m;
        return n;
    }
    else
        return -1;
}
bool Less_Than(planetoid a, planetoid b){
  if(a.mass < b.mass)
    return true;
  if(a.mass == b.mass){
    if(a.xyz[0] > b.xyz[0])
      return true;
    if(a.xyz[0] == b.xyz[0]){
      if(a.xyz[1] > b.xyz[1])
        return true;
      if(a.xyz[1]==b.xyz[1]){
        if(a.xyz[2] > b.xyz[2])
            return true;
      }
    }
  }
  return false;
}
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)
void Swap(planetoid*a, planetoid*b){
  swap(a->mass,  b->mass);
  swap(a->itime, b->itime);
  swap(a->cmass, b->cmass);
  swap(a->nint,  b->nint);
  for(int i = 0; i < 3; i++){
    swap(a->xyz [i], b->xyz [i]);
    swap(a->v   [i], b->v   [i]);
    swap(a->ixyz[i], b->ixyz[i]);
    swap(a->cv  [i], b->cv  [i]);
  }
}
int main(){
    ll n;
    scanf("%lld %lld %lld %lld", &n, &dim[0], &dim[1], &dim[2]);
    for(int i=0; i<n; i++){
        scanf("%lld", &pl[i].mass);
        scanf("%lld %lld %lld", &pl[i].xyz[0], &pl[i].xyz[1], &pl[i].xyz[2]);
        scanf("%lld %lld %lld", &pl[i].v[0]  , &pl[i].v[1]  , &pl[i].v[2]  );
    }
    ll  earliest = 0;
    int ipass    = 0;
    while (earliest != INF){
        earliest = INF;
        for(int i=0; i<n; i++)
            pl[i].itime = -1;
        for(int i=0; i<n; i++){
            pl[i].nint = UNUSED;
            for(int j=0; j<i; j++){
                ll t = calcITime(j, i);
                if (t > 0 && t <= earliest){
                    earliest = t;
                    if (pl[j].nint == UNUSED || pl[j].itime > t){
                        pl[j].itime = t;
                        for(int k=0; k<3; k++){
                            pl[j].ixyz[k] = (pl[j].xyz[k]+t*pl[j].v[k])%dim[k];
                            if (pl[j].ixyz[k] < 0)
                                pl[j].ixyz[k] += dim[k];
                            pl[j].cv[k] = pl[j].v[k]+pl[i].v[k];
                        }
                        pl[j].cmass = pl[j].mass + pl[i].mass;
                        pl[j].nint = 2;
                    }
                    else if (pl[j].nint != USED){
                        for(int k=0; k<3; k++)
                            pl[j].cv[k] += pl[i].v[k];
                        pl[j].cmass += pl[i].mass;
                        pl[j].nint++;
                    }
                    pl[i].nint = USED;
                    pl[i].itime = t;
                }
            }
        }
        ll newn = n;
        for(int i=n-1; i>=0; i--){
            if (pl[i].itime == earliest){
                if (pl[i].nint > 0){
                    pl[i].mass = pl[i].cmass;
                    for(int k=0; k<3; k++){
                        pl[i].xyz[k] = pl[i].ixyz[k];
                        pl[i].v[k] = pl[i].cv[k]/pl[i].nint;
                    }
                }
                else if (pl[i].nint == USED)
                    pl[i] = pl[--newn];
            }
            else if (earliest != INF){
                for(int k=0; k<3; k++){
                    pl[i].xyz[k] += earliest*pl[i].v[k];
                    pl[i].xyz[k] %= dim[k];
                    if (pl[i].xyz[k] < 0)
                        pl[i].xyz[k] += dim[k];
                }
            }
        }
        n = newn;
    }
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n-1; j++){
        if(Less_Than(pl[j], pl[j+1]))
          Swap(&pl[j], &pl[j+1]);
      }
    printf("%lld\n", n);
    for(int i=0; i<n; i++){
        printf("P%d: %lld", i, pl[i].mass);
        for(int k=0; k<3; k++)
            printf(" %lld", pl[i].xyz[k]);
        for(int k=0; k<3; k++)
            printf(" %lld", pl[i].v[k]);
        puts("");
    }
    return 0;
}

