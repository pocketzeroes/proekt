#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
int main(){
  int G = in_nextInt();
  int sin[G];
  for (int i=0; i<G; ++i)
    sin[i] = in_nextInt();
  int m = 0;
  bool ok=false;
  while(!ok){
    ++m;
    bool used[m]; memset(used, 0, sizeof(used));
    ok = true;
    for(int i = 0; ok && i < G; ++i)
      if(used[sin[i]%m])
        ok = false;
      else
        used[sin[i]%m]=true;
  }
  printf("%d\n", m);
  return 0;
}
