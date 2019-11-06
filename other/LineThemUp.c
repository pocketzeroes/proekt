#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}


int main(){
  int N, i;
  bool increasing, decreasing;
  char*people[20];
  char*largest;
  char*smallest;
  scanf("%d", &N);
  for(i=0; i<N; i++)
    people[i] = getstr();
  increasing = decreasing = true;
  for(i=0; i<N-1; i++){
    int rv = strcmp(people[i], people[i+1]);
    if(rv > 0) increasing = false;
    if(rv < 0) decreasing = false;
  }
  if(increasing == true && decreasing == false)
    puts("INCREASING");
  else if(increasing == false && decreasing == true)
    puts("DECREASING");
  else
    puts("NEITHER");
  return 0;
}
