#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}


int W, H, N, L = 10;
char**words;
char**G;
bool**V;

bool**newmat(int x, int y){
  bool**rv = calloc(x, sizeof(bool*));
  for(int i=0; i<x; i++)
    rv[i] = calloc(y, sizeof(bool));
  return rv;
}

typedef struct trie{
    bool present;
    struct trie*next;
}trie;
trie root;

bool inbounds(int y, int x){
    return y > -1 && y < H && x > -1 && x < W;
}
void buildfs(int i, int j, int depth, trie*p){
    if(depth > L)
        return;
    V[i][j] = true;
#define c G[i][j]
    int ni[4] = {i+1, i-1, i, i};
    int nj[4] = {j, j, j+1, j-1};
    p = &(p->next[c - 'A']);
    if(!p->present){
        p->present = true;
        p->next=calloc(26, sizeof(trie));
    }
    for(int k=0; k<4; k++){
        if(inbounds(ni[k], nj[k]) && !V[ni[k]][nj[k]])
            buildfs(ni[k], nj[k], depth + 1, p);
    }
    V[i][j] = false;
    #undef c
}
int main(){
    scanf("%d %d", &H, &W);
    G = calloc(H, sizeof(char*));
    V=newmat(H, W);//of bool
    root.present = true;
    root.next = calloc(26, sizeof(trie));
    for(int i=0; i<H; i++)
        G[i]=getstr();
    scanf("%d", &N);
    words = calloc(N, sizeof(char*));
    for(int i=0; i<N; i++)
        words[i]=getstr();
    for(int i=0; i<H; i++)
        for(int j=0; j<W; j++)
            buildfs(i, j, 1, &root);
    int count = 0;
    for(int z=0;z<N;z++){char*s = words[z];
        bool e = true;
        trie*p = &root;
        for(int q=0;s[q];q++){char c=s[q];
            if(!p->next[c - 'A'].present){
                e = false;
                break;
            }
            p = &(p->next[c - 'A']);
        }
        if(e)
            count++;
    }
    printf("%d\n", count);
    return 0;
}
