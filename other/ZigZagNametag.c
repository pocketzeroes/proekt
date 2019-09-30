#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int maxSum(int N, int lastCharacter){
   if (N == 0)
      return 0;
   int firstSum = fmax(25-lastCharacter, lastCharacter);
   firstSum += 25*(N-1);
   return firstSum;
}
int main(){
   int K;
   scanf("%d", &K);
   int N = (K+24)/25+1;
   int lastCharacter = -1;
   for(int k=0; k<26; k++){
      int sum = maxSum(N-1, k);
      if (sum >= K){
         putchar((char)('a'+k));
         lastCharacter = k;
         break;
      }
   }
   if(lastCharacter == -1){
      puts("-1");
      return 0;
   }
   for(int i=1; i<N; i++){
      for(int k=0; k<26; k++){
         int sum = maxSum(N-i-1, k) + abs(lastCharacter-k);
         bool passed = sum >= K;
         if (i == N-1)
            passed = sum == K;
         if (passed){
            putchar((char)('a'+k));
            K -= abs(lastCharacter-k);
            lastCharacter = k;
            break;
         }
      }
   }
   if(K != 0)
      puts("Solution Broken");
   return 0;
}
