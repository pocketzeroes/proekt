#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmpstr(const void*p1, const void*p2){
  return strcmp(*(char* const*) p1, *(char* const*) p2);
}

typedef long long ll;
char*a[3003];
int faktorijel[3003];
enum{ mod = 1000000007};
char ime[3003];

int rijesi(int lo, int hi, int p){
    if(hi - lo <= 1)
        return 1;
    int ret = 1;
    int novi_lo = lo;
    int komponenata = 1;
    for(int i = lo + 1; i < hi; ++i){
        if(a[novi_lo][p] != a[i][p]){
            ret = (ll)ret * rijesi(novi_lo, i, p + 1) % mod;
            novi_lo = i;
            ++komponenata;
        }
    }
    ret  = (ll)ret * rijesi(novi_lo, hi, p + 1) % mod;
    return (ll)ret * faktorijel[komponenata] % mod;
}
int main(){
    int n;
    scanf("%d", &n);
    faktorijel[0] = 1;
    for(int i=0; i<n; ++i){
        scanf("%s", ime);
        a[i] = strdup(ime);
        faktorijel[i + 1] = (ll)faktorijel[i] * (i + 1) % mod;
    }
    qsort(a, n, sizeof(char*), cmpstr);
    printf("%d\n", rijesi(0, n, 0));
    return 0;
}
