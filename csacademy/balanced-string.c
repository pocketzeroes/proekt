#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

enum{ inf =(int) 1e9};


#define BUFFLEN 100000

int solve(char*s){
    int ssize=strlen(s);
    if(ssize == 1) return 1;
    int n = ssize;
    bool alt = true;
    for (int i = 0; i < n; ++i) {
        if (s[i] == s[(i + 1) % n]) {
            alt = false;
            break;
        }
    }
    if (alt) return 1;
    bool aa = false, bb = false;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'A' && s[(i + 1) % n] == 'A') aa = true;
        if (s[i] == 'B' && s[(i + 1) % n] == 'B') bb = true;
    }
    if (aa && bb) return 0;
    if (bb) {
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'A') s[i] = 'B';
            else s[i] = 'A';
        }
    }
    int*cnt=NULL;int cntSz=0;
    cnt=pushback(cnt,&cntSz,0);
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'A') ++cnt[cntSz-1];
        else if(cnt[cntSz-1]) cnt=pushback(cnt,&cntSz,0);
    }
    if (!cnt[cntSz-1])cntSz--;
    if (s[0] == 'A' && s[n - 1] == 'A' && cntSz > 1){
        cnt[0] += cnt[cntSz-1];
        cntSz--;
    }
    int maxx = -inf, minn = inf;
    for (int i = 0; i < cntSz; ++i) {
        maxx = max(maxx, cnt[i]);
        minn = min(minn, cnt[i]);
    }
    if (maxx - minn > 1) return 0;
    char t[cntSz+1];
    int  tLen=0;
    for (int i = 0; i < cntSz; ++i) {
        if (cnt[i] == maxx) t[tLen++] = 'A';
        else                t[tLen++] = 'B';
    }
    t[tLen]='\0';
    return solve(t);
}
int main(){
    int tt;
    scanf("%d", &tt);
    while (tt--) {
        char s[BUFFLEN];
        scanf("%s", &s);
        int rez = solve(s);
        printf("%d\n", rez);
    }
}








































