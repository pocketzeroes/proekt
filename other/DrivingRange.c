#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define A first
#define B second

enum{ MAXNM = 1000100};

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
int cmpP(pair a, pair b){
  if(a.first  != b.first) return(a.first  < b.first )?-1:1;
  if(a.second != b.second)return(a.second < b.second)?-1:1;
  return 0;
}
typedef struct{
  int   first;
  pair second;
}trip;
trip*newTrip(int a, pair b){
  trip*rez=calloc(1, sizeof(trip));
  rez->first =a;
  rez->second=b;
  return rez;
}
int cmpT(const void*pa, const void*pb){
  trip*a = (trip*)pa;
  trip*b = (trip*)pb;
  if(a->first != b->first)return(a->first < b->first )?-1:1;
  return cmpP(a->second, b->second);
}
trip elis[MAXNM];
int n, m, ans, cou;

int pre[MAXNM];
int getp(int p){
  return (pre[p] == pre[pre[p]]) ? pre[p] : (pre[p] = getp(pre[p]));
}
int main(){
  scanf("%d%d", &n, &m);
  while(n != 0 || m != 0){
    for(int i = 0; i < m; ++i) {
      scanf("%d%d%d", &elis[i].B.A, &elis[i].B.B, &elis[i].A);
    }
    qsort(elis, m, sizeof(trip), cmpT);
    for(int i = 0; i < n; ++i)
      pre[i] = i;
    ans = -1;
    cou = 0;
    for(int i = 0; i < m; ++i){
      int a = getp(elis[i].B.A);
      int b = getp(elis[i].B.B);
      if(a != b){
        pre[b] = a;
        cou++;
        ans = elis[i].A;
      }
    }
    if(cou != n - 1)
      puts("IMPOSSIBLE");
    else
      printf("%d\n", ans);
    break;
    scanf("%d%d", &n, &m);
  }
  return 0;
}
