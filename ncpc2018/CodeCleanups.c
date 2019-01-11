#include <stdio.h>

int main(){
  int n, t;
  int cl = 0, num = 0, acc = 0, last = 0;
  scanf("%d",&n);
  while (n--) {
    scanf("%d",&t);
    if (acc + num * (t - last) > 19) {
      cl++;
      acc = num = 0;
    } 
    acc += num * (t - last);
    num++;
    last = t;
  }
  cl++;
  printf("%d\n", cl);
  return 0;
}
