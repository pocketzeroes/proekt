#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char num[12];
int trie[1000000][10];
int last;

int insert(int cnt, int where){
  int i,w;
  if(where>last){
    last++;
    for(i=0; i<=9; i++)
      trie[last][i] = -1;
  }
  w = trie[where][num[cnt]-48];
  if (w==-2)
    return 0;
  if (w==-1){
    trie[where][num[cnt]-48]=num[cnt+1]?last+1:-2;
    w=last+1;
  }
  return num[cnt+1]? insert(cnt+1,w): w==last+1;
}
int main(){
  int t,n;
  scanf("%d", &t);
  while(t--){
    int i,pre=0;
    last=-1;
    scanf("%d", &n);
    for(i=0; i<n; i++){
      scanf("%s", num);
      if (!pre)
        pre|= !insert(0, 0);
    }
    printf("%s\n",pre?"NO":"YES");
  }
  return 0;
}
