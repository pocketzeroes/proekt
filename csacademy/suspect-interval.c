#include<stdio.h>

inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int main() {
    int n;
    scanf("%d", &n);
    int els[n+2];
    int i;
    for(i = 0; i < n; i += 1) {
        scanf("%d", &els[i]);
    }
    els[i++]= 0;
    els[i++]= (int)1e5 + 1;
    qsort(els, i, sizeof(int), cmp);
    int mx = 0;
    for (int i = 0; i < n; i += 1) {
        mx = max(mx, els[i + 2] - els[i] - 1);
    }
    printf("%d\n", mx);
    return 0;
}
