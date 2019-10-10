#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define int long long
typedef long long ll;

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

enum{ MAXN =(int)1e5+10};
char*s;
int  slen;
int N, gap;
int sa[MAXN], pos[MAXN], lcp[MAXN], tmp[MAXN];


bool sufCmp(int i, int j){
    if(pos[i] != pos[j])
        return pos[i] < pos[j];
    i += gap;
    j += gap;
    return (i < N && j < N) ? pos[i] < pos[j] : i > j;
}
signed sfCmp(const void*pa, const void*pb){
    int*a=(int*)pa;
    int*b=(int*)pb;
    return sufCmp(*a, *b)?-1:1;
}
void buildSA(){
    N = slen;
    for(int i = 0; i < N; ++i){
        sa[i] = i;
        pos[i] = s[i];
    }
    for(gap = 1;; gap *= 2){
//        sort(sa, sa + N, sufCmp);
        qsort(sa, N, sizeof(int), sfCmp);
        for(int i = 0; i < N-1; ++i)
            tmp[i+1] = tmp[i] + sufCmp(sa[i], sa[i+1]);
        for(int i = 0; i < N; ++i)
            pos[sa[i]] = tmp[i];
        if(tmp[N-1] == N-1)
            break;
    }
}
void buildLCP(){
    N = slen;
    for(int i = 0, k = 0; i < N; ++i){
        if(pos[i] != 0 ){
            for(int j = sa[pos[i]-1]; s[i+k] == s[j+k];)
                k++;
            lcp[pos[i]] = k;
            if(k)
               k--;
        }
    }
}
signed main(){
    s=getstr();
    slen=strlen(s);
    buildSA();
    buildLCP();
    int bestval = -1;
    int bestidx = -1;
    for(int i = 0; i < slen; i++){
        if(lcp[i] > bestval){
            bestval = lcp[i];
            bestidx = sa [i];
        }
    }
    for(int i = 0; i < bestval; i++){
        putchar(s[bestidx+i]);
    }
    puts("");
}
