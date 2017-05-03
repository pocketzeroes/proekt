#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>


int cmp(const void*pa,const void*pb){
  const char* a = *(const char**)pa;
  const char* b = *(const char**)pb;
  char*ptr1=NULL;
  char*ptr2=NULL;
  
  asprintf(&ptr1,"%s%s",a,b);
  asprintf(&ptr2,"%s%s",b,a);
  int rv=strcmp(ptr1, ptr2)>0?-1:1;
  free(ptr1);
  free(ptr2);
  return rv;
}
char buff[100000];
int main() {
  int n;
  scanf("%d", &n);
  char* a[n];
  for(int i = 0; i <= (n - 1); ++i) {
    scanf("%s", &buff);
    a[i]=strdup(buff);
  }
  qsort(a, n, sizeof(char*), cmp);
  if(a[0][0]=='0'){
    puts("0");
    return 0;
  }
  for(int i = 0; i <= (n - 1); ++i){
    printf("%s", a[i]);
  }
  puts("");
  return 0;
}
