#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

#define pbs(zpv, zvv) zpv.ptr = pushbackS(zpv.ptr, &zpv.sz, zvv)
#define pb(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
char**pushbackS(char**array, int *size, char*value) {
  char**output = resizeArray(array, char*, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  char**ptr;
  int sz;
}vecs;
vecs newVecS(){
  vecs rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

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

/////////////////////
int main(){
    int h, w, n=0;
    while(scanf("%d %d", &h, &w)==2){
        n++;
        vecs grid=newVecS();
        for(int i=0; i<h; ++i){
            char*row=getstr();
            grid.ptr = pushbackS(grid.ptr, &grid.sz, row);
        }
        int cnt=0;
        for(int r=0; r<h; ++r){
            for(int c=0; c<w; ++c){
                if(grid.ptr[r][c] == '-'){
                    cnt++;
                    pair tmp =(pair){r, c};
                    grid.ptr[r][c] = '.';
                    vecp vs=newVecP();
                    pb(vs, tmp);
                    while(vs.sz > 0){
                        tmp = vs.ptr[vs.sz-1];
                        vs.sz--;
                        int r2=tmp.first,
                            c2=tmp.second;
                        int dx[4] = {0, 1, 0, -1};
                        int dy[4] = {-1, 0, 1, 0};
                        for(int z = 0; z < 4; ++z){
                            int i=dy[z], 
                                j=dx[z];
                            if (i+r2 >= 0 && i+r2 < h &&
                                j+c2 >= 0 && j+c2 < w &&
                                grid.ptr[i+r2][j+c2]== '-'){
                                grid.ptr[i+r2][j+c2] = '.';
                                tmp =(pair){i+r2, j+c2};
                                pb(vs, tmp);
                            }
                        }
                    }
                }
            }
        }
        printf("Case %d: %d\n", n, cnt);
    }
    return 0;
}
