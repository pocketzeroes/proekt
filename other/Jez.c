#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<setjmp.h>

static jmp_buf exception_env;
static int exception_type;

typedef long long ll;
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ LOG_MAXN = 20};

int R, S;
ll K;
int nd, visak;

int prebroji(int x, int ymax){
   int rez = 0;
   for ( int k=LOG_MAXN; k>=0; --k ){
      if ( (ymax&(1<<k)) != 0 ) {
         int jed = __builtin_popcount(x&((1<<k)-1));
         rez += 1<<(k-jed);
         if ( (x&(1<<k)) != 0 )
            break;
      }
   }
   return rez;
}
int jedanred(int r){
   int smax = nd-r;
   if ( nd%2 == 0 ) {
      int sr = nd - max(0, nd-R+1);
      smax += sr-r >= 0 && sr-r < visak;
   }
   else {
      int sr = max(0, nd-S+1);
      smax += r-sr >= 0 && r-sr < visak;
   }
   smax = max(smax, 0);
   smax = min(smax, S);
   return prebroji(r, smax);
}
void dodaj(ll*ukupno, int x){
   (*ukupno) += x;
   if( *ukupno > K ){
//    throw 1;
      longjmp(exception_env, 1);
   }
   ++nd;
   visak = K - *ukupno;
}
int main() {
   scanf("%d %d %lld", &R, &S, &K);
   if(!setjmp(exception_env)){
      int najdulja = min(R, S);
      ll ukupno = 0;
      nd = 0;
      for ( int i=1; i<=najdulja; ++i ) 
         dodaj(&ukupno, i);
      for ( int i=0; i<R+S-2*najdulja; ++i ) 
         dodaj(&ukupno, najdulja);
      for ( int i=najdulja-1; i>0; --i ) 
         dodaj(&ukupno, i);
   }
   else{
      ;
   }
   ll rez = 0;
   for(int r=0; r<R; ++r)
      rez += jedanred(r);
   printf("%lld\n", rez);
   return 0;
}
