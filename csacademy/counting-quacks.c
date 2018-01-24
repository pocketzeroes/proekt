#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int max(int a,int b){return a>b?a:b;}

int sito [1000100]={0};
int zlicz[1000100]={0};
int n,t;
int maks;

int main(){
    scanf("%d %d", &n, &t);
    for(int i = 0; i<n; ++i){
        int temp;
        scanf("%d", &temp);
        zlicz[temp]++;
    }
    for(int i = 1; i<= (t); i++){
        if(zlicz[i]!=0){
            for(int j=i;j<=t;j+=i){
                sito[j]+=zlicz[i];
            }
        }
    }
    for(int i = 1; i<= (t); i++){
        maks=max(maks, sito[i]);
    }
    int policzenia=0;
    for(int i = 1; i<= (t); i++){
        if(sito[i]==maks)
            policzenia++;
    }
    if(maks==0)
        printf("0 %d\n", t);
    else
        printf("%d %d\n", maks, policzenia);
    return 0;
}
