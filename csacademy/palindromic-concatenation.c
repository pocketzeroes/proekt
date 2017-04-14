#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}


enum{ N = 100002};
enum{ nmax  =(int) 1e5+5};
enum{ sigma = 26};
int trie[nmax][sigma];
int cnt[nmax];
int d[2*nmax];
int trieStates = 0;
int n;
char*s[N];int sLen=0;
char*r[N];int rLen=0;


void inplace_reverse(char * str)
{
  if (str)
  {
    char * end = str + strlen(str) - 1;
#   define XOR_SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
    while (str < end)
    {
      XOR_SWAP(*str, *end);
      str++;
      end--;
    }
#   undef XOR_SWAP
  }
}

bool check_palindrome(int x, int y) {
  if (x == y) return true;
  int c = x + y - 1;
  return d[c] >= y - x;
}
void build_manacher(char*s){
  char get_at(int x){
    if (x % 2 == 1){
      return '#';
    }
    return s[x / 2];
  }
  int l, r, c;
  l = r = c = -1;
  int sz = 2 * strlen(s) - 1;
  for (int i = 0; i < sz; i++) {
    if (i <= r) {
      int j = 2 * c - i;
      d[i] = min(d[j], j - l);
    } 
    else {
      d[i] = 0;
    }
    while (i + d[i] < sz && i - d[i] >= 0) {
      if (get_at(i + d[i]) != get_at(i - d[i]))
        break;
      d[i]++;
    }
    if (i + d[i] > r) {
      r = i + d[i];
      l = i - d[i];
      c = i;
    }
  }
}
void trie_add(char*s){
  int sz = strlen(s);
  int crt = 0;
  for (int j = 0; j < sz; j++) {
    int transition = s[j] - 'a';
    if (!trie[crt][transition])
      trie[crt][transition] = ++trieStates;
    crt = trie[crt][transition];
  }
  cnt[crt]++;
}
long long trie_and_mana(bool flip, int offset){
  char**a;int aSz;
  char**b;int bSz;
  if(!flip){
    a=s;aSz=sLen;
    b=r;bSz=rLen;
  }
  else{
    a=r;aSz=rLen;
    b=s;bSz=sLen;
  }
  memset(trie, 0, sizeof(int) * sigma * trieStates);
  memset(cnt,  0, sizeof(int) *         trieStates);
  trieStates = 0;
  long long ans = 0;
  for(int i=0;i<aSz;i++){ char*ss = a[i];
    trie_add(ss);
  }
  for(int i=0;i<bSz;i++){ char*ss = b[i];
    build_manacher(ss);
    int crt = 0, sz = strlen(ss);
    for (int j = 0; j < sz + offset; j++) {
      int transition = ss[j] - 'a';
      int nxt = trie[crt][transition];
      if (!nxt) 
        break;
      crt = nxt;
      if (check_palindrome(j + 1, sz))
        ans += cnt[crt];
    }
  }
  return ans;
}
#define MAX_STR_SZ 200000
char p[MAX_STR_SZ];
int main(){
  scanf("%d", &n);
  int cnt_pals = 0;
  for (int i = 1; i <= n; i++){
    scanf("%s", &p);
    s[sLen++]=strdup(p);
    inplace_reverse(p);
    r[rLen++]=strdup(p);
    if(strcmp(s[sLen-1] , r[rLen-1]) == 0)
      cnt_pals++;
  }
  long long ans = 0;
  ans += trie_and_mana(0,  0);
  ans += trie_and_mana(1, -1);
  ans -= cnt_pals;
  printf("%lld\n", ans);
  return 0;
}



























