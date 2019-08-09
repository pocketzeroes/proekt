#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
int cmpC(const void * a, const void * b){ return ( *(char*)a - *(char*)b );}


int n;

bool process(char*currcol, int*col){
    qsort(col, n, sizeof(int), cmp);
    qsort(currcol, n, sizeof(char), cmpC);
    bool works = true;
    for(int i = 0; i < n; i++){
        if(currcol[i] == '(')
            col[i]++;
        else
            col[i]--;
        if(col[i] < 0)
            works = false;
    }
    return works;
}
int main(){
    scanf("%d", &n);
    char v[n][n];
    getchar();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            v[i][j]=getchar();
        }
        getchar();
    }
    int col[n]; memset(col,0,sizeof(col));
    bool works = true;
    for(int i = 0; i < n; i++) {
        char currcol[n];
        for(int j = 0; j < n; j++){
            currcol[j] = v[j][i];
        }
        if(!process(currcol, col)){
            works = false;
            break;
        }
    }
    for(int i = 0; i < n; i++){
        if(col[i] != 0){
            works = false;
            break;
        }
    }
    if(works)
        puts("Yes");
    else
        puts("No");
    return 0;
}
