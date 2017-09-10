#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef unsigned long long ull;
typedef          long long  ll;

int cmp(const void*pa, const void*pb){
   ull*a=(ull*)pa;
   ull*b=(ull*)pb;
   return *a < *b ? -1 : 1;
}
char*concat(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}

int n, c[55];
bool vis[55];
ull v[100009];
char*t;
char s[100000];
int main(){
    t = strdup("");
    scanf("%d", &n);
    scanf("%s", &s);
    for (int i = 0; i < n; i++) {
        int p = s[i] <= 'Z' ? s[i] - 65 : s[i] - 71;
        if (!vis[p]){
            vis[p] = true;
            t = concat(t, s[i]);
        }
    }
    for (int i = 0; i <= n; i++) {
        int tsz = strlen(t);
        for (int j = 1; j < tsz; j++)
            v[i] = v[i] * 1777777777 + (c[j] - c[0] + 123456789);
        if(i < n){
            char*pidx = strchr(t, s[i]);
            int idx;
            if(pidx)
                idx = pidx - t;
            else 
                idx=0;
            c[idx]++;
        }
    }
    qsort(v, n + 1, sizeof(ull), cmp);
    int l  = 0; 
    ll ret = 0;
    for (int i = 1; i <= n + 1; i++){
        if (i == n + 1 || v[i] != v[i - 1])
            ret += 1LL * (i - l) * (i - l - 1) / 2, l = i;
    }
    printf("%lld\n", ret % 1000000007 );
    return 0;
}












