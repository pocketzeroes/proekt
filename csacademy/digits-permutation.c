#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char str[15];
int  c1 [10];
int  n1, n2;
int  candi = 0;

bool dfs(int x, bool same){
    if(x == n1){
        printf("%d\n", candi);
        return true;
    }
    if(same && c1[str[x]-'0']){
        c1[str[x]-'0']--;
        candi = candi * 10 + (str[x]-'0');
        if(dfs(x+1, true))
            return true;
        candi /= 10;
        c1[str[x]-'0']++;
    }
    int until = (str[x]-'0')-1;
    if(!same)
        until = 9;
    for(int i=until;i>=(!x);i--){
        if(c1[i]){
            c1[i]--;
            candi= candi * 10 + i;
            if(dfs(x+1, false))
                return true;
            candi /= 10;
            c1[i]++;
        }
    }
    return false;
}
int main(){
    scanf("%s", str);
    n1 = (int)strlen(str);
    for(int i=0;i<n1;i++)
        c1[str[i]-'0']++;
    scanf("%s", str);
    n2 = (int)strlen(str);
    if(n1 < n2){
        for(int i=9;i>=0;i--){
            for(int j=0;j<c1[i];j++)
                printf("%d", i);
        }
        printf("\n");
        return 0;
    }
    if(n1 > n2){
        printf("-1\n");
        return 0;
    }
    if(!dfs(0, true)){
        printf("-1\n");
        return 0;
    }
}

