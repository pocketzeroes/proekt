#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
  int N,k,S[100],grundy[10001],tag[10001],cookie=1;
  memset(tag,0,sizeof(tag));
  while (1) {
    scanf("%d", &k);
    if(!k) 
      break;
    for(int i=0;i<k;i++)
      scanf("%d", &S[i]);
    for(int i=0,j;i<=10000;i++,cookie++){
      for(j=0;j<k;j++)
        if (i-S[j]>=0)
          tag[grundy[i-S[j]]]=cookie;
      for(j=0;tag[j]==cookie;j++);
      grundy[i]=j;
    }
    scanf("%d", &k);
    while (k--){
      int h,j,mask=0;
      scanf("%d", &h);
      while (h--){
        scanf("%d", &j);
        mask^=grundy[j];
      }     
      printf("%c", mask ? 'W' : 'L');
    }
    puts("");
    break;
  }
  return 0;
}
