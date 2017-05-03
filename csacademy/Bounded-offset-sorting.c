#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int v[N];
    for (int i = 0; i < N; ++i) {
        int val;
        scanf("%d", &val);
        v[i]=(val);
    }
    qsort(v, N, sizeof(int), cmp);
    for (int i = 0; i < N; ++i) {
        printf("%d ", v[i]);
    }
    return 0;
}
