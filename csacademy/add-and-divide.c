#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int main() {
    int n; 
    scanf("%d", &n);
    int ans = 0;
    while (n != 1){
        if (n & 1){
            n += 1;
        } 
        else{
            n /= 2;
        }
        ans += 1;
    }
    printf("%d\n", ans);
    return 0;
}
