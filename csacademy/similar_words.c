#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

#define MAX_SIZE 200000

typedef long long int64;
inline int min(int64 a,int64 b){return a<b?a:b;}
inline int max(int64 a,int64 b){return a>b?a:b;}

int Wsize;
int Ssize;

int lcp(char* W, char* S){
    int result = 0;
    for (int itr = 0; itr < min(Wsize, Ssize) && W[itr] == S[itr]; itr ++)
        result ++;
    return result;
}
int lcs(char* W, char* S){
    int result = 0;
    for (int itr = 1; itr <= min(Wsize, Ssize) && W[Wsize - itr] == S[Ssize - itr]; itr ++)
        result ++;
    return result;
}
bool addOne(char* W, char* S){
    if (lcp(W, S) + lcs(W, S) >= Wsize)
        return true;
    else
        return false;
}
bool canChangeOne(char* W, char* S){
    if (strcmp(W , S)==0)
        return true;
    if (lcp(W, S) + lcs(W, S) == Wsize - 1)
        return true;
    else 
        return false;
}
bool deleteOne(char* W, char* S){
    if (lcp(W, S) + lcs(W, S) >= Wsize - 1)
        return true;
    else 
        return false;
}
char S[MAX_SIZE];
char W[MAX_SIZE];
int main() {
    memset(S,0,sizeof(S));
    memset(W,0,sizeof(W));
    int N;
    scanf("%d", &N);
    scanf("%s", &S);
    int result = 0;
    Ssize=strlen(S);
    for (int i = 0; i < N; i++){
        scanf("%s", &W);
        Wsize=strlen(W);
        if      (Wsize     == Ssize    ) result += canChangeOne(W, S);
        else if (Wsize     == Ssize + 1) result += deleteOne   (W, S);
        else if (Wsize + 1 == Ssize    ) result += addOne      (W, S);
        memset(W,0,sizeof(W));
    }
    printf("%d", result);
    return 0;
}




















