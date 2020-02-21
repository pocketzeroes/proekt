#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
char buff[1001];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int main(){
  int mx = getchar()-'a'+1;
  int N;
  scanf("%d", &N);
  char*s[N];         clr(s);
  int graph[mx][mx]; clr(graph);
  int indeg[mx];     clr(indeg);
  bool conn[mx][mx]; clr(conn);
  for(int i=0; i<N; i++)
    s[i] = getstr();
  for(int i=0; i<N; i++){
    for(int j=i+1; j<N; j++){
      int k = 0;
      int silen=strlen(s[i]);
      int sjlen=strlen(s[j]);
      for(; k<fmin(silen, sjlen); k++){
        if(s[i][k] != s[j][k]){
          conn[s[i][k]-'a'][s[j][k]-'a'] = true;
          graph[s[i][k]-'a'][s[j][k]-'a']++;
          indeg[s[j][k]-'a']++;
          break;
        }
      }
      if(k == fmin(silen, sjlen) && silen > sjlen)
        return puts("IMPOSSIBLE")*0;
    }
  }
  int queue[mx]; clr(queue);
  int front = 0, back = 0;
  for(int i=0; i<mx; i++)
    if(indeg[i] == 0)
      queue[back++] = i;
  while(front < back){
    int n = queue[front++];
    for(int i=0; i<mx; i++){
      if(graph[n][i] > 0){
        indeg[i] -= graph[n][i];
        graph[n][i] = 0;
        if(indeg[i] == 0)
          queue[back++] = i;
      }
    }
  }
  if(front != mx)
    puts("IMPOSSIBLE");
  else{
    bool unique = true;
    for(int i=1; i<mx; i++){
      if(!conn[queue[i-1]][queue[i]]){
        unique = false;
        break;
      }
    }
    if(unique){
      for(int i=0; i<mx; i++)
        putchar((char)(queue[i]+'a'));
      puts("");
    } 
    else
      puts("AMBIGUOUS");
  }
  return 0;
}
