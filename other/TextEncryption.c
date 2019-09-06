#include<stdio.h>
#include<string.h>
enum{ MAX_SIZE = 10000};
char trans[256];
char text[MAX_SIZE + 1];
char enc [MAX_SIZE + 1];
int main(){
  int i, j, k, n;
  char c;
  memset(trans, 0, sizeof(trans));
  for (i = 'a'; i <= 'z'; ++i)
    trans[i] = trans[i - 'a' + 'A'] = (char)(i - 'a' + 'A');
  while (1){
    scanf("%d\n", &n);
    if (n == 0)
      break;
    i = 0;
    while (1){
      c = getchar();
      if (c == '\n')
        break;
      c = trans[c];
      if (c)
        text[i++] = c;
    }
    k = 0;
    for (j = 0; j < i; ++j){
      if (k >= i){
        k %= n;
        ++k;
      }
      enc[k] = text[j];
      k += n;
    }
    enc[i] = '\0';
    printf("%s\n", enc);
  }
  return 0;
}
