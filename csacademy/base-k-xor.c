#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

void solve(){
  int a,b,k;
  scanf("%d %d %d",&a, &b, &k);
  int ans = 0;
  int kk = k%2==0 ? 2*k : k;
  int aa = ((a+kk-1)/kk)*kk;
  int bb = (b/kk)*kk;
  int*po=NULL;int poSz=0;
  for(int i=a; i<aa ;++i)po=pushback(po,&poSz,i);
  for(int i=bb;i<b+1;++i)po=pushback(po,&poSz,i);
  int base = 1;
  while(base < 1000000000){
    int tmp = 0;
    for(int i=0;i<poSz;i++){
        int x=po[i];
        tmp = (tmp+x)%k;
    }
    ans += tmp*base;
    base *= k;
    for(int i=0;i<poSz;i++){
        po[i]/=k;
    }
  }
  printf("%d\n",ans);
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)
      solve();
  return 0;
}

















