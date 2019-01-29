#include<stdint.h>
#include<stdio.h>

int main(){
  static char buf[1001];
  const char*bp;
  if((bp=fgets(buf,sizeof buf,stdin)) != buf)
    return 1;
  static uint32_t have[10];
  while('0'<=*bp && *bp<='9')
    ++have[bp++[0]-'0'];
  int res[2]={have[0]+2,0};
  for (int i=1; i<10; i++)
    if (have[i]+1<res[0])
      res[0]=have[i]+1,
      res[1]=i;
  if (res[1]==0) 
    putc('1',stdout), --res[0];
  while (res[0]--) 
    putc('0'+res[1],stdout);
  puts("");
  return 0;
}
