#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int n1,n2;

int main(){
    int n;
    bool b=false;
    while(scanf("%d", &n) && n){
        if(b)
            puts("");
        b =true;
        n1=0;
        n2=0;
        char*s;
        int nmb;
        while(n--){
            s = getstr();
            scanf("%d", &nmb);
            if(strcmp(s,"TAKE")==0){
                if(n1>=nmb){
                    printf("TAKE 1 %d\n", nmb);
                    n1-=nmb;
                }
                else{
                    if(n1!=0)
                        printf( "TAKE 1 %d\n", n1);
                    nmb-=n1;
                    printf("MOVE 2->1 %d\n", n2);
                    n1=n2;
                    n2=0;
                    printf("TAKE 1 %d\n", nmb);
                    n1-=nmb;
                }
            }
            else{
                n2+=nmb;
                printf("DROP 2 %d\n", nmb);
            }
        }
    }
    return 0;
}
