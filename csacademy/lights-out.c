#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
pair*pushbackP(pair*array, int *size, pair value){
    pair*output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}



int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n][m];
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            scanf("%d", &a[i][j]);
        }
    }
    pair*ans=NULL;int ansSz=0;
    ans=pushbackP(ans,&ansSz,newPair(-1, -1));
    int*odd_col=NULL;int odd_colSz=0;
    int*odd_row=NULL;int odd_rowSz=0;
    for (int j = 0; j < m; ++j){
        if (a[0][j]){
            odd_col=pushback(odd_col, &odd_colSz, j);
        }
    }
    int b[n][m];
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            b[i][j]=a[i][j];
        }
    }
    for(int z=0;z<odd_colSz;z++){
        int j = odd_col[z];
        for (int i = 0; i < n; ++i){
            b[i][j] ^= 1;
        }
    }
    for (int i = 1; i < n; ++i){
        bool ok = false;
        for (int j = 0; j < m; ++j){
            if (b[i][j]) {
                ok = true;
                break;
            }
        }
        if (ok){
            odd_row=pushback(odd_row, &odd_rowSz, i);
            for (int j = 0; j < m; ++j){
                b[i][j] ^= 1;
            }
        }
    }
    bool off = true;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            if (b[i][j]) {
                off = false;
                break;
            }
        }
        if (!off){
            break;
        }
    }
    if (off && (odd_colSz % 2) == (odd_rowSz % 2)){
        pair*relax=NULL;int relaxSz=0;
        while(odd_colSz < odd_rowSz){
            odd_col=pushback(odd_col, &odd_colSz, 0);
        }
        while(odd_rowSz < odd_colSz){
            odd_row=pushback(odd_row, &odd_rowSz, 0);
        }
        for(int i = 0; i < odd_colSz; ++i){
            relax=pushbackP(relax,&relaxSz,newPair(odd_row[i], odd_col[i]));
        }
        if(ansSz > relaxSz || (ansSz == 1 && ans[0].first == -1 && ans[0].second == -1)){
            ans = relax;
            ansSz = relaxSz;
        }
    }
    free(odd_col);odd_col=NULL;odd_colSz=0;
    free(odd_row);odd_row=NULL;odd_rowSz=0;
    odd_row=pushback(odd_row,&odd_rowSz,0);
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            b[i][j]=a[i][j];
        }
    }
    for (int j = 0; j < m; ++j) {
        b[0][j] ^= 1;
    }
    for (int j = 0; j < m; ++j) {
        if (b[0][j]) {
            odd_col=pushback(odd_col,&odd_colSz,j);
        }
    }
    for(int z=0;z<odd_colSz;z++){
        int j = odd_col[z];
        for (int i = 0; i < n; ++i) {
            b[i][j] ^= 1;
        }
    }
    for (int i = 1; i < n; ++i) {
        bool ok = false;
        for (int j = 0; j < m; ++j) {
            if (b[i][j]) {
                ok = true;
                break;
            }
        }
        if (ok) {
            odd_row=pushback(odd_row,&odd_rowSz,i);
            for (int j = 0; j < m; ++j) {
                b[i][j] ^= 1;
            }
        }
    }
    off = true;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (b[i][j]) {
                off = false;
                break;
            }
        }
        if (!off) {
            break;
        }
    }
    if (off && (odd_colSz % 2) == (odd_rowSz % 2)){
        pair*relax=NULL;int relaxSz=0;
        while(odd_colSz < odd_rowSz){
            odd_col=pushback(odd_col,&odd_colSz,0);
        }
        while(odd_rowSz < odd_colSz){
            odd_row=pushback(odd_row,&odd_rowSz,0);
        }
        for (int i = 0; i < odd_colSz; ++i){
            relax=pushbackP(relax, &relaxSz, newPair(odd_row[i], odd_col[i]));
        }
        if(ansSz > relaxSz || (ansSz == 1 && ans[0].first == -1 && ans[0].second == -1)){
            ans = relax;
            ansSz = relaxSz;
        }
    }
    if (ansSz == 1 && ans[0].first == -1 && ans[0].second == -1){
        puts("-1");
        return 0;
    }
    printf("%d\n", ansSz);
    for (int i = 0; i < ansSz; ++i){
        printf("%d %d\n", ans[i].first+1, ans[i].second+1);
    }
}






































