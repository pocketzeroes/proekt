#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int main() {
    int M, S;
    scanf("%d %d", &M, &S);
    int L [S]; memset(L , 0, sizeof(L ));
    int MX[S]; memset(MX, 0, sizeof(MX));
    for (int i = 0; i < S; ++i)
        scanf("%d", &L[i]), --L[i], MX[L[i]] = i;
    for (int i = 1; i < M; ++i)
        for (int j = 0, v; j < S; ++j){
            scanf("%d", &v);
            if (MX[v - 1] < j) 
                MX[v - 1] = j;
        }
    int i = -1, l = 0;
    while (i < l) 
        if (l < MX[L[++i]]) 
            l = MX[L[i]];
    ++l;
    printf("%d\n", l);
    qsort(L, l, sizeof(int), cmp);
    for(int i = 0; i < l; ++i)
        printf("%d%c", L[i]+1, " \n"[i + 1 == l]);
    return 0;
}
