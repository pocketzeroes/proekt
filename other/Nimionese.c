#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<ctype.h>

void erase(char*v, int pos){
  int vsz=strlen(v);
  for(int i=pos; i<vsz-1; i++)
    v[i] = v[i+1];
  v[vsz-1]='\0';
}
char*convertWord(char*s){
  char c = s[0];
  char teststrlow[] = "bcdgknpt";
  char teststrup [] = "BCDGKNPT";
  char*teststr = teststrlow;
  int  teststr_sz=8;
  if(isupper(c))
    teststr = teststrup;
  int best = 30;
  char best_char = 'b';
  for(int i = 0; i < teststr_sz; ++i ){
    if( abs(s[0] - teststr[i]) < best ){
      best = abs(s[0] - teststr[i]);
      best_char = teststr[i];
    }
  }
  s[0] = best_char;
  bool itson = false;
  for( int i = 0; s[i]; ++i){
    if( s[i] == '-' ){
      itson = true;
      erase(s, i);
      i--;
      continue;
    }
    if( itson ){
      for(int j = 0; j < teststr_sz; ++j ){
        if( s[i] == teststrlow[j] ){
          s[i] = tolower(best_char);
        }
      }
    }
  }
  for(int i=0; i<teststr_sz; ++i){
    char testchar = tolower(s[strlen(s)-1]);
    if( testchar == teststrlow[i] ){
      int best = 30;
      char best_str[] = "ah";
      if(abs(testchar - 'a') < best){
        best = abs(testchar - 'a');
        strcpy(best_str, "ah");
      }
      if(abs(testchar - 'o') < best){
        best = abs(testchar - 'o');
        strcpy(best_str, "oh");
      }
      if(abs(testchar - 'u') < best){
        best = abs(testchar - 'u');
        strcpy(best_str, "uh");
      }
      strcat(s, best_str);
      break;
    }
  }
  return s;
}
char word[10000];
int main(){
  bool first = true;
  while(scanf("%s", &word)==1){
    if(first)
      first = false;
    else
      printf(" ");
    printf("%s", convertWord(word));
  }
  puts("");
  return 0;
}
