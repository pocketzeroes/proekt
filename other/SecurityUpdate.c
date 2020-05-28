#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int*size, pair value){
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
///////////////

void test_case(){
  int n, m;
  scanf("%d %d", &n, &m);
  int X[n+1]; clr(X);
  for(int i=2; i<=n; ++i)
    scanf("%d", &X[i]);
  int order[n+1]; clr(order);
  int taken[n+1]; clr(taken);
  order[1]=1;
  for(int pos=2; pos<=n; ++pos){
    for(int a=2; a<=n; ++a){
      if(!taken[a] && X[a] < 0 && -X[a] < pos){
        order[pos] = a;
        taken[a] = pos;
        break;
      }
    }
    if(!order[pos]){
      int best = -1;
      for(int a=2; a<=n; ++a){
        if(!taken[a] && X[a] > 0 && (best == -1 || X[a] < X[best]))
          best = a;
      }
      taken[best] = pos;
      order[pos] = best;
    }
  }
  vecp edges[n+1]; clr(edges);
  for(int i=0; i<m; ++i){
    int a, b;
    scanf("%d %d", &a, &b);
    if(taken[a] < taken[b])
      pbp(edges[b], newpair(a, i));
    else
      pbp(edges[a], newpair(b, i));
  }
  int when  [n+1]; clr(when  );
  int answer[m];   clr(answer);
  for(int i=1; i<=n; ++i){
    int a = order[i];
    if(X[a] > 0)
      when[a] = X[a];
    else{
      when[a] = when[order[i-1]];
      if(taken[a] == -X[a] + 1)
        when[a]++;
      for(int j=1; j<i; ++j){
        if(X[order[j]] < 0 && -X[order[j]] < -X[a])
          when[a] = fmax(when[a], when[order[j]] + 1);
      }
    }
    bool achieved = false;
    for(int z=0;z<edges[a].sz;z++){pair edge = edges[a].ptr[z];
      int b = edge.first;
      if(when[b] < when[a])
        achieved = true;
    }
    for(int z=0;z<edges[a].sz;z++){pair edge = edges[a].ptr[z];
      int b = edge.first;
      if(!achieved && when[b] == when[a])
        when[a]++;
    }
    for(int z=0;z<edges[a].sz;z++){pair edge = edges[a].ptr[z];
      int b = edge.first;
      int id = edge.second;
      int cost = when[a] - when[b];
      answer[id] = fmax(1, cost);
    }
  }
  for(int id=0; id<m; ++id)
    printf(" %d", answer[id]);
  puts("");
}
int main(){
  int T;
  scanf("%d", &T);
  for(int nr=1; nr<=T; ++nr){
    printf("Case #%d:", nr);
    test_case();
  }
  return 0;
}

