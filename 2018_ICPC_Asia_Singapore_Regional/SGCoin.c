#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

enum{MX   = (int)1e9};
enum{MUL  = (int)1e7};
enum{MOOD = 1000000007};

ll H(ll previousHash, char*transaction, ll token){
  ll v = previousHash;
  for(int i=0; transaction[i]; i++)
    v = (v * 31 + transaction[i]) % MOOD;
  return (v * 7 + token) % MOOD;
}
int getToken(int previousHash){
  char*transaction = "a";
  ll h = H(previousHash, transaction, 0);
  for(int i = 1 ; ; i++){
    int tgt = i * MUL;
    int sisa = (tgt - h + MOOD) % MOOD;
    if (sisa < MUL){
      return sisa;
    }
  }
}
int main(){
  int n;
  scanf("%d", &n);
  for(int i=0; i<2; i++){
    int res = getToken(n);
    char*res_first="a";
    int nxt = H(n, res_first, res);
    n = nxt;
    printf("a %d\n", res);
  }
  return 0;
}
