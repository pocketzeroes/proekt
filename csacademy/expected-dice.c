#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int a[6];
int b[6];
int f[200];
int mx , ans;
int main(){
    for(int i=0;i<6;i++) 
        scanf("%d", &a[i]);
    for(int i=0;i<6;i++)
        scanf("%d", &b[i]);
    for(int i=0;i<6;i++) {
        for(int j=0;j<6;j++) {
            if ( ++f[ a[i]+b[j] ] > mx ){
                mx  = f[ a[i]+b[j] ];
                ans = a[i]+b[j];
            }
            if (f[ a[i]+b[j] ] == mx){
                ans = min(ans,a[i]+b[j]);
            }
        }
    }
    printf("%d\n", ans);
}


















































