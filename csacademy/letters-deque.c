#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

char v[100000];int vSz;
char g[100000];int gSz;

int main(){
    int n; 
    scanf("%d", &n);
    while(n--){
        int q;
        scanf("%d", &q);
        getchar();
        char x;
        x = getchar();
        if(q == 0) 
            v[vSz++] = x;
        else
            g[gSz++] = x;
    }
    for(int i = vSz - 1;i >= 0;i--) 
        putchar( v[i]);
    for(int i = 0;i < gSz;i++) 
        putchar( g[i]);
}
