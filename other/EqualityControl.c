#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  int first;
  int second;
}pair;
typedef struct{
  int  first;
  pair second;
}trip;
int cmpT(const void*pa, const void*pb){
  trip*a=(trip*)pa;
  trip*b=(trip*)pb;
  int diff;
  int a2nd = a->second.first ; int a3rd = a->second.second;
  int b2nd = b->second.first ; int b3rd = b->second.second;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  diff = a2nd - b2nd; if(diff!=0) return diff;
  return a3rd - b3rd;
}

enum{ MAXN = 1000005};


void process2(trip a[MAXN], int*ac, char s[MAXN], int sc, int*pos){
  if      (s[*pos  ] == '['){
    while (s[*pos] != ']') {
      (*pos)++;
      int num = 0;
      while ((s[*pos] != ',') && (s[*pos] != ']')) {
        num = num * 10 + (int)(s[*pos] - '0');
        (*pos)++;
      }
      a[*ac].first = num;
      a[*ac].second.first = -1;
      a[*ac].second.second = -1;
      (*ac)++;
    }
    (*pos)++;
  }
  else if (s[*pos  ] == 'c'){
    (*pos) += 7;
    process2(a, ac, s, sc, pos);
    (*pos)++;
    process2(a, ac, s, sc, pos);
    (*pos)++;
  }
  else if (s[*pos+1] == 'o'){
    (*pos) += 7;
    process2(a, ac, s, sc, pos);
    (*pos)++;
  }
  else {
    (*pos) += 8;
    process2(a, ac, s, sc, pos);
    (*pos)++;
  }
}
void process (trip a[MAXN], int*ac, char s[MAXN], int sc, int*pos){
  if      (s[*pos  ] == '['){
    while (s[*pos] != ']'){
      (*pos)++;
      int num = 0;
      while ((s[*pos] != ',') && (s[*pos] != ']')) {
        num = num * 10 + (int)(s[*pos] - '0');
        (*pos)++;
      }
      a[*ac].first = num;
      a[*ac].second.first = -1;
      a[*ac].second.second = -1;
      (*ac)++;
    }
    (*pos)++;
  }
  else if (s[*pos  ] == 'c'){
    (*pos) += 7;
    process(a, ac, s, sc, pos);
    (*pos)++;
    process(a, ac, s, sc, pos);
    (*pos)++;
  }
  else if (s[*pos+1] == 'o'){
    (*pos) += 7;
    int cur = *ac;
    process2(a, ac, s, sc, pos);
    qsort(a+cur, (*ac)-cur, sizeof(trip), cmpT);
    (*pos)++;
  }
  else {
    (*pos) += 8;
    int cur = *ac;
    process2(a, ac, s, sc, pos);
    qsort(a+cur, (*ac)-cur, sizeof(trip), cmpT);
    if(cmpT(&a[cur], &a[*ac-1])!=0){
      for (int i = cur; i < *ac; i++) {
        a[i].second.first = cur;
        a[i].second.second = *ac;
      }
    }
    (*pos)++;
  }
}
int main(){
  static trip a[MAXN];
  int ac = 0;
  static char sa[MAXN];
  int sac;
  static trip b[MAXN];
  int bc = 0;
  static char sb[MAXN];
  int sbc;
  scanf("%s", sa);
  sac = strlen(sa);
  scanf("\n%s", sb);
  sbc = strlen(sb);
  int posa = 0;
  process(a, &ac, sa, sac, &posa);
  int posb = 0;
  process(b, &bc, sb, sbc, &posb);
  if (ac != bc){
    printf("not equal\n");
    return 0;
  }
  for (int i = 0; i < ac; i++){
    if ((a[i].first != b[i].first) || (a[i].second.first != b[i].second.first) || (a[i].second.second != b[i].second.second)){
      printf("not equal\n");
      return 0;
    }
  }
  printf("equal\n");
  return 0;
}

