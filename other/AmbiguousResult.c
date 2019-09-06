#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<ctype.h>
typedef long long ll;
enum{ MAXNUMS = 1000};
int numbers[MAXNUMS];
char opers[MAXNUMS-1];
int count;
ll minres[MAXNUMS+1][MAXNUMS+1];
ll maxres[MAXNUMS+1][MAXNUMS+1];

ll compute(ll a, char op, ll b){
  return (op == '+') ? a+b : a*b;
}
bool run(){
  count = 0;
  for(;;){
    int ch = getchar();
    if(ch == 'E')
      return false;
    numbers[count] = 0;
    while(isdigit(ch)){
      numbers[count] = numbers[count] * 10 + ch - '0';
      ch = getchar();
    }
    ++count;
    if(ch == '\r') ch = getchar();
    if(ch == '\n') break;
    opers[count] = (char) ch;
  }
  for(int i = 0; i < count; ++i)
    minres[i][i+1] = maxres[i][i+1] = numbers[i];
  for(int k = 2; k <= count; ++k){
    for(int i = 0; i <= count-k; ++i){
      minres[i][i+k] = LLONG_MAX;
      maxres[i][i+k] = -1;
      for(int j = i+1; j < i+k; ++j){
        ll x = compute(minres[i][j], opers[j], minres[j][i+k]);
        if(x < minres[i][i+k])
          minres[i][i+k] = x;
        x = compute(maxres[i][j], opers[j], maxres[j][i+k]);
        if(x > maxres[i][i+k])
          maxres[i][i+k] = x;
      }
    }
  }
  printf("%lld %lld\n", minres[0][count], maxres[0][count]);
  return true;
}
int main(){
  while(run());
  return 0;
}
