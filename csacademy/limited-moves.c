#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

inline void ff(){
    fflush(stdout);
}
int licz;
int n;
int rusz(int v){
    printf("%d\n", v); ff();
    licz++;
    n-=v;
    if (!n)
        exit(0);
}
int czyt(){
    int x;
    scanf("%d", &x);
    n-=x;
    return x;
}
int main(){
    scanf("%d", &n);
    while(1){
        rusz(n&(-n));
        czyt();
        if (licz==500)
            exit(0);
    }
    assert(0);
    return 0;
}
