#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{ MAXN = 1100100 };
enum{ MAXX = 1000100 };
enum{ oo   = 10001001};

typedef struct{
  int value[MAXX];
  int index[MAXX];
  int sign;
  int head, tail;
}MonQue;

MonQue*newMonQue(int sign){
  MonQue*rez=calloc(1, sizeof(MonQue));
  rez->head = 0;
  rez->tail =-1;
  rez->sign = sign;
  return rez;
}
bool comp(MonQue*q, int a, int b){
  if(q->sign==1)
    return a>b;
  return a<b;
}
void push(MonQue*q, int val, int ind){
  while(q->head <= q->tail && comp(q, q->value[q->tail], val))
    --q->tail;
  ++q->tail;
  q->value[q->tail ] = val;
  q->index[q->tail ] = ind;
}
int pop(MonQue*q, int ind){
  if(q->head > q->tail)
    return -1;
  if(q->index[q->head ] == ind )
    return q->value[q->head++];
  return -1;
}
int top(MonQue*q){
  return q->value[q->head];
}
///////////////
int visine     [MAXN];
int nove_visine[MAXN];
int opalio     [MAXN];
int n, m, x;
MonQue*Q1;
MonQue*Q2;

int main(){
  Q1=newMonQue(1);
  Q2=newMonQue(0);
  scanf("%d %d", &n, &x);
  for(int i = 0; i < n; ++i)
    scanf("%d", visine+i);
  for(int i = 0; i < x; ++i)
    visine[n+i] = oo;
  for(int i = 0; i < n+x; push(Q1, visine[i], i), ++i){
    if(i < x)
      continue;
    nove_visine[i-x] = top(Q1);
    pop(Q1, i-x);
  }
  ll cetkicom = 0;
  for(int i = 0; i < n; ++i){
    if(i <= n-x)
      push(Q2, nove_visine[i], i);
    if(x <= i)
      pop(Q2, i-x);
    cetkicom = cetkicom + visine[i] - top(Q2);
    opalio[ i ]= top(Q2);
  }
  int zadnja_visina = -1;
  int do_kuda       = -1;
  int poteza        = 0;
  for(int i = 0; i < n; ++i){
    if(opalio[i] != zadnja_visina || do_kuda < i){
      ++poteza;
      zadnja_visina = opalio[i];
      do_kuda = i+x-1;
    }
  }
  printf("%lld\n%d\n", cetkicom, poteza);
  return 0;
}
