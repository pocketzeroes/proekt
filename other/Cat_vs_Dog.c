#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
    int*ptr;
    int sz;
}vec;
vec newVec(){
    vec rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}
//////////////////////////////
enum{ MAXVOTE = 500};
enum{ MAXCAT  = 100};
char disagree[MAXVOTE][MAXVOTE];
char group   [MAXVOTE];
int  linked  [MAXVOTE];
int  N;
char used[MAXVOTE];

int augment(int x){
  if(used[x])
    return 0;
  used[x] = 1;
  if(group[x] == 0){
    for(int i=0;i<N;i++){
      if(disagree[i][x] && linked[i] != x && augment(i)){
        linked[i] = x;
        return 1;
      }
    }
  }
  else {
    if(linked[x] == -1 || augment(linked[x])) 
      return 1;
  }
  return 0;
}
int maxflow(){
  int res = 0;
  for(int i=0;i<N;i++){
    memset(used, 0, sizeof(used));
    if(group[i] == 0 && augment(i)) 
      res++;
  }
  return res;
}
int main(){
  int runs;
  scanf("%d", &runs);
  while(runs--){
    memset(disagree,0,sizeof(disagree));
    memset(linked, -1, sizeof(linked));
    int a, b;
    scanf("%d %d %d", &a, &b, &N);
    vec B1 = newVec();
    vec B2 = newVec();
    for(int i=0;i<N;i++) {
      char s1[10], s2[10];
      scanf("%s %s", s1, s2);
      B1.ptr=pushback(B1.ptr, &B1.sz, (s1[0] == 'C' ? MAXCAT+10 : 0) + atoi(s1+1));
      B2.ptr=pushback(B2.ptr, &B2.sz, (s2[0] == 'C' ? MAXCAT+10 : 0) + atoi(s2+1));
      group[i] = B1.ptr[i] < MAXCAT+10;
      for(int j=0;j<i;j++){
        if(B1.ptr[i] == B2.ptr[j] || B2.ptr[i] == B1.ptr[j])
          disagree[i][j] = disagree[j][i] = 1;
      }
    }
    printf("%d\n", N - maxflow());
  }
  return 0;
}
