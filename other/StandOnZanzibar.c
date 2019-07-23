#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int main(){
  int T, previous = 1, current, answer;
  scanf("%d", &T);
  while(T--){
    answer = 0;
    scanf("%d", &previous);
    while(scanf("%d", &current)==1){
      if(current == 0)
        break;
      answer += max(0, current-(previous*2));
      previous = current;
    }
    printf("%d\n", answer);
  }
  return 0;
}
