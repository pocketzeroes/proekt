#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>



int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  char**a=malloc(n*sizeof(char*));
  for(int i = 0; i <= (n - 1); ++i) {
    char buff[1024];
    scanf("%s", &buff);
    a[i]=strdup(buff);
  }
  int p = n - 1, cur = strlen(a[p]);
  while (p >= 0) {
    p--;
    if (p < 0) break;
    if (cur + strlen(a[p]) + 1 > k) break;
    cur += strlen(a[p]) + 1;
  }
  p++;
  int i = 0;
  while(true){
    if (i >= p) {
      for(int k = i; k <= (n - 1); ++k) {
        printf("%s", a[k]);
        if (k < n - 1) {
          printf(" ");
        }
      }
      break;
    }
    int j = i;
    cur = strlen(a[i]);
    while (true) {
      j++;
      if (j >= n) break;
      if (cur + strlen(a[j])+1 > k) break;
      cur += strlen(a[j]) + 1;
    }
    j--;
    int p1 = 0, p2 = 0;
    if (j > i) {
      p1 = (k - cur) / (j - i), p2 = (k - cur) % (j - i);
    }
    for(int k = i; k <= (j); ++k) {
      printf("%s", a[k]);
      if (k < j) {
        for(int l = 0; l <= (p1); ++l) printf( " ");
        if (p2) {
          printf( " ");
          p2--;
        }
      }
    }
    if (j == i) {
      for(int i = 1; i <= ((k - cur)); ++i) {
        printf( " ");
      }
    }
    i = j+1;
    puts("");
  }
  return 0;
}


