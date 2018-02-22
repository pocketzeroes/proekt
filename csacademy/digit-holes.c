#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    int mx = 0, res=0;
    for(int i=a; i<=b; i++){
        int p = i;
        int c = 0;
        if(!p){
            if(mx<1)
                mx=1,res=i;
        }
        while(p){
            int r = p%10;
            if     (r==0)c++;
            else if(r==6)c++;
            else if(r==9)c++;
            else if(r==8)c+=2;
            p /= 10;
        }
        if(c>mx)
            mx=c, res=i;
    }
    if(!mx)
        res=a;
    printf("%d\n", res);
    return 0;
}


