#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

int main(){
  while (!feof(stdin)){
    int64_t res = 0;
    int     chr = 0;
    while('0' <= (chr = getc(stdin)) && chr <= '9')
      (res *= 10), (res += chr - '0');
    if(res == 0){
      puts("");
    }
    else{
      printf("%" PRId64 "\n", (res = (res >= 3 ? res - 2 : 1)));
    }
  }
  return 0;
}
