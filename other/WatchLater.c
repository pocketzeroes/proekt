#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
//////////////////////

int N, K;
char*s;
int memo[(1 << 20)+10];

int f(int used){
  if(used == 0)
    return 0;
  if(memo[used] >= 0)
    return memo[used];
  int chunks[26] = {0};
  char prev = -1;
  for(int i = 0; i < N; i++){
    int c = s[i] - 'a';
    if(!((1 << c) & used))
      continue;
    if(c != prev)
      chunks[c]++;
    prev = c;
  }
  memo[used] = N;
  for(int i = 0; i < 26; i++){
    if(!chunks[i]) 
      continue;
    int temp = chunks[i] + f(used ^ (1 << i));
    memo[used] = fmin(memo[used], temp);
  }
  return memo[used];
}
int main(){
  int used = 0;
  scanf("%d %d", &N, &K);
  s=getstr();
  for(int z=0;s[z];z++){char c = s[z];
    used |= (1 << (c-'a'));
  }
  fill(memo, (1<<20)+10, -1);
  printf("%d\n", f(used));
  return 0;
}
