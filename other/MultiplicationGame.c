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

int Fac[2];

int solve(int N){
   int pos = 0;
   while(N%2 == 0){
      N/=2;
      Fac[pos]++;
   }
   if(Fac[pos] != 0)
      pos++;
   for(long long i = 3; i*i <= N; i+=2){
      while(N%i == 0){
         N/=i;
         if(pos > 1)
            return -1;
         Fac[pos]++;
      }
      if(Fac[pos] != 0)
         pos++;
   }
   if(N != 1 && pos > 1)
      return -1;
   if(N != 1){
      Fac[pos]++;
      pos++;
   }
   if(pos == 1)
      return Fac[0]%2;
   else if(pos == 2){
      if(Fac[0] == Fac[1])
         return 0;
      if(Fac[0] + 1 == Fac[1] || Fac[0] == Fac[1] + 1)
         return 1;
      return -1;
   }
}
int main(){
   int T;
   scanf("%d", &T);
   while(T--){
      Fac[0] = Fac[1] = 0;
      int N;
      char*s;
      scanf("%d", &N);
      s = getstr();
      int ans = solve(N);
      if(ans == 1)
         printf("%s", s);
      else if(ans == 0)
         puts(s[0] == 'A' ? "Bob" : "Alice");
      else
         printf("tie");
      puts("");
   }
   return 0;
}
