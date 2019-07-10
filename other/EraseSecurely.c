#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
 int n;
 char buf1[3000], buf2[3000];
 scanf("%d\n",&n);
 gets(buf1); gets(buf2);
 int m=strlen(buf1);
 for(int _n=(m),i=0; i<_n; ++i)
  if ((n&1)!=(buf1[i]!=buf2[i])) goto hell;
 printf("Deletion succeeded\n");
 return 0;
hell:
 printf("Deletion failed\n");
 return 0;
}
