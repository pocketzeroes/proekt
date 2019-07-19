#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

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
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
void filll(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
///////////////////////////////////
char rules[100];
char candy[100];
int alphabet_size;
enum{ A = 64};
enum{ M = 10000000};

typedef struct{
  int**trans;
  bool*is_final;
  int nb_states;
}Auto;

Auto newAuto(int n){
  Auto rez;
  rez.nb_states = n;
  rez.is_final = calloc(n, sizeof(bool));
  rez.trans    = newmat(n, A);
  return rez;
}
void destroy(Auto*a){
  freemat(a->trans, a->nb_states);
  free(a->is_final);
}
Auto create_from(int beg, int end){
  Auto res = newAuto(end-beg-1);
  int decal = 0 ;
  int fail = 0 ;
  for(int i = beg ; i < end-1 ; i++){
     int cur = i-beg ;
    if(rules[i]=='>'){
      decal = 1;
      fail = cur ;
    }
    res.is_final[cur] = (decal==0) ;
    for( int c = 0 ; c < alphabet_size ; c++){
      if( candy[c]==rules[i+decal] )
        res.trans[cur][c] = (cur+1)%res.nb_states ;
      else{
        res.trans[cur][c] = fail;
        res.trans[cur][c] = res.trans[fail][c];
      }
    }
  }
  return res ;
}
Auto product(Auto a, Auto b){
  int * remap = calloc(a.nb_states*b.nb_states, sizeof(int));
  int * map   = calloc(a.nb_states*b.nb_states, sizeof(int));
  fill(remap, a.nb_states * b.nb_states,-1);
  fill(map, a.nb_states * b.nb_states,-1);
  remap[0] = 0;
  map[0] = 0 ;
  int nb_map = 1;
  for(int s  = 0 ; s < nb_map ; s++ ){
     int s_a = map[s] / b.nb_states ;
     int s_b = map[s] % b.nb_states ;
    for(int c = 0 ; c < alphabet_size ; c++ ){
       int ns = a.trans[s_a][c]*b.nb_states + b.trans[s_b][c] ;
      if(remap[ns] < 0){
        map[nb_map] = ns ;
        remap[ns] = nb_map++ ;
      }
    }
  }
  Auto res = newAuto(nb_map);
  for(int s  = 0 ; s < nb_map ; s++ ){
    int s_a = map[s] / b.nb_states;
    int s_b = map[s] % b.nb_states;
    for(int c = 0 ; c < alphabet_size ; c++)
      res.trans[s][c] = remap[a.trans[s_a][c]*b.nb_states + b.trans[s_b][c]];
    res.is_final[s] = a.is_final[s_a] && b.is_final[s_b];
  }
  free(map);
  free(remap);
  destroy(&a);
  destroy(&b);
  return res ;
}
Auto compute_automaton(int beg, int end){
  for(int i = beg ; i < end ; i++)
    if(rules[i] == '|')
      return product(create_from(beg,i), compute_automaton(i+1,end));
  return create_from(beg,end);
}
int count(Auto a, int size){
  ll*valid[2];
  valid[0] = calloc(a.nb_states, sizeof(ll));
  valid[1] = calloc(a.nb_states, sizeof(ll));
  filll(valid[0], a.nb_states, 0);
  valid[0][0] = 1 ;
  for(int step = 0 ; step < size ; step++){
    int cur = step%2;
    int nxt = (step+1)%2;
    for(int s = 0 ; s < a.nb_states ; s++){
      valid[cur][s] %= M ;
      valid[nxt][s] = 0 ;
    }
    for(int s = 0 ; s < a.nb_states ; s++)
      for(int c = 0 ; c < alphabet_size ; c++)
        valid[nxt][a.trans[s][c]] += valid[cur][s] ;
  }
  int res = 0 ;
  for(int i = 0 ; i < a.nb_states ; i++ )
    if(a.is_final[i])
      res = (res+valid[size%2][i]) % M ;
  free(valid[0]);
  free(valid[1]);
  return res;
}
int main(){
  int size;
  scanf("%d %s\n%s\n", &size, candy, rules);
  alphabet_size = strlen(candy);
  Auto res = compute_automaton(0, strlen(rules));
  printf("%d\n", count(res, size));
  destroy(&res);
  return 0;
}
