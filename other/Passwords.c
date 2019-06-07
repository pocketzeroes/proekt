#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

enum{ MAX_PWD_SIZE  =  22};
enum{ MAX_WORD_SIZE =  22};
enum{ MAX_WORDS     =  52};
enum{ NUM_LETTERS   =  26};
enum{ NUM_LEET      =   5};
enum{ MIN_REQ       =   8};
enum{ MAX_NODES     = (MAX_PWD_SIZE * MAX_WORDS + 1)};
enum{ MOD           = 1000003};

typedef struct node{
  struct node*child[NUM_LETTERS];
  struct node*next [NUM_LETTERS];
  bool word;
  int  pos;
}*Trie;

int a, b, n, num_nodes;
char dic[MAX_WORDS][MAX_WORD_SIZE];
Trie black_list, node[MAX_NODES];
int  dp  [MAX_PWD_SIZE][MIN_REQ][MAX_NODES];
bool calc[MAX_PWD_SIZE][MIN_REQ][MAX_NODES];
int  leet[NUM_LEET] = {'o','i','e','s','t'};

int next(int i){
  if (i<52)
    return i%NUM_LETTERS;
  if (i<=56)
    return leet[i-52]-'a';
  return 0;
}
int type(int i){
  if (i<26)
    return 1;
  if (i<52)
    return 2;
  return 4;
}
int go(int pos, int mr, int s){
  if (!calc[pos][mr][s]){
    calc[pos][mr][s] = true;
    if (pos>b || node[s]->word)
      return 0;
    if (pos>=a && pos <=b && mr==7)
      dp[pos][mr][s]=1;
    for (int i=0; i<=56; i++){
      dp[pos][mr][s] = (dp[pos][mr][s] + go(pos+1, mr|type(i), node[s]->next[next(i)]->pos)) % MOD;
    }
    dp[pos][mr][s] = (dp[pos][mr][s] + 5*go(pos+1, mr|4, 0)) % MOD;
  }
  return dp[pos][mr][s];
}
Trie mkNode(){
  Trie aux = (Trie)malloc(sizeof(struct node));
  for (int i=0; i<NUM_LETTERS; i++)
    aux->child[i] = NULL;
  aux->word = false;
  aux->pos  = num_nodes;
  node[num_nodes++] = aux;
  return aux;
}
void insert(Trie t, char *s){
  if (s[0] == 0)
    t->word = true;
  else{
    int pos = s[0]-'a';
    if (t->child[pos] == NULL)
      t->child[pos] = mkNode();
    insert(t->child[pos], s+1);
  }  
}
Trie exists(Trie t, char *s){
  if (t==NULL)
    return NULL;
  if (s[0] == 0)
    return t;
  int pos = s[0]-'a';
  return exists(t->child[pos], s+1);
}
void makeFailLinks(Trie t, char *s, int len){
  s[len+1] = 0;
  for (int i=0; i<NUM_LETTERS; i++){
    s[len] = i+'a';
    Trie aux = NULL;
    for (int j=0; j<=len+1; j++)      
      if ( (aux = exists(black_list, &s[j])) )
        break;
    t->next[i] = aux;
  }
  for (int i=0; i<NUM_LETTERS; i++){
    if (t->child[i] != NULL){
      s[len] = i+'a'; 
      makeFailLinks(t->child[i], s, len+1);
    }
  }
}
bool hasSubstring(int i){
  for (int j=0; j<n; j++)
    if (i!=j && strstr(dic[i], dic[j]))
      return true;
  return false;
}
int main(){
  num_nodes = 0;
  black_list = mkNode();
  scanf("%d %d %d", &a, &b, &n);
  for (int i=0; i<n; i++)
    scanf("%s", dic[i]);
  for (int i=0; i<n; i++)
    if (!hasSubstring(i))
      insert(black_list, dic[i]);
  char buf[MAX_WORD_SIZE];    
  makeFailLinks(black_list, buf, 0);
  printf("%d\n", go(0,0,0));
  return 0;
}
