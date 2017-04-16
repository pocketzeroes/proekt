#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int main() {
    int mx = 0;
    int n;
    scanf("%d", &n);
    int current_sum = 0;
    for (int i = 0; i < n; i += 1) {
        int x;
        scanf("%d", &x);
        if (x == 1) {
            current_sum += 1;
        } else {
            current_sum -= 1;
        }
        current_sum = max(0, current_sum);
        mx = max(mx, current_sum);
    }
    printf("%d\n", mx);
    return 0;
}
