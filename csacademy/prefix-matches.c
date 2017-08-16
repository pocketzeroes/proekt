#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int main() {
    int n;
    scanf("%d", &n);
    int a[n-1];
    for(int i = 0; i <(n - 1); i++)
        scanf("%d", &a[i]);
    int b[n - 1];
    memset(b,0,sizeof(b));
    for(int i = 0; i < (n - 1); i++)
        if(a[i])
            b[i + a[i] - 1] = max(b[i + a[i] - 1], a[i]);
    for (int i = n - 2; i > 0; i--) {
        b[i - 1] = max(b[i - 1], b[i] - 1);
    }
    for(int i = 0; i <(n - 1); i++)
        printf("%d ", b[i]);
    return 0;
}










