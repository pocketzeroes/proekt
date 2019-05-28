#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef struct trie{
  struct trie*next[26];
  int  aut_len;
  char aut_sym;
}trie;

trie*newtrie(){
  trie*rez = calloc(1, sizeof(trie));
  rez->aut_len = -1;
  return rez;
}
trie*get_next(trie*t, char c){
  return t->next[c-'a'] ? t->next[c-'a'] : NULL;
}
void add(trie*t, const char *s){
  if(*s){
    if(!t->next[*s-'a'])
      t->next[*s-'a'] = newtrie();
    add(t->next[*s-'a'], s+1);
  }
  if(t->aut_len == -1){
    t->aut_len = *s ? t->next[*s-'a']->aut_len + 1 : 0;
    t->aut_sym = *s;     
  }
}
  
char  buf[1<<24];
trie *seq[1<<24];
int   opt[1<<24];

int solve(const char *word, trie *t){
  int L = 0;
  for(;word[L] && t; seq[L] = t, t = get_next(t, word[L++]));
  opt[L] = strlen(word)-L;
  for (int i = L-1, nxtb = L; i >= 0; --i) {
    opt[i] = 1 + opt[i+1];
    if (!i || seq[i]->aut_sym != word[i])
      nxtb = i;
    else
      opt[i] = min(opt[i], 1 + seq[i]->aut_len - (nxtb-i) + opt[nxtb]);
  }
  return opt[0];
}
int main(){
  int n, m;
  trie*t = newtrie();
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i){
    scanf("%s", buf);
    add(t, buf);
  }
  for (int i = 0; i < m; ++i){
    scanf("%s", buf);
    printf("%d\n", solve(buf, t));
  }
  return 0;
}
