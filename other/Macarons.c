#include<stdio.h>
typedef unsigned long long ull;
ull N,M,S;
enum{ T = 1<<8};
const unsigned __int128 mod = 1000*1000*1000;
ull bin_fibo[2*T], res[T][T], tr[T][T], tmp[T][T] ;

void mult_egal(ull a[T][T], ull b[T][T]){
  for(ull i = 0 ; i < S ; i++ )
    for(ull j = 0 ; j <= i ; j++ ){
      unsigned __int128 v=0;
      for(ull k = 0 ; k < T ; k++ )
        v += a[i][k]*b[k][j] ;
      v%=mod;
      tmp[i][j]=v;
      tmp[j][i]=v;
    }
  for(ull i = 0 ; i < S ; i++ )
    for(ull j = 0 ; j < S ; j++ )
      a[i][j]=tmp[i][j];
}
int main(){
  scanf("%llu\n%llu\n", &N, &M);
  S=(1<<N);
  for(ull i = 0 ; i < S; i++ )
    res[i][i] = 1;
  bin_fibo[0]=bin_fibo[1]=1;
  for(ull i = 2 ; i < 2*S ; i++){
    bin_fibo[i]=bin_fibo[i/2];
    if( (i&3) == 0)
      bin_fibo[i]+=bin_fibo[i/4];
  }
  for(ull i = 0 ; i < S ; i++ ) 
    for(ull j = 0 ; j < S ; j++ )
      if( (i&j) == 0 )
        tr[i][j]=bin_fibo[S+(i|j)] ;
  while(M){
    if(M&1)
      mult_egal(res,tr);
    mult_egal(tr,tr);
    M/=2;
  }
  printf("%llu\n",res[0][0]);
  return 0;
}
