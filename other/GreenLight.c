#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

///////////////////

int main() {
  int ts[3];
  for(int i=0; i<3; i++)
    scanf("%d", &ts[i]);
  int T = ts[0] + ts[1] + ts[2];
  int n;
  scanf("%d", &n);
  pair o[3]={{-1, -1},
             {-1, -1},
             {-1, -1}};
  vecp d = newVecP();
  while(n--){
    int t;
    scanf("%d", &t);
    char*c = getstr();
    t %= T;
    int id = 0;
    if(c[0] == 'g')      id = 0;
    else if(c[0] == 'y') id = 1;
    else if(c[0] == 'r') id = 2;
    d.ptr = pushbackP(d.ptr, &d.sz, newPair(t  , id));
    d.ptr = pushbackP(d.ptr, &d.sz, newPair(t+T, id));
  }
  qsort(d.ptr, d.sz, sizeof(pair), cmpP);
  int last_colour = d.ptr[d.sz-1].second;
  for(int i = 0; i < d.sz; ++i){
    int c = d.ptr[i].second;
    if (c != last_colour){
      if (o[c].first != -1)
        break;
      o[c].first = d.ptr[i].first;
    }
    o[c].second = d.ptr[i].first;
    last_colour = c;
  }
  for(int i = 0; i <= 1; ++i){
    if(o[i].first > o[i + 1].first)
      o[i + 1].first += T, o[i + 1].second += T;
  }
  int t_min = max(o[0].second - ts[0], max(o[1].second - ts[0] - ts[1], o[2].second - T));
  int t_max = min(o[0].first, min(o[1].first - ts[0], o[2].first - ts[0] - ts[1]));
  int tq;
  scanf("%d", &tq);
  char*sq = getstr();
  tq %= T;
  int i_min, i_max;
  if(sq[0]=='g'){
    i_min = tq - ts[0];
    i_max = tq;
  }
  else if(sq[0]== 'y'){
    i_min = tq - ts[0] - ts[1];
    i_max = tq - ts[0];
  }
  else if(sq[0]== 'r'){
    i_min = tq - ts[0] - ts[1] - ts[2];
    i_max = tq - ts[0] - ts[1];
  }
  while(i_max > t_min)
    i_min -= T, i_max -= T;
  while(i_max <= t_min)
    i_min += T, i_max += T;
  int len = max(min(t_max, i_max) - max(t_min, i_min), 0);
  printf("%.15lf\n", (double)len /(double)(t_max - t_min) );
  return 0;
}
