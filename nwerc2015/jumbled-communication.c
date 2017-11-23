#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int main() {
  int obf[256];
  for (int x=0; x<256; x++){
    obf[x ^ (((x << 1) & 255))] = x;
  }
  bool first=true;
  int n;
  scanf("%d", &n);
  while (n--){
    int x;
    scanf("%d", &x);
    if (first) {
      first=false;
    } 
    else{
      printf(" ");
    }
    printf("%d", obf[x]);
  }
  puts("");
  return 0;
}
