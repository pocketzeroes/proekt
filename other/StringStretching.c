#define _GNU_SOURCE 1
#include<stdio.h> // stretching
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char* substr(const char* str, size_t begin, size_t len){
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return strdup(""); 
  return strndup(str + begin, len); 
}

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int N, K;
int off;
char*c;

int main(){
  c = getstr();
  N = strlen(c);
  for(K=1; K<=N; K++){
    if(N % K != 0)
      continue;
    char*best = NULL;
    for(off = 0; off + K <= N; off++){
      bool seen[N][N/K+1][K+1]; memset(seen, 0, sizeof(seen));
      bool dp  [N][N/K+1][K+1]; memset(dp  , 0, sizeof(dp  ));
bool generatable(int s, int copies, int curletter){
  if(copies == 0)
    return true;
  if(curletter == K)
    return generatable(s, copies - 1, 0);
  if(seen[s][copies][curletter])
    return dp[s][copies][curletter];
  seen[s][copies][curletter] = true;
  bool ok = c[curletter + off] == c[s] && generatable(s+1, copies, curletter+1);
  for(int times = 1; !ok && times < copies; times++)
    ok |= generatable(s, times, 0) && generatable(s + times * K, copies - times, curletter);
  return dp[s][copies][curletter] = ok;
}
      if(generatable(0, N/K, 0)){
        char*cand = substr(c, off, K);
        if(best == NULL || strcmp(cand, best) < 0)
          best = cand;
      }
    }
    if(best != NULL){
      puts(best);
      return 0;
    }
  }
  return 0;
}
