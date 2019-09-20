#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{MAX_BOOKS = 10000};
typedef long long ll;
bool taken[MAX_BOOKS];
typedef struct{
  ll a, d;
}book;

int cmpB(const void*pa, const void*pb){
  book*x=(book*)pa;
  book*y=(book*)pb;
  return(x->a < y->a)?-1:1;
}
ll readDate(){
  ll Y, M, D, h, m;
  ll d;
  scanf("%lld-%lld-%lld %lld:%lld", &Y, &M, &D, &h, &m);
  d = (Y - 2013) * 365 + (M - 1) * 30 + (D - 1);
  if(M > 2){
    d--; 
    if(Y % 4)
      d--;
  }
  while(--M){
    if((M <= 7 && M % 2) || (M > 7 && !(M % 2)))
      d++;
  }
  return m + 60 * (h + 24 * d);
}
void tc(){
  ll B, C;
  scanf("%lld %lld", &B, &C);
  book books[B];
  for(int z=0;z<B;z++){
    book b;
    char dummy[22];
    scanf("%s", &dummy);
    b.a = readDate();
    b.d = readDate();
    books[z] = b;
  }
  ll res = 0;
  memset(taken, 0, sizeof(taken));
  qsort(books, B, sizeof(book), cmpB);
  for(ll i=0; i<B; i++){
    if(taken[i])
      continue;
    res++;
    ll end = books[i].d;
    for(ll j=i+1; j<B; j++){
      if(taken[j])
        continue;
      if(books[j].a >= end + C){
        end = books[j].d;
        taken[j] = true;
      }
    }
  }
  printf("%lld\n", res);
}
int main(){
  int T;
  scanf("%d", &T);
  while(T--)
    tc();
  return 0;
}
