#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#include<stdbool.h>
#include<stdint.h>

int n, a[100 +5][100 +5], b[100 +5][100 +5];
bool suc;

inline 
int rit(){
    int f=0,key=1;
    char ch;
    do{
        ch = getchar();
        if(ch=='-') key=-1;
    }
    while(ch<'0'||ch>'9');
    do{
        f = f*10+ch-'0';
        ch = getchar();
    }
    while(ch>='0'&&ch<='9');
    return f*key;
}
int32_t main(void){
    n = rit();
    for(int i=0;i<(n);i++) 
        for(int j=0;j<(n);j++){
            a[i][j] = rit();
        }
    for(int i=0;i<(n);i++) 
        for(int j=0;j<(n);j++){
            b[i][j] = rit();
        }
    suc = true;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            if(a[i][j]!=b[i][n-j-1])
                suc = false;
        }
    }
    if(suc)
        return puts("1")*0;
    suc = true;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            if(a[i][j]!=b[n-i-1][j])
                suc = false;
        }
    }
    puts(suc ? "1" : "0");
}
