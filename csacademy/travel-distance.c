#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

char buff[100000];
int main(){
    scanf("%s", &buff);
    int x=0, y=0;
    for (int i=0; buff[i]; i++){
        if(buff[i]=='N') x++;
        if(buff[i]=='S') x--;
        if(buff[i]=='E') y++;
        if(buff[i]=='W') y--;
    }
    int res = abs(x) + abs(y);
    printf("%d\n", res);
    return 0;
}
