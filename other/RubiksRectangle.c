#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
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
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}
void freemat(int**m, int x){
  for(int i=0; i<x; i++)
    free(m[i]);
  free(m);
  m = NULL;
}
//////////////////////////////////////////////////

int nrows, ncols;
int**data;
vecp moves;

bool invalid(int r, int c){
    return data[r][c] != (ncols * r + c + 1);
}
void move(bool d, int i){
    moves.ptr = pushbackP(moves.ptr, &moves.sz, newPair(d, i));
    if(d)
        for(int col = 0, loc = ncols-1; col < loc; ++col, --loc)
            swap(data[i][col], data[i][loc]);
    else
        for(int row = 0, wor = nrows-1; row < wor; ++row, --wor)
            swap(data[row][i], data[wor][i]);
}
int main(){
    int ncases;
    scanf("%d", &ncases);
    while(ncases-- > 0){
        if(data)
          freemat(data, nrows);
        scanf("%d %d", &ncols, &nrows);
        data = newmat(nrows, ncols);
        moves.sz = 0;
        for(int row = 0; row < nrows; ++row)
            for(int col = 0; col < ncols; ++col)
                scanf("%d", &data[row][col]);
        if(nrows % 2 == 1)
            for(int col = 0, row = nrows/2; col < ncols; ++col)
                if(invalid(row, col))
                    move(true, row);
        if(ncols % 2 == 1)
            for(int row = 0, col = ncols/2; row < nrows; ++row)
                if(invalid(row, col))
                    move(false, col);
        for(int row = 0, wor = nrows-1; row < wor; ++row, --wor){
            for(int col = 0, loc = ncols-1; col < loc; ++col, --loc){
                if(invalid(row, col)) { move(true , wor); move(false,col); move(true , wor); move(false,col); }
                if(invalid(row, col)) { move(false, loc); move(true, row); move(false, loc); move(true, row); }
                if(invalid(row, col)) { move(false, col); move(true, row); move(false, col); move(true, row); }
                if(invalid(wor, loc)) { move(false, loc); move(true, wor); move(false, loc); move(true, wor); }
                if(invalid(wor, loc)) { move(false, loc); move(true, wor); move(false, loc); move(true, wor); }
                if(invalid(row, loc))
                    if(col){ move(true , row); move(false, col); move(true , row); }
                    else   { move(false, col); move(true , row); move(false, col); }
            }
        }
        bool possible = true;
        for(int row = 0; row < nrows; ++row)
            for(int col = 0; col < ncols; ++col)
                if(invalid(row, col))
                    possible = false;
        if(possible){
            printf("POSSIBLE %lu", moves.sz);
            for (int i = 0; i < moves.sz; ++i)
                printf(moves.ptr[i].first ? " R%d" : " C%d", moves.ptr[i].second+1);
            printf("\n");
        }
        else
            printf("IMPOSSIBLE\n");
    }
    return 0;
}
