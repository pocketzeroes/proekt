#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
#define pb(zpv, zvv) zpv.ptr = pushbackS(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
char**pushbackS(char**array, int *size, char*value) {
  char**output = resizeArray(array, char*, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  char**ptr;
  int sz;
}vecs;
vecs newVecS(){
  vecs rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
//////////////////////////
int  numWords,
     numBoggles;
char*boggle[4];
bool vis[4][4];
vecs found;
int dx[] = { 0, 0,-1,-1,-1,+1,+1,+1};
int dy[] = {-1,+1,-1, 0,+1,-1, 0,+1};
int toScore[] = {0, 0, 0, 1, 1, 2, 3, 5, 11, 11, 11, 11, 11, 11, 11, 11, 11};

typedef struct{
    bool valid;
    int  edges[26];
    int  last;
}trie;
enum{ MAX_TRIE = (5+8*300000)};
trie tries[MAX_TRIE];
int  edgeCnt;
int  kase;

int init(){
    int id = edgeCnt;
    tries[id].valid = false;
    for(int i = 0; i < 26; i++)
        tries[id].edges[i] = -1;
    edgeCnt++;
    assert(edgeCnt < MAX_TRIE);
    return id;
}
void add(int id, char*w, int idx){
    if(idx >= strlen(w)){
        tries[id].valid = true;
        return;
    }
    int letter = (int) (w[idx] - 'A');
    if (tries[id].edges[letter] == -1)
        tries[id].edges[letter] = init();
    add(tries[id].edges[letter], w, idx + 1);
}
void rec(int i, int j, char*cur, int id){
    if(i < 0 || j < 0 || i >= 4 || j >= 4)
        return;
    if(vis[i][j])
        return;
    if(strlen(cur) >= 8){
        free(cur);
        cur=NULL;
        return;
    }
    vis[i][j] = true;
    cur = concatc(cur, boggle[i][j]);
    int letter = (int) (boggle[i][j] - 'A');
    int next = tries[id].edges[letter];
    if(next == -1){
        vis[i][j] = false;
        return;
    }
    if(tries[next].valid && tries[next].last < kase) {
        tries[next].last = kase;
        pb(found, strdup(cur));
    }
    for(int c = 0; c < 8; c++)
        rec(i + dx[c], j + dy[c], cur, next);
    vis[i][j] = false;
}
int main(){
    edgeCnt = 0;
    int root = init();
    scanf("%d", &numWords);
    for(int i=0; i<numWords; i++){
        char*t=getstr();
        add(root, t, 0);
    }
    scanf("%d", &numBoggles);
    for(int i=0; i<numBoggles; i++){
        kase = i + 1;
        for(int j=0; j<4; j++)
            boggle[j] = getstr();
        found.sz=0;
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                rec(j, k, strdup(""), root);
        char*best = strdup(found.ptr[0]);
        int score = 0;
        for(int z=0; z<found.sz; z++){char*iter = found.ptr[z];
            int best_len=strlen(best);
            int iter_len=strlen(iter);
            if(best_len < iter_len || best_len == iter_len && strcmp(iter, best)<0)
                best = strdup(iter);
            score += toScore[iter_len];
        }
        printf("%d %s %d\n", score, best, found.sz);
    }
    return 0;
}
