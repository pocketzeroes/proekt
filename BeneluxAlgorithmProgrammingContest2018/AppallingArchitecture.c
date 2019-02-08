#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ N = 100};

int main(){
    int R, C;
    scanf("%d %d", &R, &C);
    int left  = N + 1, 
        right = -1, 
        sum   = 0, 
        count = 0;
    for(int r=0; r<R; ++r){
        getchar();
        for(int c = 0; c < C; ++c){
            char x = getchar();
            if(x != '.'){
                ++count;
                sum += c;
                if(r == R - 1)
                    left  = min(left, c),
                    right = max(right, c);
            }
        }
    }
    if(2 * sum < (2 * left - 1) * count)
        puts("left");
    else if(2 * sum > (2 * right + 1) * count)
        puts("right");
    else
        puts("balanced");
    return 0;
}
