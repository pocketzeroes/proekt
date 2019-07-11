#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXF    = 100};
enum{ ICONROW =  15};
enum{ ICONCOL =   9};
int rowVals[MAXF+1];
int colVals[MAXF+1];
int nrows, ncols;
int grid  [MAXF][MAXF];
int wspace[MAXF][MAXF];

typedef struct{
    int r, c;
}pos;
pos dfiles[MAXF];
pos sfiles[MAXF];

void insert(int val, int*list, int*n){
    int j=0;
    while (j < *n){
        if (list[j] < val)
            j++;
        else if (list[j] == val)
            return;
        else
            break;
    }
    int tmp = list[j];
    list[j] = val;
    while (j < *n){
        j++;
        int tmp2 = list[j];
        list[j] = tmp;
        tmp = tmp2;
    }
    (*n)++;
}
void insertInGrid(pos*p, int npos, int val){
    for(int k=0; k<npos; k++){
        int i=0, j=0;
        while (rowVals[i] != p[k].r)
            i++;
        while (colVals[j] != p[k].c)
            j++;
        grid[i][j] = val;
    }
}
int calcMoves(int startr, int startc, int ndel){
    for(int i=startr; i<nrows; i++)
        for(int j=startc; j<ncols; j++)
            wspace[i][j] = 0;
    wspace[startr][startc] = ndel + grid[startr][startc];
    int minMoves = wspace[startr][startc];
    for(int i=startr+1; i<nrows; i++){
        int val = wspace[i-1][startc] + grid[i][startc];
        if (val < minMoves)
            minMoves = val;
        wspace[i][startc] = val;
    }
    for(int j=startc+1; j<ncols; j++){
        int val = wspace[startr][j-1] + grid[startr][j];
        if (val < minMoves)
            minMoves = val;
        wspace[startr][j] = val;
    }
    for(int i=startr+1; i<nrows; i++){
        for(int j=startc+1; j<ncols; j++){
            int val = wspace[i-1][j] + wspace[i][j-1] - wspace[i-1][j-1] + grid[i][j];
            if (val < minMoves)
                minMoves = val;
            wspace[i][j] = val;
        }
    }
    return minMoves;
}
int main(){
    int maxr, maxc, ndel, nsav, bobs_adjustment=0;
    scanf("%d%d%d%d", &maxr, &maxc, &ndel, &nsav);
    nrows = ncols = 0;
    for(int i=0; i<ndel; i++){
        scanf("%d%d", &dfiles[i].r, &dfiles[i].c);
        if (dfiles[i].r > maxr - 8 || dfiles[i].c > maxc - 4){
          i--;
          ndel--;
          bobs_adjustment++;
          continue;
        }
        insert(dfiles[i].r, rowVals, &nrows);
        insert(dfiles[i].c, colVals, &ncols);
    }
    for(int i=0; i<nsav; i++){
        scanf("%d%d", &sfiles[i].r, &sfiles[i].c);
        insert(sfiles[i].r, rowVals, &nrows);
        insert(sfiles[i].c, colVals, &ncols);
    }
    for(int i=0; i<nrows; i++)
        for(int j=0; j<ncols; j++)
            grid[i][j] = 0;
    insertInGrid(dfiles, ndel, -1);
    insertInGrid(sfiles, nsav, 1);
    int minMoves = ndel+nsav;
    for(int i=0; i<nrows; i++){
        for(int j=0; j<ncols; j++){
            int moves = calcMoves(i, j, ndel);
            if (moves < minMoves)
                minMoves = moves;
        }
    }
    printf("%d\n", minMoves+bobs_adjustment);
    return 0;
}
