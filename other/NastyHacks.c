#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int n, x, y, z;
    scanf("%d", &n);
    while(n--){
        scanf("%d %d %d", &x, &y, &z);
        if(x > y-z)
            puts("do not advertise");
        else if(x == y-z)
            puts("does not matter");
        else
            puts("advertise");
    }
    return 0;
}
