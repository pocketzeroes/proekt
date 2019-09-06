#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
bool run(){
  int len, cnt;
  if(scanf("%d %d", &len, &cnt)!=2)
    return false;
  int pos[cnt];
  int cntL = 0, maxL = -1, maxR = -1;
  for(int i = 0; i < cnt; ++i){
    int p; scanf("%d", &p);
    pos[i] = p;
    getchar();
    char ch = getchar();
    if(ch == 'L'){
      ++cntL;
      if (p > maxL)
        maxL = p;
    }
    else if (ch == 'R'){
      p = len - p;
      if (p > maxR)
        maxR = p;
    }
    else
      assert(!"newIllegalArgumentException");
  }
  qsort(pos,cnt,sizeof(int),cmp);
  printf("The last ant will fall down in %d seconds - started at ", (int)fmax(maxL, maxR));
  if(maxL == maxR)
    printf("%d and %d", pos[cntL-1] , pos[cntL]);
  else
    printf("%d", (maxL > maxR) ? pos[cntL-1] : pos[cntL]);
  puts(".");
  return true;
}
int main(){
  while(run()){}
  return 0;
}
