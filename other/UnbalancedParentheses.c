#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

enum{ MAXCOST = 1200};
int counts[MAXCOST];

void check(char*s, int*mindep, int*finaldep){
   int dep = 0;
  *mindep  = 0;
   for(int i=0; s[i]; i++){
      if(s[i] == '(')
         dep++ ;
      else
        *mindep = fmin(*mindep, --dep);
   }
  *finaldep = dep;
}
int main(){
   int n, k;
   char*s;
   scanf("%d %d", &n, &k);
   s = getstr();
   int c[n];
   int basevalue = 0;
   for(int i=0; i<n; i++){
      scanf("%d", &c[i]);
      if(c[i] < 0){
         c[i] = - c[i] ;
         basevalue += c[i] ;
         s[i] = '(' + ')' - s[i] ;
      }
   }
   int mindep, finaldep;
   check(s, &mindep, &finaldep);
   int leftfix  = (1-mindep) >> 1;
   int rightfix = (1+finaldep-mindep) >> 1;
   int fixcost  = leftfix + rightfix;
   if(fixcost > k || (n & 1)){
      printf("%d\n", -basevalue);
      exit(0) ;
   }
   int avail = 0;
   for(int i=0; i<n; i++){
      if(s[i] == ')'){
         counts[c[i]]++ ;
         avail++ ;
      }
   }
   int bestsol = INT_MAX;
   int dep = 0 ;
   for(int i=0; i<=n; i++){
      int leftfix = (1-dep) >> 1;
      int rightfix = (1+finaldep-dep) >> 1;
      if(avail + leftfix + rightfix > k){
         int totcost = 0;
         int need = k - leftfix - rightfix + 1;
         for(int ci=0; need > 0; ci++){
            if(counts[ci]){
               if(counts[ci] >= need){
                  totcost += ci * need;
                  break ;
               }
               else{
                  totcost += ci * counts[ci] ;
                  need -= counts[ci] ;
               }
            }
         }
         bestsol = fmin(bestsol, totcost) ;
      }
      if(i < n){
         if(s[i] == ')'){
            dep--;
            counts[c[i]]--;
            avail--;
         }
         else{
            dep++;
            counts[c[i]]++;
            avail++;
         }
      }
   }
   if(bestsol == INT_MAX)
      puts("?");
   else
      printf("%d\n", bestsol - basevalue);
   return 0;
}
