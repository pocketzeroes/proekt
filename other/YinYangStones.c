#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int c, imb = 0 ;
    while((c = getchar()) != EOF)
        if(c == 'B')
            imb++ ;
        else if(c == 'W')
            imb-- ;
    printf("%d\n", (imb == 0) );
    return 0;
}
