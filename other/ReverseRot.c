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

int main(){
  int N, i, inLength;
  char* inString;
  char*outString;
  scanf("%d", &N);
  while(N > 0){
    inString = getstr();
    outString = strdup(inString);
    inLength = strlen(inString);
    for(i=0; i < inLength; i++)
      outString[inLength -1 -i] = inString[i];
    for(i=0; i < inLength; i++){
      if(outString[i] >= 'A' && outString[i] <= 'Z'){
        if((int)(outString[i] - 'A' + N) % 28 < 26)
          outString[i] = 'A' + (outString[i] - 'A' + N) % 28;
        else if((outString[i] - 'A' + N) % 28 == 26)
          outString[i] = '_';
        else
          outString[i] = '.';
      }
      else if(outString[i] == '_'){
        if(N == 1)
          outString[i] = '.';
        else
          outString[i] = 'A' + N - 2;
      }
      else{
        if(N == 27)
          outString[i] = '_';
        else
          outString[i] = 'A' + N - 1;
      }
    }
    puts(outString);
    scanf("%d", &N);
  }
  return 0;
}
