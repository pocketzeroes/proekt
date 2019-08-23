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

vecs city;

int get(char*s){
  for(int i=0; i<city.sz; i++)
    if(strcmp(city.ptr[i], s)==0)
      return i;
  city.ptr = pushbackS(city.ptr, &city.sz, s);
  return city.sz-1;
}
int d[51][51];
int nr[51][51], rd[51][51], R;
int*Rx;
int*Ry;
int*Rd;

double nroute[51][51];
double doit(int x, int y){
#define ret nroute[x][y]
  if (ret != 0)
    return ret;
  if (x == y)
    return ret = 1;
  for (int i = 0; i < R; i++){
    if (x == Rx[i] && rd[Rx[i]][Ry[i]] == Rd[i]) {
      if (Rd[i] + d[Ry[i]][y] == d[x][y])
        ret += doit(Ry[i], y);
    }
  }
  return ret;
  #undef ret
}
int main(){
  int N, prob = 1;
  char*s;
  for(scanf("%d", &N); N--;){
    scanf("%d", &R);
    s=getstr();
    city.sz=0;
    get(s);
    memset(d , 60, sizeof(d) );
    memset(rd, 60, sizeof(rd));
    memset(nr,  0, sizeof(R) );
    Rx = calloc(R, sizeof(int)); 
    Ry = calloc(R, sizeof(int)); 
    Rd = calloc(R, sizeof(int));
    for (int i = 0; i < R; i++) {
      int x, y, ln;
      s=getstr(); x = get(s);
      s=getstr(); y = get(s);
      scanf("%d", &ln);
      Rx[i] = x;
      Ry[i] = y; 
      Rd[i] = ln;
      if(ln < rd[x][y]){
        d[x][y] = rd[x][y] = ln;
        nr[x][y] = 1;
      }
      else if(ln == rd[x][y])
        nr[x][y]++;
    }
    for (int i = 0; i < city.sz; i++)
      d[i][i] = 0;
    for (int k = 0; k < city.sz; k++)
      for (int i = 0; i < city.sz; i++)
        for (int j = 0; j < city.sz; j++)
          d[i][j] = fmin(d[i][j], d[i][k]+d[k][j]);
    memset(nroute, 0, sizeof(nroute));
    int nreachable = 0;
    double Rp[R];memset(Rp, 0, sizeof(Rp));
    for (int dest = 0; dest < city.sz; dest++)
      if (dest != 0 && d[0][dest] < 100000000){
        nreachable++;
        for(int i = 0; i < R; i++){
          if(rd[Rx[i]][Ry[i]] == Rd[i]) {
            if(d[0][Rx[i]] + Rd[i] + d[Ry[i]][dest] == d[0][dest])
              Rp[i] += doit(0, Rx[i]) * doit(Ry[i], dest) / doit(0, dest);
          }
        }
      }
    printf("Case #%d:", prob++);
    for (int i = 0; i < R; i++) 
      printf(" %.7lf", Rp[i] / nreachable);
    printf("\n");
  }
  return 0;
}
