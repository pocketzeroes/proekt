#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int n;
    scanf("%d", &n);
    int AxorB=0;
    int h,i;
    int is_aru=0, B_h=0, B_pa=0;
    for(h=0; h<15; h++){
        int q=0;
        for(i=0;i<n;i++)
            if((i&(1<<h))==0)
                q++;
        printf("Q %d", q); fflush(stdout);
        for(i=0;i<n;i++)
            if((i&(1<<h))==0){
                printf(" %d", i+1); fflush(stdout);
            }
        puts(""); fflush(stdout);
        int in;
        scanf("%d", &in);
        if(in!=0 && in!=q)
            continue;
        printf("Q %d", n-q); fflush(stdout);
        for(i=0;i<n;i++)
            if((i&(1<<h))!=0){
                printf(" %d", i+1); fflush(stdout);
            }
        puts("");fflush(stdout);
        scanf("%d", &in);
        if(in==n-q&&is_aru==0) 
            is_aru=1, B_h=h, B_pa=0;
        if(in==0  &&is_aru==0) 
            is_aru=1, B_h=h, B_pa=1;
        if(in!=0&&in!=n-q) 
            continue;
        AxorB += (1<<h);
    }
    int A=0;
    if(B_pa==0) 
        A += (1<<B_h);
    for(h=0; h<15; h++){
        if(h==B_h) 
            continue;
        int q=0;
        for(i=0;i<n;i++)
            if( (((i&(1<<B_h))==0)==(B_pa==0)) || ((i&(1<<h))==0) )
                q++;
        printf("Q %d", q); fflush(stdout);
        for(i=0;i<n;i++)
            if( (((i&(1<<B_h))==0)==(B_pa==0)) || ((i&(1<<h))==0) ){
                printf(" %d", i+1); fflush(stdout);
            }
        puts("");fflush(stdout);
        int in;
        scanf("%d", &in);
        if(in==0) 
            A+=(1<<h);
    }
    printf("A %d %d\n", A+1, (A^AxorB)+1); fflush(stdout);
    return 0;
}
