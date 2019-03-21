#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int main() {
    int l1, h1, l2, h2;
    scanf("%d %d %d %d", &l1, &h1, &l2, &h2);
    int ans = max(l1 * h1, l2 * h2);
    ans = max(ans, (l1 + l2) * min(h1, h2));
    ans = max(ans, (l1 + h2) * min(h1, l2));
    ans = max(ans, (h1 + l2) * min(l1, h2));
    ans = max(ans, (h1 + h2) * min(l1, l2));
    printf("%d\n", ans);
    return 0;
}
