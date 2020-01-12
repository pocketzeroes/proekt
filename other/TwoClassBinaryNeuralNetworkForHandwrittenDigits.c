#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int seed=123123;

bool r(){
    seed*=123;
    return (seed%16)>7;
}
int main(){
    for(int i=0; i<30; i++){
        for(int j=0; j<51; j++){
            puts(r()?"-1 ":"1 ");
        }
        puts("");
    }
    return 0;
}
