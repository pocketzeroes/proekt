#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int A[(1 << 18)];
bool Used[(1 << 18)];

int main(){
   int n;
   scanf("%d", &n);
   for(int i = 0; i < (1 << n); i++){
      int x;
      scanf("%d", &x);
      int pos = 0;
      int l = (1 << (n-1)),r = 1;
      for(int j = 0; j <= n/2; j++){
         if(l & i)
            pos |= r;
         if(r & i)
            pos |= l;
         l /= 2;
         r *= 2;
      }
      A[pos] = x;
   }
   int saved = 0;
   for(int i = n; i > 0; i--){
      int s = (1 << i);
      int pos = 0;
      while(pos < (1 << n)){
         if(!Used[pos]){
            bool works = true;
            int cur = A[pos];
            for(int j = pos; j < pos+s; j++){
               if(cur != A[j]){
                  works = false;
                  break;
               }
            }
            if(works){
               for(int j = pos; j < pos+s; j++)
                  Used[j] = true;
               saved += (1 << (i+1)) - 2;
            }
         }
         pos += s;
      }
   }
   printf("%d\n", (1 << (n+1)) - 1 - saved );
   return 0;
}
