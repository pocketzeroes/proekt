#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
enum{ MAXV = 100 * 100};

char*string(int sz, char ch){
  char space[sz+1]; memset(space, ch , sizeof(space)); space[sz]='\0';
  return strdup(space);
}
char*minstr(char*a, char*b){return strcmp(a, b)<0?a:b;}

int main(){
    int n;
    scanf("%d", &n);
    int a[n];
    int b[n];
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    for (int i = 0; i < n; ++i)
        scanf("%d", &b[i]);
    int dp[n+1][2*MAXV]; clr(dp);
    dp[n][MAXV]=true;
    for(int i = n; i; --i){
        for(int j = -MAXV; j < MAXV; ++j){
            if(!dp[i][j + MAXV])
                continue;
            dp[i - 1][j + MAXV + a[i - 1]] = 1;
            dp[i - 1][j + MAXV - b[i - 1]] = 1;
        }
    }
    int goal = MAXV;
    for(int j = -MAXV; j < MAXV; ++j)
        if(dp[0][j + MAXV])
            goal = fmin(goal, abs(j));
    char*walk(int g){
        char*res = string(n, 'A');
        if(dp[0][g + MAXV] == 0){
            res[0] = 'C';
            return res;
        }
        for(int i=0; i<n; ++i){
            if(dp[i + 1][g + MAXV - a[i]])
                g -= a[i];
            else{
                res[i] = 'B';
                g += b[i];
            }
        }
        return res;
    };
    char*s = minstr(walk(-goal), walk(goal));
    puts(s);
    return 0;
}
