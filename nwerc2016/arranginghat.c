#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define MAXN       45
#define MAXMOVES (MAXN*2)
#define MAXM      405

int M;

char findSmallestGood (char *prev, char *cur, char *ans, int mv){
    int MV = mv;
    memcpy(ans, cur, M * sizeof(char));
    ans[M] = 0;
    int pos = 0;
    while ((pos < M) && (MV)){
        if (ans[pos] != prev[pos]){
            ans[pos] = prev[pos];
            MV--;
        }
        pos++;
    }
    if (strncmp(prev, ans, M) <= 0) return 1;
    pos--;
    while ((pos >= 0) && (ans[pos] == '9'))
        pos--;
    if (pos < 0)
        return 0;
    memcpy(ans, cur, M * sizeof(char));
    ans[M] = 0;
    MV = mv;
    for (int i = 0; i < pos; i++){
        if (ans[i] != prev[i]){
            ans[i] = prev[i];
            MV--;
        }
    }
    if (ans[pos] != prev[pos] + 1){
        ans[pos] = (char)((int)prev[pos] + 1);
        MV--;
    }
    pos++;
    while ((pos < M) && (MV)){
        if (ans[pos] != '0'){
            ans[pos] = '0';
            MV--;
        }
        pos++;
    }
    return 1;
}
int main (){
    int N;
    scanf("%d %d\n",&N,&M);
    static char a  [MAXN][MAXMOVES];
    static int  w  [MAXN][MAXMOVES];
    static char num[MAXN][MAXMOVES][MAXM];
    char     newNum[MAXM];
    int i, j, k;
    memset(a,0,sizeof(a));
    a[0][0] = 1;
    w[0][0] = 0;
    static char data[MAXN][MAXM];
    for (i = 0; i < N; i++) 
        scanf("%s",data[i]);
    for (j = 0; j < M; j++)
        num[0][0][j] = '0';
    num[0][0][M] = 0;
    for (i = 0; i < N; i++){
        for (j = 0; j < MAXMOVES; j++){
            if (a[i][j]){
                for (k = 0; (k <= M) && (j+k < MAXMOVES); k++){
                    if (findSmallestGood(num[i][j], data[i], newNum, k)){
                        if ((a[i+1][j+k] == 0) || (strncmp(newNum, num[i+1][j+k], M) < 0)){
                            a[i+1][j+k] = 1;
                            w[i+1][j+k] = k;
                            memcpy(num[i+1][j+k], newNum, M * sizeof(char));
                            num[i+1][j+k][M] = 0;
                        }
                    }
                }
            }
        }
    }
    i = N;
    j = 0;
    while (a[i][j] == 0) 
        j++;
    static int res[MAXN];
    while (i){
        res[i-1] = j;
        j -= w[i][j];
        i--;
    }
    for (i = 0; i < N; i++){
        if(i)
            printf(" ");
        printf("%s",num[i+1][res[i]]);
    }
    printf("\n");
    return 0;
}


















































