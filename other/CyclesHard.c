#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}



vec s[400];
int n,zero,paths,cycles;
bool b[400];

void dfs(int x){
  b[x]=1;
  for(int i=0; i<s[x].sz; i++)
    if(!b[s[x].ptr[i]])
      dfs(s[x].ptr[i]);
}
void calc(){
  zero=paths=cycles=0;
  memset(b,0,sizeof(b));
  for(int i=1;i<=n;i++){
    if(!b[i]&&s[i].sz==1){
      paths++;
      int cur=i;
      while(1){
        b[cur]=1;
        int j=0;
        while(j<s[cur].sz&&b[s[cur].ptr[j]])
          j++;
        if(j==s[cur].sz)
          break;
        cur=s[cur].ptr[j];
      }
    }
  }
  for(int i=1;i<=n;i++)
    if(!s[i].sz)
      zero++,b[i]=1;
  for(int i=1;i<=n;i++){
    if(!b[i]){
      cycles++;
      dfs(i);
    }
  }
}
int main(){
  int C;
  scanf("%d", &C);
  int fact [3000]={1},
      fact2[3000]={1,1,1};
  for (int i=0; i<2999; i++)
    fact[i+1]=fact[i]*(i+1)%9901;
  for(int i=3;i<3000;i++)
    fact2[i]=fact2[i-1]*i%9901;
  for(int c=1;c<=C;c++){
    int k,t[20][2],ans=0;
    scanf("%d %d", &n, &k);
    for (int z=0; z<k; z++)
      scanf("%d %d", &t[z][0], &t[z][1]);
    for (int take=0; take<(int)(1<<k); take++){
      int mult=1;
      for (int i=0; i<(int)(k); i++)
        if(take&1<<i)
          mult*=-1;
      for(int i=1;i<=n;i++)
        s[i].sz=0;
      for (int i=0; i<(int)(k); i++)
        if(take&1<<i)
          for(int j=0; j<2; j++)
            s[t[i][j]].ptr = pushback(s[t[i][j]].ptr, &s[t[i][j]].sz, t[i][j^1]);
      for(int i=1;i<=n;i++)
        if(s[i].sz>2)
          goto hell;
      calc();
      mult=(mult%9901 +9901)%9901;
      if(cycles>1)
        goto hell;
      if(cycles){
        if(zero+paths)
          goto hell;
        ans=(ans+mult)%9901;
        goto hell;
      }
      if(!paths){
        ans=(ans+fact2[n-1]*mult)%9901;
        goto hell;
      }
      for (int z=0; z<(int)(paths-1); z++)
        mult=mult*2%9901;
      ans=(ans+mult*fact[zero+paths-1])%9901;
hell:;
    }
    printf("Case #%d: %d\n", c, ans);
  }
  return 0;
}
