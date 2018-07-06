#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

int n, m, x, y, z, k, w, area, res, atmost;
int delta[1000005];

int main (){
    scanf("%d %d", &n, &area);
    for(int i =0; i<n; i++){
        scanf("%d %d", &x, &y);
        atmost = min(area / y, 1000000);
        if (atmost < x)
            continue;
        delta[x]++;
        delta[atmost + 1]--;
    }
    for(int i=1; i <=1000000; i++)
        delta[i] += delta[i - 1], res = max(res, delta[i]);
    printf("%d\n", res);
    return 0;
}
