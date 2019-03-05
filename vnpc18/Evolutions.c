#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}

enum{ MAX    = 1000100};
enum{ SQRT   = 1515 };
enum{ LENGTH = 20 };

int result[MAX], 
    pw    [MAX][LENGTH + 3];

int gcd(int a, int b){
  while (true){
    if (a == 0)
      return b;
    if (b == 0)
      return a;
    if (a > b)
      a %= b;
    else
      b %= a;
  }
}
int getSum(int p, int q, int k){
  ll res = 0;
  for (int i = 0, _n = (k + 1); i < _n; i++){
    res += 1LL * pw[p][i] * pw[q][k - i];
    if (res >= MAX) 
      return MAX;
  }
  return res;
}
void prepare(){
  for (int i = (1), _b = (MAX - 1); i <= _b; i++){
    pw[i][0] = 1;
    for (int j = (1), _b = (LENGTH); j <= _b; j++)
      pw[i][j] = min(1LL * MAX, 1LL * pw[i][j - 1] * i);
  }
  int numPair = 0;
  for (int k = (2), _b = (LENGTH); k <= _b; k++){
    for (int q = (1), _b = (SQRT); q <= _b; q++){
      if (pw[q][k] >= MAX) 
        break;
      for (int p = (q + 1), _b = (SQRT); p <= _b; p++){
        int sum = getSum(p, q, k);
        if (sum >= MAX) 
          break;
        if (gcd(p, q) > 1) 
          continue;
        numPair++;
        result[sum]++;
      }
    }
  }
  int cnt = 0;
  for (int i = (1), _b = (MAX - 1); i <= _b; i++) 
    if (result[i] > 0) 
      cnt++;
  for (int i = (MAX - 1), _a = (1); i >= _a; i--) 
    for (int j = 2 * i; j < MAX; j += i) 
      result[j] += result[i];
}
int solve(int n) {
  if (n < 3) return 1;
  int numOne = 1;
  int numTwo = n % 2 == 0 ? n / 2 - 1 : n / 2;
  return numOne + numTwo + result[n];
}
int main(){
  prepare();
  int input;
  scanf("%d", &input);
  while (scanf("%d", &input) == 1)
    printf("%d ", solve(input));
  printf("\n");
  return 0;
}
