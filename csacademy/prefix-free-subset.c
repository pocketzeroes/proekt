#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int cmpstr(const void*p1, const void*p2)
{
  return strcmp(*(char* const*) p1, *(char* const*) p2);
}

enum{ MAX_N = 100000}; 
enum{ INDEX = 1     };
int n, k;
char* words[MAX_N + INDEX];


bool isPrefix(char*a,char*b){
    if(strlen(a) > strlen(b)){
        return false;
    }
    for (int i = 0; i < strlen(a); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}
bool isGood(int l){
    int lastInd = 0, cnt = 0;
    for (int i = 1; i <= n; i++) {
        if(strlen(words[i]) <= l) {
            if (!isPrefix(words[lastInd], words[i])) {
                cnt++;
            }
            lastInd = i;
        }
    }
    return cnt >= k;
}
char buff[100000];
int main() {
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i++) {
        scanf("%s", &buff);
        words[i]=strdup(buff);
    }
    qsort(words+INDEX, n,sizeof(char*), cmpstr);
    words[0] = strdup("#csacademy");
    int l = 1, r = 0;
    for (int i = 1; i <= n; i++) {
        r = max(r, strlen(words[i]));
    }
    while (r > l) {
        int m = (l + r) / 2;
        if (isGood(m)) 
            r = m;
        else 
            l = m + 1;
    }
    int ans = (l + r) / 2;
    if (isGood(ans)) 
        printf("%d\n", ans);
    else 
        puts("-1");
    return 0;
}





















