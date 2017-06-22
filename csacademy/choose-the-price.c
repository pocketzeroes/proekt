#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int cmp (const void *b, const void *a)
{
   return ( *(int*)a - *(int*)b );
}

int main() {
    int n; 
    scanf("%d", &n);
    int elements[n];
    for (int i = 0; i < n; i += 1) {
        scanf("%d", &elements[i]);
    }
    qsort(elements, n, sizeof(int), cmp);//    reverse
    int mx = 0;
    for (int i = 0; i < n; i += 1) {
        mx = max(mx, (i + 1) * elements[i]);
    }
    printf("%d\n", mx);
    return 0;
}
