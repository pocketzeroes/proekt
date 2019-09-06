#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int G, S, C;
    scanf("%d%d%d", &G, &S, &C);
    int v = C + 2 * S + 3 * G;
    if     (v >= 8){ printf("Province"); goto here;}
    else if(v >= 5){ printf("Duchy");    goto here;}
    else if(v >= 2){ printf("Estate");   goto here;}
if(0){
 here:
    printf(" or ");
}
    if(v >= 6)      printf("Gold");
    else if(v >= 3) printf("Silver");
    else            printf("Copper");
    puts("");
    return 0;
}
