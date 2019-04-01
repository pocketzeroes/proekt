#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
  int n;
  scanf("%d", &n);
  if(n == 1){
    puts("NO");
    return 0;
  }
  for(int i=2; i*i<n; i++){
    if(n % i == 0){
      while(n % i == 0)
        n /= i;
      if(n == 1){
        puts("YES");
        return 0;
      }
      else{
        puts("NO");
        return 0;
      }
    }
  }
  puts("YES");
  return 0;
}
