#include<stdio.h>
#include<stdbool.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
enum{ inf = 1000000000};

int n, k;
int x [100], y [100];
int cm[100], sm[100];
int cv[100], sv[100];


int nabavi(int grama, int cm, int sm, int cv, int sv){
   int rez, malih, velikih;
   rez     = inf;
   velikih = 0;
   do{
      malih = (grama - velikih * sv + sm-1) / sm;
      if(malih < 0) malih = 0;
      if(malih * cm + velikih * cv < rez)
         rez = malih * cm + velikih * cv;
      velikih = velikih + 1;
      if((velikih-1) * sv > grama)
         break;
   }
   while(1);
   return rez;
}

bool moguce( int porcija ){
   int cijena = 0;
   for( int i = 0; i < n; ++i )
      cijena += nabavi( x[i] * porcija - y[i], cm[i], sm[i], cv[i], sv[i] );
   return cijena <= k;
}
int main(){
   scanf( "%d%d", &n, &k );
   for( int i = 0; i < n; ++i )
      scanf( "%d%d%d%d%d%d", &x[i], &y[i], &sm[i], &cm[i], &sv[i], &cv[i] );
   int lo = 0, hi = 1;
   while( moguce( hi ) )
      hi = hi * 2;
   while( lo < hi ) {
      int mid = (lo+hi+1) / 2;
      if( moguce( mid ) ) lo = mid; else hi = mid-1;
   }
   printf( "%d\n", lo );
   return 0;
}
