#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tp; tp = a; a = b; b = tp; }while(0)
int n;
int*a;
int*b;
int*c;
int*pb;
int*ipb;

void print(int*v, int*ipb){
    for(int ii=0; ii<n; ++ii){
        int i = ipb[ii];
        printf("%d%c", (v[i] == 0 ? n : v[i]), (ii + 1 < n ? ' ' : '\n'));
    }
}
bool count(int*set, int el){
    if(set[0]==el || set[1]==el)
        return true;
    return false;
}
void fix(int j, int nj){
    for(int k=0; k<n; ++k){
        int w[2] = {c[j], c[nj]};
        int alt1 = (j + b[j]) % n;
        int alt2 = (j + b[nj]) % n;
        if(count(w, alt1) || count(w, alt2)){
            int res = count(w, alt1) ? alt1 : alt2;
            if (res == alt2){
                swap(b[j], b[nj]);
                swap(pb[j], pb[nj]);
            }
            if (c[nj] == res)
                swap(c[j], c[nj]);
            return;
        }
        int sol = (n + c[j] - b[j]) % n;
        swap(b[j], b[sol]);
        swap(pb[j], pb[sol]);
        swap(c[j], c[sol]);
        swap(c[j], c[nj]);
    }
}
int main(){
    scanf("%d", &n);
    a   = calloc(n, sizeof(int));
    b   = calloc(n, sizeof(int));
    c   = calloc(n, sizeof(int));
    pb  = calloc(n, sizeof(int));
    ipb = calloc(n, sizeof(int));
    for(int i=0; i<n; ++i)
        a[i] = c[i] = pb[i] = i;
    int s = 0;
    for(int i=0; i<n-1; ++i){
        int d;
        scanf("%d", &d);
        for(int j=0; j<n; ++j)
            ipb[pb[j]] = j;
        s = (s + d) % n;
        b[ipb[i]] = d;
        b[ipb[i + 1]] = (n - s) % n;
        fix(ipb[i], ipb[i + 1]);
    }
    int d;
    scanf("%d", &d);
    if ((d + s) % n != 0){
        puts("impossible");
        return 0;
    }
    for(int i=0; i<(n); ++i)
        assert((a[i] + b[i]) % n == c[i]);
    for(int j=0; j<(n); ++j)
        ipb[pb[j]] = j;
    for(int j=0; j<(n); ++j)
        a[j] = (n - a[j]) % n;
    print(a, ipb);
    print(c, ipb);
    return 0;
}
