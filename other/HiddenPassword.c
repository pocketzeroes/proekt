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
////////////////////
char*testPass(char*p, char*pf){
  int p_len  = strlen(p);
  int pf_len = strlen(pf);
  char*retval = "FAIL";
  int i, j;
  int position[40];
  for(i=0; i<40; i++)
    position[i] = -1;
  int letter  [26] = {0};
  bool found = true;
  for(i=0; i<p_len && found; i++){
    found = false;
    for(j=0; j<pf_len && !found; j++){
      if(p[i] == pf[j] && position[j] < 0){
        found = true;
        position[j] = i;
        letter[(int)(p[i] - 'A')]++;
      }
    }
  }
  if(found){
    bool inOrder = true;
    int char2Check = 0;
    for(i=0; i<pf_len; i++){
      if(position[i] >= 0){
        if(position[i] == char2Check)
          char2Check++;
        else
          inOrder = false;
      }
    }
    retval = (inOrder) ? "PASS" : "FAIL";
  }
  return retval;
}
int main(){
  char*pass       = getstr();
  char*testphrase = getstr();
  puts(testPass(pass, testphrase));
  return 0;
}
