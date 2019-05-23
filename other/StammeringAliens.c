#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}

typedef unsigned long long ull;

typedef struct{
  ull first;
  int second;
}pair;
pair newPair(ull a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
////////////////
enum{ maxlen = 40000};
char str[maxlen + 2];
int n, mintimes, tablesize;

ull mod = 288230376151711013ull;

ull stephash(ull hash, int letter){
  return ((hash << 5) | letter) % mod;
}
ull hashfunc(const char* str, int l){
  ull h = 0;
  while (l--)
    h = stephash(h, *str++ - 'a');
  return h;
}
vecp table[maxlen + 1];

int insert(ull hash){
  int pos = hash % tablesize;
  for (int i = 0; i < table[pos].sz; ++i)
    if (table[pos].ptr[i].first == hash)
      return ++table[pos].ptr[i].second;
  table[pos].ptr = pushbackP(table[pos].ptr, &table[pos].sz, newPair(hash, 1));
  return 1;
}
bool possible(int len, int*best){
  if (len > n)
    return false;
  tablesize = max((n - len + 1) / 2, 100);
  for (int i = 0; i < tablesize; ++i)
    table[i].sz=0;
  ull add[26];
  ull pot32 = 1;
  for (int i = 0; i < len - 1; ++i)
    pot32 = (pot32 << 5) % mod;
  for (int i = 0; i < 26; ++i) {
    add[i] = (pot32 * i) % mod;
    add[i] = (mod - add[i]) % mod;
  }
  ull hash = hashfunc(str, len - 1);
  int bestindex = -1;
  for (int i = 0; i + len <= n; ++i) {
    if (i)
      hash = (hash + add[str[i - 1] - 'a']) % mod;
    hash = stephash(hash, str[i + len - 1] - 'a');
    int times = insert(hash);
    if (times >= mintimes)
      bestindex = i;
  }
 *best = bestindex;
  return bestindex >= 0;
}
int main() {
  while (scanf("%i\n", &mintimes), mintimes){
    gets(str);
    n = strlen(str);
    int best;
    if (!possible(1, &best))
      puts("none");
    else {
      int a = 1, b = n + 1;
      while (b - a != 1) {
        int m = (a + b) / 2;
        if (possible(m, &best))
          a = m;
        else
          b = m;
      }
      possible(a, &best); 
      printf("%i %i\n", a, best);
    }
  }
  return 0;
}
