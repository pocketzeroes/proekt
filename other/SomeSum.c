#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int n, b, s;
    scanf("%d", &n);
    bool even = false;
    bool odd  = false;
    for(int a = 1; a <= 101 - n; ++a){
        b = a + n - 1;
        s = (a + b) * n / 2;
        if (s % 2 == 0)
            even = true;
        else
            odd = true;
        if (even && odd)
            break;
    }
    if (even && odd) puts("Either");
    else if (even)   puts("Even"  );
    else             puts("Odd"   );
    return 0;
}
