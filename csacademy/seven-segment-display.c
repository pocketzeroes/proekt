#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

const int D[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
char buff[1000000];
int buffsz;

int main(){
  int k;
  scanf("%d", &k);
  if (k == 6) 
    return puts("0")*0;
  int keta = (k + 6) / 7;
  for(int i= (0);i< (keta);++i) {
    int rketa = keta - i - 1;
    bool ok = 0;
    for(int d= (0);d< (10);++d) {
      if (i == 0 && d == 0) 
        continue;
      int r = k - D[d];
      if (rketa * 2 <= r && r <= rketa * 7) {
        k = r;
        buff[buffsz++] = ('0'+d);
        ok = 1;
        break;
      }
    }
    if (!ok) {
      return puts("-1")*0;
    }
  }
  puts(buff);
  return 0;
}












