#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  int ok = 1;
  int cnt = 1, n;
  char wrd[10];
  scanf("%d",&n);
  while (n--){
    scanf("%s",wrd);
    if (strcmp(wrd,"mumble"))
        ok &= cnt == atoi(wrd);
    cnt++;
  }
  if (ok)
    printf("makes sense\n");
  else
    printf("something is fishy\n");
}
