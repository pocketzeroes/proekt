#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)

int gcd(int y, int x){
    while(x){
        y %= x;
        swap(y, x);
    }
    return y;
}
int main() {
    int p, q, s;
    scanf("%d %d %d", &p, &q, &s);
    if(p * q / gcd(p, q) <= s)
        puts("yes");
    else
        puts("no");
    return 0;
}
