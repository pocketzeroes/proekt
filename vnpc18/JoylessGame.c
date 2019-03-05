#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char s[100000];
char*fi = "Chikapu";
char*se = "Bash";
int main(){
  int ntests;
  scanf("%d", &ntests);
  while(ntests --){
    scanf("%s", &s);
    int n = strlen(s);
    if(s[0] != s[n - 1])
      puts( (n % 2 == 0) ? se : fi );
    else
      puts( (n % 2 == 1) ? se : fi );
  }
  return 0;
}
