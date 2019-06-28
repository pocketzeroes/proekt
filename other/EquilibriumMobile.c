#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>

enum{ MAXN = 2500000};

#define max(a,b) ((a) > (b) ? (a) : (b))

int nw;
long long weights[MAXN];

int cmp(const void *a1, const void *b1){
  long long a = *((long long *) a1);
  long long b = *((long long *) b1);
  if ( a<b )
    return -1;
  if ( a>b )
    return 1;
  return 0;
}
int read(int level){
  char c = getc(stdin);
  long long w;
  if ( c=='[' ){
    read(level+1);
    c = getc(stdin);
    if ( c!=',' )
      return 0;
    read(level+1);
    c = getc(stdin);
    if ( c!=']' )
      return 0;
  }
  else {
    ungetc(c,stdin);
    scanf("%lld",&w);
    weights[nw++] = w*(1<<level);
  }
  return 1;
}
int read_old(int level){
  char c;
  long long w;
  do {
    c = getc(stdin);
  }
  while ( isspace(c) );
  if ( c=='B' ){
    read(level+1);
    read(level+1);
  }
  else if ( c=='W' ) {
    scanf("%lld",&w);
    weights[nw++] = w*(1<<level);
  }
  else
    return 0;
  return 1;
}
int main(){
  int run, nruns;
  int best, curr, i;
  scanf("%d\n",&nruns);
  for(run=0; run<nruns; run++) {
    nw = 0;
    if ( ! read(0) )
      return 1;
    scanf("\n");
    qsort(weights,nw,sizeof(long long),cmp);
    best = 0;
    curr = 1;
    for(i=1; i<nw; i++) {
      if ( weights[i]==weights[i-1] ) {
        curr++;
      }
      else {
        best = max(best,curr);
        curr = 1;
      }
    }
    best = max(best,curr);
    printf("%d\n",nw-best);
  }
  return 0;
}
