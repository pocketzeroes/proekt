#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)

int main(){
   char c;
   int lowval = 0, hival = 0, lowpos = -1, hipos = -1, pos = 0, curval = 0;
   while((c=getchar())!=EOF){
      if(c=='R'){
         curval++;
         if(curval>hival){
            hival = curval;
            hipos = pos;
         }
         pos++;
      }
      else if(c=='B'){
         curval--;
         if(curval<lowval){
            lowval=curval;
            lowpos=pos;
         }
         pos++;
      }
   }
   if(lowpos>hipos)
      swap(lowpos, hipos);
   printf("%d %d\n", (lowpos+2), (hipos+1));
   return 0;
}
