#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cmp (const void * a, const void * b){ return ( *(int*)a - *(int*)b ); }
int fourXtremes(int a, int b, int c, int d) {
    int aux[4];
    aux[0]=a;
    aux[1]=b;
    aux[2]=c;
    aux[3]=d;
    qsort(aux, 4, sizeof(int), cmp);
    return aux[3] - aux[0];
}
int main() {
    int a, b, c, d, maxDiff;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    maxDiff = fourXtremes(a, b, c, d);
    printf("%d\n", maxDiff);
    return 0;
}