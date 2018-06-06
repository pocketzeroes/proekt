#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}
typedef struct{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

enum{ MAX = 110};
#define x first
#define y second

int q, ans, pm;
pair a[MAX];

int main(){
    scanf("%d %d", &q, &ans);
    for(int i=1; i<=q; i++)
        scanf("%d %d", &a[i].x, &a[i].y);
    for(int i=1; i<=12; i++){
        pm=0;
        for(int j=1; j<=q; j++)
            if(a[j].x<=ans)
                pm = max(pm, a[j].y-a[j].x);
        ans+=pm;
    }
    printf("%d", ans);
    return 0;
}
