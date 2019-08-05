#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ maxn = 4050};
int n, numl[maxn*15];
int la [maxn], lb[maxn];
int sta[maxn], L[maxn], R[maxn];
char s [maxn];

void init(){
    numl[0] = 0;
    for(int i = 1;i < maxn*15;i++)
        numl[i] = numl[i/10] + 1;
}
int main(){
    init();
    scanf("%s", s);
    n = strlen(s);
    for(int i = 0;i < n;i++)
        la[i] = lb[i] = 1;
    while(1){
        int top = 0, cur = 0;
        for(int i = 0;i < n;i++){
            if(s[i] == '('){
                cur += la[i] + lb[i] + 2;
                L[i] = cur;
                sta[top++] = i;
            }
            else 
                R[sta[--top]] = cur;
        }
        bool flag = 1;
        for(int i = 0;i < n;i++){
            if(s[i] == '('){
                if(numl[L[i]] != la[i] || lb[i] != numl[R[i]]){
                    flag = 0;
                    break;
                }
            }
        }
        if(flag) 
            break;
        for(int i = 0;i < n;i++){
            if(s[i] == '(')
                la[i] = numl[L[i]], lb[i] = numl[R[i]];
        }
    }
    for(int i = 0;i < n;i++){
        if(s[i] == '(')
            printf("%d,%d:", L[i], R[i]);
    }
    printf("\n");
    return 0;
}
