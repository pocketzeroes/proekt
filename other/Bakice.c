#include<stdio.h> // bakice
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

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
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


#define SQR(x) ((x)*(x))

vecs tlocrt;
vecp bakice;
vecp sjedala;

int dist(int b, int s){
    return SQR(bakice.ptr[b].first  - sjedala.ptr[s].first) +
           SQR(bakice.ptr[b].second - sjedala.ptr[s].second);
}
int main(){
    int r, s;
    scanf("%d %d", &r, &s);
    for(int i = 0; i < r; i++){
        char*a=getstr();
        tlocrt.ptr = pushbackS(tlocrt.ptr, &tlocrt.sz, a);
    }
    for (int i = 0; i < r; i++){
        for (int j = 0; j < s; j++){
            if(tlocrt.ptr[i][j] == 'X')
                bakice.ptr = pushbackP(bakice.ptr, &bakice.sz, newPair(i, j));
            else if(tlocrt.ptr[i][j] == 'L')
                sjedala.ptr = pushbackP(sjedala.ptr, &sjedala.sz, newPair(i, j));
        }
    }
    int  boom = 0;
    char done = 0;
    while(!done){
        int najnajblizi = -1;
        int najblizi[bakice.sz]; fill(najblizi, bakice.sz, -1);
        done = 1;
        for(int b=0; b<bakice.sz; b++){
            if(tlocrt.ptr[bakice.ptr[b].first][bakice.ptr[b].second] == 'X'){
                int best = -1;
                for(int s = 0; s < sjedala.sz; s++){
                    if(tlocrt.ptr[sjedala.ptr[s].first][sjedala.ptr[s].second] == 'L'){
                        if(best == -1 || dist(b, s) < dist(b, best))
                           best = s;
                    }
                }
                if(best == -1)
                    break;
                done = 0;
                najblizi[b] = best;
                if ( najnajblizi == -1 || dist(b, best) < dist(najnajblizi, najblizi[najnajblizi]) )
                    najnajblizi = b;
            }
        }
        if ( done ) 
            break;
        vec explodes = newVec();
        for (int b = 0; b < bakice.sz; b++)
            if(tlocrt.ptr[bakice.ptr[b].first][bakice.ptr[b].second] == 'X')
                if ( najblizi[b] == najblizi[najnajblizi] && dist(b, najblizi[najnajblizi]) == dist(najnajblizi, najblizi[najnajblizi]) )
                    explodes.ptr = pushback(explodes.ptr, &explodes.sz, b);
        if(explodes.sz > 1)
            boom++;
        for(int i=0; i<explodes.sz; i++)
            tlocrt.ptr[bakice.ptr[explodes.ptr[i]].first][bakice.ptr[explodes.ptr[i]].second] = '.';
        tlocrt.ptr[sjedala.ptr[najblizi[najnajblizi]].first][sjedala.ptr[najblizi[najnajblizi]].second] = '.';
    }
    printf("%d\n", boom);
    return 0;
}
