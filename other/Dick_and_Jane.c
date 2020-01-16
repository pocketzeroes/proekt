#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    unsigned long long s, p, y, j, d = 12, spot, puff, yertle;
    while(scanf("%llu %llu %llu %llu", &s, &p, &y, &j)==4){
        if((d + j + s + y) % 3 == 0){
            spot = (d + j + s + y) / 3;
            yertle = spot - y;
            puff = spot - s;
        }
        else if((d + j + s + y) % 3 == 1){
            spot = (d + j + s + y + 2) / 3;
            yertle = spot - y - 1;
            puff = spot - s - 1;
        }
        else{
            spot = (d + j + s + y + 1) / 3;
            yertle = spot - y;
            puff = spot - s;
            if (y == s + p + 1)
                puff--;
            else
                yertle--;
        }
        printf("%llu %llu %llu\n", spot, puff, yertle);
    }
    return 0;
}
