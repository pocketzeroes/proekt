#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int sol [8][100] = {
  {0},                                                                                             
  {0},                                                                                             
  {0, 0, 0, 0, 4, 6, 6, 6, 6},                                                                     
  {0, 0, 0, 4},                                                                                    
  {0, 0, 4, 6, 8,  12, 14, 18, 20, 22, 24, 28, 30, 34},                                            
  {0, 0, 6, 8, 12, 12, 18, 22, 24, 28, 32, 36, 38},                                                
  {0,  0,  6, 10,  14,  18,  24,  26,  32,  36,  42,  44,  48,  54,  58,  62,  66,  72,  74,  80, 
  84, 88, 94, 98, 100, 106, 112, 114, 118, 124, 128, 130, 136, 140, 144, 148, 154, 158, 162, 166, 
 170,176,180,184, 188, 192, 196, 200, 204, 210, 214, 218, 222, 226, 232, 236, 240, 244, 248, 254, 
   256, 260, 266, 270, 274},                                                                       
  {0, 0, 6, 12, 18, 22, 26, 32, 36, 42, 46, 52, 58, 64, 70, 76, 80, 88, 92},                       
};
int rowPeriod   [8] = {1, 1, 4, 1, 10, 1,  33,  6};
int squarePeriod[8] = {0, 0, 4, 2, 26, 4, 142, 36};

int sizes[]={
 1 ,
 1 ,
 9 ,
 4 ,
 14,
 13,
 65,
 19
};

int main(){
  ll M, N;
  while(scanf("%lld %lld", &M, &N)==2){
    M--, N--;
    if(N >= sizes[M]){
      ll rep = (N- sizes[M]) / rowPeriod[M] + 1;
      printf("%lld\n", sol[M][N-rep*rowPeriod[M]] + rep*squarePeriod[M]);
    }
    else
      printf("%d\n", sol[M][N]);
  }
  return 0;
}
