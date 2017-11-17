#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int max(int a,int b){return a>b?a:b;}

int a[1000000];
int b[1000000];

int main(){
    int n;
    scanf("%d", &n);
    for (int i = (0); i < (n); i++) scanf("%d", &a[i]);
    for (int i = (0); i < (n); i++) scanf("%d", &b[i]);
    int hi = 0;
    for (int i = (0); i < (n); i++) hi = max(hi,max(a[i],b[i]));
    int lo = -1;
    while (lo+1 < hi){
        int mi = (lo+hi)/2;
        bool ok = true;
        int last = -1;
        for (int i = (0); i < (n); i++) if (a[i] <= mi) continue; else if (last == -1) last = a[i]; else if (last == a[i]) last = -1; else ok = false;
        ok &= last == -1;
        last = -1;
        for (int i = (0); i < (n); i++) if (b[i] <= mi) continue; else if (last == -1) last = b[i]; else if (last == b[i]) last = -1; else ok = false;
        ok &= last == -1;
        if (ok) hi = mi; else lo = mi;
    }
    printf("%d\n", hi);
}
