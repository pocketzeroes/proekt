#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
typedef long long ll;

int main(){
  int t = in_nextInt();
  while(t-- > 0){
    int number  = 0;
    ll result = 0ll;
    char*br=getstr();
    for(int z=0;br[z];z++){char ch = br[z];
      if(ch == ','){
        result *= 60LL;
        result += number;
        number = 0;
      } 
      else{
        number *= 10;
        number += (ch - '0');
      }
    }
    result *= 60LL;
    result += number;
    printf("%lld\n", result);
  }
  return 0;
}
