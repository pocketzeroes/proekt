#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int main() {
  int N;
  scanf("%d", &N);
  do{
    int A[N];
    for (int i = 0; i < N; i++) 
      scanf("%d", &A[i]);
    int tot = 0;
    for (int i = 0; i < N; i++) 
      tot += A[i];
    int ret;
    for(ret = 100; ret; ret--){
      int v[N];
      for (int i = 0; i < N; i++) 
        v[i]=A[i];

      if (tot%2) 
        goto fail;
      if (ret == 1 && tot != 2) 
        goto fail;
      for(int i = ret, p1 = 0, p2 = N-1; i; i--){
        if (v[p1] < i) 
          goto fail;
        v[p1] -= i;
        while (p1 < p2 && v[p1] == 0) 
          p1++;
        if (v[p2] < i) 
          goto fail;
        v[p2] -= i;
        while (p1 < p2 && v[p2] == 0) 
          p2--;
      }
      break;
   fail:;
    }
    if (ret)
      printf("%d\n", ret);
    else
      puts("no quotation");
  }while(0);
}


















































