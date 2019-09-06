#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; ++i){
        int x;
        scanf("%d", &x);
        if (x & 1) {
            printf("%d is odd\n", x);
        }
        else {
            printf("%d is even\n", x);
        }
    }
    return 0;
}
