#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

int main(){
  int runs;
  scanf("%d", &runs);
  while(runs--){
    int N,K;
    scanf("%d %d", &K, &N);
    int x[N+2*K]; fill(x, N+2*K, -1);
    for(int i=0; i<N; i++){
      scanf("%d", &x[i+K]);
      x[i+K]--;
    }
    int ncnt=0;
    int cnt[K];     memset(cnt, 0, sizeof(cnt));
    int ok [N+K+1]; memset(ok , 0, sizeof(ok) );
    for(int i=0; i<N+K+1; i++){
      if(ncnt==K)
        ok[i]=1;
      if(i<K && ncnt==i)
        ok[i]=1;
      if(i>N && ncnt==N+K-i)
        ok[i]=1;
      if(i==N+K)
        break;
      if(x[i]!=-1 && --cnt[x[i]]==0)
        ncnt--;
      if(x[i+K]!=-1 && cnt[x[i+K]]++==0)
        ncnt++;
    }
    int res=0;
    for(int i=0; i<K; i++){
      int tmp=1;
      for(int j=i; j<N+K+1; j+=K)
        if(!ok[j])
          tmp=0;
      res += tmp;
    }
    if(res==N+1)
      res=K;
    printf("%d\n", res);
  }
  return 0;
}
