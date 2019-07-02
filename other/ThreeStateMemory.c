#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ MOD = 1000000009};
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
void reverse(char * str){
  if (str)
  {
    char * end = str + strlen(str) - 1;
#   define XOR_SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
    while (str < end)
    {
      XOR_SWAP(*str, *end);
      str++;
      end--;
    }
#   undef XOR_SWAP
  }
}

int main(){
  char*arr = getstr();
  reverse(arr);
  int n = strlen(arr);
  ll prev[n+1]; memset(prev, 0, sizeof(prev));
  ll cur [n+1]; memset(cur , 0, sizeof(cur ));
  if(arr[0] == '1')
    prev[1] = 1;
  else
    prev[0] = 1;
  int firstIndex = 0;
  for(int i = 1; i < n; i++){
    if(arr[i] == '1'){
      ll sum = 0;
      ll sumOfSums = 0;
      for(int j = firstIndex; j <= i + 1; j++){
        sum += prev[j];
        if(sum >= MOD)
           sum -= MOD;
        if(j == i){
          cur[j] = sumOfSums;
          firstIndex = j;
        }
        else if(j == i + 1)
          cur[j] = sum;
        else
          cur[j] = 0;
        sumOfSums += sum;
        if(sumOfSums >= MOD)
           sumOfSums -= MOD;
        prev[j] = cur[j];
      }
    }
  }
  ll sum = 0;
  for(int i = 0; i <= n; i++){
    sum += prev[i];
    if(sum >= MOD)
       sum -= MOD;
  }
  printf("%lld\n", sum);
  return 0;
}
