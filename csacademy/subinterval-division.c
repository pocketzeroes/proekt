#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

typedef long double ld;


typedef struct trip{
  int first;
  int second;
  int third;
}trip;

int cmpT(const void*pa, const void*pb)
{
    trip*a=(trip*)pa;
    trip*b=(trip*)pb;
    int diff;
    diff = a->first  - b->first;  if(diff!=0) return diff;
    diff = a->second - b->second; if(diff!=0) return diff;
    return a->third  - b->third;
}

typedef struct pair{
  int first;
  ld second;
}pair;
pair newPair(int a, ld b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}



enum{ MX = 100500};


trip a [MX];
pair sp[MX];
ld  ans[MX];

ld get_intersect(int i, int j){
    ld x0 = a[i].first;
    ld y0 = a[i].second;
    ld x1 = a[j].first;
    ld y1 = a[j].second;
    return (y1 * y1 - y0 * y0 + x1 * x1 - x0 * x0) / 2 / (x1 - x0);
}

void lets_print(ld x){
    int z = x;
    x -= z;
    printf("%d.", z);
    for(int i = 0; i < 8; i++){
        x *= 10;
        z = x;
        printf("%d", z);
        x -= z;
    }
    puts("");
}

int main()
{
    int n, x;
    scanf("%d %d", &n, &x);
    for(int i = 0; i < n; i++){
        scanf("%d %d", &a[i].first, &a[i].second);
        a[i].third = i;
    }
    qsort(a, n, sizeof(trip), cmpT);
    int k = 0;
    for(int i = 0; i < n; i++){
        if(i > 0 && a[i].first == a[i - 1].first) continue;
        while(k > 0){
            ld z = get_intersect(sp[k - 1].first, i);
            if(z < sp[k - 1].second) {k--; continue;}
            break;
        }
        if(k == 0) sp[k++] = newPair(i, 0); else{
            ld z = get_intersect(sp[k - 1].first, i);
            if(z > x) z = x;
            sp[k++] = newPair(i, z);
        }
    }
    sp[k] = newPair(0, x);
    for(int i = 0; i < k; i++){
        double d = sp[i + 1].second - sp[i].second;
        if(d > 0) ans[ a[ sp[i].first ].third ] = d;
    }
    for(int i = 0; i < n; i++){
        lets_print(ans[i]);
    }
    return 0;
}


















































