#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

bool white(int s, int x, int y){
    return(x%s != 0 && y%s != 0 && (x/s)%2+(y/s)%2 == 1);
}
void solve(int s, int x, int y, int dx, int dy){
    for(int i=0; i<2*s; i++, x += dx, y += dy){
        if(white(s, x, y)){
            printf("After %d jumps the flea lands at (%d, %d).\n", i, x, y);
            return;
        }
    }
    puts("The flea cannot escape from black squares.");
}
int main(){
    int s, x, y, dx, dy;
    while(scanf("%d %d %d %d %d", &s, &x, &y, &dx, &dy)==5 && s != 0){
        solve(s, x, y, dx, dy);
    }
    return 0;
}
