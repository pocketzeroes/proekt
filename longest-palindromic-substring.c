#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

int expandAroundCenter(char*,int,int);

char * substr(const char *str, int start, int end) {
  if (0 > start)     return NULL;
  int len = strlen(str);
  if (-1 == end) end = len;
  if (end <= start)  return NULL;
  int diff = end - start;
  if (len == diff)   return strdup(str);
  if (len < start)   return NULL;
  if (len + 1 < end) return NULL;
  char *res = malloc(sizeof(char) * diff + 1);
  if (NULL == res)   return NULL;
  memset(res, '\0', diff + 1);
  strncpy(res, str + start, diff);
  return res;
}

char* longestPalindrome(char*s){
    int iLen=strlen(s);
    if (iLen==1)
        return s;
    int start = 0, end = 0;
    for (int i = 0; i < iLen; i++) {
        int len1 = expandAroundCenter(s, i, i);
        int len2 = expandAroundCenter(s, i, i + 1);
        int len  = MAX(len1, len2);
        if (len > end - start) {
            start = i - (len - 1) / 2;
            end   = i + len / 2;
        }
    }
    return substr(s, start, end + 1);
}

int expandAroundCenter(char*s, int left, int right){
    int L = left, R = right;
    while (L >= 0 && s[R] && s[L] == s[R] ){
        L--;
        R++;
    }
    return R - L - 1;
}

int main(int argc, char**argv){
#if 0
    puts(longestPalindrome("babad")); // expected : "bab"  or "aba"
    puts(longestPalindrome("cbbd") ); // expected : "bb"
#endif
    return 0;
}



