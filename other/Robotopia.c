#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int problems;
    scanf("%d", &problems);
    for(int z = 0; z < problems; z++){
        int L1, A1, L2, A2, LT, AT;
        scanf("%d%d%d%d%d%d", &L1, &A1, &L2, &A2, &LT, &AT);
        int solved = 0;
        int ones = 0;
        int twos = 0;
        for(int i = 1; i <= LT / L1 && solved < 2; i++){
            if((LT - (i*L1)) % L2 == 0){
                int robot2s = (LT - (i*L1)) / L2;
                if(AT - i*A1 - robot2s*A2 == 0 && robot2s >= 1){
                    ones = i;
                    twos = robot2s;
                    solved++;
                }
            }
        }
        if(solved != 1)
            puts("?");
        else
            printf("%d %d\n", ones, twos);
    }
    return 0;
}
