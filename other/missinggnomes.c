#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
  int n, m;
  scanf("%d %d", &n, &m);
  bool used[100001]; memset(used, 0, sizeof(used));
  int  rem [100000];
  for(int i=0; i<m; i++){
    scanf("%d", &rem[i]);
    used[rem[i]] = true;
  }
  int ui = 1;
  for(int i=0; i<m; i++){
    while(ui <= n){
      if(used[ui])
				ui++;
			else if(ui < rem[i])
				printf("%d\n", ui++);
			else
				break;
    }
    printf("%d\n", rem[i]);
  }
  for(; ui<=n; ui++)
    if(!used[ui])
      printf("%d\n", ui);
  return 0;
}
