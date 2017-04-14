#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
int cmp(const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
  
int*c=NULL;int cSz=0;
int n, r, b;
int a[100007];
int upper_bound(int*a, int n, int x) {
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x >= a[mid])
            l = mid + 1;
        else
            h = mid;
    }
    return l;
}
int main() {
    scanf("%d %d %d", &n, &r, &b);
    for(int i = 1; i <= r; ++i) {
        scanf("%d", &a[i]);
    }
    for(int j = 1; j <= b; ++j) {
        int x;
        scanf("%d", &x);
        c=pushback(c,&cSz,x);
    }
    qsort(c, cSz, sizeof(int), cmp);
    long long ans = 0;
    for(int i = 1; i <= r; ++i) {
        int pz1 = upper_bound(c, cSz, a[i]);
        int x = fabs(a[i] - c[pz1]);
        if(pz1 + 1 < b) {
            x = min(x, (int)fabs(c[pz1 + 1] - a[i]));
        }
        if(pz1 > 0) {
            x = min(x, (int)fabs(c[pz1 - 1] - a[i]));
        }
        ans += x;
    }
    printf("%lld\n", ans);
    return 0;
}












