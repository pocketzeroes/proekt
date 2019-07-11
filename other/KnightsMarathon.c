#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

int main(){
    int nx, ny, kx, ky, cx, cy;
    scanf("%d%d%d%d%d%d", &nx, &ny, &kx, &ky, &cx, &cy);
    int x = abs(cx - kx),
        y = abs(cy - ky);
    if(x < y){
        swap(x ,  y);
        swap(nx, ny);
        swap(cx, cy);
        swap(kx, ky);
    }
    if(x == 1 && y == 0)
        return puts("3")*0;
    if(x == 2 && y == 2)
        return puts("4")*0;
    if(x == 1 && y == 1 && (((cx == 0 || cx == nx - 1) && (cy == 0 || cy == ny - 1)) || ((kx == 0 || kx == nx - 1) && (ky == 0 || ky == ny - 1))))
        return puts("4")*0;
    int steps = max((x + y + 2) / 3, (x + 1) / 2);
    return printf("%d\n", steps + ((x + y + steps) & 1))*0;
}
