#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int i,j,a,b,ts,f=1,cn=0,n,p,t,st,cp;
    scanf("%d %d %d", &n, &p, &t);
    st=(t/9)*3;
    t%=9;
    if(t==5)
        st++;
    else if(t>=7)
        st+=t-6;
    cp=p-st;
    if(cp<1||cp>n){
        puts("-1");
        return 0;
    }
    printf("%d\n", cp);
    return 0;
}
