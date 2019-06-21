#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll  v[36];
int bitcnt[1<<18];


int countbits(ll a){
  return bitcnt[a>>18]+bitcnt[a&0x3FFFF];
}
int check(int n, int cur, int sel, ll mask){
  if(countbits(mask)<n) 
    return 0;
  if(sel==n) 
    return 1;
  if(sel+36-cur<n) 
    return 0;
  return check(n, cur+1, sel  , mask)||
         check(n, cur+1, sel+1, mask&v[cur]);
}
int main(){
  for(int i=0; i<(1<<18); i++){
    int cnt=0;
    for(int j=0; j<18; j++){
      if ((1<<j)&i)
        cnt++;
      bitcnt[i]=cnt;
    }
  }
  int N;
  scanf("%d", &N);
  while(N--){
    int m;
    scanf("%d", &m);
    for(int i=0; i<36; i++)
      v[i]=0;
    for(int i=0; i<m; i++){
      int x, y;
      scanf("%d %d", &x, &y);
      v[y-1] |= (1LL<<(x-1));
    }
    int n;
    for(n=2; n*n<=m && check(n,0,0,(1LL<<36)-1); n++);
    printf("%d\n", n-1);
  }
  return 0;
}
