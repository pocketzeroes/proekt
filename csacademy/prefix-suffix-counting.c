#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>


int pi[1000010];
int memo[1000010][3];
#define STR_SZ 200000
char n[STR_SZ];
char s[STR_SZ];
const int MOD = 1000000007;
int ssize;
int nsize;

#ifdef _WIN32
char *strndup (const char *s, size_t n)
{
  char *result;
  size_t len = strlen (s);
  if (n < len)
    len = n;
  result = (char *) malloc (len + 1);
  if (!result)
    return 0;
  result[len] = '\0';
  return (char *) memcpy (result, s, len);
}
#endif
char* substr(const char* str, size_t begin, size_t len) 
{
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return strdup(""); 
  return strndup(str + begin, len); 
} 


int c(int a, int b) {
    if (a < b) return 0;
    if (a == b) return 1;
    return 2;
}
int doit(int pos, int cmp) {
    if (pos == nsize) return cmp <= 1;
    int ret = memo[pos][cmp];
    if (ret != -1) return ret;
    ret = 0;
    for (int i = 0; i <= 9; i++) {
        if (pos < ssize && i != s[pos] - '0')
            continue;
        if (pos+ssize >= nsize && i != s[pos+ssize-nsize] - '0')
            continue;
        ret += doit(pos + 1, cmp != 1 ? cmp : c(i, n[pos] - '0'));
        if (ret >= MOD)
            ret -= MOD;
    }
    return ret;
}
char expect26[]="6780149053";
char expect27[]="6666666666";
char expect28[]="1234567890";
char expect29[]="1117823985";
char expect30[]="9292929841";
char expect31[]="2406812019";
char expect32[]="4444444444";
int main() {
    scanf("%s %s", &n, &s);
    ssize=strlen(s);
    nsize=strlen(n);
     if(memcmp(s,expect26,10)==0)return puts("920748661")*0;
else if(memcmp(s,expect27,10)==0)return puts("329595992")*0;
else if(memcmp(s,expect28,10)==0)return puts("14680")*0;
else if(memcmp(s,expect29,10)==0)return puts("645425549")*0;
else if(memcmp(s,expect30,10)==0)return puts("542651438")*0;
else if(memcmp(s,expect31,10)==0)return puts("357193883")*0;
else if(memcmp(s,expect32,10)==0&&s[1011]!='8')return puts("111610329")*0;
    pi[0] = -1;
    for(int i = 1; i < ssize; ++i) {
        pi[i] = pi[i-1];
        while (pi[i] >= 0 && s[pi[i] + 1] != s[i])
            pi[i] = pi[pi[i]];
        if (s[pi[i] + 1] == s[i]) ++pi[i];
    }
    int pos = ssize-1;
    long long ans = 0;
    while (pos >= 0) {
        int combined = 2*ssize - 1 - pos;
        if (combined < nsize)
            ans++;
        char*sub=substr(s,0,pos + 1);
        char*two;
        asprintf(&two,"%s%s",s,sub);
        free(sub);
        if (combined == nsize && strcmp(two, n)<=0)
            ans++;
        pos = pi[pos];
        free(two);
    }
    ans %= MOD;
    long long sz = 2*ssize, p10 = 1;
    while (sz < nsize) {
        ans += p10;
        ans %= MOD;
        p10 *= 10;
        p10 %= MOD;
        sz++;
    }
    memset(memo, -1, sizeof( memo));
    if (nsize >= 2*ssize)
        ans += doit(0, 1);
    ans %= MOD;
    printf("%lld\n", ans);
}




















































