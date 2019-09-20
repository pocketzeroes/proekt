#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
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
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
enum{ MOD = 21092013};


int main(){
  int N, prob=1;
  for(scanf("%d", &N); N--;){
    char*S = getstr();
    char*T = getstr();
    int Tsize = strlen(T);
    vec st=newVec();
    for(int i=0; S[i]; i++){
      if(S[i]=='U'){
        if(st.sz)
          st.sz--;
      }
      else
        pb(st, S[i]);
    }
    int nextL[Tsize]; clr(nextL);
    int nextR[Tsize]; clr(nextR);
    int nl = Tsize;
    int nr = Tsize;
    for(int i=Tsize-1; i >= 0; i--){
      nextL[i] = nl;
      nextR[i] = nr;
      if(T[i] == 'L') nl = i;
      if(T[i] == 'R') nr = i;
    }
    int dp[Tsize+2]; clr(dp);
    dp[Tsize] = 1;
    for(int i=Tsize-1; i >= 0; i--){
      if     (T[i] == 'L') dp[i] = 2*dp[i+1] - dp[nextL[i]+1];
      else if(T[i] == 'R') dp[i] = 2*dp[i+1] - dp[nextR[i]+1];
      else
        dp[i] = dp[i+1];
      dp[i] %= MOD;
    }
    int ret = dp[0];
    for(int i=0; i<Tsize && st.sz; i++){
      if(T[i] == 'U'){
        ret++;
        if(st.ptr[st.sz-1] == 'L')
          ret = (ret + dp[nextR[i]+1]) % MOD;
        else if(st.ptr[st.sz-1] == 'R')
          ret = (ret + dp[nextL[i]+1]) % MOD;
        st.sz--;
      }
    }
    printf("Case %d: %d\n", prob++, (ret + MOD) % MOD);
  }
  return 0;
}
