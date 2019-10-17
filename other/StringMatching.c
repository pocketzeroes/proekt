#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000000];
char*getln(){
  char*rv=gets(buff);
  if(rv==NULL)return rv;
  return strdup(buff);
}
int wlen;
int*compute_prefix_function(char*word){
  int pisz = wlen;
  int*pi = calloc(pisz, sizeof(int));
  int k = pi[0] = -1;
  for(int i=1; word[i]; ++i){
    while(k>=0&&word[k + 1] != word[i])
      k = pi[k];
    if(word[k + 1] == word[i])
      k++;
    pi[i] = k;
  }
  return pi;
}
void knuth_morris_pratt(char*sentence, char*word){
  wlen=strlen(word);
  int q=-1;
  int*pi = compute_prefix_function(word);
  for(int i=0; sentence[i]; ++i){
    while(q >= 0 && word[q+1] != sentence[i])
      q = pi[q];
    if(word[q+1] == sentence[i])
      q++;
    if(q+1 == wlen){
      printf("%d ", (i-wlen+1));
      q = pi[q];
    }
  }
}
int main(){
  char*p;
  char*s;
  while((p=getln())!=NULL){
    s=getln();
    knuth_morris_pratt(s, p);
    puts("");
  }
  return 0;
}
