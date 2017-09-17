#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int main(){
    int n, i, t, x, sum = 0, MIN = 0, MAX = 0;
    scanf("%d", &n);
    while(n--){
        scanf("%d %d", &t, &x);
        if(t == 0)
            sum += x;
        else
            sum -= x;
        MIN = min(MIN, sum);
        MAX = max(MAX, sum);
    }
    printf("%d", MAX-MIN);
    return 0;
}


















