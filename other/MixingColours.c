#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<float.h>


long long chash(char*s){
  const int p = 31;
  const int m = 1e9 + 9;
  long long hash_value = 0;
  long long p_pow = 1;
  for(int z=0;s[z];z++){char c = s[z];
    hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
    p_pow = (p_pow * p) % m;
  }
  return hash_value;
}
typedef struct{
  int c1, c2, c3;
}rule;

typedef struct cell{
  int    N;
  double*hyp;
}cell;

cell*newcell(int n){
  cell*rv=calloc(1, sizeof(cell));
  rv->N   = n;
  rv->hyp = calloc(n, sizeof(double));
  for(int i=0; i<n; i++)
    rv->hyp[i] = -DBL_MAX;
  return rv;
}
void dcell(cell c){
  free(c.hyp);
}

int solve_game(rule*R, int NR, cell**S, int NS, int NC){
  cell***table = calloc(NS, sizeof(cell**));
  table[0] = S;
  for(int i=1; i<NS; i++) {
    table[i] = calloc(NS-i, sizeof(cell*));
    for(int j=0; j<NS-i; j++)
      table[i][j] = NULL;
  }
  for(int i=1; i<NS; i++)
    for(int j = 0; j<NS-i; j++)
      for(int k = 0; k<i; k++){
        cell *cell1 = table[k][j];
        cell *cell2 = table[i-k-1][j+k+1];
        if( cell1 && cell2 ){
          for(int r=0; r<NR; r++)
            if( cell1->hyp[R[r].c1] > -DBL_MAX && cell2->hyp[R[r].c2] > -DBL_MAX ) {
              cell *aux = table[i][j];
              double  pr = cell1->hyp[R[r].c1] + cell2->hyp[R[r].c2];
              if( !aux ) {
                table[i][j] = newcell(NC);
                table[i][j]->hyp[R[r].c3]=pr;
              }
              else {
                if( table[i][j]->hyp[R[r].c3] < pr )
                  table[i][j]->hyp[R[r].c3]=pr;
              }
            }
        }
      }
  int MLC=-1;
  if( table[NS-1][0] ) {
    double MLCpr = -DBL_MAX;
    for(int i=0; i<NC; i++) {
      if( table[NS-1][0]->hyp[i] > MLCpr ) {
        MLCpr = table[NS-1][0]->hyp[i];
        MLC = i;
      }
    }
  }
  for(int i=1; i<NS; i++) {
    for(int j=0; j<NS-i; j++)
      if( table[i][j] )
        free(table[i][j]);
    free(table[i]);
  }
  free(table);
  return MLC;
}
typedef struct{
  int key;
  int val;
}hm;
hm  arr[1000];
int arrsz;
void put(int k, int v){
  arr[arrsz++]=(hm){k,v};
}
int get(int k){
  for(int i=0;i<arrsz;i++)
    if(arr[i].key == k)
      return arr[i].val;
  return -1;
}


int main(){
  int NRules,
      NColours;
  char tok1[64], 
       tok2[64],
       tok3[64];
  scanf("%d", &NRules);
  if(NRules<=0){
    fprintf(stderr, "Error reading number of rules!\n");
    return -1;
  }

  rule*RULES = calloc(NRules*2, sizeof(rule));
  const char*key2col[512];
  int col2keysz=0;
  for(int nr=0; nr<NRules; nr++){
    scanf("%s %s %s", tok1, tok2, tok3);
    int htok1=chash(tok1);
    int htok2=chash(tok2);
    int htok3=chash(tok3);
    if(get(htok1) == -1){put(htok1, col2keysz); key2col[NColours++]=strdup(tok1);col2keysz++;}
    if(get(htok2) == -1){put(htok2, col2keysz); key2col[NColours++]=strdup(tok2);col2keysz++;}
    if(get(htok3) == -1){put(htok3, col2keysz); key2col[NColours++]=strdup(tok3);col2keysz++;}
    RULES[2*nr].c1   = get(htok1);
    RULES[2*nr].c2   = get(htok2);
    RULES[2*nr].c3   = get(htok3);
    RULES[2*nr+1].c1 = get(htok2);
    RULES[2*nr+1].c2 = get(htok1);
    RULES[2*nr+1].c3 = get(htok3);
  }
  NRules *= 2;
  int NCases, SeqLen;
  scanf("%d", &NCases);
  if(NCases<=0){
    fprintf(stderr, "Error reading number of cases!\n");
    return -1;
  }
  for(int nc=0; nc<NCases; nc++){
    scanf("%d", &SeqLen);
    if( SeqLen <=0 ) {
      fprintf(stderr, "Error reading sequence length (test case %d)!\n", nc);
      return -1;
    }
    cell**SEQ = calloc(SeqLen, sizeof(cell*));
    for(int elem=0; elem<SeqLen; elem++){
      double pr;
      SEQ[elem] = newcell(NColours);
      scanf("%s", tok1);
      while( strcmp(tok1, "END")){
        scanf("%lf", &pr);
        SEQ[elem]->hyp[get(chash(tok1))] = log(pr);
        scanf("%s", tok1);
      }
    }
    int solution = solve_game(RULES, NRules, SEQ, SeqLen, NColours);
    if( solution < 0 )
      printf("GAMEOVER\n");
    else
      printf("%s\n", key2col[solution]);
    free(SEQ);
  }
  return 0;
}

