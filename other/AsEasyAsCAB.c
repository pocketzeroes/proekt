#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  free(a);
  return ptr;
}
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
//////////////////////

bool edge[30][30];
int  pred[30],
     succ[30];

int main(){
   char lastlet = getchar(); getchar();
   int  nwords;
   scanf("%d", &nwords);
   char*prev=strdup("");
   char*w   =strdup("");
   bool inconsistent = false;
   int nlet = lastlet - 'a' + 1;
   for(int i=0; i<nwords; i++, prev = strdup(w)){
      w = getstr();
      int d = 0;
      while(d < strlen(prev) && d < strlen(w) && prev[d] == w[d])
         d++;
      if(d >= strlen(prev))
         continue;
      if(d >= strlen(w)){
         inconsistent = 1;
         continue;
      }
      if(edge[prev[d]-'a'][w[d]-'a'] == 0){
         edge[prev[d]-'a'][w[d]-'a'] = 1;
         pred[w[d]-'a']++;
         succ[prev[d]-'a']++;
      }
   }
   char*res=strdup("");
   bool insuff = false;
   for(int i=0; i<nlet; i++){
      int head = -1;
      for(int j=0; j<nlet; j++){
         if(pred[j] == 0){
            if(head < 0)
               head = j;
            else
               insuff = true;
         }
      }
      if(head < 0){
         inconsistent = 1;
         break;
      }
      pred[head] = -1;
      for(int j=0; j<nlet; j++)
         if(edge[head][j])
            pred[j]--;
      res = concatc(res, head + 'a');
   }
   if(insuff)
      puts("AMBIGUOUS");
   else if(inconsistent)
      puts("IMPOSSIBLE");
   else
      puts(res);
   return 0;
}
