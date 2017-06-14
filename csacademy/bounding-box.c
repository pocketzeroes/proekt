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
    int mn_x = 1005, mx_x = 0, mn_y = 1005, mx_y = 0;
    for(int i = 0; i < n; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        mn_x = min(mn_x, x);
        mn_y = min(mn_y, y);
        mx_x = max(mx_x, x);
        mx_y = max(mx_y, y);
    }

    printf("%d\n", (mx_x - mn_x) * (mx_y - mn_y) );
    return 0;
}


