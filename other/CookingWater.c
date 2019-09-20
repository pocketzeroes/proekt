#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int N;
    scanf("%d", &N);
    int mi = INT_MIN;
    int ma = INT_MAX;
    for (int i = 0; i < (N); ++i){
        int a, b;
        scanf("%d %d", &a, &b);
        mi = fmax(mi, a);
        ma = fmin(ma, b);
    }
    if(mi <= ma)
        puts("gunilla has a point");
    else
        puts("edward is right");
    return 0;
}
